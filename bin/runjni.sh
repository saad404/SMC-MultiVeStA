#!/bin/bash

javac -h include jnisimulator/*.java tests/*.java -cp ~/eclipse-workspace/JNI_intro/lib/multivesta.jar 
 
g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libcoinflib.so CoinFlipSimulatorState.cpp 
 
java -cp .:~/eclipse-workspace/JNI_intro/lib/multivesta.jar -Djava.library.path=. tests.MyMain
