#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include <jni.h>

using namespace std;

//define the global time data type
#define TimeType double

//define constants
#define TEST_SIZE 15
#define NUM_TASKS 6
//some strings
//
#define SIM_LENGTH 100
#define MAX_DURATION 20
#define NUM_SERVERS 3

//define event types
typedef enum {ARRIVAL, SERVED} EventType;

//define an event struct to store events
typedef struct {
	string taskName;
	TimeType eventTime;
	TimeType duration;
	EventType event;
	TimeType waitTime;
} EventStruct;

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
	queue<EventStruct> serverQueue;
	TimeType GT = 0;
	bool debugger = false;
	int serversAvailable = NUM_SERVERS;
public:
	void addEvent(EventStruct & event);
	void addServerQueueTask(EventStruct & event);
	void activateDebug(bool val) {debugger = val};
	void printServerNumberChange();
	void runSim();
	double getGT(void);
	void setGT(double cur_time)
}; //end ServerSimulatorState

void ServerSimulatorState::addEvent(EventStruct & event) {
	if (debugger) {
		cout << "[" << GT << "] Adding event: ";
		printEvent(event);
		cout << endl;
	}
	//eventQueue.push(event);
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

}

double ServerSimulatorState::getGT(void) {
	return GT;
}

void ServerSimulatorState::setGT(double cur_time) {
	GT = cur_time;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_ServerWrapper_getTime(JNIEnv *env, jobject obj) {
	ServerSimulatorState servsim;
	jdouble sample_x = ((jdouble) rand()) / (RAND_MAX) + 1;
	jdouble simulatedTime = 0.0;
	simulatedTime += -(log(sample_x)) / 0.1;
	servsim.setGT(simulatedTime);
	return servsim.getGT();
}

JNIEXPORT void JNICALL Java_jnisimulator_ServerWrapper_performOneStepOfSimulation(JNIEnv *env, jobject obj) {

}
