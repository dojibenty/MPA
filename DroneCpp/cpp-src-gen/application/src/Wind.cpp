/*
 * Wind.cpp
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

#include "Wind.h"
#include "compWind.h"
// Start of user code  : Additional imports for Wind
// End of user code


Wind::Wind(compWind *container)	{
		myContainer = container;
// Start of user code  : Implementation of constructor method

// End of user code
	}
Wind::~Wind(){
// Start of user code  : Implementation of destructor method

// End of user code
	}
void Wind::initialize() {
// Start of user code  : Implementation of initialize method

// End of user code
	}

void Wind::end() {
// Start of user code  : Implementation of end method

// End of user code
	}

void Wind::doStep(int nStep) {
// Start of user code  : Implementation of doStep method
		// to implement
// End of user code
	}
	
	
// Start of user code  : Additional methods

// End of user code
	

void Wind::setPosition(Vector3 arg) {
		position = arg;
	}

Vector3 Wind::getForce() {
		return force;
	}
	// +++++++++++++ Access for windData parameter +++++++++++++
WindData Wind::getWindData() {
		return windData;
	}
	
void Wind::setWindData(WindData arg) {
		windData = arg;
	}

