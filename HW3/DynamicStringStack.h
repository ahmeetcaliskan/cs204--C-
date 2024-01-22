#include <iostream>
#include <string>

using namespace std;

struct CommandNode
{
	string value;
	CommandNode* nextCommand;
	CommandNode(){}
	CommandNode(string Value, CommandNode* ptr) {
		nextCommand = ptr;
		value = Value;
	}
};

struct FunctionNode {
	string value;
	CommandNode* commands;
	FunctionNode* functions;

};


struct RequestNode {
	string name;
	string Function;
	int ID;
	int price;
	RequestNode* next;
	RequestNode(int id, int bill, string Name, string function) {
		ID = id;
		price = bill;
		name = Name;
		Function = function;
		next = nullptr;
	}
};

class DynamicStringStack
{
private:
	FunctionNode* head;
	 
public:
	DynamicStringStack(void);
	FunctionNode* getTheTop();
	CommandNode* getCommand(FunctionNode*);
	void pushCommand(string, FunctionNode*);
	FunctionNode* pushFunction(string, DynamicStringStack&);
	void pop(string&);
	bool isEmpty(void);
};
