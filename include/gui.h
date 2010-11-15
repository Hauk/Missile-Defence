/*
 * gui.h
 *
 *  Created on: 21 Jul 2010
 *      Author: hauk
 */

#ifndef GUI_H_
#define GUI_H_

#include <iostream>
#include <vector>
#include <allegro.h>

#include "missile.h"
#include "sensor.h"
#include "stss.h"
#include "target.h"
#include "statistics.h"

using namespace std;

class GUI
{
	public:

		GUI(vector<Sensor*> sensors, vector<Missile*> missiles, vector<Target*> targets, STSS * satRadar, Statistics * stats);
		inline ~GUI ();

		void drawMap();
		void drawSensors(vector<Sensor*> sensors);
		void drawSTSS(STSS * satRadar);
		void drawMissiles(vector<Missile*> missiles);
		void drawTargets(vector<Target*> targets);
		bool getMouseState(Sensor *sensor);
		void getSensorPos(Sensor *sensor);

		void drawTrajectories(vector<Sensor> sensors, vector<Target> targets);

		void drawStats(Statistics * stats);

		void guiHandler();

	protected:

		BITMAP * buffer;

		//Background object
		BITMAP * background;

	private:
};

class Menu
{
	public:

		Menu();
		~Menu();

		friend class GUI;

		void getInput(vector<Sensor> sensors, vector<Missile> missiles);

		int getNumSensors();
		int getNumMissiles();
		int getSensorRange();

		bool checkRandomPos();

	protected:

	private:

};

#endif /* GUI_H_ */
