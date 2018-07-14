#ifndef EDGE_REQUEST_LIST
#define EDGE_REQUEST_LIST

#include "EdgeRequest.hpp"
#include "Null.hpp"
#include "Util.hpp"
#include <atomic>
#include <zmq.hpp>
#include <boost/lexical_cast.hpp>

namespace sam {

class EdgeRequestMapException : public std::runtime_error {
public:
  EdgeRequestMapException(char const * message) : 
    std::runtime_error(message) { }
  EdgeRequestMapException(std::string message) : 
    std::runtime_error(message) { }
};

/**
 * This class has a list of edge requests that have been made of a node.
 * We store them in a hash table where each entry in the hash table has a 
 * mutex lock.  Each entry is a list of edge requests that hash to the
 * same location.
 *
 * When process(tuple) is called, we find if there are any matching edge 
 * requests.  If so, we send the tuple to the appropriate node(s).
 */
template <typename TupleType, size_t source, size_t target, size_t time,
          typename SourceHF, typename TargetHF,
          typename SourceEF, typename TargetEF>
class EdgeRequestMap
{
public:
  typedef EdgeRequest<TupleType, source, target> EdgeRequestType;
  typedef typename std::tuple_element<source, TupleType>::type SourceType;
  typedef typename std::tuple_element<target, TupleType>::type TargetType;

private:
  SourceHF sourceHash;
  TargetHF targetHash;
  SourceEF sourceEquals;
  TargetEF targetEquals;

  size_t numNodes;
  size_t nodeId;

  /// The size of the hash table storing the edge requests.
  size_t tableCapacity;

  /// An array of lists of edge requests
  std::list<EdgeRequestType> *ale;

  /// mutexes for each array element of ale.
  std::mutex* mutexes;

  /// Keeps track of how many edges we send
  std::atomic<size_t> edgePushCounter;

  zmq::context_t& context;// = zmq::context_t(1);

  /// This has all the push sockets that we use to send edges to other nodes.
  std::vector<std::shared_ptr<zmq::socket_t>> pushers;

  // Comes from GraphStore
  std::mutex& terminationLock;

  std::function<size_t(TupleType const&)> sourceIndexFunction;
  std::function<bool(EdgeRequestType const&, TupleType const&)> 
    sourceCheckFunction;
  std::function<size_t(TupleType const&)> targetIndexFunction;
  std::function<bool(EdgeRequestType const&, TupleType const&)> 
    targetCheckFunction;
  std::function<size_t(TupleType const&)> sourceTargetIndexFunction;
  std::function<bool(EdgeRequestType const&, TupleType const&)> 
    sourceTargetCheckFunction;

  std::atomic<size_t> pushFails; ///> How many pushes fail

public:
  /**
   * Constructor.  
   * \param pushers Must pass in the pushers, which is what we use to 
   *  send edges to other nodes.
   * \param tableCapacity The size of the hash table.
   */
   EdgeRequestMap(
                  zmq::context_t& _context,
                  std::size_t numNodes,
                  std::size_t nodeId,
                  std::vector<std::string> edgeHostnames,
                  std::vector<std::size_t> edgePorts,
                  uint32_t hwm,
                  size_t tableCapacity,
                  std::vector<std::shared_ptr<zmq::socket_t>> edgePushers,
                  std::mutex& terminationLock);

  /**
   * Destructor.
   */
  ~EdgeRequestMap();

  /**
   * Add a request to the list.  This is called by the requestPullThread of
   * the GraphStore class.  
   */
  void addRequest(EdgeRequestType request);

  /**
   * Given the tuple, finds if there are any open edge requests that are 
   * satisfied with the given tuple. If so, sends them on to the appropriate
   * node using the push sockets. 
   * \return Returns a number representing the amount of work done.
   */
  size_t process(TupleType const& tuple);


  /**
   * Returns how many edges we've sent
   */
  size_t getTotalEdgePushes() { return edgePushCounter; }

  /**
   * Iterates through the edge push sockets and sends a terminate
   * signal.
   */
  void terminate();

  /**
   * Returns how many send() calls to the push sockets failed.
   */
  size_t getPushFails() { return pushFails.load(); }


private:

  size_t process(TupleType const& tuple,
        std::function<size_t(TupleType const&)> indexFunction,
        std::function<bool(EdgeRequestType const&, TupleType const&)> 
          checkFunction);


  #ifdef DETAIL_TIMING
  double totalTimePush = 0;
  #endif

  std::atomic<bool> terminated;
};

// Constructor 
template <typename TupleType, size_t source, size_t target, size_t time,
          typename SourceHF, typename TargetHF,
          typename SourceEF, typename TargetEF>
EdgeRequestMap<TupleType, source, target, time,
  SourceHF, TargetHF, SourceEF, TargetEF>::
EdgeRequestMap( 
                zmq::context_t& _context,
                std::size_t numNodes,
                std::size_t nodeId,
                std::vector<std::string> hostnames,
                std::vector<std::size_t> ports,
                uint32_t hwm,
                size_t tableCapacity,
                std::vector<std::shared_ptr<zmq::socket_t>> edgePushers,
                std::mutex& _terminationLock)
: context(_context), terminationLock(_terminationLock)
{

  pushFails = 0;

  sourceIndexFunction = [this](TupleType const& tuple) {
    SourceType src = std::get<source>(tuple);
    return sourceHash(src) % this->tableCapacity;
  };

  targetIndexFunction = [this](TupleType const& tuple) {
    TargetType trg = std::get<target>(tuple);
    return targetHash(trg) % this->tableCapacity;
  };
  
  sourceTargetIndexFunction = [this](TupleType const& tuple) {
    SourceType src = std::get<source>(tuple);
    TargetType trg = std::get<target>(tuple);
    return (sourceHash(src) * targetHash(trg)) % this->tableCapacity;
  };

  sourceCheckFunction = [this](EdgeRequestType const& edgeRequest,
                               TupleType const& tuple) 
  {
    SourceType src = std::get<source>(tuple);
    TargetType trg = std::get<target>(tuple);
    SourceType edgeRequestSrc = edgeRequest.getSource();
    if (this->sourceEquals(src, edgeRequestSrc)) {
      
      size_t node = edgeRequest.getReturn();
      // TODO: Partition info
      if (this->targetHash(trg) % this->numNodes != node) {
        return true;
      }
    }
    return false;
  };

  targetCheckFunction = [this](EdgeRequestType const& edgeRequest,
                               TupleType const& tuple) 
  {
    SourceType src = std::get<source>(tuple);
    TargetType trg = std::get<target>(tuple);
    TargetType edgeRequestTrg = edgeRequest.getTarget();
    DEBUG_PRINT("Node %lu EdgeRequestMap::targetCheckFunction trg %s "
      "edgeRequestTrg %s\n", this->nodeId, trg.c_str(), edgeRequestTrg.c_str());
    if (this->targetEquals(trg, edgeRequestTrg)) {
      
      size_t node = edgeRequest.getReturn();
      DEBUG_PRINT("Node %lu EdgeRequestMap::targetCheckFunction "
        "sourceHash(src) mod numNodes  %llu node %lu\n", 
        this->nodeId, sourceHash(src) % this->numNodes, node);
      // TODO: Partition info
      if (this->sourceHash(src) % this->numNodes != node) {
        DEBUG_PRINT("Node %lu targetCheckFunction returning true\n",
          this->nodeId);
        return true;
      }
    }
    return false;
  };

  sourceTargetCheckFunction = [this](EdgeRequestType const& edgeRequest,
                                     TupleType const& tuple)
  {
    SourceType src = std::get<source>(tuple);
    TargetType trg = std::get<target>(tuple);
    TargetType edgeRequestTrg = edgeRequest.getTarget();
    SourceType edgeRequestSrc = edgeRequest.getSource();
    if (targetEquals(trg, edgeRequestTrg) &&
        sourceEquals(src, edgeRequestSrc)) 
    {
      size_t node = edgeRequest.getReturn();

      // TODO: Partition info
      if (sourceHash(src) % this->numNodes != node &&
          targetHash(trg) % this->numNodes != node)
      {
        return true;
      }
    }
    return false;
  };

 
  terminated = false;
  this->numNodes = numNodes;
  this->nodeId = nodeId;
  pushers = edgePushers;
  //createPushSockets(&context, numNodes, nodeId, hostnames, ports,
  //                  this->pushers, hwm);
  this->tableCapacity = tableCapacity;
  mutexes = new std::mutex[tableCapacity];
  ale = new std::list<EdgeRequestType>[tableCapacity];
  edgePushCounter = 0;
}

// Destructor 
template <typename TupleType, size_t source, size_t target, size_t time,
          typename SourceHF, typename TargetHF,
          typename SourceEF, typename TargetEF>
EdgeRequestMap<TupleType, source, target, time,
  SourceHF, TargetHF, SourceEF, TargetEF>::
~EdgeRequestMap()
{
  delete[] mutexes;
  delete[] ale;
  terminate();
  DEBUG_PRINT("Node %lu end of ~EdgeRequestMap\n", nodeId);
}



template <typename TupleType, size_t source, size_t target, size_t time,
          typename SourceHF, typename TargetHF,
          typename SourceEF, typename TargetEF>
void
EdgeRequestMap<TupleType, source, target, time,
  SourceHF, TargetHF, SourceEF, TargetEF>::
addRequest(EdgeRequestType request)
{
  SourceType src = request.getSource();
  TargetType trg = request.getTarget();

  size_t index;

  // TODO: Very similar to SubgraphQueryResult::hash.  Anyway to combine?
  if (isNull(src) && !isNull(trg))
  {
    index = targetHash(trg) % tableCapacity;
    //printf("hashing target %s index %lu edge request %s\n", 
    //trg.c_str(), index, request.toString().c_str());
  } else
  if (!isNull(src) && isNull(trg))
  {
    index = sourceHash(src) % tableCapacity;
  } else
  if (!isNull(src) && !isNull(trg))
  {
    index = (sourceHash(src) * targetHash(trg)) % tableCapacity;
  } else
  {
    throw EdgeRequestMapException("EdgeRequestMap::addRequest tried to"
      " add a request with no source or target");
  }

  mutexes[index].lock();
  ale[index].push_back(request);
  mutexes[index].unlock();

}

template <typename TupleType, size_t source, size_t target, size_t time,
          typename SourceHF, typename TargetHF,
          typename SourceEF, typename TargetEF>
size_t
EdgeRequestMap<TupleType, source, target, time,
  SourceHF, TargetHF, SourceEF, TargetEF>::
process(TupleType const& tuple)
{
  DEBUG_PRINT("Node %lu EdgeRequestMap::process(tuple) tuple: %s\n", nodeId,
    toString(tuple).c_str());
 
  size_t totalWork = 0; 
  totalWork += process(tuple, sourceIndexFunction, sourceCheckFunction);
  totalWork += process(tuple, targetIndexFunction, targetCheckFunction);
  totalWork += process(tuple, sourceTargetIndexFunction, 
                       sourceTargetCheckFunction);
  return totalWork;
}


template <typename TupleType, size_t source, size_t target, size_t time,
          typename SourceHF, typename TargetHF,
          typename SourceEF, typename TargetEF>
size_t
EdgeRequestMap<TupleType, source, target, time,
  SourceHF, TargetHF, SourceEF, TargetEF>::
process(TupleType const& tuple,
        std::function<size_t(TupleType const&)> indexFunction,
        std::function<bool(EdgeRequestType const&, TupleType const&)> 
          checkFunction)
{
  size_t index = indexFunction(tuple);

  double currentTime = std::get<time>(tuple);

  mutexes[index].lock();
  size_t count = 0;
  DEBUG_PRINT("Node %lu EdgeRequestMap::process number of requests to look at %lu "
    " processing tuple %s\n", nodeId, ale[index].size(), toString(tuple).c_str());
  for(auto edgeRequest = ale[index].begin();
        edgeRequest != ale[index].end();)
  {
    DEBUG_PRINT("Node %lu EdgeRequestMap::process looking at edgeRequest %s "
      " processing tuple %s\n", 
      nodeId, edgeRequest->toString().c_str(), toString(tuple).c_str());
    if (edgeRequest->isExpired(currentTime)) {
      DEBUG_PRINT("Node %lu EdgeRequestMap::process deleting old edgeRequest"
        " %s currentTime %f\n", nodeId, edgeRequest->toString().c_str(), 
        currentTime);
      edgeRequest = ale[index].erase(edgeRequest);
    } else {

      count++;
      if(checkFunction(*edgeRequest, tuple)) {
        size_t node = edgeRequest->getReturn();
        if (!terminated) {
          DETAIL_TIMING_BEG1
          zmq::message_t message = tupleToZmq(tuple);
          DETAIL_TIMING_END_TOL1(nodeId, totalTimePush, 0.001, 
            "EdgeRequestMap::process creating message exceeded tolerance")
          DEBUG_PRINT("Node %lu->%lu EdgeRequestMap::process sending"
            " edge %s\n", nodeId, node, toString(tuple).c_str());
          DETAIL_TIMING_BEG2
          terminationLock.lock();
          DETAIL_TIMING_END_TOL2(nodeId, totalTimePush, 0.001, 
            "EdgeRequestMap::process obtaining termination lock exceeded "
            "tolerance")
          if (!terminated) {
            DEBUG_PRINT("Node %lu->%lu EdgeRequestMap::process sending %s\n",
              nodeId, node, toString(tuple).c_str());
            DETAIL_TIMING_BEG2
            edgePushCounter.fetch_add(1);
            #ifdef NOBLOCK 
            bool sent = pushers[node]->send(message, ZMQ_NOBLOCK);  
            if (!sent) {
              pushFails.fetch_add(1);
              edgePushCounter.fetch_add(-1);
              DEBUG_PRINT("Node %lu->%lu EdgeRequestMap::process failed to "
                "send edge %s\n", nodeId, node, toString(tuple).c_str());
                
            }
            #elif defined NOBLOCK_WHILE
            bool sent = false;
            while(!sent) {
              sent = pushers[node]->send(message, ZMQ_NOBLOCK);
            }
            #else
            pushers[node]->send(message);
            #endif
            DETAIL_TIMING_END_TOL2(nodeId, totalTimePush, 0.001, 
              "EdgeRequestMap::process sending message exceeded "
              "tolerance")
          }
          terminationLock.unlock();
        }
      }
      ++edgeRequest;
    }
  }
  mutexes[index].unlock();
  return count;
  //return ale[index].size();
}

template <typename TupleType, size_t source, size_t target, size_t time,
          typename SourceHF, typename TargetHF,
          typename SourceEF, typename TargetEF>
void
EdgeRequestMap<TupleType, source, target, time,
  SourceHF, TargetHF, SourceEF, TargetEF>::
terminate()
{
  DEBUG_PRINT("Node %lu entering EdgeRequestMap::terminate\n", nodeId);
  if (!terminated) {
    for(size_t i = 0; i < this->numNodes; i++)
    {
      if (i != this->nodeId) { 

        DEBUG_PRINT("Node %lu EdgeRequestMap::terminate() sending terminate"
          " to %lu\n", nodeId, i); 
        
        try {
          pushers[i]->send(terminateZmqMessage());
        } catch (std::exception e) {
          std::string message = "Couldn't send termination message "
            + boost::lexical_cast<std::string>(nodeId) + "->" 
            + boost::lexical_cast<std::string>(i) + " because of "
            + e.what();
          throw EdgeRequestMapException(message);
        }
      }
    }
  }
  terminated = true;
  DEBUG_PRINT("Node %lu exiting EdgeRequestMap::terminate\n", nodeId);
}


} //End namespace sam

#endif
