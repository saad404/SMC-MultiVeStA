package tests;

import jnisimulator.CoinFlipJNISimulatorState;
import jnisimulator.CoinFlipWrapper;
import vesta.mc.ParametersForState;

public class MyMain {
	public static void main(String[] args) {
		CoinFlipJNISimulatorState SimuState = new CoinFlipJNISimulatorState(new ParametersForState("none", ""));
		for (int i = 0; i < 2; i++) {
			for (int seed = 0; seed < 2; seed++) {
				SimuState.setSimulatorForNewSimulation(seed);
				for (int steps = 1; steps < 5; steps++) {
					SimuState.performOneStepOfSimulation();
					System.out.println("i: " + i + " seed: " + seed + " steps: " + steps);
					System.out.println("\tCurrent time is: " + SimuState.getTime());
					System.out.println("\tCurrent steps are: " + SimuState.rval("steps"));
					System.out.println("\tCurrent heads are: " + SimuState.rval("heads"));
					System.out.println("\tCurrent tails are: " + SimuState.rval("tails"));
					System.out.println("Current flips performed are: " + SimuState.rval("flips_performed"));
//					SimuState.performWholeSimulation();
//					SimuState.rval(1);
//					SimuState.rval("1");
				}
				
			}
		}
		
		
	}

}
