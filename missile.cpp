/*
 * missile.cpp
 *
 *  Created on: 22 Jul 2010
 *      Author: hauk
 */

#include <iostream>

#include "include/random.h"
#include "include/missile.h"

using namespace std;

Missile::Missile()
{
	//Initialise missiles.
	spawned = false;
	reserved = false;
	discovered = false;
	damage = 20;
	destroyed = false;
}

Missile::~Missile()
{
	//Clean up missiles.
}

void Missile::setXLat(int x)
{
	xLat = x;
}

void Missile::setYLong(int y)
{
	yLong = y;
}

void Missile::setTargetID(int newTarget)
{
	targetID = newTarget;
}

void Missile::setReserved(bool setReserved)
{
	reserved = setReserved;
}

void Missile::setDiscovered(bool newThreat)
{
	discovered = newThreat;
}

void Missile::setDestroyed(bool newDest)
{
	destroyed = newDest;
}

void Missile::spawnMissilePoint()
{
	//This function takes the vector of missiles
	//Randomly assigns values to xLat and yLong.

	int randX, randY;

	//Generate x co-ordinate
	randX =  (1100) + getRandom(180);

	//Generate y co-ordinate
	randY = getRandom(MAX_Y_SPAWN);

	//Set x co-ordinate
	this->setXLat(randX);

	//Set y co-ordinate
	this->setYLong(randY);
}

void Missile::assignID()
{
	//assign ID to Sensor.
	int randTemp;

	randTemp = getRandom(100000);

	id = randTemp;
}
