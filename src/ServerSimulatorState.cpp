#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include <queue>
#include <jni.h>
#include <random>
#include "include/jnisimulator_ServerWrapper.h"

using namespace std;

//define the global time data type
//#define TimeType double
typedef double TimeType;

//define constants
const int TEST_SIZE = 15;
const int NUM_TASKS = 6;
const int NUM_NAMES = 15;
const TimeType THRESHOLD = 100.0;
//some strings
//string firstNames[NUM_TASKS] = {"Task","Task","Task","Task","Task","Task"};
//string lastNames[NUM_NAMES] = {"1","2","3","4","5","6"};
//
string firstNames[NUM_NAMES] =
    { "Alice", "Ambroise", "Bert", "Denise", "Larry", "Emily" , "John", "Charlie", "Dean", "Eli", "Fabian", "Gary", "Harry", "Ian", "Kevin"};
string lastNames[NUM_NAMES] =
    { "Ghosh", "Jones", "Lee", "Smith", "Zhang", "Zuckerman" , "Wick", "Austin", "James", "Sorensen", "Rodriguez", "Lineker", "Potter", "McKellen", "Costner"};

const int SIM_LENGTH = 100;
const int MAX_DURATION = 12;
const int NUM_SERVERS = 2;
int serversAvailable = NUM_SERVERS;
TimeType GT = 0.0;
TimeType simulatedTime = 0.0;

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
    cout << event.taskName;
    cout << ", Time: " << event.eventTime;
    cout << ", Duration: " << event.duration;
    cout << ", Event type: ";
    if (event.event == ARRIVAL) cout << "ARRIVAL";
    else cout << "SERVED";
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
    queue<EventStruct> serverQueue;
    //TimeType GT = 0.0;
    bool debugger = false;
    //int serversAvailable = NUM_SERVERS;
public:
    //TimeType GT = 0.0;
    void addEvent(EventStruct & event);
    void addServerQueueTask(EventStruct & event);
    void activateDebug(bool val) { debugger = val; };
    void printServerNumberChange();
    void runSim();
    double getGT(void);
    void setGT(double cur_time);
    int getSizeOfQ();
    void resetQ();
    double advanceTime();
}; //end ServerSimulatorState

ServerSimulatorState servsim;

void ServerSimulatorState::addEvent(EventStruct & event) {
    if (debugger) {
        cout << "[" << GT << "] Adding event: ";
        printEvent(event);
        cout << endl;
    }
    eventQ.push(event);
}

void ServerSimulatorState::addServerQueueTask(EventStruct & event) {
    if (debugger) {
        cout << "[" << GT << "] Adding server queue task: ";
        printEvent(event);
        cout << endl;
    }
    event.waitTime = GT;
    serverQueue.push(event);
}

void ServerSimulatorState::printServerNumberChange() {
    if (debugger) {
        cout << "[" << GT << "] Current number of servers available: " << serversAvailable << endl;
    }
}

double ServerSimulatorState::advanceTime() {
	double sample_x = ((jdouble) rand()) / (RAND_MAX) + 1; // rand: random number between 0 to RAND_MAX. sample_x: random number between 1 to 2
	//simulatedTime += -(log(sample_x))  / 0.1;  // log(1) = 0, log(2) = 0.69, 0/0.1 = 0, 0.69/0.1 = 6.9 -> -0 to -6.9
	simulatedTime += (log(sample_x))  / 0.1;  // log(1) = 0, log(2) = 0.69, 0/0.1 = 0, 0.69/0.1 = 6.9 -> -0 to -6.9
	return simulatedTime;
}

void ServerSimulatorState::runSim() {
	if (!eventQ.empty() && GT < THRESHOLD) {
        EventStruct nextEvent = eventQ.top();
        GT = nextEvent.eventTime;
        eventQ.pop();
        switch (nextEvent.event) {
        case ARRIVAL: //when a task arrives, schedule arrival of new task and serve task
            if (serversAvailable) {
            	//enter served event in eventQ
            	//EventStruct servedEvent;
            	//servsim.setGT(servedEvent.eventTime = GT + nextEvent.duration);
            	nextEvent.eventTime = GT + nextEvent.duration;
            	nextEvent.event = SERVED;
            	addEvent(nextEvent);
            	serversAvailable--;
            	printServerNumberChange();
            } else {
            	//no servers available
            	addServerQueueTask(nextEvent);
            }
            break;
        	case SERVED:
        	if(!serverQueue.empty()) {
        		EventStruct nextTask = serverQueue.front();
        		serverQueue.pop(); //fix below as done above
        		nextTask.eventTime = GT + nextTask.duration;
        		//servsim.setGT(nextTask.eventTime = GT + nextEvent.duration);
        		nextTask.event = SERVED;
        		addEvent(nextTask);
        	} else {
        		serversAvailable++;
        		printServerNumberChange();
        	}
        	break;
        default:
        	cout << "ERROR: default should never be reached" << endl;
        }
    } else if (!serverQueue.empty()){

    }
    //ServerSimulatorState servsim;

}

double ServerSimulatorState::getGT() {
    return GT;
}

void ServerSimulatorState::setGT(double cur_time) {
    GT = cur_time;
}

int ServerSimulatorState::getSizeOfQ() {
  return eventQ.size();
}

void ServerSimulatorState::resetQ() {
	eventQ = priority_queue<EventStruct, vector<EventStruct>, compareEventTime> ();
	serverQueue = queue<EventStruct> ();
	serversAvailable = NUM_SERVERS;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_ServerWrapper_getTime(JNIEnv *env, jobject obj) { //advanceTime
	return servsim.getGT();
}

JNIEXPORT void JNICALL Java_jnisimulator_ServerWrapper_performOneStepOfSimulation(JNIEnv *env, jobject obj) {
	servsim.runSim();
}

JNIEXPORT void JNICALL Java_jnisimulator_ServerWrapper_performWholeSimulation(JNIEnv *env, jobject obj) {
	for(int i = 0; i < SIM_LENGTH; i++) {
		servsim.runSim();
	}
}

JNIEXPORT void JNICALL Java_jnisimulator_ServerWrapper_setSimulatorForNewSimulation(JNIEnv *env, jobject obj, jint seed) {
	srand(seed);
	servsim.resetQ();
	GT = 0.0;
	simulatedTime = 0.0;
	servsim.activateDebug(true);
	EventStruct myEvent;
	cout << "Adding " << TEST_SIZE << " events. \n \n";
	for (int i = 0; i < TEST_SIZE; i++) { //populate queue with tasks
		myEvent.taskName = firstNames[i] + string(" ")
				+ lastNames[i];
		myEvent.eventTime = servsim.advanceTime();
		myEvent.duration = rand()%MAX_DURATION+1;
		//cout << "duration: " << myEvent.duration << endl;
		myEvent.event = ARRIVAL;
		servsim.addEvent(myEvent);
	}
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_ServerWrapper_rval__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring obs) {
	jdouble ret = 0.0;
    const char *path = env -> GetStringUTFChars(obs, NULL);
    env -> ReleaseStringUTFChars(obs, NULL);

    if(strcmp(path, "size") == 0) {
        ret = servsim.getSizeOfQ();
    }

    return ret;
}


