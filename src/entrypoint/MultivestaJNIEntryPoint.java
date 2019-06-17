package entrypoint;

import entrypointmultivesta.UniqueEntryPoint;

public class MultivestaJNIEntryPoint {
	public static void main(String[] args) {
		if(args == null || args.length == 0) {
			String[] mvargs = {
					"-c", 
					"-sm", "false", 
					"-sd", "jnilayer.ServerJNISimState",
					"-bs", "20", 
					"-l", "oneLocal", 
					"-f", "Server.quatex", 
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
