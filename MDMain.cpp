/*
 * MDMain.cpp
 *
 *  Created on: 13 Jul 2010
 *      Author: hauk
 */

#include <iostream>
#include <vector>
#include <allegro.h>

#include "include/gui.h"
#include "include/gameWorld.h"


#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1280

/*
 * Todo:
 *
 * Increase maximums
 * stats, targets -
 * red ones have no effect.
 * pause

	Fix those two functions.
	Finish drawings.
	Do map and adjust co-ordinates.

 * */

using namespace std;

int main()
{
	cout << "Welcome to Missile Defence; a simulation of the U.S. Ballistic Missile Defence System." << endl << "Use the simple menu system to enter the number of missiles and sensors you require." << endl;

	int numSensors, numMissiles, radarRange;
	bool checkStatic = false;

	//Want to read in the number of sensors, missiles, and targets.
	//in such a way that they can be created in the simulation loop.
	//create an empty vector in GameWorld.h for (sensors, missiles, targets).
	//Create ints in main() for numSensors, numMissiles, numTargets
	//Read in ints from user, and create GameWorld, passing in new values.

	//Then, in simLoop(), call createSensors(), createMissiles(), createMissiles().

	//Create Menu
	//Get all user input from Menu.
	//Create new variable to check if they want random or user placed.
	//Create Game World
	//Pass data
	//Dont loop.
	//Remove loop for assign Random pos

	//Create a new Menu
	Menu* userInput = new Menu();

	clog << "Getting sensors..." << endl;

	numSensors = userInput->getNumSensors();

	//checkStatic = userInput->checkRandomPos();

	clog << "Getting Sensor range..." << endl;

	radarRange = userInput->getSensorRange();

	clog << "Getting missiles..." << endl;

	numMissiles = userInput->getNumMissiles();

	//Install Allegro
	allegro_init();

	//Initialise keyboard
	install_keyboard();

	//Install mouse
	install_mouse();

	//Set colour depth
	set_color_depth(32);

	//setup screen
	set_gfx_mode(GFX_AUTODETECT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	show_mouse(NULL);

	//Create Simulation World, and initialise loop.
	GameWorld* simWorld = new GameWorld(numSensors, numMissiles, radarRange);

	clog << "SimWorld created. Entering Simulation..." << endl;

	(*simWorld).simLoop();

	//test for quit.
	if(key[KEY_Q])
	{
		return 0;
	}

	return 0;
}
END_OF_MAIN()
