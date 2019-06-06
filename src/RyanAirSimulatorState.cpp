#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include <queue>
#include <jni.h>
#include <random>
#include <sstream>
#include "include/jnisimulator_RyanAirWrapper.h"

using namespace std;

//define the global time data type
//#define TimeType double
typedef double TimeType;

//define constantsRyanAir
//const int TEST_SIZE = 15;
//const int NUM_TASKS = 6;
//const int NUM_NAMES = 15;
const TimeType THRESHOLD = 400.0;
//some strings
//string firstNames[NUM_TASKS] = {"Task","Task","Task","Task","Task","Task"};
//string lastNames[NUM_NAMES] = {"1","2","3","4","5","6"};
//
//string firstNames[NUM_NAMES] =
//    { "Alice", "Bill", "Jeff", "Susan", "Larry", "Emily" , "John", "Charlie", "Dean", "Eli", "Fabian", "Gary", "Harry", "Ian", "Kevin"};
//string lastNames[NUM_NAMES] =
//    { "Johnson", "Gates", "Bezos", "Wojcicki", "Ellison", "Adams" , "Wick", "Austin", "James", "Sorensen", "Rodriguez", "Lineker", "Potter", "McKellen", "Costner"};

const int SIM_LENGTH = 100;
const int MAX_DURATION = 12;
const int NUM_SERVERS = 2;
// AVG_INTERARRIVAL_TIME -> 0 = "udskyder" tidspunktet hvor size() = 0
const double AVG_INTERARRIVAL_TIME = 5.0;
const double RATE_EXP = 1.0 / AVG_INTERARRIVAL_TIME;
int serversAvailable = NUM_SERVERS;
//TimeType GT = 0.0;
//TimeType simulatedTime = 0.0;

//define event types
enum EventType {ARRIVAL, SERVED};

//define an event struct to store events
struct EventStruct {
    int taskPriority;
    string taskName;
    TimeType eventTime;
    TimeType duration;
    EventType event;
    TimeType waitTime;
};

//function to print events
void printEvent(const EventStruct& event) {
   // cout << event.taskName;
   // cout << ", Time: " << event.eventTime;
   // cout << ", Duration: " << event.duration;
   // cout << ", Event type: ";
   // if (event.event == ARRIVAL) cout << "ARRIVAL";
   // else cout << "SERVED";
}

//compare event times for list
struct compareEventTime {
    bool operator()(const EventStruct& lhs, const EventStruct& rhs) const {
        return lhs.taskPriority < rhs.taskPriority && lhs.eventTime > rhs.eventTime;
	// lhs.eventTime > rhs.eventTime;
    }
};

class RyanAirSimulatorState {
private:
    //event queue: pq with events queued by event time
    priority_queue<EventStruct, vector<EventStruct>, compareEventTime> eventQ;
    //wait queue: q with waiting tasks queued by arrival time
    queue<EventStruct> serverQueue;
    TimeType GT = 0.0;
    bool debugger = false;
    //int serversAvailable = NUM_SERVERS;
public:
    //TimeType GT = 0.0;
    void addEvent(EventStruct & event);
    void addServerQueueTask(EventStruct & event);
    void activateDebug(bool val) { debugger = val; };
    void printServerNumberChange();
    void scheduleArrivedEvent(EventStruct & currentEvent);
    void scheduleServedEvent();
    void runSim();
    double getGT(void);
    void setGT(double cur_time);
    int getSizeOfQ();
    int getSizeOfWQ();
    void resetQ();
    double sampleInterarrivalTime();
    string genTaskNumber();
    string genPremiumTaskNumber();
}; //end ServerSimulatorState

RyanAirSimulatorState servsim;

void RyanAirSimulatorState::addEvent(EventStruct & event) {
    if (debugger) {
    //    cout << "[" << GT << "] Adding event: ";
        printEvent(event);
   //     cout << endl;
    }
    eventQ.push(event);
}

void RyanAirSimulatorState::addServerQueueTask(EventStruct & event) {
    if (debugger) {
     //   cout << "[" << GT << "] Adding server queue task: ";
        printEvent(event);
     //   cout << endl;
    }
    event.waitTime = GT;
    serverQueue.push(event);
}

void RyanAirSimulatorState::printServerNumberChange() {
    if (debugger) {
     //   cout << "[" << GT << "] Current number of servers available: " << serversAvailable << endl;
    }
}

// add EventStruct & to be parsed?
void RyanAirSimulatorState::scheduleArrivedEvent(EventStruct & currentEvent) {
	EventStruct futureEvent;
	futureEvent.eventTime = servsim.getGT() + currentEvent.duration;
	futureEvent.event = SERVED;
	futureEvent.taskName = currentEvent.taskName;
	addEvent(futureEvent);
	serversAvailable--;
	printServerNumberChange();
}

void RyanAirSimulatorState::scheduleServedEvent() {
	EventStruct nextTask = serverQueue.front();
	serverQueue.pop(); //fix below as done above
	nextTask.eventTime = servsim.getGT() + nextTask.duration;
	//servsim.setGT(nextTask.eventTime = GT + nextEvent.duration);
	nextTask.event = SERVED;
	addEvent(nextTask);
}

string RyanAirSimulatorState::genTaskNumber() {
	int taskNumber = rand() % 100 + 1;
	ostringstream str1;
	str1 << taskNumber;
	return str1.str();
}

string RyanAirSimulatorState::genPremiumTaskNumber() {
	int premiumTaskNumber = rand() % 100 + 1;
	ostringstream str2;
	str2 << premiumTaskNumber;
	return str2.str();
}


double RyanAirSimulatorState::sampleInterarrivalTime() {
	double sample_x = ((jdouble) rand()) / (RAND_MAX); // rand: random number between 0 to RAND_MAX. sample_x: random number between 0 and 1
	return -(log(sample_x))  / RATE_EXP;  // log(1) = 0, log(2) = 0.69, 0/0.1 = 0, 0.69/0.1 = 6.9 -> 0 to -6.9
}

void RyanAirSimulatorState::runSim() {
	// try to move if-statement at nextArrival and see if it works.
	// It doesn't work. It will pop until size = 1 and then stop instead of 0.
	if(servsim.getGT() >= THRESHOLD && eventQ.size() > 0) {
		eventQ.pop();
	}
	if (!eventQ.empty() && servsim.getGT() < THRESHOLD) {
        EventStruct currentEvent = eventQ.top();
        servsim.setGT(currentEvent.eventTime);
        eventQ.pop();
        switch (currentEvent.event) {
        case ARRIVAL:
        	{ //when a task arrives, schedule arrival of new task and serve task
				if (serversAvailable) {
					scheduleArrivedEvent(currentEvent);
					//EventStruct servedEvent;
					//servsim.setGT(servedEvent.eventTime = GT + nextEvent.duration);
					// Put the following lines in a function and invoke instead. Call it scheduleServedEvent(currentEvent). Don't do a static method, instance method instead.
					
					
					//string("Task ") + servsim.genTaskNumber();
					//futureEvent.duration = rand() % MAX_DURATION + 1;

					//nextEvent.eventTime = GT + nextEvent.duration;
					//nextEvent.event = SERVED;
					//addEvent(nextEvent);

				} else {
					//no servers available
					addServerQueueTask(currentEvent);
				}
				//create an event that represents the arrival of the new task, add event to addEvent
				// add if here
				EventStruct nextArrival;
				nextArrival.eventTime = servsim.getGT() + servsim.sampleInterarrivalTime();
				nextArrival.event = ARRIVAL;
				nextArrival.duration = rand() % MAX_DURATION + 1;
				nextArrival.taskName = string("Task ") + servsim.genTaskNumber();
				addEvent(nextArrival);
        	}
            break;
        case SERVED:
        	{
				if(!serverQueue.empty()) {
					// Call scheduleServedEvent(currentEvent). Don't do a static method, instance method instead.
					scheduleServedEvent();
					
				} else {
					serversAvailable++;
					printServerNumberChange();
				}
        	}
				break;
        default:
        	cout << "ERROR: default should never be reached" << endl;
        }
    }

}

void RyanAirSimulatorState::setGT(double cur_time) {
	GT = cur_time;
}

double RyanAirSimulatorState::getGT() {
    return GT;
}

int RyanAirSimulatorState::getSizeOfWQ() {
  return serverQueue.size();
}

int RyanAirSimulatorState::getSizeOfQ() {
  return eventQ.size();
}

void RyanAirSimulatorState::resetQ() {
	eventQ = priority_queue<EventStruct, vector<EventStruct>, compareEventTime> ();
	serverQueue = queue<EventStruct> ();
	serversAvailable = NUM_SERVERS;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_RyanAirWrapper_getTime(JNIEnv *env, jobject obj) { //advanceTime
	return servsim.getGT();
}

JNIEXPORT void JNICALL Java_jnisimulator_RyanAirWrapper_performOneStepOfSimulation(JNIEnv *env, jobject obj) {
	servsim.runSim();
}

JNIEXPORT void JNICALL Java_jnisimulator_RyanAirWrapper_performWholeSimulation(JNIEnv *env, jobject obj) {
	for(int i = 0; i < SIM_LENGTH; i++) {
		servsim.runSim();
	}
}

JNIEXPORT void JNICALL Java_jnisimulator_RyanAirWrapper_setSimulatorForNewSimulation(JNIEnv *env, jobject obj, jint seed) {
	srand(seed);
	servsim.resetQ();
	servsim.setGT(0.0);
	servsim.activateDebug(true);
	EventStruct myEvent;
	EventStruct myPremiumEvent;
	//add just one arrival event
	myEvent.taskPriority = 0;
	myPremiumEvent.taskPriority = 1;
	myEvent.taskName = string("Task ") + servsim.genTaskNumber();//firstNames[0] + string(" ") + lastNames[0];
	myPremiumEvent.taskName = string("Premium Task ") + servsim.genPremiumTaskNumber();
	myEvent.eventTime = servsim.getGT() + servsim.sampleInterarrivalTime();
	myPremiumEvent.eventTime = servsim.getGT() + servsim.sampleInterarrivalTime();	
	myEvent.duration = rand() % MAX_DURATION + 1;
	myPremiumEvent.duration = rand() % MAX_DURATION + 1;
	myEvent.event = ARRIVAL;
	myPremiumEvent.event = ARRIVAL;
	servsim.addEvent(myEvent);
	servsim.addEvent(myPremiumEvent);
	//cout << "Adding " << myEvent << " event. \n \n";

//	for (int i = 0; i < TEST_SIZE; i++) { //populate queue with tasks
//		myEvent.taskName = firstNames[i] + string(" ")
//				+ lastNames[i];
//		myEvent.eventTime = servsim.advanceTime();
//		myEvent.duration = rand()%MAX_DURATION+1;
//		//cout << "duration: " << myEvent.duration << endl;
//		myEvent.event = ARRIVAL;
//		servsim.addEvent(myEvent);
//	}
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_RyanAirWrapper_rval__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring obs) {
	jdouble ret = 0.0;
    const char *path = env -> GetStringUTFChars(obs, NULL);
    env -> ReleaseStringUTFChars(obs, NULL);

    if(strcmp(path, "size") == 0) {
        ret = servsim.getSizeOfQ();
    }
    if(strcmp(path, "waitSize") == 0) {
	// WQ = Waiting Queue
	ret = servsim.getSizeOfWQ();
    }
    return ret;
}

