/*Ahmet Çalýþkan 31065 HW6*/



#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
#include <algorithm>
#include <numeric>
#include <cstdint>

using namespace std;

uint64_t a1 = 97102761753631939, b1 = 42506983374872291;            //necessarcy variables stroed as global for hash function
uint64_t a2 = 56842397421741207, b2 = 18456721873196387;
uint64_t a3 = 61811894731001917, b3 = 37217717671130671;
uint64_t a4 = 31415926535897931, b4 = 27182818284590453;
uint64_t a5 = 98765432109876543, b5 = 57548533468232177;

uint64_t hashA[5] = {a1, a2, a3, a4, a5};
uint64_t hashB[5] = {b1, b2, b3, b4, b5};

constexpr uint64_t c1 = 0xcc9e2d51ull;
constexpr uint64_t c2 = 0x1b873593ull;
constexpr uint64_t r1 = 15;
constexpr uint64_t r2 = 13;
constexpr uint64_t m = 5;
constexpr uint64_t n = 0xe6546b64ull;
/***************************************************************************************/

uint64_t murmur_hash(const std::string& key, uint64_t seed = 0) {
    uint64_t hash = seed;
    const uint8_t* data = reinterpret_cast<const uint8_t*>(key.c_str());
    size_t len = key.length();
    for (size_t i = 0; i < len / 8; ++i) {
        uint64_t k = *reinterpret_cast<const uint64_t*>(data + i * 8);
        k *= c1;
        k = (k << r1) | (k >> (64 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (64 - r2))) * m + n;
    }
    const uint8_t* tail = data + (len / 8) * 8;
    uint64_t k1 = 0;
    switch (len & 7) {
    case 7:
        k1 ^= static_cast<uint64_t>(tail[6]) << 48;
    case 6:
        k1 ^= static_cast<uint64_t>(tail[5]) << 40;
    case 5:
        k1 ^= static_cast<uint64_t>(tail[4]) << 32;
    case 4:
        k1 ^= static_cast<uint64_t>(tail[3]) << 24;
    case 3:
        k1 ^= static_cast<uint64_t>(tail[2]) << 16;
    case 2:
        k1 ^= static_cast<uint64_t>(tail[1]) << 8;
    case 1:
        k1 ^= static_cast<uint64_t>(tail[0]);
        k1 *= c1;
        k1 = (k1 << r1) | (k1 >> (64 - r1));
        k1 *= c2;
        hash ^= k1;
    }
    hash ^= len;
    hash ^= (hash >> 37);
    hash *= 0x85ebca6bull;
    hash ^= (hash >> 32);
    return hash;
}

uint64_t ax_b_string_func(uint64_t a, uint64_t b, string to_hash) {

    uint64_t hash = b;
    for (char c : to_hash) {
        hash = hash * a + static_cast<uint64_t>(c);
    }

    return (uint64_t)hash;
}


/***************************************************************************************/


/***************************************************************************************/

class Sketch {                              //parent sketch class 
    virtual void add(string s) = 0;

};

class MembershipSketch : public Sketch {             //child membership class
    virtual bool isMember(string s) = 0;
};

class BloomFilter : public MembershipSketch {                    
public:                               //bloomfilter class. it is  size/64 array. according to every hash function for number index must change to be 1
    void add(string s) {                       
        if (_switch == 1) {                                               //  for ax+b function
            for (int counter = 0; counter < k; counter++) {
                uint64_t hashVal = ax_b_string_func(hashA[counter], hashB[counter], s) % size;
                int mod = hashVal % 64;
                int dividend = hashVal / 64;
                filter[dividend] = filter[dividend] | (1ULL << (63 - mod));
            }
        }
        else if(_switch == 2){                    // for murmur hash function
            for (int counter = 0; counter < k; counter++) {
                uint64_t hashVal = murmur_hash(s) % size;
                int mod = hashVal % 64;
                int dividend = hashVal / 64;
                filter[dividend] = filter[dividend] | (1ULL << (63 - mod));
            }

        }
    }

    bool isMember(string s) {
        uint64_t* myFilter = new uint64_t[size/64];
        std::fill(myFilter, myFilter + (size/64), 0);
        for (int counter = 0; counter < k; counter++) {
            uint64_t hashVal;
            if (_switch == 1) {
                hashVal = ax_b_string_func(hashA[counter], hashB[counter], s) % size;
            } 
            else if (_switch == 2) {
                hashVal = murmur_hash(s) % size;
            }

            int mod = hashVal % 64;
            int dividend = hashVal / 64;
            myFilter[dividend] |= (1ULL << (63 - mod));
        }
        for (int counter2 = 0; counter2 < (size / 64); counter2++) {
            if ((myFilter[counter2] & filter[counter2]) != myFilter[counter2]) {
                delete[] myFilter;
                return false;
            }
        }
        delete[] myFilter;
        return true;
    }

    BloomFilter(int k, int size, int _switch) : k(k), size(size), _switch(_switch) {
        filter = new uint64_t[size/64];
        std::fill(filter, filter + size/64, 0);

    }
    int get_size() {
        return size;
    }
    int get_k() { return k; }
protected:
    int k;
    int size;
    int _switch;
    uint64_t* filter;
};

class CardinalitySketch : public Sketch {
    virtual double estimateCardinality() = 0;

};

class HyperLogLog : public CardinalitySketch { 
public:
    uint64_t getZeros() {            //function calculates consecutive number of zeros with bit wise operators and return #zeros+1
        int counter = 0;
        while ((buckets[counter] & 1) == 0) {
            buckets[counter] >> 1;
            counter++;
        }
        return counter+1;
    }

    void add(string s) {           //add function. it determines consecutive number of zeros which starts from the least significant bit. 
                                     // also it determines head part of the bit with and if index-1 part of buckets less than consective zeros. number of consecutive zeros is the buckets[index -1]
        uint64_t hashVal;
        if (_switch == 1) {
            hashVal = ax_b_string_func(a1, b1, s);
        }
        else if (_switch == 2) {
            hashVal = murmur_hash(s);
        }
        uint64_t index = hashVal >> int((64 - log2(b)));
        uint64_t zero = getZeros();
        if (buckets[index - 1] < zero) {
            buckets[index - 1] = zero;
        }

    }
    double estimateCardinality() {                        //executes the formula and calculates cardinality for every situation given the homework file 
        double sumProblem = 0;
        double cardinal = 0;
        for (int counter = 0; counter < b; counter++) {
            sumProblem += (1.0) / (pow(2, buckets[counter]));
        }
        if (b <= 16) {
            cardinal = 0.673 * b * (b / sumProblem);
        }
        else if (b == 32) {
            cardinal = 0.697 * b * (b / sumProblem);
        }
        else if (b == 64) {
            cardinal = 0.703 * b * (b / sumProblem);
        }
        else if (b >= 128) {
            double value = 0.7213 / (1 + (1.079 / b));
            cardinal = value * b * (b / sumProblem);
        }
        return cardinal;
    }
    HyperLogLog() {};                      //default and parameter constructors
    HyperLogLog(int k, int _switch) : b(k), _switch(_switch) {
        buckets = new uint64_t[b];
        std::fill(buckets, buckets + b, 0);
    }
protected:
    int b;
    int _switch;
    uint64_t* buckets;
};

class KMinVal : public HyperLogLog {
public:                               //KMinVal function. Ýt creates k size array size return last element of sorted k size array. 
    void add(string s) {
        uint64_t hash1;
        if (_switch == 1) {
           hash1 = ax_b_string_func(a1, b1, s);
        }
        else if (_switch == 2) {
           hash1 = murmur_hash(s);
        }
        int counter = 0;
        for (counter; counter < k; counter++) {
            if (val[counter] == hash1) {
                return;
            }
            if (val[counter] > hash1) {
                break;
            }
        }
        if (counter < k) {
            if (val[counter] > hash1) {
                int counter2 = k - 1;
                for (int counter2 = k - 1; counter2 > counter; counter2--) {
                    val[counter2] = val[counter2 - 1];
                }
                val[counter] = hash1;

            }
        }
        
    }
    double estimateCardinality() {                                     //it calculates caridnality with function given that homework file 
        double minimumHash = val[k - 1];
        uint64_t maximum = 18446744073709551615ULL;
        double cardinal = (k - 1) * (maximum / minimumHash);

        return cardinal;

    }

    KMinVal(int K, int _switch):k(K), _switch(_switch){             // constructor of KMinVal
        val = new uint64_t[k];
        std::fill(val, val + k, -1);
    }
protected:
    int k;
    int _switch;
    uint64_t* val;
};



/***************************************************************************************/



void evaluate_bloom(vector<string> words, BloomFilter *bloom, int i){

  int true_positives = 0;
  int false_positives = 0;
  
  for(int i = 0; i < 100; i++){
    true_positives += (int)bloom->isMember(words[i]);
  }

  for(int i = 0; i < 100; i++){
    false_positives += (int)bloom->isMember(words[words.size() - i - 1]);
  }  
  
  cout << "size: " << bloom->get_size() << " k: " << bloom->get_k() << " Inserted: " << i << " TP: " << true_positives << " FP: " << false_positives << endl;
}

int main(int argc, char** argv) {

    string fname;
    fname = argv[1];
  
  ifstream file(fname);
  if(!file.is_open()){
    cout << "Error opening file: " << fname << endl;
    return 1;
  }

  vector<string> words;
  string word;

  //Reading each line into vector of strings
  while(std::getline(file, word)){
    words.push_back(word);
  }

  cout << "#######################################################################################" << endl;
  cout << "HyperLogLog Using ax+b hash" << endl;
  for(int an = 2; an <= 8192; an *= 2){
    HyperLogLog loglog(an, 1);
    for(int i = 0; i < words.size(); i++){
      loglog.add(words[i]);
    }
    
    cout << "buckets: " << an << " HyperLogLog estimate: " << loglog.estimateCardinality() << endl;
  }
  cout << "#######################################################################################" << endl;

  cout << "#######################################################################################" << endl;
  cout << "HyperLogLog Using MurMurHash" << endl;
  for(int an = 2; an <= 8192; an *= 2){
    HyperLogLog loglog(an, 2);
    for(int i = 0; i < words.size(); i++){
      loglog.add(words[i]);
    }
    
    cout << "buckets: " << an << " HyperLogLog estimate: " << loglog.estimateCardinality() << endl;
  }
  cout << "#######################################################################################" << endl;

  cout << "#######################################################################################" << endl;
  cout << "KMinVal Using ax + b hash" << endl;
  for(int an = 2; an <= 8192; an *= 2){
    KMinVal kminval(an, 1);
    for(int i = 0; i < words.size(); i++){
      kminval.add(words[i]);
    }
    cout << "buckets: " << an << " KMinVal estimate: " << kminval.estimateCardinality() << endl;
  }
  cout << "#######################################################################################" << endl;

  cout << "#######################################################################################" << endl;
  cout << "KMinVal Using MurMurHash" << endl;
  for(int an = 2; an <= 8192; an *= 2){
    KMinVal kminval(an, 2);
    for(int i = 0; i < words.size(); i++){
      kminval.add(words[i]);
    }
    cout << "buckets: " << an << " KMinVal estimate: " << kminval.estimateCardinality() << endl;
  }
  cout << "#######################################################################################" << endl;

  cout << "#######################################################################################" << endl;
  cout << "BloomFilter using ax + b hash" << endl;
  for(int i = 64; i <= 131072; i *= 2){
    BloomFilter *bloom = new BloomFilter(5, i, 1); //Note that we are using 5 hashes with ax + b
    for(int i = 0; i < words.size() - 100; i++){ //We do not add last 100 words to the bloom filter to be able to check if they return as false positives
      bloom->add(words[i]);
      if(i == 100)
	evaluate_bloom(words, bloom, i);
      if(i == 500)
	evaluate_bloom(words, bloom, i);
      if(i == 1000)
	evaluate_bloom(words, bloom, i);
      if(i == 100000)
	evaluate_bloom(words, bloom, i);
      if(i == 1000000)
	evaluate_bloom(words, bloom, i);
    }
    delete bloom;
  }
  cout << "#######################################################################################" << endl;

  cout << "#######################################################################################" << endl;
  cout << "BloomFilter using MurMurHash" << endl;
  for(int i = 64; i <= 131072; i *= 2){
    BloomFilter *bloom = new BloomFilter(5, i, 2); //Note that we are using 5 hashes with ax + b
    for(int i = 0; i < words.size() - 100; i++){ //We do not add last 100 words to the bloom filter to be able to check if they return as false positives
      bloom->add(words[i]);
      if(i == 100)
	evaluate_bloom(words, bloom, i);
      if(i == 500)
	evaluate_bloom(words, bloom, i);
      if(i == 1000)
	evaluate_bloom(words, bloom, i);
      if(i == 100000)
	evaluate_bloom(words, bloom, i);
      if(i == 1000000)
	evaluate_bloom(words, bloom, i);
    }
    delete bloom;
  }
  cout << "#######################################################################################" << endl;

    
}
