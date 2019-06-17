package tests;

import jnilayer.ServerJNISimState;
import vesta.mc.ParametersForState;

public class MyMainServer {
	public static void main(String[] args) {
		ServerJNISimState SimuState = new ServerJNISimState(new ParametersForState("none", ""));
		for (int i = 0; i < 2; i++) {
			for (int seed = 0; seed < 2; seed++) {
				SimuState.setSimulatorForNewSimulation(seed);
				for (int steps = 1; steps < 5; steps++) {
					SimuState.performOneStepOfSimulation();
					System.out.println("i: " + i + " seed: " + seed + " steps: " + steps);
					System.out.println("\tCurrent time is: " + SimuState.getTime());
					System.out.println("\tCurrent steps are: " + SimuState.rval("steps"));
					System.out.println("\tCurrent size of queue is: " + SimuState.rval("size"));
				}
				
			}
		}
		
		
	}

}
