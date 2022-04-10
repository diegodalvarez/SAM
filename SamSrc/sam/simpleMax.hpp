#ifndef SIMPLE_MAX_HPP
#define SIMPLE_MAX_HPP

/**
 * Thi is a simple implementation of the  max that is not space efficient
 * (i.e. O(N) where N is the size of the sliding window)
 * 
 */

//bring in all of the relevant packages
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
#include <sam/AbstractConsumer.hpp>
#include <sam/BaseComputation.hpp>
#include <sam/Features.hpp>
#include <sam/Util.hpp>
#include <sam/FeatureProducer.hpp>
#include <sam/tuples/Edges.hpp>

//define sam namespace
namespace sam{

    //then define a namespace for the max details
    namespace SimpleMaxDetails{

        //then define a template because a lot of the functions take in class-defined variable-types
        template <typename T>

        //then define  class to hold the information
        class SimpleMaxDataStructure{

            //define the private information
            private:

                //start with saving the size of the string
                size_t N;

                //define a pointer for the typename
                T* array;

                //define a variable to keep track of the max
                T max;

                //then define a variable to keep track of the current spot
                int current = 0;

            //public variables
            public:

                //creating the constructor of the variable
                SimpleMaxDataStructure(size_t N){

                    //use the this to access to the private member class object 
                    this -> N = N;

                    //then define the array of size N
                    array = new T[N]();

                    //then initialize the array with all zeros
                    for (int i = 0; i < N; i++) array[i] = 0;

                    //then set the sum to be zero
                    max = 0;
                }

                //make the destructor
                ~SimpleMaxDataStructure(){

                    //delete
                    delete[] array;
                }

                //make an insert function 
                void insert(T item){

                    //this keeps the max to be same as we pass new values along
                    max = max - array[current];

                    //this wil add in the new value
                    array[current] = item;

                    //this pretty much iterates the current so that we load the information in the right spot
                    current++;

                    //this pretty much reset the max once we get to the end of the array
                    if (current >= N){

                        //reset the max
                        max = 0;
                    }

                    //this is the actual max check 
                    if (max > item){
                        
                        //set max to be the item
                        max = item;
                    }
                }

                //define the "getter" function to return the max
                T getMax(){

                    return max;
                }


        };
    }

    //ok everything from here is mostly coming from the other files I'm not 100% sure of everything 
    //but I'll try my best at explaining it

    //most of this code was written by Dr. Goodman and deals with reading in the data

    //define template for reading in the data
    template <typename T, typename EdgeType, size_t valueField, size_T... keyFields>

    //then define the class with member initialzier list coming from other files
    class SimpleMax: public AbstractConsumer<EdgeType>, public BaseComputation, public FeatureProducer{

        //then create these public attributes
        public:

            //not sure what this is doing but it looks like edge data is getting assignment to be tupled or detupled
            typedef typename EdgeType::LocalTupleTyple TupleType;

        //private attributes
        private:

            //size of the window
            size_t N;

            //this looks like we are passing the information through
            typedef SimpleMaxDetails::SimpleMaxDataStructure<T> value_t;

            //then we create a map to keep track of the values we've seen
            std::map<std::string, value_t*> allWindows;

            //the most recent item location in the array
            size_t top = 0;

        //this public will be for the constructor
        public:

            //constructor
            SimpleMax(size_t N, size_t nodeId, std::shared_ptr<FeatureMap> featureMap, std::string identifier): BaseComputation(nodeId, featureMap, identifier){

                //then use this for the pointer
                this -> N = N;
            }

            //destructor
            ~SimpleMax(){

                //not sure what most of this means but looks like allWindows has a member method that deletes
                for (auto p: allWindows){
                    delete p.second;
                }
            }

            //the consume function is the mean function for reading in information
            bool consume(EdgeType const& edge){

                //again not sure but looks like we are extracting information from the tuple
                TupleType tuple = edge.tuple;

                //then same idea we have to access the functions
                this -> feedCount++;

                //not sure what this is doing  but it looks like its going through the feed count
                if (this -> feedCount % this -> metricInterval == 0){

                    //then we want to ouptut the information
                    std::cout << "SimpleMax: NodeId " << this -> nodeId << " feedcount " << this -> feedCount << std::endl;

                }

                //this generates the unique key I guess the best way to think of this is like its a hash function
                std::string key = generateKey<keyFields...>(tuple);

                //then we want to reset the key if its zero
                if (allWindows.count(key) == 0){

                    //get key value
                    auto value = new value_t(N);

                    //set the key
                    allWindows[key] = value;

                } 

                //not sure what this is doing but looks like its saving the string
                std::string sValue = boost::lexical_cast<std::string>(std::get<valueField>(tuple));

                //get the value as well
                T value;

                //then it seems like we are using try statement to make sure we can cast
                try{

                    value = boost::lexical_cast<T>(sValue);
                }catch(std::exception e){

                    //output error message
                    std::cerr << "SimpleSum::consume Caught exception trying to cast string value of " << sValue << std::endl;

                    //set value to 0 to avoid error again
                     value = 0;
                }

                //then we want to insert the value in the window
                allWindows[key] -> insert(value);

                //now we want to get the current Max via featureMap
                T currentMax = allWindows[key] -> getMax();

                //then we want to pushback the feature
                SingleFeature feature(currentMax);

                //then we want to update all of our information
                this -> featureMap -> updateInsert(key, this -> identifier, feature);

                //then notify the subsrciber
                notifySubscribers(edge.id, currentMax);

                return true;
            }

            //create the "getter" function
            T getSum(std::string){

                //return the max
                return allWindows[key] -> getMax();
            }

            //not sure what this is doing but it looks like this is putting the information into a vector
            std::vector<std:string> keys() const{
                std::vector<std::string> theKeys;

                for (auto p: allWindows){
                    theKeys.push_back(p.first);
                }

                return theKeys;
            }

            void terminate(){}
    };
}

#endif