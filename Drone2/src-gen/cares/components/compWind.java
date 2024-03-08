/*
 * Wind.java
 *
 * Generated by Cares generator, written with Acceleo
 * Author: jpb
 */

package cares.components;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import cares.framework.LeafComponent;

import cares.application.*;

import cares.types.Vector3;
import cares.types.WindData;



public class compWind extends LeafComponent {

	//inputs source
	protected LeafComponent PositionSourceComponent;
	protected String portNamePosition;

	protected Vector3 oldForce;
	protected Vector3 newForce;
	protected boolean newValue;
	protected int delay;


	protected Wind appli;

	public compWind()	{
		appli = new Wind(this);
		delay = 0;
		delayMax = 0;
		newValue = false;
		isActive = true;
		oldForce = appli.getForce();
		newForce = appli.getForce();
	}

	public void doOneStep() {
		if (newValue) {
			delay++;
			if (delay == delayMax) {
					oldForce = newForce;
					newValue = false;
			}
		}
	}

	public void doStep(int nStep) {	
		if (newValue) {
			oldForce = newForce;
			newValue = false;
		}
		this.readInputs();
		appli.doStep(nStep);
		newForce = appli.getForce();
		if (delayMax == 0) {
			oldForce = newForce;
			newValue = false;
		} else {
			newValue = true;
			delay = 0;
		}
	}

	public void readInputs() {
	}
	
	public void initialize() {
		appli.initialize();
	}

	public void end() {
		appli.end();
	}
	
	public Vector3 getForce() {
		return oldForce;
	}
	public Wind getAppli() {
		return appli;
	}
	// +++++++++++++ Access for windData parameter +++++++++++++
	public WindData getWindData() {
		return appli.getWindData();
	}
	
	public void setWindData(WindData arg) {
		appli.setWindData(arg);
	}
}
