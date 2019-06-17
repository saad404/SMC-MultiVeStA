#include <jni.h>       // JNI header provided by JDK
#include <iostream>    // C++ standard IO header
//#include "include/tests_MyMain.h"  // Generated
#include "include/jnilayer_CoinFlipWrapper.h"
#include <random>
#include <time.h>
#include <string.h>

using namespace std;

int heads = 0;
int head_limit = 0;
int tails = 0;
int flips_performed = 0;
double biasFactor = 55;
int steps = 0;
double cur_time = 0.0;
double rate = 1.0;

int NO_STEPS = 10; // number of total steps for performWholeSimulation - already done

// this is not a JNI method but will be used by jni methods - not put in h file as h file can be
// regenerated

// transform 55 into a variable named bias
// do a method in reset which takes an input integer and sets the bias
void flip_coin() {
	head_limit = RAND_MAX * biasFactor;
	int flip = rand();
	if(flip <= head_limit) { // head
		heads++;
	}
	else {
		tails++;
	}
	// increased number of flips perfomed
	flips_performed++;

}


JNIEXPORT jdouble JNICALL Java_jnilayer_CoinFlipWrapper_getTime(JNIEnv *env, jobject obj) {
	// get current time based on

	std::cout << "Native method called: getTime() " << std::endl;
	jdouble sample_x = ((double) rand() / (RAND_MAX));
	cur_time += (-log(sample_x)) / rate;
	//std::cout << "Will return  " << now << std::endl;
	return cur_time;
}

JNIEXPORT void JNICALL Java_jnilayer_CoinFlipWrapper_performOneStepOfSimulation(JNIEnv *env, jobject obj) {
	std::cout << "Native method called: performOneStepOfSimulation() " << std::endl;

	flip_coin();

	std::cout << "Native method called: values after performOneStepOfSimulation()" << std::endl;
	std::cout << "\theads(" << heads << ")" << std::endl;
	std::cout << "\ttails(" << tails << ")" << std::endl;
	std::cout << "\tflips_performed(" << flips_performed << ")" << std::endl;
}

JNIEXPORT void JNICALL Java_jnilayer_CoinFlipWrapper_performWholeSimulation(JNIEnv *env, jobject obj) {
	std::cout << "Native method called: performWholeSimulation() " << std::endl;

	for(int i = 0; i < NO_STEPS; i++) {
		flip_coin();
	}

	std::cout << "Native method called: values after performWholeSimulation()" << std::endl;
	std::cout << "\theads(" << heads << ")" << std::endl;
	std::cout << "\ttails(" << tails << ")" << std::endl;
	std::cout << "\tflips_performed(" << flips_performed << ")" << std::endl;

}

JNIEXPORT void JNICALL Java_jnilayer_CoinFlipWrapper_setSimulatorForNewSimulation(JNIEnv *env, jobject obj, jint seed) {
	std::cout << "Native method called: setSimulatorForNewSimulation() " << std::endl;

	// initialize random seed
	srand(seed);
	heads = 0;
	tails = 0;
	flips_performed = 0;
	cur_time = 0.0;

	std::cout << "Native method called: values after setSimulatorForNewSimulation()" << std::endl;
//	std::cout << "\theads(" << heads << ")" << std::endl;
//	std::cout << "\ttails(" << tails << ")" << std::endl;
//	std::cout << "\tflips_performed(" << flips_performed << ")" << std::endl;
}

JNIEXPORT jdouble JNICALL Java_jnilayer_CoinFlipWrapper_rval__I(JNIEnv *env, jobject obj, jint obs) {
	std::cout << "Native method called: rval(int) " << obs << std::endl;
	jdouble ret = 0.0;
	return ret;
}

JNIEXPORT jdouble JNICALL Java_jnilayer_CoinFlipWrapper_rval__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring obs) {
	jdouble ret = 0.0;
	const char *path = env -> GetStringUTFChars(obs, NULL);
	std::cout << "Native method called: sval(string) " << path << std::endl;
	env -> ReleaseStringUTFChars(obs, NULL);

	if(strcmp(path, "time") == 0) {
		ret = cur_time;
	}

	if(strcmp(path, "heads") == 0) {
		ret = heads;
	}
	if(strcmp(path, "tails") == 0) {
		ret = tails;
	}
	if(strcmp(path, "flips_performed") == 0) {
		ret = flips_performed;
	}

	return ret;
}

JNIEXPORT void JNICALL Java_jnilayer_CoinFlipWrapper_setBias(JNIEnv *end, jobject object, jdouble bias) {
	biasFactor = bias;
}


