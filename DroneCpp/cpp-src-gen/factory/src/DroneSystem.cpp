/* 
 * DroneSystem.cpp
 * Root Component
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */
#include "DroneSystem.h"
#include "Drone.h"
#include "Wind.h"
InstDrone *DroneSystem::get_InstDrone() {
		return instInstDrone;
	}
InstWind *DroneSystem::get_InstWind() {
		return instInstWind;
	}

DroneSystem::DroneSystem() {
	//leafComponents = new std::vector<LeafComponent*>();
	instInstDrone = new InstDrone(0.0);
	leafComponents.push_back(instInstDrone);
	instInstWind = new InstWind(0.0);
	leafComponents.push_back(instInstWind);
	instInstDrone->setInstWind(instInstWind);
	instInstWind->setInstDrone(instInstDrone);
	}
DroneSystem::~DroneSystem() {}
void DroneSystem::initialize() {
	instInstDrone->setSpeed(1.);
	instInstDrone->setDirection(Vector3.FORWARD);
	instInstDrone->setDrPosition(Vector3.ZERO);
	//instInstDrone->setFrequency(0.0);
	instInstWind->setWindData(new WindData(Vector3.ZERO,Vector3.ZERO));
	//instInstWind->setFrequency(0.0);
	if(instInstDrone->getIsActive()) instInstDrone->initialize();
	if(instInstWind->getIsActive()) instInstWind->initialize();
// Start of user code  : Implementation of initialize method DroneSystem
// End of user code
	}

void DroneSystem::end() {
	instInstDrone->end();
	instInstWind->end();
// Start of user code  : Implementation of initialize method DroneSystem
// End of user code
	}
