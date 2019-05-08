#!/bin/bash

reset
javac -h include tests/*.java jnisimulator/*.java entrypoint/*.java -cp ~/eclipse-workspace/JNI_intro/lib/multivesta.jar  && g++ -fPIC -I/usr/lib/jvm/java-1.11.0-openjdk-amd64/include -I/usr/lib/jvm/java-1.11.0-openjdk-amd64/include/linux -shared -o libwebserver.so ServerSimulatorState.cpp && java -cp .:/home/saad404/eclipse-workspace/JNI_intro/lib/multivesta.jar -Djava.library.path=. tests.MyMainServer
