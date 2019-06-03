cls

javac -h include jnisimulator/*.java tests/*.java -cp ../lib/multivesta.jar && x86_64-w64-mingw32-g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o webserver.dll ServerSimulatorState.cpp && java -cp .;../lib/multivesta.jar -Djava.library.path=. tests.MyMainServer