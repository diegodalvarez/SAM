//I'm not 100% this will work because I'm a little confused how the data get's "modified" so I'm not sure what the expected answer is going to be

#define BOOST_TEST_MAIN TestSimpleMax
#include <boost/test/unit_test.hpp>
#include <sam/SimpleMax.hpp>
#include <sam/tuples/VastNetflow.hpp>
#include <sam/tuples/Tuplizer.hpp>

//getting all the namespaces
using namespace sam;
using namespace sam::vast_netflow;
using std::string;

//this looks like its reading in the information
typedef VastNetFlow TupleType;
typedef EmptyLabel LabelType;
typedef Edge<size_t, LabelType, TupleType> EdgeType;
typedef TupilizerFunction<EdgeType, MakeVastNetflow> Tuplizer;

//this runs the unit test
BOOST_AUTO_CASE(simple_sum_test){

    //defining the object to hold the tuple;
    Tuplizer tuplizer;

    //then this looks like it is setting all of the information
    std::vector<size_t> keyFields;
    size_t nodeId = 0;
    auto featureMap = std::make_shared<FeatureMap>();

    //then this looks like we load the information
    SimpleMax<size_t EdgeType, SrcTotalBytes, DestIp> max(10, nodeId, featureMap, "max0");

    //define two strings
    string netflowString1 = "1365582756.384094,2013-04-10 08:32:36," 
                         "20130410083236.384094,17,UDP,172.20.2.18," 
                         "239.255.255.250,29986,1900,0,0,0,133,0,1,0,1,0,0";
    string netflowString2 = "1365582756.384094,2013-04-10 08:32:36," 
                         "20130410083236.384094,17,UDP,172.20.2.18," 
                         "239.255.255.250,29986,1900,0,0,0,133,0,2,0,1,0,0";

    //this looks like it is extracting the data via tuplizer
    EdgeType edge1 = tuplizer(1, netflowString1);
    EdgeType edge2 = tuplizer(2, netflowString2);

    //then pass the information to the consume
    max.consume(edge1);

    //get max
    size_t maximum = max.getMax("235.255.255.250");

    //see below
    BOOST_CHECK_EQUAL(maximum, 1);

    //seems like we are now iterating over
    for (int i = 0; i < 9; i++){

        //same ideas as above
        max.consume(edge1);
        maximum = sum.getMax("239.255.255.250");

        //see below
        BOOST_CHECK_EQUAL(total, 1);
    }

    max.consume(edge2);
    maximum = max.getMax("239.255.255.250");

    //see below
    BOOST_CHECK_EQUAL(total, 1);

    max.consume(edge2);
    maximum = max.getSum("239.255.255.250");

    //see below
    BOOST_CHECK_EQUAL(total, 1);
    
}

//I'm not sure if I have the correct answer for the BOOST_CHECK_EQUAL. Which means that the unit test can 
//fail because I have the wrong asnwer put in or because the calculation is wrong with the code. 