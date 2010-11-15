/*
 * gameWorld.h
 *
 *  Created on: 22 Jul 2010
 *      Author: hauk
 */

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include <iostream>
#include <vector>
#include <string>

#include "gui.h"
#include "missile.h"
#include "sensor.h"
#include "stss.h"
#include "target.h"
#include "random.h"
#include "statistics.h"

using namespace std;

typedef vector<int> ThreatID;

class GameWorld
{
	public:
		GameWorld(int numSensors, int numMissiles, int sensorRange);
		~GameWorld();

		void updateTrajectory(vector<Missile*> missiles, vector<Target*> targets);
		void updateTargetDamage(vector<Target*> targets, vector<Missile*> missiles);

		void simLoop();


		//These will be called when the simulation loop is executed.
		void createSensors();
		void createMissiles();
		void createTargets();

		void initSensorScan(vector<Sensor*> sensors, vector<Missile*> missiles);

		void initSTSSScan(STSS * satRadar, ThreatID * threatLog, vector<Missile*> missiles);

		void updateSatPos(STSS * satRadar);

		void assignTargets(vector<Missile*> missiles, vector<Target*> targets);

		void clearDestMissiles(vector<Missile*> missiles);

		void calcStats(vector<Sensor*> sensors, vector<Missile*> missiles, vector<Target*> targets, Statistics * stats, ThreatID * threatLog);

	protected:

		int numSensors, numMissiles, numTargets, radarRange;
		bool checkStaticInput;

		vector<Sensor*> sensors;
		vector<Missile*> missiles;
		vector<Target*> targets;
		Statistics * stats;
		STSS * satRadar;

		ThreatID * threatLog;

	private:
};

#endif /* GAMEWORLD_H_ */
