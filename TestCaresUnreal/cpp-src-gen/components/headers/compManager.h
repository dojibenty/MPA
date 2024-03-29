/*
 * compManager.h
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

#ifndef compManager_H_
#define compManager_H_

#include "LeafComponent.h"
class Manager;

#include "Vector3.h"
#include "Vector3.h"
#include "Vector3.h"



class compManager : public LeafComponent {

	protected :
/*pyp : inutile
	//inputs source
	 LeafComponent DrLocationSourceComponent;
	 String portNameDrLocation;
*/
	 Vector3 oldNewLocation;
	 Vector3 newNewLocation;

	 bool newValue;
	 int delay;


	Manager *appli;

	public :
           compManager(double aFrequency);
           virtual ~compManager();
	       void doOneStep();
	       void doStep(int nStep);

	       virtual void readInputs() ;
	       void initialize();
	       void end();
	
	     Vector3 getNewLocation();
	     Manager *getAppli() ;
	// +++++++++++++ Access for direction parameter +++++++++++++
	     Vector3 getDirection();
	
	     void setDirection(Vector3 arg);
};
#endif /* compManager_H_ */
