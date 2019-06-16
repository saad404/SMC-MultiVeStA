package mock;

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

}
