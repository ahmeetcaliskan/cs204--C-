#ifndef STATICSTRUCTQUEUE_H
#define STATICSTRUCTQUEUE_H


using namespace std;
#include <iostream>
#include <string>

struct StringQueueNode
{
	int ID;
	string name, function;
	StringQueueNode(){}
	StringQueueNode(int num, string Name, string functionName)
	{
		function = functionName;
		name = Name;
		ID = num;

	}
};


class StructQueue
{
private:
	StringQueueNode* queueArray;
	int queueSize; //capacity of queue
	int front;
	int rear;
	int numItems; //# of elements currently in the queue
public:
	StructQueue(int); //constructor, parameter is capacity
	void enqueue(int, string, string);
	void dequeue(StringQueueNode&);
	bool isEmpty() const;
	bool isFull() const;
	void clear(); //removes all elements
};
#endif // !STATICSTRUCTQUEUE
