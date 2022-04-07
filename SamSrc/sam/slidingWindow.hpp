#ifndef SLIDING_MAX_HPP
#define SLIDING_MAX_HPP

/**
 * Calculates the sum over a sliding window using Mayur Datar's work on 
 * exponential histograms.
 */

#include <iostream>
#include <map>

#include <sam/AbstractConsumer.hpp>
#include <sam/BaseComputation.hpp>
#include <sam/ExponentialHistogram.hpp>
#include <sam/Features.hpp>
#include <sam/Util.hpp>
#include <sam/FeatureProducer.hpp>
#include <sam/tuples/Edge.hpp>

namespace sam {

template <typename T, typename EdgeType, 
          size_t valueField, size_t... keyFields>
class Max: public AbstractConsumer<EdgeType>, 
                               public BaseComputation,
                               public FeatureProducer
{
private:

    T getMax(valueIn){
      
      output = std::max(valueIn);
      return output
    }

  // Determines number of buckets.  If there are k/2 + 2 buckets
  // of the same size (k + 2 buckets if the bucket size equals 1), 
  // the oldest two buckets are combined.
  size_t k; 

  // The size of the sliding window
  size_t N; 

  // A mapping from keyFields to the stream.
  std::map<std::string, std::vector> allWindows;

  // a mapping to keep track of location in stream
  std::map<std::string, int> streamLocation;

public:
  /**
   * Constructor.
   * \param N The number of elements in the sliding window.
   * \param k Determines the number of buckets.  If there are k/2 + 2 buckets
   *          of the same size (k + 2 buckets if bucket size equals 1),
   *          the oldest two buckets are combined. 
   * \param nodeId The nodeId of the node that is running this operator.
   * \param featureMap The global featureMap that holds the features produced
   *                   by this operator.
   * \param identifier A unique identifier associated with this operator.
   */
  Sum(size_t N, size_t k,
                          size_t nodeId,
                          std::shared_ptr<FeatureMap> featureMap,
                          std::string identifier) :
                          BaseComputation(nodeId, featureMap, identifier) 
                                          
  {
    this->N = N;
    this->k = k;
  }

  /**
   * Main method of an operator.  Processes the tuple.
   * \param input The tuple to process.
   */
  bool consume(EdgeType const& edge) 
  {
    this->feedCount++;

    if (this->feedCount % this->metricInterval == 0) {
      std::cout << "NodeId " << this->nodeId << " number of keys " 
                << allWindows.size() << " feedCount " << this->feedCount
                << std::endl;
    }

    // Generates unique key from key fields
    std::string key = generateKey<keyFields...>(edge.tuple);

    // Create an Sum if it doesn't exist for the given key
    if (allWindows.count(key) == 0) {
      auto eh = std::shared_ptr<Max<T>>(
                  new Max<T>(N, k));
      allWindows[key] = eh;
    }

    // Update the data structure
    T value = std::get<valueField>(edge.tuple);
    allWindows[streamLocation[key]]->add(value);

    // Getting the current sum and providing that to the feature map.
    T max = allWindows[key]->getMax(allWindows[streamLocation[key]]);
    SingleFeature feature(max);

    // Update the freature map with the new feature.  The feature map
    // takes as input the key for this item, the identifier for this operator,
    // and the feature itself.  The key and the identifier together uniquely
    // identify the feature.
    this->featureMap->updateInsert(key, this->identifier, feature);

    this->notifySubscribers(edge.id, max);

    return true;
  }

  void terminate() {}

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//this is not used yet//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//TODO Should make the function a template parameter so we don't have to copy
// the code.
template <typename T, typename EdgeType,
          size_t valueField, size_t... keyFields>
class ExponentialHistogramAve: public AbstractConsumer<EdgeType>, 
                               public BaseComputation,
                               public FeatureProducer
{
private:

  // Determines number of buckets.  If there are k/2 + 2 buckets
  // of the same size (k + 2 buckets if the bucket size equals 1), 
  // the oldest two buckets are combined.
  size_t k; 

  // The size of the sliding window
  size_t N; 

  // Mapping from string key to the ExponentialHistogram representing the
  // key.
  std::map<std::string, std::shared_ptr<ExponentialHistogram<T>>> allWindows;

public:
  ExponentialHistogramAve(size_t N, size_t k,
                          size_t nodeId,
                          std::shared_ptr<FeatureMap> featureMap,
                          std::string identifier) :
                          BaseComputation(nodeId, featureMap, identifier) 
                                          
  {
    this->N = N;
    this->k = k;
  }

  bool consume(EdgeType const& edge) 
  {
    this->feedCount++;
    if (this->feedCount % this->metricInterval == 0) {
      std::string message = "ExponentialHistogramAve id " + this->identifier +
        " NodeId " + boost::lexical_cast<std::string>(this->nodeId) + 
        " number of keys " + 
        boost::lexical_cast<std::string>(allWindows.size()) + 
        " feedCount " + boost::lexical_cast<std::string>(this->feedCount)+ "\n";
      printf("%s", message.c_str());
    }

    // Generates unique key from key fields
    std::string key = generateKey<keyFields...>(edge.tuple);

    // Create an exponential histogram if it doesn't exist for the given key
    if (allWindows.count(key) == 0) {
      auto eh = std::shared_ptr<ExponentialHistogram<T>>(
                  new ExponentialHistogram<T>(N, k));
      allWindows[key] = eh;
    }

    T value = std::get<valueField>(edge.tuple);

    allWindows[key]->add(value);

    // Getting the current sum and providing that to the featuremap data
    // structure.
    T currentSum = allWindows[key]->getTotal();
    SingleFeature feature(currentSum/ allWindows[key]->getNumItems());
    this->featureMap->updateInsert(key, this->identifier, feature);
  
    // Notify any subscribers of the new value, which is a frequency.
    this->notifySubscribers(edge.id, 
                            currentSum / allWindows[key]->getNumItems());

    return true;
  }

  void terminate() {}
};


}
#endif