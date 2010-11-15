/*
 * sensor.h
 *
 *  Created on: 22 Jul 2010
 *      Author: hauk
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#define MAX_SENSOR_CEILING 650
#define MIN_SENSOR_FLOOR 400
#define MAX_SENSOR_WIDTH 600

#include <iostream>
#include <vector>

#include "missile.h"

using namespace std;

class Sensor
{
	public:

		Sensor();
		~Sensor();

		inline void setXLat(int x) { xLat = x; };
		inline void setYLong(int y) { yLong = y; };
		inline void setID(int tempID) { id = tempID;};
		void setDetected(int plusOne) { numDetected = plusOne; };
		void setRange(int newRange) { range = newRange; };
		void setDisplayed(bool changeDisp) { displayed = changeDisp; };

		int getX() { return xLat; };
		int getY() { return yLong; };
		int getID() { return id; };
		int getRange() { return range; };
		int getNumDetected() { return numDetected; };
		int getDisplayed() { return displayed; };

		void assignPositions();
		void scanForThreat(vector<Missile*> missiles);
		void assignID();

	protected:

		int id, health, range, numDetected;
		int xLat, yLong;

		double radarAccuracy;
		bool displayed;

	private:
};

#endif /* SENSOR_H_ */
