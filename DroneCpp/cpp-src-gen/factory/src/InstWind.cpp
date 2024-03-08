/* 
 * InstWind.cpp
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

#include "InstWind.h"
#include "Wind.h"

InstWind::InstWind(double aFrequency)	: compWind(aFrequency){
		
}
InstWind::~InstWind()	{
		
}
void InstWind::setInstDrone(InstDrone *pInstDrone) {
		attInstDrone = pInstDrone;
}

void InstWind::readInputs() {
		appli->setPosition(attInstDrone->getPosition());
}


