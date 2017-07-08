#ifndef SAM_FEATURE_SUBSCRIBER_HPP
#define SAM_FEATURE_SUBSCRIBER_HPP

#include <vector>
#include <atomic>
#include <sstream>
#include <map>

#define MAP_EMPTY        0
#define MAP_OCCUPIED     1
#define MAP_INTERMEDIATE 2

namespace sam {

class FeatureSubscriber
{
private:
  // The column/feature names
  std::vector<std::string> names;

  std::map<std::string, int> featureIndices;

  // Stores the results of completed rows
  std::stringstream ss;

  mutable std::mutex mu;

  int numFeatures;
  int capacity;

  std::atomic<int> volatile * flags;
  double* values;
  int* keys;
  int* counts;

public:
  FeatureSubscriber(std::vector<std::string> const& _names, 
                    int _capacity = 10000) : 
    names(_names),                
    numFeatures(_names.size()),
    capacity(_capacity)
  {
    values = new double[capacity * numFeatures]();
    flags = new std::atomic<int>[capacity];
    keys = new int[capacity];
    counts = new int[capacity];

    // TODO add parallel loop
    for(int i = 0; i < capacity; i++) {
      counts[i] = 0;
      flags [i] = 0;
    }

    for(int i = 0; i < numFeatures; i++)
    {
      featureIndices[names[i]] = i;
    }
  }

  ~FeatureSubscriber() {
    delete[] values;  
    delete[] flags;
    delete[] keys;
    delete[] counts;
  }
  
  void addFeature(std::string name) {
    names.push_back(name);
  }

  int getNumFeatures() { return numFeatures; }

  bool update(int key,
              std::string featureName,
              double value);

  int size() {
    int count = 0;
    for (int i = 0; i < capacity; i++) {
      if (flags[i] == MAP_OCCUPIED) {
        count++; 
      }
    }
    return count;
  }

  std::string getOutput();
private:
  unsigned int hashFunction(int key) const;
  
};

inline
bool FeatureSubscriber::update(int key, std::string featureName, double value)
{
  unsigned int hash = hashFunction(key);
  int i = hash % capacity;
  int index = i;
  do
  {
    if (flags[i] == MAP_EMPTY ||
        flags[i] == MAP_INTERMEDIATE)
    {
      do
      {
        int expected = MAP_EMPTY;
        bool b = std::atomic_compare_exchange_strong(&flags[i], &expected,
                                                    MAP_INTERMEDIATE);
        if (b) {
          int featureIndex = featureIndices[featureName];
          values[i * numFeatures + featureIndex] = value;
          counts[i]++; 
          keys[i] = key;
          flags[i] = MAP_OCCUPIED;
          return true; 
        }

      } while (flags[i] != MAP_OCCUPIED);
    }

    if (flags[i] == MAP_OCCUPIED &&
        keys[i] == key)
    {
      bool b;
      do
      {
        int expected = MAP_OCCUPIED;
        b = std::atomic_compare_exchange_strong(&flags[i], &expected,
                                                MAP_INTERMEDIATE);
      } while (!b);
      int featureIndex = featureIndices[featureName]; 
      values[i * numFeatures + featureIndex] = value;
      counts[i]++; 
      keys[i] = key;

      if (counts[i] >= numFeatures) {
        // The lock_guard makes it so that only one thread can access the 
        // following body of the if statement.
        std::lock_guard<std::mutex> lock(mu);
        counts[i] = 0;
        flags[i] = MAP_EMPTY;
        for (int j = 0; j < numFeatures - 1; j++) {
          ss << values[i * numFeatures + j] << ","; 
        }
        ss << values[i * numFeatures + numFeatures - 1] << std::endl;
        return true;
      }

      flags[i] = MAP_OCCUPIED;
      return true; 
    }

    i = (i + 1) % capacity;
  } while (i != index);
  return false;
}

inline
std::string FeatureSubscriber::getOutput() {
  std::lock_guard<std::mutex> lock(mu);
  return ss.str();
}

inline
unsigned int FeatureSubscriber::hashFunction(int key) const
{
  return key * 31280644937747LL;
}

}

#endif