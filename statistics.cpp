/*
 * statistics.cpp
 *
 *  Created on: 12 Aug 2010
 *      Author: hauk
 */

#include "include/statistics.h"

using namespace std;

Statistics::Statistics()
{
	dtctdPerSensor = 0;
	avgHealth = 0;
	totalSatDetected = 0;
}

Statistics::~Statistics()
{

}

void Statistics::setTotalMissiles(vector<Missile*> missiles)
{
	//Set total missiles
	totalMiss = missiles.size();
}

void Statistics::setTotalSensors(vector<Sensor*> sensors)
{
	totalSensors = sensors.size();
}

void Statistics::setUndetectedMiss(vector<Missile*> missiles)
{
	int undetected;

	undetected = 0;

	for(unsigned int i = 0; i < missiles.size(); i++)
	{
		if(missiles.at(i)->getDiscovered() == false)
			undetected++;
	}

	undetectedMissiles = undetected;
}

void Statistics::setDetectedMiss(vector<Missile*> missiles)
{
	int detected;

	detected = 0;

	for(unsigned int i = 0; i < missiles.size(); i++)
	{
		if(missiles.at(i)->getDiscovered() == true)
			detected++;
	}

	totalDetected = detected;
}

void Statistics::setAvgHealth(vector<Target*> targets)
{
	//Create an avg int.
	int totalHealth;

	totalHealth = 0;

	float avgTargetHealth;

	avgTargetHealth = 0;

	int totalTargets = 7;

	//Get sum total of damage from each target.
	for(unsigned int i = 0; i < targets.size(); i++)
	{
		totalHealth += targets.at(i)->getHealth();
	}

	avgTargetHealth = (totalHealth / totalTargets);

	avgHealth = avgTargetHealth;
}

void Statistics::setTotalSatTracking(ThreatID * threatLog)
{
	totalSatDetected = threatLog->size();
}

void Statistics::avgMissDetectedPerSensor(vector<Sensor*> sensors)
{
	int totalDetected, avgDetected;
	totalDetected = 0;

	for(unsigned int i = 0; i < sensors.size(); i++)
	{
		totalDetected = totalDetected + sensors.at(i)->getNumDetected();
		//cout << "total detected " << " for sensor" << i << ": " << totalDetected << endl;
	}

	//cout << "total detected: " << totalDetected;

	avgDetected = (totalDetected / sensors.size());

	dtctdPerSensor = avgDetected;
}
