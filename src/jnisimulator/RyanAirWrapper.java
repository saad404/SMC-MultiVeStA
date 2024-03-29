package jnisimulator;

public class RyanAirWrapper {
	
	public native double getTime();
	public native void performOneStepOfSimulation();
	public native void performWholeSimulation();
	public native void setSimulatorForNewSimulation(int seed);
	public native double rval(int obs);
	public native double rval(String obs);

}
