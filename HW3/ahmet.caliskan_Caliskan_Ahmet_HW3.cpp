#include "DynamicStructQueue.h"
#include "DynamicStringStack.h"
#include "StaticStructQueue.h"
#include "DynamicStack.h"

#include <iostream>
#include <fstream>       // for ifstream
#include <cctype>
#include <string>
#include <vector>
#include <sstream>      // std::stringstream

using namespace std;

//********************************************************************
// Implementation of the DynamicStructQueue class
//********************************************************************
DynStructQueue::DynStructQueue()
{
	front = nullptr;
	rear = nullptr;
}

bool DynStructQueue::isEmpty() const
{
	// Check if the queue is empty
	if (front == nullptr)
		return true;
	else
		return false;
}

void DynStructQueue::enqueue(int num, int bill, string name, string functionName)
{
	if (isEmpty())
	{
		// If the queue is empty, create a new node and set front and rear to it
		front = new QueueNode(num, bill, name, functionName, nullptr);
		rear = front;
	}
	else
	{
		// If the queue is not empty, add a new node to the rear
		rear->next = new QueueNode(num, bill, name, functionName, nullptr);
		rear = rear->next;
	}
}

void DynStructQueue::dequeue(QueueNode*& student)
{
	if (isEmpty())
	{
		// If trying to dequeue from an empty queue, display an error message and exit
		cout << "Attempting to dequeue on an empty queue, exiting program...\n";
		exit(1);
	}
	else
	{
		// Dequeue by updating front and returning the removed node
		student = front;
		front = front->next;
	}
}

void DynStructQueue::clear()
{
	// Clear the queue by dequeuing all nodes until the queue is empty
	QueueNode* value;
	while (!isEmpty())
		dequeue(value);
}
//********************************************************************

//********************************************************************
// Implementation of the DynamicStack class
//********************************************************************
DynamicStack::DynamicStack()
{
	top = nullptr;
}

StackNodee* DynamicStack::getStackTop()
{
	return top;
}

bool DynamicStack::isEmpty(void)
{
	// Check if the stack is empty
	bool status;
	if (top == nullptr)
		status = true;
	else
		status = false;
	return status;
}

void DynamicStack::pushStack(string value)
{
	// Push a new node onto the stack
	StackNodee* newNode;
	newNode = new StackNodee;
	newNode->data = value;
	if (isEmpty())
	{
		top = newNode;
		newNode->next = nullptr;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}

void DynamicStack::pop(string functionName)
{
	cout << functionName << " is finished. Clearing the stack from its data..." << endl;
	StackNodee* temp = getStackTop();
	while (temp != nullptr && temp->data.substr(0, 10) == functionName)
	{
		temp = top->next;
		delete top;
		top = temp;
	}
}
//********************************************************************

//********************************************************************
// Implementation of the DynamicStringStack class
//********************************************************************
DynamicStringStack::DynamicStringStack()
{
	head = nullptr;
}

FunctionNode* DynamicStringStack::getTheTop()
{
	return head;
}

CommandNode* DynamicStringStack::getCommand(FunctionNode* head)
{
	return head->commands;
}

bool DynamicStringStack::isEmpty()
{
	// Check if the stack is empty
	bool status;

	if (head == nullptr)
		status = true;
	else
		status = false;

	return status;
}

void DynamicStringStack::pushCommand(string elmt, FunctionNode* function)
{
	// Push a new command node onto the stack
	CommandNode* newNode;
	newNode = new CommandNode;
	newNode->value = elmt;

	if (function->commands == nullptr)
	{
		newNode->nextCommand = nullptr;
		function->commands = newNode;
	}
	else
	{
		CommandNode* ptr = function->commands;
		while (ptr->nextCommand != nullptr)
		{
			ptr = ptr->nextCommand;
		}
		ptr->nextCommand = newNode;
		newNode->nextCommand = nullptr;
	}
}

FunctionNode* DynamicStringStack::pushFunction(string elmt, DynamicStringStack& databese)
{
	// Push a new function node onto the stack
	FunctionNode* newFunctionNode;
	newFunctionNode = new FunctionNode;
	newFunctionNode->value = elmt;

	if (isEmpty())
	{
		newFunctionNode->commands = nullptr;
		newFunctionNode->functions = nullptr;
		head = newFunctionNode;
	}
	else
	{
		FunctionNode* ptr = head;
		while (ptr->functions != nullptr)
		{
			ptr = ptr->functions;
		}
		ptr->functions = newFunctionNode;
		newFunctionNode->commands = nullptr;
		newFunctionNode->functions = nullptr;
	}
	return newFunctionNode;
}
//********************************************************************

//********************************************************************
// Implementation of the StructQueue class
//********************************************************************
StructQueue::StructQueue(int s)
{
	queueArray = new StringQueueNode[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

bool StructQueue::isFull() const
{
	// Check if the queue is full
	if (numItems < queueSize)
		return false;
	else
		return true;
}

bool StructQueue::isEmpty() const
{
	// Check if the queue is empty
	if (numItems > 0)
		return false;
	else
		return true;
}

void StructQueue::enqueue(int num, string name, string functionName)
{
	if (isFull())
	{
		// If the queue is full, display a message that the enqueue operation cannot be performed
		cout << "The queue is full. " << num << " not enqueued\n";
	}
	else
	{
		// Enqueue by updating rear and adding a new node
		rear = (rear + 1) % queueSize;
		queueArray[rear] = StringQueueNode(num, name, functionName);
		numItems++;
	}
}

void StructQueue::dequeue(StringQueueNode& num)
{
	if (isEmpty())
	{
		// If trying to dequeue from an empty queue, display an error message and exit
		cout << "Attempting to dequeue on an empty queue, exiting program...\n";
		exit(1);
	}
	else
	{
		// Dequeue by updating front and returning the removed node
		front = (front + 1) % queueSize;
		num = queueArray[front];
		numItems--;
	}
}

void StructQueue::clear()
{
	// Clear the queue by resetting front, rear, and numItems
	front = -1;
	rear = -1;
	numItems = 0;
}
//********************************************************
void pushRequests(int id, int prize, string name, string function, RequestNode* &head)      // Push all requests in prdered way for students and instructors
{
	bool isFound = false;
	RequestNode* foundPtr = head;
	while (foundPtr != nullptr && isFound == false) {
		if (foundPtr->ID == id) {
			isFound = true;
		}
		foundPtr = foundPtr->next;
	}
	RequestNode* newNode;
	newNode = new RequestNode(id, prize, name, function);
	if (head == nullptr)
	{
		head = newNode;
	}
	else if(isFound == false)
	{
		RequestNode* ptr = head;
		while (ptr->next != nullptr) {
			ptr = ptr->next;
		}
		ptr->next = newNode;
	}
}

RequestNode* findPerson(RequestNode* head, int id) {         // find student or instructor while workload for updating their bill
	RequestNode* ptr = head;
	while (ptr->ID != id) {
		ptr = ptr->next;
	}
	return ptr;
}



void addInstructorWorkload(DynamicStringStack databese, StructQueue& instructorsQueue, RequestNode* &head) { //adding to workload function for instructors. 
	string functionName;
	cout << "Add a service(function) that the instructor wants to use :" << endl;
	cin >> functionName;
	FunctionNode* functionPtr = databese.getTheTop();
	bool functionFound = false;
	while(functionPtr != nullptr && !functionFound){
		if (functionPtr->value == functionName) {
			string InstructorName;
			int ID;
			cout << "Give instructor's name: ";
			cin >> InstructorName;
			cout << "Give instructor's ID (an int): ";
			cin >> ID;
			cout << "Prof." << InstructorName << "'s service request of " << functionName << endl << "has been put in the instructor's queue.";
			instructorsQueue.enqueue(ID, InstructorName, functionName);
			pushRequests(ID, 0, InstructorName, functionName, head);
			functionFound = true;
		}
		functionPtr = functionPtr->functions;
	}
	if (functionPtr == nullptr && !functionFound) {
		cout << "The requested service (function) does not exist.";
	}

}

void addStudentWorkload(DynamicStringStack databese, DynStructQueue& studentsQueue, RequestNode* &head) {
	string functionName;
	cout << "Add a service(function) that the student wants to use :" << endl;            //adding to workload function for students.
	cin >> functionName;
	FunctionNode* functionPtr = databese.getTheTop();
	bool functionFound = false;
	while (functionPtr != nullptr && !functionFound) {
		if (functionPtr->value == functionName) {
			string StudentName;
			int ID;
			cout << "Give student's name: ";
			cin >> StudentName;
			cout << "Give student's ID (an int): ";
			cin >> ID;
			cout << StudentName << "'s service request of " << functionName << "has been put in the student's queue.";
			studentsQueue.enqueue(ID, 0, StudentName, functionName);
			pushRequests(ID, 0, StudentName, functionName, head);
			functionFound = true;
		}
		functionPtr = functionPtr->functions;
	}
	if (functionPtr == nullptr && functionFound == false) {
		cout << "The requested service (function) does not exist.";
	}
}

void displayUsers(RequestNode* & wholeRequests)                 //displayin student instructors and thier prices
{
	RequestNode* ptr = wholeRequests;
	if (ptr == nullptr) {
		cout << "No payments defined." << endl;
	}
	while (ptr != nullptr) {
		cout << "Name: " << ptr->name << " ID: " << ptr->ID << " " << ptr->price << " TRY" << endl;
		ptr = ptr->next;
	}
}
void printStack(StackNodee* stackHead, StackNodee* stackPtr, string functionName) {          //printing stack for workload funciton in recursive way
	if (stackHead == nullptr) {
		cout << "The stack is empty" << endl;
	}
	else {
		if (stackHead == stackPtr) {
		cout << "Executing print stack; command from " << functionName << endl << "PRINTING THE STACK TRACE :" << endl;
		}
		if (stackPtr->next != nullptr) {
			printStack(stackHead, stackPtr->next, functionName);
		}
		cout << stackPtr->data << ";" << endl;

	}	
}

void processWorkload(StringQueueNode instructor, FunctionNode* &function, RequestNode* & requestPtr, DynamicStringStack& databese, DynamicStack& stack) {
	CommandNode* commandPtr;                                      //process workload function for instructors. it is overloaded verison of main workload function
	commandPtr = databese.getCommand(function);
	while (commandPtr != nullptr) {
		stringstream ss(commandPtr->value);
		string first, second;
		ss >> first >> second;
		if (first == "define") {
			requestPtr->price += 1;
			StackNodee* valuePtr = stack.getStackTop();
			stack.pushStack(function->value + ": " + commandPtr->value);
		}
		else if (first == "print") {
			requestPtr->price += 2;
			printStack(stack.getStackTop(), stack.getStackTop(), function->value);
		}
		else if (first == "call") {
			requestPtr->price += 5;
			cout << "Calling " << second.substr(0, second.length()) << " from " << function->value << endl;
			FunctionNode* checkFunction = function;
			if (checkFunction->functions != nullptr && checkFunction->functions->value == second) {
				processWorkload(instructor, function->functions, requestPtr, databese, stack);
				stack.pop(function->functions->value);
			}
		}
		commandPtr = commandPtr->nextCommand;
	} 
}

void processWorkload(QueueNode *student, FunctionNode* &function, RequestNode* &requestPtr, DynamicStringStack& databese, DynamicStack& stack) {
	CommandNode* commandPtr;                            //process workload function for students. it is overloaded verison of main workload function
	commandPtr = databese.getCommand(function);
	while (commandPtr != nullptr) {
		stringstream ss(commandPtr->value);
		string first, second;
		ss >> first >> second;
		if (first == "define") {
			requestPtr->price += 1;
			StackNodee* valuePtr = stack.getStackTop();
			stack.pushStack(function->value + ": " + commandPtr->value);
		}
		else if (first == "print") {
			requestPtr->price += 2;
			printStack(stack.getStackTop(), stack.getStackTop(), function->value);
		}
		else if (first == "call") {
			requestPtr->price += 5;
			cout << "Calling " << second.substr(0, second.length()) << " from " << function->value << endl;
			FunctionNode* checkFunction = function;
			if (checkFunction->functions != nullptr && checkFunction->functions->value == second) {
				processWorkload(student, function->functions, requestPtr, databese, stack);
				stack.pop(function->functions->value);
			}
		}
		commandPtr = commandPtr->nextCommand;
	}
}


void processWorkload(DynStructQueue& studentsQueue, StructQueue & instructorsQueue, RequestNode* &head, DynamicStringStack& databese, DynamicStack& stack, int & counter)
{
	if (!instructorsQueue.isEmpty() && counter < 10)
	{                                                    //main workload function it consists itself and its overloads
		StringQueueNode instructor;
		cout << "Processing instructors queue..." << endl;
		instructorsQueue.dequeue(instructor);
		RequestNode* requestPtr = head;
		while (requestPtr->ID != instructor.ID) {
			requestPtr = requestPtr->next;
		}
		FunctionNode* functionPtr = databese.getTheTop();
		while (functionPtr->value != instructor.function) {
			functionPtr = functionPtr->functions;
		}
		cout << "Processing " << instructor.name << "'s request (with ID " << instructor.ID << ") of service (function):\n" << instructor.function << endl;
		cout << "-------------------------------------------------------" << endl;
		CommandNode* commandPtr;
		commandPtr = databese.getCommand(functionPtr);
 		while (commandPtr != nullptr) {
			stringstream ss(commandPtr->value);
			string first, second;
			ss >> first >> second;
			if (first == "define") {
				requestPtr->price += 1;
				StackNodee* valuePtr = stack.getStackTop();
				stack.pushStack(functionPtr->value + ": " + commandPtr->value);
			}
			else if (first == "print") {
				requestPtr->price += 2;
				printStack(stack.getStackTop(), stack.getStackTop(), functionPtr->value);
			}
			else if (first == "call") {
				requestPtr->price += 5;
				cout << "Calling " << functionPtr->value << " from " << second.substr(0, second.length()) << endl;
				FunctionNode* checkFunction = functionPtr;
				if (checkFunction->functions != nullptr && checkFunction->functions->value == second) {
					processWorkload(instructor, functionPtr->functions, requestPtr, databese, stack);
					stack.pop(functionPtr->functions->value);
				}	
			}
			commandPtr = commandPtr->nextCommand;
		}
		stack.pop(functionPtr->value);
		cout << "GOING BACK TO MAIN MENU" << endl;
		counter++;
	}
	else if (!studentsQueue.isEmpty())
	{
		if (counter == 10) {
			cout << "10 instructors are served. Taking 1 student from the queue..." << endl;
		}
		else {
			cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
		}
		counter = 1;
		QueueNode *student;
		cout << "Processing instructors queue..." << endl;
		studentsQueue.dequeue(student);
		RequestNode* requestPtr = head;
		while (requestPtr->ID != student->value) {
			requestPtr = requestPtr->next;
		}
		FunctionNode* functionPtr = databese.getTheTop();
		while (functionPtr->value != student->functionName) {
			functionPtr = functionPtr->functions;
		}
		cout << "Processing " << student->name << "'s request (with ID " << student->value << ") of service (function):\n" << student->functionName << endl;
		cout << "-------------------------------------------------------" << endl;
		CommandNode* commandPtr;
		commandPtr = databese.getCommand(functionPtr);
		while (commandPtr != nullptr) {
			stringstream ss(commandPtr->value);
			string first, second;
			ss >> first >> second;
			if (first == "define") {
				requestPtr->price += 1;
				StackNodee* valuePtr = stack.getStackTop();
				stack.pushStack(functionPtr->value + ": " + commandPtr->value);
			}
			else if (first == "print") {
				requestPtr->price += 2;
				printStack(stack.getStackTop(), stack.getStackTop(), functionPtr->value);
			}
			else if (first == "call") {
				requestPtr->price += 5;
				cout << "Calling " << functionPtr->value << " from " << second.substr(0, second.length()) << endl;
				FunctionNode* checkFunction = functionPtr;
				if (checkFunction->functions != nullptr && checkFunction->functions->value == second) {
					processWorkload(student, functionPtr->functions, requestPtr, databese, stack);
					stack.pop(functionPtr->functions->value);
				}
			}
			commandPtr = commandPtr->nextCommand;
		}
		stack.pop(functionPtr->value);
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else
	{
		cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
	}
}

DynamicStringStack creatingDatabese(DynamicStringStack & inputfiles, ifstream &openfile) {
	FunctionNode* currentFunction = nullptr;
	string lines;                                                              //creating databases and shaping for putting witihout their last chars
	while (getline(openfile, lines)) {
		if (lines[lines.length() - 1] == ':') {			
			currentFunction = inputfiles.pushFunction(lines.substr(0, lines.length()-1), inputfiles);
		}
		else if (lines[lines.length() - 1] == ';') {
			inputfiles.pushCommand(lines.substr(0, lines.length() - 1), currentFunction);
		}
	}
	return inputfiles;
	
}


void displayFunctions(DynamicStringStack databese) {                              //displaiyng input functions
	cout << "------------------------------------------------------------------" << endl << "PRINTING AVAILABLE SERVICES(FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl << "------------------------------------------------------------------" << endl << endl << endl;
	FunctionNode* head = databese.getTheTop();
	FunctionNode* function = head;
	while (function != nullptr) {
		cout << function->value << ":" << endl;
		CommandNode* command = function->commands;
		while (command->nextCommand != nullptr) {
			cout << command->value << ";, ";
			command = command->nextCommand;
		}
		cout << command->value << "." << endl;
		command = command->nextCommand;
		function = function->functions;
	}
}

DynamicStringStack InputProcess(DynamicStringStack& functionDatabese, bool & error) {
	int counter = 0;                         //gettinf input from user 
	ifstream openFile;
	string fileName;
	bool processIsdone = false;
	do {
		string input, fileName;
		if (counter == 0) {
			string input;
			cout << "If you want to open a service(function) defining file," << endl << "then press(Y / y) for 'yes', otherwise press any single key" << endl;
			cin >> input;
			if (!(input == "y" || input == "Y")) {
				displayFunctions(functionDatabese);
				processIsdone = true;
			}
			else {
				cout << "Enter the input file name" << endl;
				cin >> fileName;
				openFile.open(fileName);
				if (openFile.fail()) {
					cout << "Could not open the file " << fileName << endl;
					error = true;
				}
				else {
					creatingDatabese(functionDatabese, openFile);
					openFile.close();
				}
			}	
		}
		else if(!processIsdone && !error) {
			string input;
			cout << "Do you want to open another service defining file?" << endl << "Press (Y/y) for 'yes', otherwise press anykey" << endl;
			cin >> input;
			if (!(input == "y" || input == "Y")) {
				displayFunctions(functionDatabese);
				processIsdone = true;
			}
			cout << "Enter the input file name" << endl; /*Importing input from user*/
			cin >> fileName;
			openFile.open(fileName);                    /*Input check process with if condition*/
			if (openFile.fail()) {
				cout << "Could not open the file " << fileName << endl;
				error = true;
			}
			else {
				creatingDatabese(functionDatabese, openFile);
				openFile.close();
			}
		}
	} while (openFile.fail() && !processIsdone && !error);
	return functionDatabese;
}




int main()
{
	bool error = false;
	int counter = 0;
	DynamicStack stack;                      // whole variables for executing functions in main
	DynamicStringStack database;
	DynStructQueue studentsQueue;
	RequestNode* wholeRequests = nullptr;
	StructQueue instructorsQueue(10);
	database = InputProcess(database,error);
	while (true && !error) {
		cout << endl;
		cout << "**********************************************************************" << endl
			<< "**************** 0 - EXIT PROGRAM                        *************" << endl
			<< "**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************" << endl
			<< "**************** 2 - ADD A STUDENT SERVICE REQUEST       *************" << endl
			<< "**************** 3 - SERVE (PROCESS) A REQUEST           *************" << endl
			<< "**************** 4 - DISPLAY USER PAYMENTS               *************" << endl
			<< "**********************************************************************" << endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "PROGRAM EXITING ... " << endl;
			exit(0);
		case 1:
			addInstructorWorkload(database, instructorsQueue, wholeRequests);
			break;
		case 2:
			addStudentWorkload(database, studentsQueue, wholeRequests);
			break;
		case 3:
			processWorkload(studentsQueue, instructorsQueue, wholeRequests, database, stack, counter);
			break;
		case 4:
			displayUsers(wholeRequests);
			break;
		default:
			cout << "INVALID OPTION!!! Try again" << endl;
		}
	}
	return 0;
}