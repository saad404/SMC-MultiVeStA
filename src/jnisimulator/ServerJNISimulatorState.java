package jnisimulator;

import vesta.mc.NewState;
import vesta.mc.ParametersForState;

public class ServerJNISimulatorState extends NewState {
	static {
		System.loadLibrary("webserver");
	}
	
	private ServerWrapper simulator;
	
	public ServerJNISimulatorState(ParametersForState parameters) {
		super(parameters);
		simulator = new ServerWrapper();
	}
	
	public double getTime() {
		return simulator.getTime();
	}
	
	public void performOneStepOfSimulation() {
		simulator.performOneStepOfSimulation();
	}
	
	public void performWholeSimulation() {
		simulator.performWholeSimulation();
	}
	
	public void setSimulatorForNewSimulation(int seed) {
		simulator.setSimulatorForNewSimulation(seed);
	}
	
	public void setMaxNumberOfEvents(int maxNumberOfEvents) {
		simulator.setMaxNumberOfEvents(maxNumberOfEvents);
	}
	
	public double rval(int obs) {
		return simulator.rval(obs);
	}
	
	public double rval(String obs) {
		if (obs.equals("steps")) {
			return getNumberOfSteps();
		} else if (obs.equals("time")) {
			return getTime();
		} else {
			return simulator.rval(obs);
		}
	}

}
