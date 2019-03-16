package tests;

import jnisimulator.*;
import vesta.mc.ParametersForState;

public class MyMainDice {

	public static void main(String[] args) {
		DiceJNISimulatorState SimuState = new DiceJNISimulatorState(new ParametersForState("none", ""));
		for (int i = 0; i < 2; i++) {
			for (int seed = 0; seed < 2; seed++) {
				SimuState.setSimulatorForNewSimulation(seed);
				for (int steps = 1; steps < 5; steps++) {
					SimuState.performOneStepOfSimulation();
					System.out.println("i: " + i + " seed: " + seed + " steps: " + steps);
					System.out.println("\tCurrent time is: " + SimuState.getTime());
					System.out.println("\tCurrent steps are: " + SimuState.rval("steps"));
					System.out.println("\tCurrent value of rolled 1s are: " + SimuState.rval("one"));
					System.out.println("\tCurrent value of rolled 2s are: " + SimuState.rval("two"));
					System.out.println("\tCurrent value of rolled 3s are: " + SimuState.rval("three"));
					System.out.println("\tCurrent value of rolled 4s are: " + SimuState.rval("four"));
					System.out.println("\tCurrent value of rolled 5s are: " + SimuState.rval("five"));
					System.out.println("\tCurrent value of rolled 6s are: " + SimuState.rval("six"));
					System.out.println("Current rolls performed are: " + SimuState.rval("rolls_performed"));
//					SimuState.performWholeSimulation();
//					SimuState.rval(1);
//					SimuState.rval("1");
					
				}
				
			}
		}

	}

}
