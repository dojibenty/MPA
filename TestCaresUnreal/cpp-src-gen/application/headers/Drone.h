/*
 * Drone.h
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */
#ifndef Drone_H_
#define Drone_H_
#include "Clock.h"
class compDrone;
	// Inputs
#include "Vector3.h"
#include "Vector3.h"
#include "Vector3.h"


// Start of user code  : Additional imports for Drone
// End of user code

class Drone {

	protected :
              compDrone *myContainer;

	// Inputs
	          Vector3 newLocation;
	// Outputs
	          Vector3 location;
	// Parameters
	          double speed;
	          Vector3 currentLocation;


// Start of user code  : Properties of Drone
// End of user code

	public :
            Drone(compDrone *container);
            ~Drone();
	        void initialize();
	       void end();

	       void doStep(int nStep) ;
	
	
// Start of user code  : Additional methods

// End of user code
	

	     void setNewLocation(Vector3 arg) ;

	    Vector3 getLocation();
	// +++++++++++++ Access for speed parameter +++++++++++++
	    double getSpeed();
	
	    void setSpeed(double arg);
	// +++++++++++++ Access for currentLocation parameter +++++++++++++
	    Vector3 getCurrentLocation();
	
	    void setCurrentLocation(Vector3 arg);
};
#endif /*  Drone_H_ */
