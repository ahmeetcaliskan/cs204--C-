#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;
int airlineID = 0;                                                 // Global airline and flights ID for constructing data structure , removing and adding flights and airlines
int flightsID = 0;                  

struct flight {
    string from;
    string to;
    int hour;
    int min;
    int price;
    int ID;

    flight* next;
    flight* prev;

    flight(string departure, string arrival, int departureHour, int departureMin, int money) { // FLight struct for read from text file
        from = departure;
        to = arrival;
        hour = departureHour;
        min = departureMin;
        price = money;
    };
    flight(string departure, string arrival, int departureHour, int departureMin, int money, int id, flight* Next, flight* previous) {
        from = departure;
        to = arrival;                                                   //FLight struct for constructing data structure
        hour = departureHour;
        min = departureMin;
        price = money;
        ID = id;
        next = Next;
        prev = previous;
    }
};
struct airline {
    string name;
    int ID;         
    airline* next;
    flight* flightss;

    airline(string Name, int id, airline* nameOfAirline, flight* Flight) {
        name = Name;
        ID = id;
        next = nameOfAirline;
        flightss = Flight;
    }
};


pair<vector<string>, vector<vector<flight>>> read_files(bool input_done) {

    ///READ FLIGHTS///
    vector<string> airlines;
    vector<vector<flight>> flights(100); //start with a previously sized vector or you get seg fault (for sure)

    while (not input_done) {
        string airline_name;
        string filename;
        cout << "Enter the name of airline: ";
        cin >> airline_name;
        cout << "Enter the name of airline file: ";
        cin >> filename;
        ifstream input(filename);

        if (filename == "done") {
            input_done = true;
            return make_pair(airlines, flights);
        }

        while (input.fail()) {
            cout << "Could not open file: " << filename << endl;
            cout << "Enter the name of airline: ";
            cin >> airline_name;
            cout << "Enter the name of airline file: ";
            cin >> filename;
            input.open(filename);

            if (filename == "done") {
                input_done = true;
                return make_pair(airlines, flights);
            }
        }

        airlines.push_back(airline_name);


        cout << "Processing input file: " << filename << endl;

        int line_no = 0;
        vector<string> lines;
        string line;
        int vector_location = airlines.size() - 1;
        while (getline(input, line)) {
            lines.push_back(line);
            line_no += 1;
            if (line_no % 5 == 0) {
                flight a_flight(lines[line_no - 5], lines[line_no - 4], stoi(lines[line_no - 3]), stoi(lines[line_no - 2]), stoi(lines[line_no - 1]));
                flights[vector_location].push_back(a_flight);
            }
        }
    }
    if (input_done) {
        cout << "Input files are already read, however you can do manual changes.." << endl;
    }

    return make_pair(airlines, flights);
}



airline* make_linked_list_structure(vector<string> airlines, vector<vector<flight>> flights) {    // This function double linked data structure with ordered wat    
    int airlineCounter = 0;
    int sizeOfAirlines = airlines.size();
    airline* airlinePtr = nullptr;                            // initiliaztion starts with nullptr
    airline* head = nullptr;
    while (airlineCounter < sizeOfAirlines) {
        int flightcounter = 0;
        int sizeOfFlights = flights[airlineCounter].size();
        flight* flightPtr = nullptr;
        if (airlinePtr == nullptr) {                      //This if situation creates head airline
            head = new airline(airlines[airlineCounter], airlineID, nullptr, nullptr);
            airlinePtr = head;
        }
        else {                                    // Creates other ailrines after head
            airline* node = new airline(airlines[airlineCounter], airlineID, nullptr, nullptr);
            airlinePtr->next = node;
            airlinePtr = airlinePtr->next;
        }
        flight* flightHead = nullptr;
        while (sizeOfFlights > flightcounter) {
            if (flightHead == nullptr) {                                 //adding first flight into airline and set the airline.flightss
                flight* flightNode = new flight(flights[airlineCounter][flightcounter].from, flights[airlineCounter][flightcounter].to, flights[airlineCounter][flightcounter].hour, flights[airlineCounter][flightcounter].min, flights[airlineCounter][flightcounter].price, flightsID, nullptr, nullptr);
                airlinePtr->flightss = flightNode;
                flightHead = flightNode;
            }
            else {
                bool comparisonIsDone = false;                 // while process check with bool and it is useful for quiting after insertion and our new flights record to heap
                flight* tempFlightNode = new flight(flights[airlineCounter][flightcounter].from, flights[airlineCounter][flightcounter].to, flights[airlineCounter][flightcounter].hour, flights[airlineCounter][flightcounter].min, flights[airlineCounter][flightcounter].price, flightsID, nullptr, nullptr);
                flight* flightPtr = flightHead;
                bool endOfList = false;
                while (flightPtr != nullptr && !comparisonIsDone) {
                    if (flightPtr->hour > tempFlightNode->hour || (flightPtr->hour == tempFlightNode->hour && flightPtr->min > tempFlightNode->min)) {
                        if (flightPtr->prev == nullptr) {                 // if new flight is smaller than first one it can be used 
                            tempFlightNode->next = flightPtr;             // add to beginning
                            tempFlightNode->prev = flightPtr->prev;
                            flightPtr->prev = tempFlightNode;
                            airlinePtr->flightss = tempFlightNode;
                            flightHead = tempFlightNode;
                            comparisonIsDone = true;
                        }
                        else {
                            tempFlightNode->next = flightPtr;
                            tempFlightNode->prev = flightPtr->prev;
                            flightPtr->prev->next = tempFlightNode;
                            flightPtr->prev = tempFlightNode;
                            comparisonIsDone = true;

                        }
                    }
                    else if (flightPtr->next == nullptr && comparisonIsDone == false && (flightPtr->hour > tempFlightNode->hour || (flightPtr->hour == tempFlightNode->hour && flightPtr->min > tempFlightNode->min))) {
                        tempFlightNode->prev = flightPtr;
                        flightPtr->next = tempFlightNode;
                        comparisonIsDone = true;
                        endOfList = false;
                    }
                    else if (flightPtr->next == nullptr && comparisonIsDone == false && (flightPtr->hour < tempFlightNode->hour || (flightPtr->hour == tempFlightNode->hour && flightPtr->min < tempFlightNode->min))) {
                        flightPtr->next = tempFlightNode;
                        tempFlightNode->prev = flightPtr;             // this is useful for adidng ennd of the list 
                    }
                    else {
                        flightPtr = flightPtr->next;
                    }
                }


            }
            flightsID++;
            flightcounter++;
        }
        airlineID++;
        airlineCounter++;
    }
    return head;


}


void print_all(airline* head) {
    if (head == nullptr) {                      //This is printing for if whole data structure is deleted 
        cout << "List is empty..." << endl;
    }
    else {
        airline* airlinePtr = head;
        while (airlinePtr != nullptr) {                      //data scanning with airlineptr and flightsptr
            flight* flightsPtr = airlinePtr->flightss;
            cout << "###################################" << endl;
            cout << "### AIRLINE ID: " << airlinePtr->ID << " ###" << endl;
            cout << "NAME: " << airlinePtr->name << endl;
            cout << "FLIGHTS: ";
            while (flightsPtr != nullptr) {                     // printing all flights with a ordered way
                cout << "#[" << flightsPtr->ID << "|" << flightsPtr->from << "->" << flightsPtr->to << "|" << flightsPtr->hour << ":" << flightsPtr->min << "|" << flightsPtr->price << "TRY]#";
                flightsPtr = flightsPtr->next;
            }
            cout << endl;
            airlinePtr = airlinePtr->next;              
        }
    }
}
void remove_flight_with_input(airline* &head) {
    airline* airlinePtr = head;
    flight* flightsPtr = head->flightss;              // detecting deleted flights with airline and flight ptr
    int removeID;
    cout << "Flight id to remove: ";
    cin >> removeID;
    bool removeProcess = false;           //checking the process whether is done or not
    while (airlinePtr != nullptr && removeProcess == false) {
        flight* flightsPtr = airlinePtr->flightss;                
        while (flightsPtr != nullptr && removeProcess == false) {
            if (removeID == flightsPtr->ID && flightsPtr->prev == nullptr && flightsPtr->next == nullptr) {       // this is fro one flight airlines becuase we have to delete airline after the deleting process of flight
                delete flightsPtr;
                removeProcess = true;
                airline* removeAirlinePtr = head;
                bool removeAirline = false;
                while (removeAirline == false && removeAirlinePtr != nullptr) {                        // airline structure is not double linked therefore we need to declare another airline pointer  linked prev and next airlines
                    if (removeAirlinePtr->next == airlinePtr) {
                        removeAirlinePtr->next = airlinePtr->next;
                        delete airlinePtr;
                        removeAirline = true;
                    }
                    removeAirlinePtr = removeAirlinePtr->next;
                }
            } 
            else if (removeID == flightsPtr->ID && flightsPtr->prev == nullptr) {                // this is for deleting from beginning 
                flightsPtr->next->prev = flightsPtr->prev;
                airlinePtr->flightss = flightsPtr->next;
                delete flightsPtr;
                removeProcess = true;
            }
            else if (removeID == flightsPtr->ID && flightsPtr->next == nullptr) {              // this is for deleting from the end
                flightsPtr->prev->next = flightsPtr->next;
                delete flightsPtr;
                removeProcess = true;
            }
            else if (removeID == flightsPtr->ID) {                        // deleting from middle 
                flightsPtr->prev->next = flightsPtr->next;
                flightsPtr->next->prev = flightsPtr->prev;
                delete flightsPtr;
                removeProcess = true;
            }
            flightsPtr = flightsPtr->next;
        }
        airlinePtr = airlinePtr->next;
    }
    if (removeProcess) {                                                              // cout process
        cout << "Flight ID " << removeID << " is removed from the list.." << endl;
    }
    else {
        cout << "Flight ID " << removeID << " is not exist in the list.." << endl;
    }
}
void add_flight_with_input(airline* &head) {
    string newAirline, newFrom, newTo;
    int newHour, newMin, newPrice;
    cout << "Adding manual entry: " << endl << "AIRLINE: ";           // getting flight detials from the user
    cin >> newAirline;
    cout << "FROM: ";
    cin >> newFrom;
    cout << "TO: ";
    cin >> newTo;
    cout << "HOUR: ";
    cin >> newHour;
    cout << "MIN: ";
    cin >> newMin;
    cout << "PRICE: ";
    cin >> newPrice;
    flight* newFlight = new flight(newFrom, newTo, newHour, newMin, newPrice, flightsID, nullptr, nullptr);                 // implement new flight with nullptrs
    
    airline* airlinePtr = head;
    bool additionProces = false;                                // checking the inseertion process done or not
    while (airlinePtr != nullptr && additionProces == false) {
        flight* flightsPtr = airlinePtr->flightss;
        while (airlinePtr->name == newAirline && additionProces == false) {                // check that airline is correct or not 
            while (flightsPtr != nullptr && additionProces == false) {
                if (flightsPtr->prev == nullptr && (flightsPtr->hour > newFlight->hour || (flightsPtr->hour == newFlight->hour && flightsPtr->min > newFlight->min))) {
                    flightsPtr->prev = newFlight;
                    newFlight->next = flightsPtr;
                    airlinePtr->flightss = newFlight;                                              // inserting to the beginning
                    additionProces = true;
                    flightsID++;
                }
                else if (flightsPtr->next == nullptr && (flightsPtr->hour < newFlight->hour || (flightsPtr->hour == newFlight->hour && flightsPtr->min < newFlight->min))) {
                    flightsPtr->next = newFlight;
                    newFlight->prev = flightsPtr;                           //inserting to the end 
                    additionProces = true;
                    flightsID++;
                }
                else if (flightsPtr->hour > newFlight->hour || (flightsPtr->hour == newFlight->hour && flightsPtr->min > newFlight->min)) {
                    flightsPtr->prev->next = newFlight;
                    newFlight->prev = flightsPtr->prev;
                    newFlight->next = flightsPtr;                             //inserting to the middle of the flight list
                    flightsPtr->prev = newFlight;
                    additionProces = true;
                    flightsID++;
                }
                flightsPtr = flightsPtr->next;
            }
        }
        if (airlinePtr->next == nullptr && additionProces == false) {
            airline* createdAirline = new airline(newAirline, airlineID, nullptr, newFlight);    // if airline is not exist, create a new airline and add flight
            airlinePtr->next = createdAirline;
            additionProces = true;
            flightsID++;
            airlineID++;
        }
        else {                                                //  if ptr is not equal with airline move to next ptr
            airlinePtr = airlinePtr->next;
        }
    }
    if (additionProces == true) {                                               
        cout << "Flight ID " << flightsID << " is added to the list..";
    }
}

void pathFinderRecursively(airline* head, string arrival, const string departure, const int maximumTransfer, int  numofTransfers, int flightPrice, int& currentBestPrice, vector<flight*>& path, vector<flight*>& currentPath) { // this recursive function search from arrival and it finish until it find the departure with recusively
    airline* airlinePtr = head;
    while (airlinePtr != nullptr && numofTransfers <= maximumTransfer) {            //data scanning and check  the maximum transfer 
        flight* flightsPtr = airlinePtr->flightss;
        while (flightsPtr != nullptr) {
            if (flightsPtr->to == arrival && flightsPtr->from == departure) {           // if this flight is ending flight process is correct 
                path.push_back(flightsPtr);                                 // adding flight to temp path 
                if (currentBestPrice == 0 || currentBestPrice > flightPrice + flightsPtr->price) {            // check that path is cheaper than other successfull paths
                    currentBestPrice = flightPrice + flightsPtr->price;                  // update price
                    currentPath.clear();                                            // clear the cheapest path then add the temp path variables to cheapest path
                    int InsertionCounter = 0;
                    while(InsertionCounter < path.size()){
                        currentPath.push_back(path[InsertionCounter]);
                        InsertionCounter++;
                    }
                }
                path.pop_back();                                         // delete last part of path and moving other flights
            }
            else if (flightsPtr->to == arrival) {                          // if path flight is found but it is not equal with departure add and move to other recursive funcitomn with updaed variables
                path.push_back(flightsPtr);
                pathFinderRecursively(head, flightsPtr->from, departure, maximumTransfer, numofTransfers + 1, flightPrice + flightsPtr->price, currentBestPrice, path, currentPath);     //recursive function to find other paths with new variables
                path.pop_back();                         // if it can not find delete it 
            }
            flightsPtr = flightsPtr->next;
        }                                                                                                  //move flight and airline
        airlinePtr = airlinePtr->next;
    }
}

int pathfinder(airline* head) {
    string pathDeparture, pathArrival;
    int maxTransfers;
    cout << "Where are you now ?" << endl;                              // adding departure arrival and transfers input from user
    cin >> pathDeparture;
    cout << "Where do you want to go" << endl;
    cin >> pathArrival;
    cout << "Maximum number of transfers: " << endl;
    cin >> maxTransfers;
    int currentTransfers = 0;                     // declaration of recursive function variables 
    int cumulativePrice = 0;
    int bestPrice = 0;
    vector<flight*> bestPath;
    vector<flight*> cumulativePath;
    pathFinderRecursively(head, pathArrival, pathDeparture, maxTransfers, currentTransfers, cumulativePrice, bestPrice, cumulativePath, bestPath);
    if (bestPath.size() == 0) {
        cout << "No path found between " << pathDeparture << " and " << pathArrival;          // if it did not find, print messeage 
    }
    else {
        cout << "##Best price path##" << endl;                                                   // displaying best price path format 
        for (int flightCounter = bestPath.size()-1; flightCounter >= 0; flightCounter--) {
            cout << "[" << bestPath[flightCounter]->ID << "|" << bestPath[flightCounter]->from << "->" << bestPath[flightCounter]->to << "|" << bestPath[flightCounter]->hour << ":" << bestPath[flightCounter]->min << "|" << bestPath[flightCounter]->price << "]->";
            if (flightCounter == 0) {
                cout << "[" << bestPath[flightCounter]->ID << "|" << bestPath[flightCounter]->from << "->" << bestPath[flightCounter]->to << "|" << bestPath[flightCounter]->hour << ":" << bestPath[flightCounter]->min << "|" << bestPath[flightCounter]->price << "] $Total Price:" << bestPrice;
            }
        }
        
    }
    return 0;
}




void deleteAirlineRecursively(airline* &head) {                                     //removing part for airlines
    airline* airlinePtr = head;
    flight* flightPtr = head->flightss;
    while (flightPtr != nullptr) {                                                  //removing part for flights
        flight* deletingFlight = flightPtr;
        flightPtr = flightPtr->next;
        delete deletingFlight;
        deletingFlight = nullptr;                                                    //declariton of deleitng part to nullptr 
    }
    head = head->next;
    delete airlinePtr;
    airlinePtr = nullptr;
    if (head != nullptr) {
        deleteAirlineRecursively(head);
    }
}

void delete_linked_list(airline*& head) {
    airline* airlinePtr = head;
    if (head == nullptr) {                                                // mixed airline remove parts recursively
        cout << "List is empty..";                                        // if it is empty display it 
    }
    else {
        deleteAirlineRecursively(head);                                        // recursive part(that function is above)
    }
}



//
void printMainMenu() {
    cout << endl;
    cout << "I***********************************************I" << endl
        << "I               0 - DELETE DATA                 I" << endl
        << "I               1 - READ FILES                  I" << endl
        << "I               2 - PRINT ALL FLIGHTS           I" << endl
        << "I               3 - ADD FLIGHT                  I" << endl
        << "I               4 - REMOVE FLIGHT               I" << endl
        << "I               5 - PATH FINDER                 I" << endl
        << "I               6 - EXIT                        I" << endl
        << "I***********************************************I" << endl
        << ">>";
    cout << endl;
}

void processMainMenu() {

    pair<vector<string>, vector<vector<flight>>> lines_flights;
    airline* head = nullptr;
    bool input_done = false;

    char input;
    do {
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        switch (input) {
        case '0':
            cout << "Commented out functionalities are going to be implemented" << endl;
            delete_linked_list(head);
            cout << "Data is deleted!" << endl;
            input_done = false;
            break;
        case '1':
            if (!input_done) {
                lines_flights = read_files(input_done);
                head = make_linked_list_structure(lines_flights.first, lines_flights.second);
                cout << "Files are read.." << endl;
            }
            else {
                cout << "Files are already read.." << endl;
            }
            input_done = true;
            break;
        case '2':
            cout << "Commented out functionalities are going to be implemented" << endl;
            print_all(head);
            break;
        case '3':
            cout << "Commented out functionalities are going to be implemented" << endl;
            add_flight_with_input(head);
            break;
        case '4':
            cout << "Commented out functionalities are going to be implemented" << endl;
            remove_flight_with_input(head);
            break;
        case '5':
            cout << "Commented out functionalities are going to be implemented" << endl;
            pathfinder(head);
            break;
        case '6':
            cout << "Exiting.." << endl;
            exit(0);
        default:
            cout << "Invalid option: please enter again" << endl;
        }
    } while (true);
}
//


int main() {

    processMainMenu();
    //Comply with the provided structs and specified linked list structure for a seamless grading

    return 0;

}
