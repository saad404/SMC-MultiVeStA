package jnisimulator;

public class CoinFlipWrapper {
	
	public CoinFlipWrapper(double bias) {
		setBias(bias);
		// TODO Auto-generated constructor stub
	}
	public native void setBias(double bias);
	public native double getTime();
	public native void performOneStepOfSimulation();
	public native void performWholeSimulation();
	public native void setSimulatorForNewSimulation(int seed);
	public native double rval(int obs);
	public native double rval(String obs);
	
	
	
//	public double getTime() {
//		int ret = 0;// TODO Invoke corresponding method on C++
//		return ret;
//	}
//
//	public void performOneStepOfSimulation() {
//		// TODO Invoke corresponding method on C++
//	}
//
//	public void performWholeSimulation() {
//		// TODO Invoke corresponding method on C++
//	}
//
//	public void setSimulatorForNewSimulation(int seed) {
//		// TODO Invoke corresponding method on C++	
//	}
//
//	public double rval(int obs) {
//		int ret = 0;// TODO Invoke corresponding method on C++
//		return ret;
//	}
//
//	public double rval(String obs) {
//		int ret = 0;// TODO Invoke corresponding method on C++
//		return ret;
//	}

}