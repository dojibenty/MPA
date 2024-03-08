/*
 * Manager.h
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */
#ifndef Manager_H_
#define Manager_H_
#include "Clock.h"
class compManager;
	// Inputs
#include "Vector3.h"
#include "Vector3.h"
#include "Vector3.h"


// Start of user code  : Additional imports for Manager
// End of user code

class Manager {

	protected :
              compManager *myContainer;

	// Inputs
	          Vector3 drLocation;
	// Outputs
	          Vector3 newLocation;
	// Parameters
	          Vector3 direction;


// Start of user code  : Properties of Manager
// End of user code

	public :
            Manager(compManager *container);
            ~Manager();
	        void initialize();
	       void end();

	       void doStep(int nStep) ;
	
	
// Start of user code  : Additional methods

// End of user code
	

	     void setDrLocation(Vector3 arg) ;

	    Vector3 getNewLocation();
	// +++++++++++++ Access for direction parameter +++++++++++++
	    Vector3 getDirection();
	
	    void setDirection(Vector3 arg);
};
#endif /*  Manager_H_ */