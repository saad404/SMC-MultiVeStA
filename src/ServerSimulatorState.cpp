#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include <queue>
#include <jni.h>
#include <random>
#include <sstream>
#include "include/jnilayer_ServerWrapper.h"

using namespace std;

//define the global time data type
typedef double TimeType;

//define constants
//const int TEST_SIZE = 15;
//const int NUM_TASKS = 6;
//const int NUM_NAMES = 15;
const TimeType THRESHOLD = 400.0;

const int SIM_LENGTH = 100;
const int MAX_DURATION = 12;
const int NUM_SERVERS = 2;
// AVG_INTERARRIVAL_TIME -> 0 = "udskyder" tidspunktet hvor size() = 0
const double AVG_INTERARRIVAL_TIME = 7.5;
const double RATE_EXP = 1.0 / AVG_INTERARRIVAL_TIME;
int serversAvailable = NUM_SERVERS;


//define event types
enum EventType {ARRIVAL, SERVED};

//define an event struct to store events
struct EventStruct {
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
        return lhs.eventTime > rhs.eventTime;
    }
};

class ServerSimulatorState {
private:
    //event queue: pq with events queued by event time
    priority_queue<EventStruct, vector<EventStruct>, compareEventTime> eventQ;
    //wait queue: q with waiting tasks queued by arrival time
    queue<EventStruct> waitQueue;
    TimeType GT = 0.0;
    bool debugger = false;
    //int serversAvailable = NUM_SERVERS;
public:
    //TimeType GT = 0.0;
    void addEvent(EventStruct & event);
    void addWaitQueueTask(EventStruct & event);
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
}; //end ServerSimulatorState

ServerSimulatorState servsim;

void ServerSimulatorState::addEvent(EventStruct & event) {
    if (debugger) {
    //    cout << "[" << GT << "] Adding event: ";
        printEvent(event);
   //     cout << endl;
    }
    eventQ.push(event);
}

void ServerSimulatorState::addWaitQueueTask(EventStruct & event) {
    if (debugger) {
     //   cout << "[" << GT << "] Adding server queue task: ";
        printEvent(event);
     //   cout << endl;
    }
    event.waitTime = GT;
    waitQueue.push(event);
}

void ServerSimulatorState::printServerNumberChange() {
    if (debugger) {
     //   cout << "[" << GT << "] Current number of servers available: " << serversAvailable << endl;
    }
}

// add EventStruct & to be parsed?
void ServerSimulatorState::scheduleArrivedEvent(EventStruct & currentEvent) {
	EventStruct futureEvent;
	futureEvent.eventTime = servsim.getGT() + currentEvent.duration;
	futureEvent.event = SERVED;
	futureEvent.taskName = currentEvent.taskName;
	addEvent(futureEvent);
	serversAvailable--;
	printServerNumberChange();
}

void ServerSimulatorState::scheduleServedEvent() {
	EventStruct nextTask = waitQueue.front();
	waitQueue.pop(); //fix below as done above
	nextTask.eventTime = servsim.getGT() + nextTask.duration;
	//servsim.setGT(nextTask.eventTime = GT + nextEvent.duration);
	nextTask.event = SERVED;
	addEvent(nextTask);
}

string ServerSimulatorState::genTaskNumber() {
	int taskNumber = rand() % 100 + 1;
	ostringstream str1;
	str1 << taskNumber;
	return str1.str();
}

double ServerSimulatorState::sampleInterarrivalTime() {
	double sample_x = ((jdouble) rand()) / (RAND_MAX); // rand: random number between 0 to RAND_MAX. sample_x: random number between 0 and 1
	return -(log(sample_x))  / RATE_EXP;  // log(1) = 0, log(2) = 0.69, 0/0.1 = 0, 0.69/0.1 = 6.9 -> 0 to -6.9
}

void ServerSimulatorState::runSim() {
	// try to move if-statement at nextArrival and see if it works.
	// It doesn't work. It will pop until size = 1 and then stop instead of 0.
//	if(servsim.getGT() >= THRESHOLD && eventQ.size() > 0) {
//		eventQ.pop();
//	}
	if (servsim.getGT() >= THRESHOLD && waitQueue.size() > 0) {
		waitQueue.pop();
	}

	if (!eventQ.empty() && servsim.getGT() < THRESHOLD) {
        EventStruct currentEvent = eventQ.top();
        servsim.setGT(currentEvent.eventTime);
        eventQ.pop();
        switch (currentEvent.event) {
        case ARRIVAL:
        	{ //when a task arrives, schedule arrival of new task and serve task
				if (serversAvailable > 0) {
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
					addWaitQueueTask(currentEvent);
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
				if(!waitQueue.empty()) {
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

void ServerSimulatorState::setGT(double cur_time) {
	GT = cur_time;
}

double ServerSimulatorState::getGT() {
    return GT;
}

int ServerSimulatorState::getSizeOfWQ() {
  return waitQueue.size();
}

int ServerSimulatorState::getSizeOfQ() {
  return eventQ.size();
}

void ServerSimulatorState::resetQ() {
	eventQ = priority_queue<EventStruct, vector<EventStruct>, compareEventTime> ();
	waitQueue = queue<EventStruct> ();
	serversAvailable = NUM_SERVERS;
}

JNIEXPORT jdouble JNICALL Java_jnilayer_ServerWrapper_getTime(JNIEnv *env, jobject obj) { //advanceTime
	return servsim.getGT();
}

JNIEXPORT void JNICALL Java_jnilayer_ServerWrapper_performOneStepOfSimulation(JNIEnv *env, jobject obj) {
	servsim.runSim();
}

JNIEXPORT void JNICALL Java_jnilayer_ServerWrapper_performWholeSimulation(JNIEnv *env, jobject obj) {
	for(int i = 0; i < SIM_LENGTH; i++) {
		servsim.runSim();
	}
}

JNIEXPORT void JNICALL Java_jnilayer_ServerWrapper_setSimulatorForNewSimulation(JNIEnv *env, jobject obj, jint seed) {
	srand(seed);
	servsim.resetQ();
	servsim.setGT(0.0);
	servsim.activateDebug(true);
	EventStruct myEvent;
	//add just one arrival event
	myEvent.taskName = string("Task ") + servsim.genTaskNumber();//firstNames[0] + string(" ") + lastNames[0];
	myEvent.eventTime = servsim.getGT() + servsim.sampleInterarrivalTime();
	myEvent.duration = rand() % MAX_DURATION + 1;
	myEvent.event = ARRIVAL;
	servsim.addEvent(myEvent);
	// cout << "Adding " << 1 << " event. \n \n";

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

JNIEXPORT jdouble JNICALL Java_jnilayer_ServerWrapper_rval__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring obs) {
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

