
#include <iostream>
#include <string>
using namespace std;


struct QueueNode
{
	string name;
	string functionName;
	int value;
	int bill;
	QueueNode* next;
	QueueNode(int ID, int Bill, string Name, string Function, QueueNode* ptr = nullptr)
	{
		functionName = Function;
		name = Name;
		value = ID;
		next = ptr;
		bill = Bill;
	}
	QueueNode(){}
};
class DynStructQueue
{
private:
	QueueNode* front;
	QueueNode* rear;
public:
	DynStructQueue(); // Constructor.
	void enqueue(int, int, string, string);
	void dequeue(QueueNode*&);
	bool isEmpty() const;
	void clear();
}; 

