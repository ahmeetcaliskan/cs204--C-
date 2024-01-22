//Fall 2023 CS204 HW#5 -- myVector.h
//Ahmet Çalýþkan 31065
#include <iostream>
#include <type_traits>
#include <cmath>
#include <unordered_map>
using namespace std;
/*******************************************************************************************************
    IMPLEMENT FOLLOWING CLASSES
    YOU CAN ADD ANY FUNCTION/STRUCT/CLASS THAT YOU WILL USE HOWEVER YOU CANNOT TOUCH MAIN FUNCTION
*******************************************************************************************************/
template <typename T1, typename T2>
class myVector {
public:
    myVector<T1, T2>();

    myVector<T1, T2>& operator=(const myVector<T1, T2> copy);
    
    bool operator==(const myVector& rhs) const;
    
    T1* operator[](T2& key);

    string getName();

    myVector<T1, T2>& begin();

    void setName(string  vectorName);

    bool isEmpty();

    void push_back(T1& value, T2& key);

    void remove(T2 key);

    void sorted_elements(vector<T1>& free_vector);
    
    double calculateMean();
    
    double findMedian(vector<T1>& sorted_vector);

    double calculateStandardDeviation(vector<T1>& sorted_vector, double& mean);
    
    T1 calculateMode();
    
    string mostOccurenceString(int& max_occurence);
    
    char mostOccurenceCharacter(int& max);
    
    void process_data();
    
    class Iterator {
    public:
        
        Iterator(myVector<T1, T2>& vectorMy);

        void setVector(myVector<T1, T2>& usedVector);

        int init();
        
        void next();
        
        bool has_More();

        int current();
        
        void printVector();
   
        bool find(const T2& key, myVector<T1, T2>& vectorMy);

        void replaceKey(T2 newKey);

    private:
        myVector<T1, T2>& myvector;
        
        int idx = 0;
    };
private:
    vector<T1> values;
    
    vector<T2> keys;
    
    string name;
};

/*******************************************************************************************************/

