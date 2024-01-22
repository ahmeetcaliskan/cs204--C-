// Ahmet Caliskan 31065 #HW4

#include <iostream>
using namespace std;


class LinkedListSet {	
	
	
	struct IntNode   // This struct is created for linkedlistset data strucuture
	{
	public:
		int num;                  
		IntNode* next;
		IntNode(int value, IntNode* ptr) {                // constructor of node
			num = value;
			next = ptr;
		}

	};

private:
	IntNode* head;                            // class has one prive member which is head of linkedlist
public:

	LinkedListSet() {                               //constructor of class
		head = nullptr;
	}

	bool isRepeated(const int& num1) {               //this fucntion is useful for check that number exist in lhs or not 
		IntNode* ptr = head;
		bool isRepeated = false;                      // returning variable. reutnring true if it is exist
		while (ptr && !isRepeated) {              // scanning every value in lhs
			if (ptr->num == num1) {
				isRepeated = true;
			}
			ptr = ptr->next;
		}
		return isRepeated;
	}
	void display() {                         //displaying lhs with expected shape
		IntNode* nodePtr = head;
		cout << "LinkedListSet{";
		while (nodePtr) {                       //scanning every varilable for displaying
			cout << nodePtr->num << ", ";
			nodePtr = nodePtr->next;
		}
		cout << "}" << endl;
	}

	LinkedListSet& operator +(const int& num) {              // adding operartor. it is also useful for += operator
		IntNode* newNode = new IntNode(num, nullptr);           // creating new linkedlist node 
		bool repeated = isRepeated(num);                        // check that it is already exist. if it is exist, do not add.
		if (!repeated) {
			if (!head || head->num > newNode->num) {        // adding for empty lists or adding to the head
				newNode->next = head;
				head = newNode;
			}
			else {                                           //inserting for other locations
				bool insertion_is_done = false;            // check variable for adding process
				IntNode* nodePtr = head;                       //for scaninng all data in linkedlist
				while (nodePtr->next && !insertion_is_done) {
					if (nodePtr->next->num > newNode->num) {
						IntNode* temp;                           // inserting a node between two nodes
						temp = nodePtr->next;                   //temp is useful for adding 
						nodePtr->next = newNode;
						newNode->next = temp;

						insertion_is_done = true;            // convert bool station to true
					}
					nodePtr = nodePtr->next;

				}
				if (!insertion_is_done) {                  // inserting node as a last element
					nodePtr->next = newNode;
				}
			}
		}
		return *this;
	}
	LinkedListSet& operator -(const int& ct) {           //substracting operator. it also useful for -= and &= operator
		if (!head) {                                     // Displaying if list is empty
			cout << "List is empty..." << endl;
		}
		else if (head->num == ct) {              // substracitg head and updating head
			IntNode* temp = head;
			head = head->next;
			delete temp;
		}
		else {                           // subtracting other locations
			IntNode* ptr = head;
			bool substraction_is_done = false;           //check that process is done or not
			while (!substraction_is_done && ptr->next) {
				if (ptr->next->num == ct) {
					IntNode* temp;                 // deleting a node which is between two nodes. temp is required
					temp = ptr->next;
					ptr->next = ptr->next->next;
					delete temp;
					substraction_is_done = true;         // conveitng to ture for process
				}
				ptr = ptr->next;
			}
			if (!substraction_is_done && ptr->num == ct) {   //subtracitng from end of the list if the values are matching
				delete ptr;
			}
		}
		return *this;
	}

	LinkedListSet& operator +=(const LinkedListSet& rhs) {      //+= operator
		IntNode* rhsPtr = rhs.head;
		while (rhsPtr) {            //scanning every data 
			if (!isRepeated(rhsPtr->num)) {
				*this + (rhsPtr->num);             // if rhs value does not exist in lhs, append it.
			}
			rhsPtr = rhsPtr->next;
		}
		return *this;
	}

	LinkedListSet& operator -=(const LinkedListSet& rhs) {  // -= operator
		IntNode* rhsPtr = rhs.head;
		while (rhsPtr) {                   // scanning every rhs value
			if (isRepeated(rhsPtr->num)) {
				*this - (rhsPtr->num);          // if rhs value exist in lhs, delete it from lhs
			}
			rhsPtr = rhsPtr->next;
		}
		return *this;
	}

	LinkedListSet& operator &=(const LinkedListSet& rhs) {       //&= operator. returning values which are exist in both lists
		IntNode* rhsPtr = rhs.head;
		while (rhsPtr) {
			if (!isRepeated(rhsPtr->num)) {                         // scanning every data
				*this - (rhsPtr->num);                   // deleting variables which ,is not in lhs but is exist in rhs,process from lhs
			}
			rhsPtr = rhsPtr->next;
		}
		IntNode* lhsPtr = head;                                
		while (lhsPtr) {                               // deleting variables which ,is not in lhs but is exist in rhs,process from lhs
			IntNode* rhsPtr2 = rhs.head;
			bool isRepeated = false;                    // checking variable 
			while (rhsPtr2 && lhsPtr) {
				if (lhsPtr->num == rhsPtr2->num) {          // if values are match, convert bool variable to true therefore it cannot delete
					isRepeated = true;
				}
				rhsPtr2 = rhsPtr2->next;
			}
			if (!isRepeated) {                // if value is not matching delete it
				IntNode* temp;
				temp = lhsPtr;
				lhsPtr = lhsPtr->next;
				*this - (temp->num);
			}
			else {                          //transffering to other lhs
				lhsPtr = lhsPtr->next;
			}

		}

		return *this;
	}
	
};


//********************************************************************************

 

int main() {

	// Example usage
	LinkedListSet set1;
	set1 + 1 + 2 + 3 + 17; // Insertion
	set1.display();

	set1 - 2; // Deletion
	set1.display();

	LinkedListSet set2;
	set2 + 3 + 4 + 5;
	set2.display();

	set2 += set1 + 7 + 3 + 19; //Insertion with multiple right-hand values
	set2.display();

	LinkedListSet set3;
	set3 + 3 + 4 + 7 + 17 + 41;
	set3.display();

	LinkedListSet set4;
	set4 + 41 + 37 + 7 + 19 + 41;
	set4.display();

	// Set Union
	set1 += set2;
	set1.display();

	// Set Difference
	set1 -= set3;
	set1.display();

	// Set Intersection
	set1 &= set4;
	set1.display();

	return 0;
}

