package jnisimulator;

import vesta.mc.NewState;
import vesta.mc.ParametersForState;

public class CoinFlipJNISimulatorState extends NewState {
	
	private CoinFlipWrapper simulator;

	public CoinFlipJNISimulatorState(ParametersForState parameters) {
		super(parameters);
		simulator = new CoinFlipWrapper(55);
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
		} else {
			return simulator.rval(obs);
		}
	}
	
	

}
