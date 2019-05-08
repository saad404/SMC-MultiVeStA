package jnisimulator;

public class ServerWrapper {
	
	public native double getTime();
	public native void performOneStepOfSimulation();
	public native void performWholeSimulation();
	public native void setMaxNumberOfEvents(int maxNumberOfEvents);
	public native void setSimulatorForNewSimulation(int seed);
	public native double rval(int obs);
	public native double rval(String obs);

}
