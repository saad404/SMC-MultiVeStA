package jnisimulator;

import vesta.mc.NewState;
import vesta.mc.ParametersForState;

public class RyanAirJNISimulatorState extends NewState {
	static {
		System.loadLibrary("ryanair");
	}
	
	private RyanAirWrapper simulator;
	
	public RyanAirJNISimulatorState(ParametersForState parameters) {
		super(parameters);
		simulator = new RyanAirWrapper();
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
