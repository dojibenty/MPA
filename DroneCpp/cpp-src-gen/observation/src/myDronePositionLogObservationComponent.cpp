/*
 * myDronePositionLogObservationComponent
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

#include "myDronePositionLogObservationComponent.h"
#include <iostream>
using namespace std;

myDronePositionLogObservationComponent::myDronePositionLogObservationComponent(string filename, double aFrequency): LogComponent( filename, aFrequency){
	try{
        WriteFirstLine();
	}
	catch (exception &e) {cerr << "myDronePositionLogObservationComponent : " << e.what() << endl;}
}
myDronePositionLogObservationComponent::~myDronePositionLogObservationComponent(){}

void myDronePositionLogObservationComponent::readInputs() {
    instPosition = theDrone->getPosition();
	}

void myDronePositionLogObservationComponent::WriteFirstLine() {
    string s = "time(ms)";
        s = s + ";" + "X.x;Y.y;Z.z";
		writeNames( s);
		endLine();
	}

void myDronePositionLogObservationComponent::setDrone(Drone *myDrone) {
		theDrone = myDrone;
	}

void myDronePositionLogObservationComponent::doStep(int nStep) {
	Clock *c = Clock::getInstance();
	readInputs();
	//int i = 0;
    long t = c->getCurrentMS();
    string s = to_string( t) + ";";
		try{

			s = s + to_string(instPosition.getX()) + ";";
			s = s + to_string(instPosition.getY()) + ";";
			s = s + to_string(instPosition.getZ()) + ";";		}
		catch (exception &e) {cerr << e.what() << endl;}

		//on retire le dernier ";" separateur
		//s = s.substring(0, s.length() - 1);
        cout << "mySwimmerPositionLogObservationComponent::doStep : " << s << endl;
		writeNames( s);
		endLine();
    }
