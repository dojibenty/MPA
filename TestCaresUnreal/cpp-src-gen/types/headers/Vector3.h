/*
 * Vector3
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */

#ifndef Vector3_H_
#define Vector3_H_

#include <vector>
#include <iostream>
using namespace std;
// Start of user code  : Additional imports for Vector3
// End of user code

class Vector3 {

	protected :
             double x;
             double y;
             double z;

	public :
             Vector3();
             virtual ~Vector3();
             Vector3( double varx, double vary, double varz);
             
             const Vector3 ZERO;
             Vector3(0,0,0) : ZERO(0,0,0) { }

	         double getX () ;

	         void setX (double varx ) ;
	         double getY () ;

	         void setY (double vary ) ;
	         double getZ () ;

	         void setZ (double varz ) ;
// Start of user code  : Additional methods

// End of user code

};
#endif /* Vector3_H_ */
