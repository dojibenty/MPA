/*
 * WindData
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

#ifndef WindData_H_
#define WindData_H_

#include <vector>
#include <iostream>
using namespace std;
// Start of user code  : Additional imports for WindData
// End of user code

class WindData {

	protected :
             Vector3 position;
             Vector3 force;

	public :
             WindData();
             virtual ~WindData();
             WindData( Vector3 varposition, Vector3 varforce);

	         Vector3 getPosition () ;

	         void setPosition (Vector3 varposition ) ;
	         Vector3 getForce () ;

	         void setForce (Vector3 varforce ) ;
// Start of user code  : Additional methods

// End of user code

};
#endif /* WindData_H_ */