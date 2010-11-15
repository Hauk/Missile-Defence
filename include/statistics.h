/*
 * statistics.h
 *
 *  Created on: 12 Aug 2010
 *      Author: hauk
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <iostream>
#include <vector>

#include "sensor.h"
#include "missile.h"
#include "target.h"
#include "stss.h"

class Statistics
{


	public:

	Statistics();
	~Statistics();

	//Functions for statistics.
	void setTotalMissiles(vector<Missile*> missiles);
	void setTotalSensors(vector<Sensor*> sensors);
	void setUndetectedMiss(vector<Missile*> missiles);
	void setDetectedMiss(vector<Missile*> missiles);
	void setAvgHealth(vector<Target*> targets);
	void setTotalSatTracking(ThreatID * threatLog);

	void avgMissDetectedPerSensor(vector<Sensor*> sensors);

	int getTotalMissiles() { return totalMiss; };
	int getTotalSensors() { return totalSensors; };
	int getUndetectedMiss() { return undetectedMissiles; };
	int getDetectedMiss() { return totalDetected; };
	int getAvgHealth() { return avgHealth; };
	int getAvgDtctdPerSensor() { return dtctdPerSensor; };

	int getSatTrackTotal() { return totalSatDetected; };

	protected:

	private:

	int totalMiss, undetectedMissiles, totalDetected, dtctdPerSensor, totalSatDetected;
	int totalSensors;
	int avgHealth;
};


#endif /* STATISTICS_H_ */
