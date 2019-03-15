#!/bin/bash

javac -h include jnisimulator/*.java tests/*.java -cp /home/saad404/eclipse-workspace/JNI_intro/lib/multivesta.jar 
 
g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libdiceroll.so DiceSimulatorState.cpp 
 
java -cp .:/home/saad404/eclipse-workspace/JNI_intro/lib/multivesta.jar -Djava.library.path=. tests.MyMainDice
