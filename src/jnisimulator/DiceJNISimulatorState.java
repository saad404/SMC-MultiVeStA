package jnisimulator;

import vesta.mc.NewState;
import vesta.mc.ParametersForState;

public class DiceJNISimulatorState extends NewState {
	private DiceSimulatorState simulator;
	
	public DiceJNISimulatorState(ParametersForState parameters) {
		super(parameters);
		// TODO Auto-generated constructor stub
		simulator = new DiceSimulatorState();
	}
	

}
