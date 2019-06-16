package mock;

import vesta.mc.NewState;
import vesta.mc.ParametersForState;

public class DiceMockSimState extends NewState {
	
	static {
		System.loadLibrary("diceroll");
	}
	
	private DiceWrapper simulator;
	
	public DiceMockSimState(ParametersForState parameters) {
		super(parameters);
		simulator = new DiceWrapper();
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
