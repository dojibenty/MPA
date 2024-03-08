package cares.framework;

import java.util.List;

public abstract class RootComponent {
	
	protected List<LeafComponent> instances;
	
	public List<LeafComponent> getListLeafComponents() {
		return instances;
	}
	
	public abstract void initialize();
}
