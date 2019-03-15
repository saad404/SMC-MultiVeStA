#include <jni.h>
#include <iostream>
#include "include/jnisimulator_DiceWrapper.h"
#include <random>
#include <string.h>

using namespace std;

int one, two, three, four, five, six = 0;
int rolls_performed = 0;
double rate = 1.0;
double cur_time = 0.0;

int no_steps = 10;

void roll_dice() {
    int roll = rand() % 6 + 1;
    if (roll == 1) {
        one++;
    } else if (roll == 2) {
        two++;
    } else if (roll == 3) {
        three++;
    } else if (roll == 4) {
        four++;
    } else if (roll == 5) {
        five++;
    } else if (roll == 6) {
        six++;
    }

    rolls_performed++;
}
   
//    time_t time_now() {
//        return time(0);
//    }

//increment time by number from exponential distribution, otherwise 10
JNIEXPORT jdouble JNICALL Java_jnisimulator_DiceWrapper_getTime(JNIEnv *env, jobject obj) {
    //time_t now = time_now();
    jdouble sample_x = ((jdouble) rand()) / (RAND_MAX) + 1;
    cur_time += -(log(sample_x))/rate;
    std::cout << "Native method called: getTime() " << std::endl;
    std::cout << "Time: " << cur_time << std::endl;
    return cur_time;
}

JNIEXPORT void JNICALL Java_jnisimulator_DiceWrapper_performOneStepOfSimulation(JNIEnv *env, jobject obj) {
    std::cout << "Native method called: performOneStepOfSimulation() " << std::endl;

    roll_dice();
    std::cout << "Native method called: values after performOneStepOfSimulation()" << std::endl;
//    std::cout << "\trolled one: " << one << std::endl;
//    std::cout << "\trolled two: " << two << std::endl;
//    std::cout << "\trolled three: " << three << std::endl;
//    std::cout << "\trolled four: " << four << std::endl;
//    std::cout << "\trolled five: " << five << std::endl;
//    std::cout << "\trolled six: " << six << std::endl;
//    std::cout << "\trolls performed: " << rolls_performed << std::endl;

}

JNIEXPORT void JNICALL Java_jnisimulator_DiceWrapper_performWholeSimulation(JNIEnv *env, jobject obj) {
    std::cout << "Native method called: performWholeSimulation() " << std::endl;

    for (int i = 0; i < no_steps; i++) {
        roll_dice();
    }

    std::cout << "Native method called: values after performWholeSimulation() " << std::endl;
    std::cout << "\trolled one: " << one << std::endl;
    std::cout << "\trolled two: " << two << std::endl;
    std::cout << "\trolled three: " << three << std::endl;
    std::cout << "\trolled four: " << four << std::endl;
    std::cout << "\trolled five: " << five << std::endl;
    std::cout << "\trolled six: " << six << std::endl;
    std::cout << "\trolls performed: " << rolls_performed << std::endl;

}

JNIEXPORT void JNICALL Java_jnisimulator_DiceWrapper_setSimulatorForNewSimulation(JNIEnv *env, jobject obj, jint seed) {
    std::cout << "Native method called: setSimulatorForNewSimulation() " << std::endl;

    srand(seed);
    one, two, three, four, five, six = 0;
    rolls_performed = 0;

    std::cout << "Native method called: values after setSimulatorForNewSimulation()" << std::endl;
    std::cout << "\trolled one: " << one << std::endl;
    std::cout << "\trolled two: " << two << std::endl;
    std::cout << "\trolled three: " << three << std::endl;
    std::cout << "\trolled four: " << four << std::endl;
    std::cout << "\trolled five: " << five << std::endl;
    std::cout << "\trolled six: " << six << std::endl;
    std::cout << "\trolls performed: " << rolls_performed << std::endl;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_DiceWrapper_rval__I(JNIEnv *env, jobject obj, jint obs) {
    std::cout << "Native method called: rval(int) " << obs << std::endl;
    jdouble ret;
//    switch (obs) {
//        case 1:
//            ret = (jdouble)time_now();
//            break;
//        case 2:
//            ret = steps;
//            break;
//        case 3:
//            ret = one;
//            break;
//        case 4:
//            ret = two;
//            break;
//        case 5:
//            ret = three;
//            break;
//        case 6:
//            ret = four;
//            break;
//        case 7:
//            ret = five;
//            break;
//        case 8:
//            ret = six;
//            break;
//        case 9:
//            ret = rolls_performed;
//            break;
//        case 10:
//            ret = 0.0;
//            break;
//    }
    
    return ret;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_DiceWrapper_rval__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring obs) {
    jdouble ret = 0.0;
    const char *path = env -> GetStringUTFChars(obs, NULL);
    std::cout << "Native method called: rval(string) " << path << std::endl;
    env -> ReleaseStringUTFChars(obs, NULL);

    if(strcmp(path, "one") == 0) {
        ret = one;
    }
    if(strcmp(path, "two") == 0) {
        ret = two;
    }
    if(strcmp(path, "three") == 0) {
        ret = three;
    }
    if(strcmp(path, "four") == 0) {
        ret = four;
    }
    if(strcmp(path, "five") == 0) {
        ret = five;
    }
    if(strcmp(path, "six") == 0) {
        ret = six;
    }
    if(strcmp(path, "rolls_performed") == 0) {
        ret = rolls_performed;
    }
    return ret;
}

