/*
 * missile.h
 *
 *  Created on: 22 Jul 2010
 *      Author: hauk
 */

#ifndef MISSILE_H_
#define MISSILE_H_

#define MAX_X_SPAWN 1000
#define MAX_Y_SPAWN 710

#

#define MAX_TRGT_ASSIGNABLE 3

#include <iostream>
#include <vector>

#include "target.h"

using namespace std;

class Missile
{
	public:

		Missile();
		~Missile();

		inline void setXLat(int x);
		inline void setYLong(int y);
		void setTargetID(int newTarget);
		void setReserved(bool setReserved);
		void setDiscovered(bool newThreat);
		void setDestroyed(bool newDest);

		int getX() { return xLat; };
		int getY() { return yLong; };
		int getID() { return id; };
		int getTargetID() { return targetID; };
		int getDamage() { return damage; };
		bool getReserved() { return reserved; };
		bool getDiscovered() { return discovered; };
		bool getDestroyed() { return destroyed; };

		void spawnMissilePoint();

		void assignID();

	protected:

		int id, damage, targetID;
		int xLat, yLong;

		double speed, accuracy;
		bool spawned, reserved, discovered, destroyed;

	private:

};

#endif /* MISSILE_H_ */
