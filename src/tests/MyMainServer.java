package tests;

import jnisimulator.ServerJNISimulatorState;
import vesta.mc.ParametersForState;

public class MyMainServer {
	public static void main(String[] args) {
		ServerJNISimulatorState SimuState = new ServerJNISimulatorState(new ParametersForState("none", ""));
		int maxNumberOfEvents = 20;
		int maxSteps = maxNumberOfEvents + 3;
		for (int i = 0; i < 2; i++) {
			for (int seed = 0; seed < 2; seed++) {
				SimuState.setMaxNumberOfEvents(maxNumberOfEvents);
				SimuState.setSimulatorForNewSimulation(seed);
				for (int steps = 1; steps < maxSteps; steps++) {
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
