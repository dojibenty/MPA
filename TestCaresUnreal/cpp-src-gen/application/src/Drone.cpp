/*
 * Drone.cpp
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

#include "Drone.h"
#include "compDrone.h"
// Start of user code  : Additional imports for Drone
// End of user code


Drone::Drone(compDrone *container)	{
		myContainer = container;
// Start of user code  : Implementation of constructor method

// End of user code
	}
Drone::~Drone(){
// Start of user code  : Implementation of destructor method

// End of user code
	}
void Drone::initialize() {
// Start of user code  : Implementation of initialize method

// End of user code
	}

void Drone::end() {
// Start of user code  : Implementation of end method

// End of user code
	}

void Drone::doStep(int nStep) {
// Start of user code  : Implementation of doStep method
		// to implement
// End of user code
	}
	
	
// Start of user code  : Additional methods

// End of user code
	

void Drone::setNewLocation(Vector3 arg) {
		newLocation = arg;
	}

Vector3 Drone::getLocation() {
		return location;
	}
	// +++++++++++++ Access for speed parameter +++++++++++++
double Drone::getSpeed() {
		return speed;
	}
	
void Drone::setSpeed(double arg) {
		speed = arg;
	}
	// +++++++++++++ Access for currentLocation parameter +++++++++++++
Vector3 Drone::getCurrentLocation() {
		return currentLocation;
	}
	
void Drone::setCurrentLocation(Vector3 arg) {
		currentLocation = arg;
	}
