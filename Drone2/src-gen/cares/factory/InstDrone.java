/* 
 * InstDrone.java
 * Root Component
 *
 * Generated by Cares generator, written with Acceleo
 * Author: jpb
 */

package cares.factory;

import cares.components.compDrone;

public class InstDrone extends compDrone {

	protected InstWind attInstWind;

	public InstDrone()	{
		super();
	}

	public void setInstWind(InstWind pInstWind) {
		this.attInstWind = pInstWind;
	}

	public void readInputs() {
		appli.setForce(attInstWind.getForce());
	}
}