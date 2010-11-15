/*
 * sensor.cpp
 *
 *  Created on: 22 Jul 2010
 *      Author: hauk
 */

#include "include/sensor.h"
#include "include/random.h"

using namespace std;

Sensor::Sensor()
{
	xLat = 0;
	yLong = 0;

	range = 0;
	numDetected = 0;
	displayed = false;
}

Sensor::~Sensor()
{

}

void Sensor::assignPositions()
{
	//Temp integers to store new X,Y co-ordinates
	int randX, randY;
	//int randMax = 200;

	//Generate random position for sensor between 0 and 200
	//Then add to MIN_SENSOR_FLOOR to get a co-ordinate in the right region.

	//Generate x co-ordinate
	randX = (400) + getRandom(MAX_SENSOR_WIDTH);

	this->setXLat(randX);

	cout << "randX in assignPositions function is " << randX << endl;

	//Generate y co-ordinate
	randY = getRandom(MAX_SENSOR_CEILING);

	cout << "randY in assignPositions function is " << randY << endl;

	this->setYLong(randY);

	clog << "Position set" << endl;
}

void Sensor::scanForThreat(vector<Missile*> missiles)
{
	int distance;
	int radSquared;

	int numDetected;

	//Using Pythagoras Theorem to get distance between two points.
	for(unsigned int i = 0; i < missiles.size(); i++)
	{
		radSquared = ((this->getRange()) * (this->getRange()));

		//Square root function is a time consuming operation
		//so squaring the final value and compare it to the range squared should speed things up.
		distance = ((this->getX() - missiles.at(i)->getX()) *  (this->getX() - missiles.at(i)->getX()) + (this->getY() - missiles.at(i)->getY()) *  (this->getY() - missiles.at(i)->getY()));


		//If distance is < than range of the sensor.
		if((distance < radSquared) && (missiles.at(i)->getDiscovered() == false))
		{
			//Set missile discovered.
			missiles.at(i)->setDiscovered(true);

			numDetected = (this->getNumDetected() + 1);

			this->setDetected(numDetected);

			//Log threat to system
			//clog << "Threat detected!" << "by Sensor ID: " << this->getID() << endl;
		}
	}
}

void Sensor::assignID()
{
	//assign ID to Sensor.
	int randTemp;

	randTemp = getRandom(100000);

	id = randTemp;
}
