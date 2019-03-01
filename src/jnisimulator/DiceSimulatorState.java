package jnisimulator;

import vesta.mc.ParametersForState;

public class DiceSimulatorState {
	
	public native double getTime();
	public native void performOneStepOfSimulation();
	public native void performWholeSimulation();
	public native void setSimulatorForNewSimulation(int seed);
	public native double rval(int obs);
	public native double rval(String obs);
	

}

