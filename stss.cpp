/*
 * stss.cpp
 *
 *  Created on: 18 Aug 2010
 *      Author: hauk
 */

#include <iostream>

#include "include/stss.h"

using namespace std;

STSS::STSS()
{
	//Constructor
	xLat = 0;
	yLong = 400;

	//Set scan ranges
	scanXLat = 20;
	scanYLong = 10;

	range = 80;
}

STSS::~STSS()
{
	//Destructor
}

void STSS::initSTSSRadar(vector<Missile*> missiles)
{

}

void STSS::stssScan(vector<Missile*> missiles, ThreatID * threatLog)
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

			threatLog->push_back(missiles.at(i)->getID());

			//Log threat to system
			//clog << "Threat detected!" << "by Sensor ID: " << this->getID() << endl;
		}
	}
}
