/*
 * gameWorld.cpp
 *
 *  Created on: 22 Jul 2010
 *      Author: hauk
 */

#include <iostream>
#include <vector>

#include "include/gameWorld.h"

using namespace std;

GameWorld::GameWorld(int a, int b, int sensorRange)
{
	//Set Simulated World variables/parameters
	numSensors = a;

	radarRange = sensorRange;

	numMissiles = b;

	numTargets = 7;

	ThreatID *threatIDs = new ThreatID();
}

GameWorld::~GameWorld()
{
	//Clean up
}


void GameWorld::updateTrajectory(vector<Missile*> missiles, vector<Target*> targets)
{
	//Works.

	for(unsigned int i = 0; i < targets.size(); i++)
	{
		for(unsigned int j = 0; j < missiles.size(); j++)
		{
			if(targets.at(i)->getID() == missiles.at(j)->getTargetID())
			{

				//Check co-ordinates of each and adjust accordingly.
				if(missiles.at(j)->getX() > targets.at(i)->getXLat())
				{
					// missile x--;
					missiles.at(j)->setXLat((missiles.at(j)->getX()) - 1);
				}
				else
				{
					// missile x++:
					missiles.at(j)->setXLat((missiles.at(j)->getX()) + 1);
				}

				//If y value of target is > y value of missile)
				if(missiles.at(j)->getY() > targets.at(i)->getYLong())
				{
					missiles.at(j)->setYLong((missiles.at(j)->getY()) - 1);
				}
				else
				{
					missiles.at(j)->setYLong((missiles.at(j)->getY()) + 1);
				}
			}
		}
	}
}

void GameWorld::clearDestMissiles(vector<Missile*> missiles)
{
	//Clear all missiles with destroyed == true
	vector<Missile*>::iterator b;

	b = missiles.begin();

	while(b != missiles.end())
	{
		if((*b)->getDestroyed() == true && (*b) != NULL)
		{
			missiles.erase(b);
			cout << "Missile deleted" << endl;
		}
		b++;
	}
}

void GameWorld::updateTargetDamage(vector<Target*> targets, vector<Missile*> missiles)
{
	//if x and y of missile are equal.
	//and target ids are the same.
		//do damage

	int randDamage;
	int totalDamage;

	vector<Missile*>::iterator iterTarget;

	for(unsigned int i = (targets.size() - 1); i > 0; i--)
	{
		iterTarget = missiles.begin();

		while(iterTarget != missiles.end())
		{
			//Missile has hit target.
			if((targets.at(i)->getID() == (*iterTarget)->getTargetID()) && ((*iterTarget)->getDestroyed() == false) && ((targets.at(i)->getXLat() == (*iterTarget)->getX()) && (targets.at(i)->getYLong() == (*iterTarget)->getY())))
			{
				//Incur damage.

				randDamage = getRandom(10);

				//cout << "randDamage is: " << randDamage;

				//cout << "target health:" << targets.at(i)->getHealth();

				totalDamage = ((targets.at(i)->getHealth() - ((*iterTarget)->getDamage()) + randDamage));

				targets.at(i)->setDamage(totalDamage);

				//cout << "target health: " << targets.at(i)->getHealth();

				//The missile has been destroyed, so destroy it.
				(*iterTarget)->setDestroyed(true);
			}

			iterTarget++;
		}
	}
}

void GameWorld::createSensors()
{
	Sensor * newSensor;

	//Create and add the required number of sensors to its vector.
	for(int k = 0; k < numSensors; k++)
	{
		newSensor = new Sensor();

		sensors.push_back(newSensor);
		clog << "Sensor created!" << endl;
	}

	//Assign ID's to each sensor.
	for(unsigned int i = 0; i < sensors.size(); i++)
	{
		cout << "ID Assigned." << endl;
		sensors.at(i)->assignID();
	}

	//Create a position on the map for each sensor
	for(unsigned int b = 0; b < sensors.size(); b++)
	{
		cout << "Position assigned" << endl;

		sensors.at(b)->assignPositions();
	}

	//Assign range
	for(unsigned i = 0; i < sensors.size(); i++)
	{
		sensors.at(i)->setRange(radarRange);
	}

	clog << "Done creating sensors" << endl;
}

void GameWorld::createTargets()
{
	Target * newTarget;

	//Initialise new target objects
	for(int i = 0; i < numTargets; i++)
	{
		//Create new targets and push_back()
		newTarget = new Target();
		targets.push_back(newTarget);
	}

	//Assign ID's
	for(unsigned int b = 0; b < targets.size(); b++)
	{
		targets.at(b)->assignID();
	}

	//Assign positions
	for(unsigned int a = 0; a < targets.size(); a++)
	{
		targets.at(a)->setupTargetPos(a);
	}
}

void GameWorld::createMissiles()
{
	Missile * newMissile;

	//Add the required number of missiles to its vector.
	for(int i = 0; i < numMissiles; i++)
	{
		newMissile = new Missile();

		//Create random ID number.
		//Assign to Missile ID.
		missiles.push_back(newMissile);
		clog << "Missiles created!" << endl;
	}

	cout << "number of missiles: " << missiles.size() << endl;
	cout << "numMissiles value: " << numMissiles << endl;

	//Assign ID's to all missiles
	for(unsigned int d = 0; d < missiles.size(); d++)
	{
		missiles.at(d)->assignID();
	}

	//Assign positions to missiles.
	for(unsigned int b = 0; b < missiles.size(); b++)
	{
		missiles.at(b)->spawnMissilePoint();
	}
}

void GameWorld::initSensorScan(vector<Sensor*> sensors, vector<Missile*> missiles)
{
	for(unsigned int i = 0; i < sensors.size(); i++)
	{
		sensors.at(i)->scanForThreat(missiles);
	}
}

void GameWorld::initSTSSScan(STSS * satRadar, ThreatID * threatLog, vector<Missile*> missiles)
{
	//Scan through missiles
	satRadar->stssScan(missiles, threatLog);
}

void GameWorld::updateSatPos(STSS * satRadar)
{
	//Y is static.

	int checkTop = satRadar->getX();

	//Need to make sure satellite doesn't leave area.
	if(checkTop == 1280)
	{
		satRadar->setXLat(0);
	}
	else
	{
		satRadar->setXLat((satRadar->getX() + 2));
	}
}

void GameWorld::calcStats(vector<Sensor*> sensors, vector<Missile*> missiles, vector<Target*> targets, Statistics * stats, ThreatID * threatLog)
{
	//Set total Missiles in stats.
	stats->setTotalMissiles(missiles);

	//Set total Sensors
	stats->setTotalSensors(sensors);

	//Set undetected missiles.
	stats->setUndetectedMiss(missiles);

	//Set detected missiles.
	stats->setDetectedMiss(missiles);

	//Set Average collatoral damage.
	stats->setAvgHealth(targets);

	//Set Avg missiles detected per sensor.
	stats->avgMissDetectedPerSensor(sensors);

	//Set total amount being tracked by STSS
	stats->setTotalSatTracking(threatLog);
}

void GameWorld::simLoop()
{
	cout << "Entering simLoop()..." << endl;

	bool missionEnd = false;

	createSensors();

	clog << "Sensors assigned ID's and Co-ordinates" << endl;

	createTargets();

	clog << "Targets assigned ID's and co-ordinates" << endl;

	createMissiles();

	clog << "Missiles assigned ID's and Co-ordinates" << endl;

	//Create STSS satellite.
	satRadar = new STSS();

	//Create new log for missile ID
	threatLog = new ThreatID();

	//Assign Targets to missiles(i.e missiles acquiring targets).
	assignTargets(missiles, targets);

	cout << "Creating GUI..." << endl;

	GUI *  myGUI = new GUI(sensors, missiles, targets, satRadar, stats);

	cout << "GUI created." << endl;

	cout << "Creating Statistics..." << endl;
	stats = new Statistics();

	/* This is the main simulation loop */
	while(missionEnd == false)
	{
		//Draw map
		myGUI->drawMap();

		//First check for pause.
		if(key[KEY_P])
		{
			cout << "Paused." << endl;
			clear_keybuf();
			sleep(1);
			while(!key[KEY_P]);
			clear_keybuf();
			sleep(1);
			cout << "Unpaused." << endl;
		}
		//Move missiles.
		updateTrajectory(missiles, targets);

		//Move satellite.
		updateSatPos(satRadar);

		//Init satellite scan.
		initSTSSScan(satRadar, threatLog, missiles);

		//Scan for threats.
		initSensorScan(sensors, missiles);

		updateTargetDamage(targets, missiles);

		//Draw sensors
		myGUI->drawSensors(sensors);

		//Draw STSS.
		myGUI->drawSTSS(satRadar);

		//Draw missiles
		myGUI->drawMissiles(missiles);

		//Draw Targets
		myGUI->drawTargets(targets);

		calcStats(sensors, missiles, targets, stats, threatLog);

		//Draw statistics
		myGUI->drawStats(stats);

		//Update buffer and draw to screen
		myGUI->guiHandler();

		if(key[KEY_Q])
		{
			missionEnd = true;
		}
	}

	cout << "Simulation Complete. Exiting..." << endl;
}

void GameWorld::assignTargets(vector<Missile*> missiles, vector<Target*> targets)
{
	//This function assigns targets to missiles
	int randIndex, randID;
	int targetSize = targets.size();
	bool reserveToggle;

	//take both vectors(missiles and targets)
	//loop(iterates through missiles)
	for(unsigned int i = 0; i < missiles.size(); i++)
	{
			//generate a random number between 0 and the size of the targets vector
			//randomly choose a target from the vector of targets
			randIndex = getRandom(targetSize);

			reserveToggle = false;

			if((missiles.at(i)->getReserved() == false))
			{
					randID = targets.at(randIndex)->getID();

					missiles.at(i)->setTargetID(randID);

					reserveToggle = true;

					//Set the missile to reserved so it cannot be assigned another target
					missiles.at(i)->setReserved(reserveToggle);

					//test outputs
					cout << "Target ID for missile ID: " << missiles.at(i)->getID() << " is: " << missiles.at(i)->getTargetID() << endl;
					cout << "Number of missiles assigned to target " << targets.at(randIndex)->getID() << " is : " << targets.at(randIndex)->getCurrMissiles() << "." << endl;
			}
			else
			{		clog << "MAX_TRGT_ASSIGNABLE for target #" << randIndex << " reached." << endl;
					clog << "Missile not assigned a target during this iteration." << endl;
			}
	}
}
