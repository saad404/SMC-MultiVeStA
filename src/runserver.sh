#!/bin/bash

reset
javac -h include mock/*.java tests/*.java -cp ../lib/multivesta.jar && g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libwebserver.so ServerSimulatorState.cpp && java -cp .:../lib/multivesta.jar -Djava.library.path=. tests.MyMainServer

