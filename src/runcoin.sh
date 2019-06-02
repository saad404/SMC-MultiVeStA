#!/bin/bash

reset
javac -h include jnisimulator/*.java tests/*.java -cp ../lib/multivesta.jar && g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libcoinflib.so CoinFlipSimulatorState.cpp && java -cp .:../lib/multivesta.jar -Djava.library.path=. tests.MyMain

