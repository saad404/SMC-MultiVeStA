#!/bin/bash

reset
javac -h include jnilayer/*.java tests/*.java -cp ../lib/multivesta.jar && g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libdiceroll.so DiceSimulatorState.cpp && java -cp .:../lib/multivesta.jar -Djava.library.path=. tests.MyMainDice

