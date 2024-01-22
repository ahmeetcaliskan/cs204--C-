#include <iostream>
#include <string>

using namespace std;

struct StackNodee {
	string data;
	StackNodee* next;
	StackNodee(string Data, StackNodee* ptr) {
		next = ptr;
		data = Data;
	}
	StackNodee(){}
}; 


class DynamicStack {
private:
	StackNodee* top;
public:
	DynamicStack(void);
	void pushStack(string);
	void pop(string);
	bool isEmpty(void);
	StackNodee* getStackTop();


};