/* 
 * InstDrone.h
 * Root Component
 *
 * Generated by Cares generator, written with Acceleo
 * Author: pyp
 */
#ifndef InstDrone_H_
#define InstDrone_H_

#include "compDrone.h"
#include "MainManager.h"
class MainManager;

class InstDrone : public compDrone {
	protected :
              MainManager *attMainManager;

	public :

            InstDrone(double aFrequency);
            virtual ~InstDrone();

	        void setMainManager(MainManager *pMainManager);

	        void readInputs()  override;
};
#endif /*  InstDrone_H_ */
