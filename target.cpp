/*
 * target.cpp
 *
 *  Created on: 28 Jul 2010
 *      Author: hauk
 */

#include "include/target.h"

using namespace std;

Target::Target()
{
	//Initialise Target
	destroyed = false;
	health = 100;
	assetValue = 100000;
	humanValue = 5000;
	currMissiles = 0;
}

Target::~Target()
{
	//destructor
}

void Target::setupTargetPos(int index)
{

	if(index == 0)
	{
		this->setXLat(150);
		this->setYLat(80);
	}
	else if(index == 1)
	{
		this->setXLat(195);
		this->setYLat(200);
	}
	else if(index == 2)
	{
		this->setXLat(610);
		this->setYLat(255);
	}
	else if(index == 3)
	{
		this->setXLat(570);
		this->setYLat(500);
	}
	else if(index == 4)
	{
		this->setXLat(185);
		this->setYLat(390);
	}
	else if(index == 5)
	{
		this->setXLat(390);
		this->setYLat(480);
	}
	else if(index == 6)
	{
		this->setXLat(410);
		this->setYLat(300);
	}
	else
	{
		cerr << "Error in indexing in function setupSensors()." << endl;
	}

	//Create new Target object
	//loop
		//assign id
		//add x, y lat
		//push back
}

void Target::setDamage(int newHealth)
{
	health = newHealth;

	if(health == 0)
	{
		destroyed = true;
	}
}

void Target::assignID()
{
	//assign ID to Sensor.
	int randTemp;

	randTemp = getRandom(100000);

	id = randTemp;
}
