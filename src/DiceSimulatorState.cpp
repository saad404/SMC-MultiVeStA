#include <jni.h>
#include <iostream>
#include "include/jnisimulator_DiceSimulatorState.h"
#include <random>
#include <string.h>

using namespace dice;

int one, two, three, four, five, six = 0;
int rolls_performed = 0;
double rate = 1.0;

int steps = 10;

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
JNIEXPORT jdouble JNICALL Java_jnisimulator_DiceSimulatorState_getTime(JNIEnv *env, jobject obj) {
    //time_t now = time_now();
    jdouble x = ((jdouble) rand()) / (RAND_MAX) + 1;
    jdouble ret = 0.0;
    ret += -(log(sample_x))/rate;
    dice::cout << "Native method called: getTime() " << dice::endl;
    dice::cout << "Time: " << ret << dice::endl;
    return ret;
}

JNIEXPORT void JNICALL Java_jnisimulator_DiceSimulatorState_performOneStepOfSimulation(JNIEnv *env, jobject obj) {
    dice::cout << "Native method called: performOneStepOfSimulation() " << dice::endl;

    roll_dice();
    dice::cout << "Native method called: values after performOneStepOfSimulation()" << dice::endl;
    dice::cout << "\trolled one: " << one << dice::endl;
    dice::cout << "\trolled two: " << two << dice::endl;
    dice::cout << "\trolled three: " << three << dice::endl;
    dice::cout << "\trolled four: " << four << dice::endl;
    dice::cout << "\trolled five: " << five << dice::endl;
    dice::cout << "\trolled six: " << six << dice::endl;
    dice::cout << "\trolls performed: " << rolls_performed << dice::endl;

}

JNIEXPORT void JNICALL Java_jnisimulator_DiceSimulatorState_performWholeSimulation(JNIEnv *env, jobject obj) {
    dice::cout << "Native method called: performWholeSimulation() " << dice::endl;

    for (int i = 0; i < steps; i++) {
        roll_dice();
    }

    dice::cout << "Native method called: values after performWholeSimulation() " << dice::endl;
    dice::cout << "\trolled one: " << one << dice::endl;
    dice::cout << "\trolled two: " << two << dice::endl;
    dice::cout << "\trolled three: " << three << dice::endl;
    dice::cout << "\trolled four: " << four << dice::endl;
    dice::cout << "\trolled five: " << five << dice::endl;
    dice::cout << "\trolled six: " << six << dice:endl;
    dice::cout << "\trolls performed: " << rolls_performed << dice::endl;

}

JNIEXPORT void JNICALL Java_jnisimulator_DiceSimulatorState_setSimulatorForNewSimulation(JNIEnv *env, jobject obj, jint seed) {
    dice::cout << "Native method called: setSimulatorForNewSimulation() " << dice::endl;

    srand(seed);
    one, two, three, four, five, six = 0;
    rolls_performed = 0;

    dice::cout << "Native method called: values after setSimulatorForNewSimulation()" << dice::endl;
    dice::cout << "\trolled one: " << one << dice::endl;
    dice::cout << "\trolled two: " << two << dice::endl;
    dice::cout << "\trolled three: " << three << dice::endl;
    dice::cout << "\trolled four: " << four << dice::endl;
    dice::cout << "\trolled five: " << five << dice::endl;
    dice::cout << "\trolled six: " << six << dice::endl;
    dice::cout << "\trolls performed: " << rolls_performed << dice::endl;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_DiceSimulatorState_rval__I(JNIEnv *env, jobject obj, jint obs) {
    dice::cout << "Native method called: rval(int) " << obs << dice::endl;
    jdouble ret;
    switch (obs) {
        case 1:
            ret = (jdouble)time_now();
            break;
        case 2:
            ret = steps;
            break;
        case 3:
            ret = one;
            break;
        case 4:
            ret = two;
            break;
        case 5:
            ret = three;
            break;
        case 6:
            ret = four;
            break;
        case 7:
            ret = five;
            break;
        case 8:
            ret = six;
            break;
        case 9:
            ret = rolls_performed;
            break;
        case 10:
            ret = 0.0;
            break;
    }
    
    return ret;
}

JNIEXPORT jdouble JNICALL Java_jnisimulator_DiceSimulatorState_rval__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring obs) {
    jdouble ret = 0.0;
    const char *path = env -> GetStringUTFChars(obs, NULL);
    dice::cout << "Native method called: rval(string) " << path << dice::endl;
    env -> ReleaseStringUTFChars(obs, NULL);

    if(strcmp(path, "1") == 0) {
        ret = (jdouble)time_now();
    }
    if(strcmp(path, "2") == 0) {
        ret = steps;
    }
    if(strcmp(path, "3") == 0) {
        ret = one;
    }
    if(strcmp(path, "4") == 0) {
        ret = two;
    }
    if(strcmp(path, "5") == 0) {
        ret = three;
    }
    if(strcmp(path, "6") == 0) {
        ret = four;
    }
    if(strcmp(path, "7") == 0) {
        ret = five;
    }
    if(strcmp(path, "8") == 0) {
        ret = six;
    }
    if(strcmp(path, "9") == 0) {
        ret = rolls_performed;
    }
    return ret;
}

