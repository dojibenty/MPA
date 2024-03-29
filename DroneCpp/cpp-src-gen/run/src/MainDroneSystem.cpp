/* 
 * Main for simulation
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

//#include "DroneSystem.h"
#include "ScenarLog.h"
#include "myDronePositionLogObservationComponent.h"
// Start of user code  : Additional imports for testDrone
// End of user code

/* 
 * MainDroneSystem for simulation
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

//import cares.framework.JsonSeries;
//import cares.framework.LogComponent;
#include "DroneSystem.h"
#include "ScenarLog.h"
//#include "DronePositionLogObservationComponent.h"
// Start of user code  : Additional imports for testDrone
// End of user code

int main() {
		DroneSystem *root = new DroneSystem();
		root->get_InstDrone()->setSpeed( 2.0);
		for(int i = 0; i < 2; i++){
        	//pyp : configuration des switches et autres actions
            root->get_InstDrone()->setDirection( "(1,0,1)");
			root->initialize();
			//pyp : run des observations
			ScenarLog *simulatedScenario = new ScenarLog(root);
            string si = to_string(i);
            string fileName = "DronePosition";
            string completeFileName = fileName + si;
	   		myDronePositionLogObservationComponent *DronePositionLogObservationComponent = new myDronePositionLogObservationComponent( completeFileName, 1.0);
			DronePositionLogObservationComponent->setDrone( root->get_InstDrone()->getAppli());
       	    simulatedScenario->push( DronePositionLogObservationComponent);
        
        
			simulatedScenario->setTime(0,100000);
			simulatedScenario->startSimulation();
			root->end();
        	simulatedScenario->end();
        }
// Start of user code  : Additional code main for testDrone
// End of user code
	}

