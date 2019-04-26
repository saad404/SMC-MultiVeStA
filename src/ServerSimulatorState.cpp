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
//some strings
//
const int SIM_LENGTH = 100;
const int MAX_DURATION = 20;
const int NUM_SERVERS = 3;

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

TimeType GT = 0.0;

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
    //list here
    priority_queue<EventStruct, vector<EventStruct>, compareEventTime> eventQ;
    queue<EventStruct> serverQueue;
    TimeType curTime = 0.0;
    bool debugger = false;
    int serversAvailable = NUM_SERVERS;
public:
    void addEvent(EventStruct & event);
    void addServerQueueTask(EventStruct & event);
    void activateDebug(bool val) { debugger = val; };
    void printServerNumberChange();
    void runSim();
    double getGT(void);
    void setGT(double cur_time);
    int getSizeOfQ();
    void resetQ();
}; //end ServerSimulatorState

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
    serverQueue.push(event);
    event.waitTime = GT;
}

void ServerSimulatorState::printServerNumberChange() {
    if (debugger) {
        cout << "[" << GT << "] Current number of servers available: " << serversAvailable << endl;
    }
}

void ServerSimulatorState::runSim() {
    while (!eventQ.empty()) {
        EventStruct nextEvent = eventQ.top();
        curTime = nextEvent.eventTime;
        eventQ.pop();
        switch (nextEvent.event) {
        case ARRIVAL:
            if (serversAvailable) {
            	//enter served event in eventQ
            	nextEvent.eventTime = curTime + nextEvent.duration;
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
        		serverQueue.pop();
        		nextTask.eventTime = curTime + nextEvent.duration;
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
    }
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
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_ServerWrapper_getTime(JNIEnv *env, jobject obj) { //advanceTime
	ServerSimulatorState servsim;
	jdouble sample_x = ((jdouble) rand()) / (RAND_MAX) + 1;
	jdouble simulatedTime = GT;
	simulatedTime += -(log(sample_x)) / 0.1;
	servsim.setGT(simulatedTime);
	return servsim.getGT();
}

JNIEXPORT void JNICALL Java_jnisimulator_ServerWrapper_performOneStepOfSimulation(JNIEnv *env, jobject obj) {
	ServerSimulatorState servsim;
	std::cout << "Native method called: performOneStepOfSimulation" << endl;
	servsim.runSim();
	std::cout << "after it's been called" << endl;
}

JNIEXPORT void JNICALL Java_jnisimulator_ServerWrapper_performWholeSimulation(JNIEnv *env, jobject obj) {
	ServerSimulatorState servsim;
	for(int i = 0; i < SIM_LENGTH; i++) {
		servsim.runSim();
	}
}

JNIEXPORT void JNICALL Java_jnisimulator_ServerWrapper_setSimulatorForNewSimulation(JNIEnv *env, jobject obj, jint seed) {
	srand(seed);
	ServerSimulatorState servsim;
	servsim.resetQ();
	GT = 0.0;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_ServerWrapper_rval__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring obs) {
    ServerSimulatorState servsim;
	jdouble ret = 0.0;
    const char *path = env -> GetStringUTFChars(obs, NULL);
    std::cout << "Native method called: rval(string) " << path << std::endl;
    env -> ReleaseStringUTFChars(obs, NULL);

    if(strcmp(path, "size") == 0) {
        ret = servsim.getSizeOfQ();
    }

    return ret;
}


