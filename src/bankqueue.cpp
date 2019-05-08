#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// define the time data type
#define TimeType int

// define constants used in our simulation
#define TEST_SIZE 15
#define NUM_NAMES 15
string firstNames[NUM_NAMES] =
    { "Alice", "Ambroise", "Bert", "Denise", "Larry", "Emily" , "John", "Charlie", "Dean", "Eli", "Fabian", "Gary", "Harry", "Ian", "Kevin"};
string lastNames[NUM_NAMES] =
    { "Ghosh", "Jones", "Lee", "Smith", "Zhang", "Zuckerman" , "Wick", "Austin", "James", "Sorensen", "Rodriguez", "Lineker", "Potter", "McKellen", "Costner"};
#define SIM_LENGTH 100
#define MAX_DURATION 20
#define NUM_TELLERS 2

// define event types
typedef enum { ARRIVAL, DEPARTURE } EventType;

// define an event struct to store events
typedef struct {
	string customerName;
	TimeType eventTime;
	TimeType duration;
	EventType event;
	TimeType waitTime;
} EventStruct;

// a standard way of printing events
void printEvent(const EventStruct & event)
{
	cout << event.customerName;
	cout << ", Time: " << event.eventTime;
	cout << ", Duration: " << event.duration;
	cout << ", Event type: ";
	if (event.event == ARRIVAL)
		cout << "ARRIVAL";
	else
		cout << "DEPARTURE";
}

// how to compare event times for the priority queue
struct compareEventTime {
	bool operator() (const EventStruct & lhs, const EventStruct & rhs)const {
		return lhs.eventTime > rhs.eventTime;
}};

// our Discrete Event Simulation class
class DESim {
private:
	// event queue -- priority queue with events queued by event time
	priority_queue < EventStruct, vector < EventStruct >,
	    compareEventTime > eventQueue;
	// wait queue -- priority queue with waiting customers queued by arrival time
	queue < EventStruct > bankQueue;
	TimeType currentTime = 0;
	bool debugOn = false;
	int tellersAvailable = NUM_TELLERS;
public:
	void addEvent(EventStruct & event);
	void addBankQueueCustomer(EventStruct & event);
	void setDebugOn(bool value) {
		debugOn = value;
	};
	void printTellerNumberChange();
	void runSim();
};				// end DESim

// add a priority queue event
void DESim::addEvent(EventStruct & event)
{
	if (debugOn) {
		cout << "[" << currentTime << "] Adding event: ";
		printEvent(event);
		cout << endl;
	}
	eventQueue.push(event);
}

// add a bank queue customer (not really an event)
void DESim::addBankQueueCustomer(EventStruct & event)
{
	if (debugOn) {
		cout << "[" << currentTime << "] Adding bank queue customer: ";
		printEvent(event);
		cout << endl;
	}
	bankQueue.push(event);
	event.waitTime = currentTime;
}

// indicate that the number of available tellers has changed
void DESim::printTellerNumberChange()
{
	if (debugOn) {
		cout << "[" << currentTime <<
		    "] Current number of tellers available: " <<
		    tellersAvailable << endl;
	}
}

// run the simulation
void DESim::runSim()
{
	while (!eventQueue.empty()) {
		EventStruct nextEvent = eventQueue.top();	// get next event in priority queue
		currentTime = nextEvent.eventTime;
		eventQueue.pop();
		switch (nextEvent.event) {
		case ARRIVAL:
			if (tellersAvailable) {
				// enter departure event in eventQueue
				nextEvent.eventTime =
				    currentTime + nextEvent.duration;
				nextEvent.event = DEPARTURE;
				addEvent(nextEvent);
				tellersAvailable--;
				printTellerNumberChange();
			} else {
				// no tellers available, put customer in bank queue
				addBankQueueCustomer(nextEvent);
			}
			break;
		case DEPARTURE:
			if (!bankQueue.empty()) {
				EventStruct nextCustomer = bankQueue.front();
				bankQueue.pop();
				nextCustomer.eventTime =
				    currentTime + nextCustomer.duration;
				nextCustomer.event = DEPARTURE;
				addEvent(nextCustomer);
			} else {
				tellersAvailable++;
				printTellerNumberChange();
			}
			break;
		default:
			cout << "ERROR: Should never get here! " << endl;
		}
	}
}

int main()
{
	cout << "*** Discrete Event Simulation Example for ECE 2574 ***\n\n";
	DESim mySim;
	mySim.setDebugOn(true);
	EventStruct myEvent;
	srand(123321);
	cout << "Adding " << TEST_SIZE << " events.\n\n";
	for (int i = 0; i < TEST_SIZE; i++) {
		myEvent.customerName =
		    firstNames[i] + string(" ")
		    + lastNames[i];
		myEvent.eventTime = rand() % SIM_LENGTH + 1;
		myEvent.duration = rand() % MAX_DURATION + 1;
		myEvent.event = ARRIVAL;
		mySim.addEvent(myEvent);
	}
	cout << "\nRunning simulation...\n";
	mySim.runSim();
	return 0;
}
