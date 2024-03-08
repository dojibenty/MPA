package cares.framework;

public class Clock {
	
	static protected long startTime = 0; // UTC epoch
	static protected long stepTime = 1;   // in ms
	static protected long currentTime = 0; // UTC epoch
	static protected long endTime = 0; // UTC epoch
	
	static protected boolean end;

	static public long getEndTime() {
		return endTime;
	}

	static public void Init(long oneStartTime,long oneStepTime,long oneEndTime) {
		startTime = oneStartTime;
		currentTime = startTime;
		stepTime = oneStepTime;
		endTime = oneEndTime;
		end = false;
	}

	static public long getStartTime() {
		return startTime;
	}
	static public long getStepTime() {
		return stepTime;
	}	
	static public long getCurrentMS() {
		return currentTime;
	}	
	static public double getCurrentSecond() {
		double result = currentTime/1000.0;
		return (result);
	}	
	
	static public void setStepTime(int oneStepTime) {
		stepTime = oneStepTime;
	}
	
	static public void doStep() {
		currentTime += stepTime;
	}
	
	static public void stop() {
		end = true;
	}
	
	static public boolean isFinished() {
		return ((currentTime > endTime) || end);
	}
}
