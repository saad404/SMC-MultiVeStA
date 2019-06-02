package entrypoint;

import entrypointmultivesta.UniqueEntryPoint;

public class MultivestaJNIEntryPoint {
	public static void main(String[] args) {
		if(args==null || args.length==0) {
			String[] mvargs = {
					"-c", 
					"-sm", "false", 
					"-sd", "jnisimulator.ServerJNISimulatorState",
					"-bs", "20", 
					"-l", "oneLocal", 
					"-f", "stepsAfterXSteps.quatex", 
					"-a", "0.05", 
					"-d1", "0.1"
			};
			UniqueEntryPoint.main(mvargs);
		}
		else {
			UniqueEntryPoint.main(args);
		}
	}
}
