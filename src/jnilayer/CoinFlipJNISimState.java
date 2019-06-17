package jnilayer;

import vesta.mc.NewState;
import vesta.mc.ParametersForState;

public class CoinFlipJNISimState extends NewState {
	
	static {
		System.loadLibrary("coinflib");
	}
	
	private CoinFlipWrapper simulator;

	public CoinFlipJNISimState(ParametersForState parameters) {
		super(parameters);
		simulator = new CoinFlipWrapper(0.55);
	}
	
	public double getTime() {
		return simulator.getTime();
	}

	public void performOneStepOfSimulation() {
		simulator.performOneStepOfSimulation();
		//incrementNumberOfSteps(); //increments steps for the both iterations, so will run 16 times
	}

	public void performWholeSimulation() {
		simulator.performWholeSimulation();
		//setNumberOfSteps(10); // needs to be setup in C++ side as well
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
		} else {
			return simulator.rval(obs);
		}
	}
	
	

}
