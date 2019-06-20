#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()
#include "catch.hpp" // included in src folder
#include <queue>
#include <string.h>

const double AVG_INTERARRIVAL_TIME = 1.0;
const double RATE_EXP = 1.0 / AVG_INTERARRIVAL_TIME;
double GT = 0.0;

double sampleInterarrivalTime() {
	double sample_x = ((double) rand()) / (RAND_MAX); 
	return -(log(sample_x))  / RATE_EXP;
}

// srand(0): sample_x == 0.840188 => sampleInterarrivalTime() == 0.1741299393 

struct EventStruct {
	int taskTime;
	double waitTime;
};

std::queue<EventStruct> eventQ;
std::queue<EventStruct> serverQueue;

void addEvent(EventStruct & event) {
    eventQ.push(event);
}

void resetQ() {
	eventQ = std::queue<EventStruct> ();
}

std::string genTaskNumber() {
	int taskNumber = rand() % 100 + 1;
	std::ostringstream str1;
	str1 << taskNumber;
	return str1.str();
}

void setGT(double cur_time) {
	GT = cur_time;
}

double getGT() {
    return GT;
}

void addServerQueueTask(EventStruct & event) {
	event.waitTime = GT;
	serverQueue.push(event);
}

int getSizeOfWQ() {
  return serverQueue.size();
}

int getSizeOfQ() {
  return eventQ.size();
}


TEST_CASE("Testing sampleInterarrivalTime") {
	SECTION("Test srand(0)") {
		srand(0);
		//INFO( FullPrecision(sampleInterarrivalTime()));
		// string d = FullPrecision(sampleInterarrivalTime()) 
		Catch::Detail::Approx d = Approx(sampleInterarrivalTime());
		// Approx ensures that result close to epsilon is accepted as true. 
		// If not included 0.1741299393 would not be accepted.
		// By default set to std::numeric_limits<float>::epsilon()*100
		// https://github.com/catchorg/Catch2/blob/master/docs/assertions.md
		REQUIRE( d == 0.1741299393  );
	}
	SECTION("Test srand(1)") {
		srand(1);
		Catch::Detail::Approx d = Approx(sampleInterarrivalTime());
		REQUIRE( d == 0.1741299393 );
	}
	SECTION("Test srand(100)") {
		// For a high value of srand it should be different from srand(0) & srand(1)
		srand(100);
		Catch::Detail::Approx d = Approx(sampleInterarrivalTime());
		REQUIRE( d != 0.1741299393 );
	}
}

TEST_CASE("Testing addEvent & getSizeOfQ") {
	SECTION("Add 1 event") {
		EventStruct myEvent;
		myEvent.taskTime = 0;
		addEvent(myEvent);
		REQUIRE( eventQ.size() == 1 );
	}
	SECTION("Adding multiple events") {
		EventStruct myEvent;
		myEvent.taskTime = 1;
		addEvent(myEvent);
		addEvent(myEvent);
		addEvent(myEvent);	
		addEvent(myEvent);
		REQUIRE( eventQ.size() == 5);
	}	
	SECTION("Remove events") {
		EventStruct myEvent;
		myEvent.taskTime = 2;
		addEvent(myEvent);
		resetQ();
		REQUIRE( eventQ.empty() );
	}
}

TEST_CASE("Testing genTaskNumber") {
	SECTION("Test srand(0) with taskNumber") {	
		srand(0); // genTaskNumber should be "84" for this seed.
		REQUIRE( genTaskNumber() == "84" );
	}
	SECTION("Test srand(1) with taskNumber") {	
		srand(1); // genTaskNumber should be "84" for this seed.
		REQUIRE( genTaskNumber() == "84" );
	}
	SECTION("Test srand(100) with taskNumber") {
		REQUIRE( genTaskNumber() != "84" );
	}
}

TEST_CASE("Testing setGT and getGT") {
	SECTION("Default GT should be cur_time = 0.0") {
		REQUIRE( GT == 0.0 );
	}
	SECTION("Set GT for cur_time = 1.0") {
		setGT(1.0);		
		REQUIRE( GT == 1.0 );
	}
	SECTION("Set GT for cur_time = -10.0") {
		setGT(-10.0);
		REQUIRE( GT == -10.0 );
	}
	SECTION("get GT for current value of cur_time. Should return -10.0") {
		REQUIRE( getGT() == -10.0 );
	}
	SECTION("set GT = 0.0") {
		setGT(0.0);
		REQUIRE( GT == 0.0);
	}
}

TEST_CASE("Testing addServerQueueTask & getSizeOfWQ") {
	SECTION("Add one event") {
		EventStruct myEvent;
		addServerQueueTask(myEvent);
		REQUIRE( serverQueue.size() == 1 );
	}
	SECTION("Test event.waitTime = GT") {
		EventStruct myEvent;
		addServerQueueTask(myEvent);
		REQUIRE( myEvent.waitTime == 0.0 );
	}
	SECTION("Test event.waitTime = GT") {
		EventStruct myEvent;
		setGT(1.0);
		addServerQueueTask(myEvent);		
		REQUIRE( myEvent.waitTime == 1.0 );
	}
}
