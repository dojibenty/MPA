package cares.framework;

import cares.framework.TimeableObject;

public abstract class LeafComponent extends TimeableObject {
	protected int delayMax;
	protected boolean isActive;

	public boolean isActive() {
		return isActive;
	}

	public int getDelayMax() {
		return delayMax;
	}

	public void setDelayMax(int delayMax) {
		this.delayMax = delayMax;
	}
	
	public boolean start() {
		isActive = true;
		return isActive;
	}
	
	public boolean stop() {
		isActive = false;
		return isActive;
	}
}
