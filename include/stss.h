/*
 * stss.h
 *
 *  Created on: 18 Aug 2010
 *      Author: hauk
 */

#ifndef STSS_H_
#define STSS_H_

#include <vector>

#include "missile.h"

using namespace std;

typedef vector<int> ThreatID;

class STSS
{
	public:

		STSS();
		~STSS();

		void initSTSSRadar(vector<Missile*> missiles);
		void stssScan(vector<Missile*> missiles, ThreatID * threatLog);
		void setDisplayed(bool changeDisp) { displayed = changeDisp; };
		void setDetected(int plusOne) { numDetected = plusOne; };
		void setXLat(int newX){ xLat = newX; };
		void setYLong(int newY) { yLong = newY; };

		int getRange() { return range; };
		int getX() { return xLat; };
		int getY() { return yLong; };
		int getNumDetected() { return numDetected; };

	protected:

		ThreatID * threatLog;

	private:

		int scanXLat, scanYLong, range, numDetected, displayed;
		int xLat, yLong;
};

#endif /* STSS_H_ */
