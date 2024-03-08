package cares.framework;

public abstract class TimeableObject {
	
	protected double frequency;
	
	public double getFrequency() {
		return frequency;
	}
	
	public void setFrequency(double frequency) {
		this.frequency = frequency;
	}
	
	public abstract void doStep(int nStep);
}
