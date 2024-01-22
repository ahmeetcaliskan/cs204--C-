//Fall 2023 CS204 HW#5 -- main.cpp
// Ahmet Çalýþkan 31065
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <type_traits>     
#include <cmath>
#include "ahmet.caliskan_Caliskan_Ahmet_HW5_vector.h"

template <typename T1, typename T2>
myVector<T1, T2>::myVector<T1, T2>() {}                       //default constructor of myVector

template <typename T1, typename T2>
myVector<T1, T2>& myVector<T1, T2>::operator=(const myVector<T1, T2> copy) {        //Copy function of myVector
    this->name = copy.name;
    this->values = copy.values;
    this->keys = copy.keys;
    return *this;
}

template <typename T1, typename T2>
bool myVector<T1, T2>::operator==(const myVector& rhs) const {                 //check equal. it compares all of the private 
    return (this->name == rhs.name) && (this->values == rhs.values) && (this->keys == rhs.keys);
}

template <typename T1, typename T2>
T1* myVector<T1, T2 >::operator[](T2& key) {          // index operator function. returne pointer of value
    T1* ptr = nullptr;
    for (int i = 0; i < keys.size(); i++) {                       //scan all key vector and find 
        if (keys.at(i) == key) {
            ptr = &values.at(i);
            return ptr;
        }
    }
    return nullptr;                                        //if it cannot find, return nullptr
}

template <typename T1, typename T2>
string myVector<T1, T2 >::getName() {                                  //retuns name
    return name;
}

template <typename T1, typename T2>
myVector<T1, T2>& myVector<T1, T2 >::begin() {                         //returns myvector itself
    return *this;
}

template <typename T1, typename T2>
void myVector<T1, T2 >::setName(string  vectorName) {               //sets vector name
    name = vectorName;
}

template <typename T1, typename T2>
bool myVector<T1, T2 >::isEmpty() {                        //check that myvector empty or not a returns bool
    if (values.size() == 0) {
        return true;
    }
    return false;
}


template <typename T1, typename T2>
void myVector<T1, T2 >::push_back(T1& value, T2& key) {                  //push back the value and key to each vector
    keys.push_back(key);
    values.push_back(value);
}

template <typename T1, typename T2>
void myVector<T1, T2 >::remove(T2 key) {                               //remove key and value 
    for (int counter = 0; counter < values.size(); counter++) {             //scanning all keys vector
        if (keys.at(counter) == key) {
            values.erase(values.begin() + counter);
            keys.erase(keys.begin() + counter);
        }
    }
}

template <typename T1, typename T2>
void myVector<T1, T2 >::sorted_elements(vector<T1>& free_vector) {           //sorted function
    Iterator iter(*this);                            //initialization of iterator
    for (iter.init(); iter.has_More(); iter.next()) {
        int counter = 0;                             //check to add which index
        bool check = false;                           //bool for ending the while loop
        while (!check && counter < free_vector.size()) {
            if (values.at(iter.current()) < free_vector.at(counter)) {
                check = true;                                    // end loop
            }
            else {
                counter++;                   //increas index
            }
        }
        free_vector.insert(free_vector.begin() + counter, values.at(iter.current()));              //adding the element to spesific index
    }
}

template <typename T1, typename T2>
double myVector<T1, T2 >::calculateMean() {              // mean calculation
    Iterator iter(*this);                  //initalization of iter 
    double sum = 0;
    for (iter.init(); iter.has_More(); iter.next()) {
        sum += values.at(iter.current());                       //summation of all values with loop
    }
    return sum / values.size();                       // returns mean
}

template <typename T1, typename T2>
double myVector<T1, T2 >::findMedian(vector<T1>& sorted_vector) {       //calculation of median
    int size = sorted_vector.size();

    if (size == 0) {                                    //checks to size of vector
        cout << "Error: The vector is empty." << std::endl;
        return 0.0;
    }

    if (size % 2 == 1) {                             //median is middle element for odd vectors
        return static_cast<double>(sorted_vector[size / 2]);
    }
    else {                                          // median is half of the summation of middle two elements in even vectors
        T1 mid1 = sorted_vector.at(size / 2 - 1);
        T1 mid2 = sorted_vector.at(size / 2);
        return static_cast<double>(mid1 + mid2) / 2.0;
    }
}


template <typename T1, typename T2>                             
double myVector<T1, T2 >::calculateStandardDeviation(vector<T1>& sorted_vector, double& mean) {
    int size = sorted_vector.size();
                                                                // calculation of standard deviation
    if (size <= 1) {
        cout << "The vector has not enough elements." << endl;
        return 0.0;                                           //checks it has enough size or not
    }
    double sum_square_difference = 0.0;
    for (int counter = 0; counter < sorted_vector.size(); counter++) {
        double difference = static_cast<double>(sorted_vector.at(counter)) - mean;           // summation of square of differences 
        sum_square_difference += difference * difference;
    }
    double variance = sum_square_difference / size;
    double standardDeviation = sqrt(variance);                             //calculation of standard deviation

    return standardDeviation;
}

template <typename T1, typename T2>
T1 myVector<T1, T2 >::calculateMode() {                        //calculation of mode 
    int max_occurence = 0;                              // initalizaiton of occurence and value of max
    T1 max = 0.0;
    for (int counter1 = 0; counter1 < values.size(); counter1++) {
        int occurence = 0;
        for (int counter2 = counter1 + 1; counter2 < values.size(); counter2++) {     //check every combination with nested for loops 
            if (values.at(counter1) == values.at(counter2)) {
                occurence++;                         //if 2 elements in vector are same, increase ocurrence
            }
        }
        if (occurence > max_occurence) {                   // changing the value and occurence
            max_occurence = occurence;
            max = values.at(counter1);
        }
        else if (occurence == max_occurence && max > values.at(counter1)) {
            max_occurence = occurence;
            max = values.at(counter1);                      // changing the value and occurence
        }
    }
    if (max_occurence == 0) {
        max = values.at(0);                              // if no element has not any duplicate, returns first element of vector
    }
    return max;
}


template <typename T1, typename T2>
string myVector<T1, T2 >::mostOccurenceString(int& max_occurence) {              // retruns most Occurence string 
    string max = "";                                               //initialize max 
    for (int counter1 = 0; counter1 < values.size(); counter1++) {
        int occurence = 1;                                                 //occurence starts witjh one because it find duplicate itself once, occurence should be 2
        for (int counter2 = counter1 + 1; counter2 < values.size(); counter2++) {
            if (values.at(counter1) == values.at(counter2)) {
                occurence++;             // if they are equal, implement occurrence 
            }
        }
        if (occurence > max_occurence) {          //changing the occurence and value
            max_occurence = occurence;
            max = values.at(counter1);
        }
        else if (occurence == max_occurence && max > values.at(counter1)) {
            max_occurence = occurence;                      //changing the occurence and value
            max = values.at(counter1);
        }
    }
    return max;                                               //return max occurent string
}


template <typename T1, typename T2>
char myVector<T1, T2 >::mostOccurenceCharacter(int& max) {                  // returning most occurent character
    int charArray[256] = { 0 };                                  // arrays for each character
    char most_occurence = '\0';                                //starts with null 
    for (int counter1 = 0; counter1 < values.size(); counter1++) {
        string word = values.at(counter1);
        for (int counter2 = 0; counter2 < word.length(); counter2++) { // scanning every sring and character, implement in array 
            int character = word[counter2];
            charArray[character]++;
        }
    }
    for (int counter3 = 0; counter3 < 256; counter3++) {            //scannig updated array , findings max value and occurrence 
        if (charArray[counter3] > max) {
            max = charArray[counter3];
            most_occurence = static_cast<char>(counter3);
        }
    }
    return most_occurence;                                // return most occurent character
}


template <typename T1, typename T2>
void myVector<T1, T2 >::process_data() {
    if constexpr ((is_same<T1, string>::value)) {            // check values for string or aritmethic 
        int countString = 0;
        int countCharacter = 0;

        string mostOccurentStr = mostOccurenceString(countString);         //most occurrence functions for strign and character 
        char mostOccurentCharacter = mostOccurenceCharacter(countCharacter);

        cout << "Most Frequent Character: '" << mostOccurentCharacter << "' (Frequency: " << countCharacter << ")" << endl;          //printing both of them
        cout << "Most Frequent Word: \"" << mostOccurentStr << "\" (Frequency: " << countString << ")" << endl;
    }
    else {
        vector<T1> sortedVector;             //adding new empty vector for sorted way 
        sorted_elements(sortedVector);               //update vector to new empty vector as sorted 
        T1 max = sortedVector.back();                   // find max
        double mean = calculateMean();                  //finding mean
        double median = findMedian(sortedVector);                  //finding median 
        double standart_deviation = calculateStandardDeviation(sortedVector, mean);        //finding standard deviation
        T1 mode = calculateMode();                    //fiding mode 
        cout << "Mean: " << mean << endl;
        cout << "Median: " << median << endl;
        cout << "Standard Deviation: " << standart_deviation << endl;        //printing all of them 
        cout << "Max: " << max << endl;
        cout << "Mode: " << mode << endl;
    }
}

 // iterator function
template <typename T1, typename T2>
myVector<T1, T2>::Iterator::Iterator(myVector<T1, T2>& vectorMy) : myvector(vectorMy) {}      //constructor, works with myvector value


template <typename T1, typename T2>
void myVector<T1, T2>::Iterator::setVector(myVector<T1, T2>& usedVector) {      //setting myvector value 
    myvector = usedVector;
}


template <typename T1, typename T2>
int myVector<T1, T2>::Iterator::init() {                   //initalize and returns iterator 
    idx = 0;
    return idx;
}


template <typename T1, typename T2>
void myVector<T1, T2>::Iterator::next() {                          //increasing by one to iterator 
    idx++;
}


template <typename T1, typename T2>
bool myVector<T1, T2>::Iterator::has_More() {                 //check function for iterator
    return idx < myvector.values.size();
}


template <typename T1, typename T2>
int myVector<T1, T2>::Iterator::current() {                   // returns current iterator 
    return idx;
}

template <typename T1, typename T2>
void myVector<T1, T2>::Iterator::printVector() {             //printing vector thanks to iterator 
    for (init(); has_More(); next()) {
        cout << "Value: " << this->myvector.values.at(current()) << ", Key: " << this->myvector.keys.at(current()) << endl;
    }
}


template <typename T1, typename T2>
bool myVector<T1, T2>::Iterator::find(const T2& key, myVector<T1, T2>& vectorMy) {      //finding key in the vector with iterator 
    for (init(); has_More(); next()) {
        if (key == vectorMy.keys.at(current())) {
            return true;
        }
    }
    return false;
}


template <typename T1, typename T2>
void myVector<T1, T2>::Iterator::replaceKey(T2 newKey) {              //replace key in the vector 
    myvector.keys.at(current()) = newKey;
}



/*******************************************************************************************************
    DO NOT CHANGE THE MAIN FUNCTION BELOW
    YOU WILL NOT GET ANY POINTS FROM THIS HOMEWORK IF YOU CHANGE IT
*******************************************************************************************************/
int main()
{
    //Vector and iterator declarations
    myVector<std::string, int> vecStringInt;
    vecStringInt.setName("vecStringInt");
    myVector<std::string, int>::Iterator itrStringInt(vecStringInt.begin());

    myVector<double, double> vecDoubleDouble;
    vecDoubleDouble.setName("vecDoubleDouble");
    myVector<double, double>::Iterator itrDoubleDouble(vecDoubleDouble.begin());

    myVector<int, std::string> vecIntString;
    vecIntString.setName("vecIntString");
    myVector<int, std::string>::Iterator itrIntString(vecIntString.begin());

    myVector<double, std::string> vecDoubleString;
    vecDoubleString.setName("vecDoubleString");
    myVector<double, std::string>::Iterator itrDoubleString(vecDoubleString.begin());

    myVector<std::string, int> vecStringInt2;
    vecStringInt2.setName("vecStringInt2");
    myVector<std::string, int>::Iterator itrStringInt2(vecStringInt2.begin());

    myVector<double, double> vecDoubleDouble2;
    vecDoubleDouble2.setName("vecDoubleDouble2");
    myVector<double, double>::Iterator itrDoubleDouble2(vecDoubleDouble2.begin());

    myVector<int, std::string> vecIntString2;
    vecIntString2.setName("vecIntString2");
    myVector<int, std::string>::Iterator itrIntString2(vecIntString2.begin());

    myVector<double, std::string> vecDoubleString2;
    vecDoubleString2.setName("vecDoubleString2");
    myVector<double, std::string>::Iterator itrDoubleString2(vecDoubleString2.begin());

    //File reading
    std::string filename;
    std::cout << "Enter the filename: ";
    std::getline(std::cin, filename);
    std::ifstream inFile(filename);

    if (!inFile.is_open() || inFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Error: Input file is empty or cannot be opened." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string command, vecName, key;
        iss >> command;

        if (command.empty()) {
            continue; // Skip empty lines or lines with only spaces
        }

        if (command == "push") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                std::string stringValue;
                iss >> intKey >> stringValue;
                vecStringInt.push_back(stringValue, intKey);
            }
            else if (vecName == "vecDoubleDouble") {
                double doubleValue;
                iss >> doubleKey >> doubleValue;
                vecDoubleDouble.push_back(doubleValue, doubleKey);
            }
            else if (vecName == "vecIntString") {
                int intValue;
                std::string stringValue;
                iss >> stringKey >> intValue;
                vecIntString.push_back(intValue, stringKey);
            }
            else if (vecName == "vecDoubleString") {
                double doubleValue;
                iss >> stringKey >> doubleValue;
                vecDoubleString.push_back(doubleValue, stringKey);
            }
        }
        else if (command == "remove") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;

            if (vecName == "vecStringInt") {
                iss >> intKey;
                vecStringInt.remove(intKey);
            }
            else if (vecName == "vecDoubleDouble") {
                iss >> doubleKey;
                vecDoubleDouble.remove(doubleKey);
            }
            else if (vecName == "vecIntString") {
                iss >> stringKey;;
                vecIntString.remove(stringKey);
            }
            else if (vecName == "vecDoubleString") {
                iss >> stringKey;
                vecDoubleString.remove(stringKey);
            }
        }
        else if (command == "find") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                iss >> intKey;
                std::string* foundValue = vecStringInt[intKey];
                if (foundValue) std::cout << "Found: Key = " << intKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << intKey << std::endl;
            }
            else if (vecName == "vecDoubleDouble") {
                iss >> doubleKey;
                double* foundValue = vecDoubleDouble[doubleKey];
                if (foundValue) std::cout << "Found: Key = " << doubleKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << doubleKey << std::endl;
            }
            else if (vecName == "vecIntString") {
                iss >> stringKey;
                int* foundValue = vecIntString[stringKey];
                if (foundValue) std::cout << "Found: Key = " << stringKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << stringKey << std::endl;
            }
            else if (vecName == "vecDoubleString") {
                iss >> stringKey;
                double* foundValue = vecDoubleString[stringKey];
                if (foundValue) std::cout << "Found: Key = " << stringKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << stringKey << std::endl;
            }
        }

        else if (command == "replace_value") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                std::string stringValue;
                iss >> intKey >> stringValue;
                std::string* foundValue = vecStringInt[intKey];
                if (foundValue) *foundValue = stringValue;
                else std::cout << "Key not found for replacement: " << intKey << std::endl;
            }
            else if (vecName == "vecDoubleDouble") {
                double doubleValue;
                iss >> doubleKey >> doubleValue;
                double* foundValue = vecDoubleDouble[doubleKey];
                if (foundValue) *foundValue = doubleValue;
                else std::cout << "Key not found for replacement: " << doubleKey << std::endl;
            }
            else if (vecName == "vecIntString") {
                int intValue;
                iss >> stringKey >> intValue;
                int* foundValue = vecIntString[stringKey];
                if (foundValue) *foundValue = intValue;
                else std::cout << "Key not found for replacement: " << stringKey << std::endl;
            }
            else if (vecName == "vecDoubleString") {
                double doubleValue;
                iss >> stringKey >> doubleValue;
                double* foundValue = vecDoubleString[stringKey];
                if (foundValue) *foundValue = doubleValue;
                else std::cout << "Key not found for replacement: " << stringKey << std::endl;
            }
        }

        if (command == "replace_key") {
            std::string oldKeyStr, newKeyStr;
            int oldKeyInt, newKeyInt;
            double oldKeyDouble, newKeyDouble;

            iss >> vecName;
            if (vecName == "vecStringInt") {
                iss >> oldKeyInt >> newKeyInt;
                if (itrStringInt.find(oldKeyInt, vecStringInt)) {
                    itrStringInt.replaceKey(newKeyInt);
                }
                else {
                    std::cout << "Key not found: " << oldKeyInt << std::endl;
                }
            }
            else if (vecName == "vecDoubleDouble") {
                iss >> oldKeyDouble >> newKeyDouble;
                if (itrDoubleDouble.find(oldKeyDouble, vecDoubleDouble)) {
                    itrDoubleDouble.replaceKey(newKeyDouble);
                }
                else {
                    std::cout << "Key not found: " << oldKeyDouble << std::endl;
                }
            }
            else if (vecName == "vecIntString") {
                iss >> oldKeyStr >> newKeyStr;
                if (itrIntString.find(oldKeyStr, vecIntString)) {
                    itrIntString.replaceKey(newKeyStr);
                }
                else {
                    std::cout << "Key not found: " << oldKeyStr << std::endl;
                }
            }
            else if (vecName == "vecDoubleString") {
                iss >> oldKeyStr >> newKeyStr;
                if (itrDoubleString.find(oldKeyStr, vecDoubleString)) {
                    itrDoubleString.replaceKey(newKeyStr);
                }
                else {
                    std::cout << "Key not found: " << oldKeyStr << std::endl;
                }
            }
            else {
                std::cout << "Unknown vector name: " << vecName << std::endl;
            }
        }

        else if (command == "print") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                iss >> intKey;
                std::string* value = vecStringInt[intKey];
                if (value) {
                    std::cout << "Key: " << intKey << ", Value: " << *value << std::endl;
                }
                else {
                    std::cout << "Error: Key not found: " << intKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
            else if (vecName == "vecDoubleDouble")
            {
                iss >> doubleKey;
                double* value = vecDoubleDouble[doubleKey];
                if (value) {
                    std::cout << "Key: " << doubleKey << ", Value: " << *value << std::endl;
                }
                else {
                    std::cout << "Error: Key not found: " << doubleKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
            else if (vecName == "vecIntString")
            {
                iss >> stringKey;
                int* value = vecIntString[stringKey];
                if (value) {
                    std::cout << "Key: " << stringKey << ", Value: " << *value << std::endl;
                }
                else {
                    std::cout << "Error: Key not found: " << stringKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
            else if (vecName == "vecDoubleString")
            {
                iss >> stringKey;
                double* value = vecDoubleString[stringKey];
                if (value) {
                    std::cout << "Key: " << stringKey << ", Value: " << *value << std::endl;
                }
                else {
                    std::cout << "Error: Key not found: " << stringKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
        }

        else if (command == "print_vector") {
            iss >> vecName;
            if (vecName == "vecStringInt") {
                if (vecStringInt.isEmpty()) {
                    std::cout << "Error: vecStringInt is empty." << std::endl;
                }
                else {
                    std::cout << "\nPrinting vecStringInt:" << std::endl;
                    itrStringInt.printVector();
                }
            }
            else if (vecName == "vecDoubleDouble") {
                if (vecDoubleDouble.isEmpty()) {
                    std::cout << "Error: vecDoubleDouble is empty." << std::endl;
                }
                else {
                    std::cout << "\nPrinting vecDoubleDouble:" << std::endl;
                    itrDoubleDouble.printVector();
                }
            }
            else if (vecName == "vecIntString") {
                if (vecIntString.isEmpty()) {
                    std::cout << "Error: vecIntString is empty." << std::endl;
                }
                else {
                    std::cout << "\nPrinting vecIntString:" << std::endl;
                    itrIntString.printVector();
                }
            }
            else if (vecName == "vecDoubleString") {
                if (vecDoubleString.isEmpty()) {
                    std::cout << "Error: vecDoubleString is empty." << std::endl;
                }
                else {
                    std::cout << "\nPrinting vecDoubleString:" << std::endl;
                    itrDoubleString.printVector();
                }
            }
            else {
                std::cout << "Error: Unknown vector name '" << vecName << "'" << std::endl;
            }
        }

        else if (command == "copy") {
            std::string targetVecName;
            iss >> vecName >> targetVecName;

            if (vecName == "vecStringInt" && targetVecName == "vecStringInt2") {
                vecStringInt2 = vecStringInt;
                std::cout << "\nPrinting vecStringInt2:" << std::endl;
                itrStringInt2.printVector();
            }
            else if (vecName == "vecDoubleDouble" && targetVecName == "vecDoubleDouble2") {
                vecDoubleDouble2 = vecDoubleDouble;
                std::cout << "\nPrinting vecDoubleDouble2:" << std::endl;
                itrDoubleDouble2.printVector();
            }
            else if (vecName == "vecIntString" && targetVecName == "vecIntString2") {
                vecIntString2 = vecIntString;
                std::cout << "\nPrinting vecIntString2:" << std::endl;
                itrIntString2.printVector();
            }
            else if (vecName == "vecDoubleString" && targetVecName == "vecDoubleString2") {
                vecDoubleString2 = vecDoubleString;
                std::cout << "\nPrinting vecDoubleString2:" << std::endl;
                itrDoubleString2.printVector();
            }
            else {
                std::cout << "Error: Incompatible vector types or unknown vector names for copy." << std::endl;
            }
        }

        else if (command == "check_equal") {
            std::string targetVecName;
            iss >> vecName >> targetVecName;

            if (vecName == "vecStringInt" && targetVecName == "vecStringInt2") {
                if (vecStringInt == vecStringInt2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                }
                else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            }
            else if (vecName == "vecDoubleDouble" && targetVecName == "vecDoubleDouble2") {
                if (vecDoubleDouble == vecDoubleDouble2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                }
                else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            }
            else if (vecName == "vecIntString" && targetVecName == "vecIntString2") {
                if (vecIntString == vecIntString2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                }
                else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            }
            else if (vecName == "vecDoubleString" && targetVecName == "vecDoubleString2") {
                if (vecDoubleString == vecDoubleString2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                }
                else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            }
            else {
                std::cout << "Error: Incompatible vector types or unknown vector names for comparison." << std::endl;
            }
        }

        if (command == "process_data") {
            iss >> vecName;
            if (vecName == "vecStringInt") {
                std::cout << "Processing data of vector " << vecStringInt.getName() << ":" << std::endl;
                vecStringInt.process_data();
            }
            else if (vecName == "vecDoubleDouble") {
                std::cout << "Processing data of vector " << vecDoubleDouble.getName() << ":" << std::endl;
                vecDoubleDouble.process_data();
            }
            else if (vecName == "vecIntString") {
                std::cout << "Processing data of vector " << vecIntString.getName() << ":" << std::endl;
                vecIntString.process_data();
            }
            else if (vecName == "vecDoubleString") {
                std::cout << "Processing data of vector " << vecDoubleString.getName() << ":" << std::endl;
                vecDoubleString.process_data();
            }
            else {
                std::cout << "Error: Unknown vector name '" << vecName << "'" << std::endl;
            }
        }
    }


    inFile.close();
    return 0;
}
/*******************************************************************************************************/