package cares.framework;

import java.util.ArrayList;
import java.util.List;

public abstract class Scenario {

	protected List<LeafComponent> leafComponents;
	protected List<LogComponent> csvLogs;//pyp
	protected List<JsonSeries> jsonLogs;//pyp

	protected RootComponent root;
	protected long min;
	protected long stepTime;
	protected long max;
	
	protected List<Long> periods; // ms
	
	protected int simulationNumber;
	
	public Scenario(RootComponent aRoot) {
		root = aRoot;
		leafComponents = root.getListLeafComponents();
		periods = new ArrayList<Long>();
		for( int i = 0; i<leafComponents.size(); ++i){
			long period;
			if (leafComponents.get(i).getFrequency()<=0) {
				period = 1;
			} else {
				period = Math.round(1000.0/(leafComponents.get(i).getFrequency()));
			}
			periods.add(period);
		}
		simulationNumber = 0;
		//pyp
		csvLogs = new ArrayList<LogComponent>();
		jsonLogs = new ArrayList<JsonSeries>();
	}
	
	public void initialize() {		//pyp
		csvLogs = new ArrayList<LogComponent>();
		jsonLogs = new ArrayList<JsonSeries>();	
	}
	
	public void setTime(long min, long max) {
		this.min = min;
		this.stepTime=1;
		this.max=max;
	}

	public void startSimulation() {
	
		Clock.Init(min, stepTime,max);
		simulationNumber++;
		System.out.println("simulation number : "+simulationNumber);
				
		while (! Clock.isFinished()) {
			// scenario events
			eventSimulation();
			
			// run des composants
			for( int i = 0; i<leafComponents.size(); ++i){
				if (((Clock.getCurrentMS() % periods.get(i)) == 0)&&leafComponents.get(i).isActive()){
					leafComponents.get(i).doStep(leafComponents.get(i).getDelayMax());
				}
			}
			//pyp : run des observations
			for( TimeableObject lc : getCsvLogs()){
				long periode = (long)( 1 / lc.getFrequency()) * 1000L;//ms
				if ((Clock.getCurrentMS() % periode) == 0){
					
					lc.doStep( 0);
				}
			}
			for( TimeableObject lc : getJsonLogs()){
				long periode = (long)( 1 / lc.getFrequency()) * 1000L;//ms
				if ((Clock.getCurrentMS() % periode) == 0){
					
					lc.doStep( 0);
				}
			}
			
			//fin pyp
			Clock.doStep();
			if (Clock.getCurrentMS() % (Clock.getEndTime()/20) == 0) {
				System.out.println((int)(100*((double)Clock.getCurrentMS()/Clock.getEndTime()))+" %");
			}
		}
	}

	public abstract void eventSimulation();
	//pyp
	public List<LogComponent> getCsvLogs() {
		return csvLogs;
	}
	public List<JsonSeries> getJsonLogs() {
		return jsonLogs;
	}
	public void end() {
        for(JsonSeries js: this.getJsonLogs()){
        	js.end();
        }
        for(LogComponent lc: this.getCsvLogs()){
        	lc.close();
        }
		
	}
}
