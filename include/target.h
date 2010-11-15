/*
 * target.h
 *
 *  Created on: 28 Jul 2010
 *      Author: hauk
 */

#ifndef TARGET_H_
#define TARGET_H_

#define TARGET_FLOOR_MIN 600
#define TARGET_WIDTH_MAX 1280
#define MAX_RAND 200

#include <iostream>
#include <vector>

#include "random.h"

using namespace std;

class Target
{
	public:

		Target();
		~Target();

		int getID() { return id; };
		int getXLat() { return xLat; };
		int getYLong() { return yLong; };
		int getHumans() { return humanValue; };
		int getCurrMissiles() { return currMissiles; };
		int getHealth () { return health; };


		bool getAssiMissile() { return assignedMissile; };

		inline void setID(int newID) { id = newID; };
		void setDamage(int health);
		void assignID();


		inline void setXLat(int x) { xLat = x; };
		inline void setYLat(int y) { yLong = y; };
		void setupTargetPos(int index);
		inline void setHumanLoss(int loss) { humanValue = loss; };
		inline void setAssiMissile(bool tempBool) { assignedMissile = tempBool; };
		inline void setCurrMissiles(int tempMissile) { currMissiles = tempMissile; };

	protected:

	private:

		int id, health, assetValue, humanValue, currMissiles;
		int xLat, yLong;
		bool assignedMissile, destroyed;

};

#endif /* TARGET_H_ */
