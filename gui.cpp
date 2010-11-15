/*
 * gui.cpp
 *
 *  Created on: 21 Jul 2010
 *      Author: Eoghan Lappin
 */

#include <iostream>
#include <string>
#include <sstream>

#include "include/gui.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1280

#define MAX_SENSORS 30
#define MAX_MISSILES 100
#define MAX_RADAR 100

using namespace std;

GUI::GUI(vector<Sensor*> sensors, vector<Missile*> missiles, vector<Target*> targets, STSS * satRadar, Statistics * stats)
{
	buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	background = load_bitmap("images/worldmap.bmp", NULL);
}

GUI::~GUI()
{
	//Destructor stuff here
	delete buffer;
	destroy_bitmap(background);
}

void GUI::drawMap()
{

	blit(background, buffer, 0, 0, 0, 0, 1280, 800);
}

void GUI::drawSensors(vector<Sensor*> sensor)
{

	//cout << "Entering drawSensors()" << endl;

	//First, get temp offsets for x and y co-ordinates
	int x1, y1, x2, y2, x3, y3;

	//Draw circle first
	for(unsigned int i = 0; i < sensor.size(); i++)
	{
		//call circle fill, and draw co-ordinates based on xLat, and YLong - This is the radar range
		circle(buffer, sensor.at(i)->getX(), sensor.at(i)->getY(), sensor.at(i)->getRange(), makecol(0, 255, 0));
	}

	//then draw Triangle
	for(unsigned int i = 0; i < sensor.size(); i++)
	{
		x1 = sensor.at(i)->getX();
		y1 = (sensor.at(i)->getY()) - 20;

		//cout << "x1 is: " << x1 << "." << endl;
		//cout << "y1 is: " << y1 << "." << endl;

		x2 = (sensor.at(i)->getX()) - 10;
		y2 = sensor.at(i)->getY();

		x3 = (sensor.at(i)->getX()) + 10;
		y3 = sensor.at(i)->getY();

		//call trianglefill, and draw co-ordinates based on xLat, YLong
		triangle(buffer, x1, y1, x2, y2, x3, y3, makecol(255, 0, 160));
	}

	//cout << "Exiting drawSensors()" << endl;
}

void GUI::drawSTSS(STSS * satRadar)
{
	stringstream satStream;

	string satString;

	//Draw scan Range.
	circle(buffer, satRadar->getX(), satRadar->getY(), satRadar->getRange(), makecol(255, 0, 0));

	//Draw Rectangle.
	rectfill(buffer, (satRadar->getX() - 10), satRadar->getY(), (satRadar->getX() + 20), (satRadar->getY() + 10), makecol(0, 0, 255));

	//Draw text.

	satStream << "STSS";

	satString = satStream.str();

	textout_ex(buffer, font, satString.c_str(), (satRadar->getX() - 10), (satRadar->getY() + 20), makecol(255, 255, 255), makecol(0, 0, 0));

}

void GUI::drawMissiles(vector<Missile*> missiles)
{
	//Loop through vector
	for(unsigned int i = 0; i < missiles.size(); i++)
	{
		if((missiles.at(i)->getDestroyed() == false) && (missiles.at(i) != NULL))
		{
			//if target is acquired
			if(missiles.at(i)->getDiscovered() == true)
			{
				//Draw small square filled with red
				rectfill(buffer, missiles.at(i)->getX(), missiles.at(i)->getY(), (missiles.at(i)->getX() + 5), (missiles.at(i)->getY() + 5), makecol(255, 0, 0));
			}
			else
			{
				//if not, colour to white
				rectfill(buffer, missiles.at(i)->getX(), missiles.at(i)->getY(), (missiles.at(i)->getX() + 5), (missiles.at(i)->getY() + 5), makecol(255, 255, 255));
			}
		}
	}

	//cout << "Exiting drawMissiles()" << endl;
}

void GUI::drawTargets(vector<Target*> targets)
{
	int x1, y1, x2, y2, x3, y3;

	//Draw triangle
	for(unsigned int i = 0; i < targets.size(); i++)
	{
		x1 = targets.at(i)->getXLat();
		y1 = (targets.at(i)->getYLong()) - 20;

		//cout << "x1 is: " << x1 << "." << endl;
		//cout << "y1 is: " << y1 << "." << endl;

		x2 = (targets.at(i)->getXLat()) - 10;
		y2 = targets.at(i)->getYLong();

		x3 = (targets.at(i)->getXLat()) + 10;
		y3 = targets.at(i)->getYLong();

		triangle(buffer, x1, y1, x2, y2, x3, y3, makecol(0, 191, 225));

		stringstream healths;

		string healthString;

		if(targets.at(i)->getHealth() > 0)
		{

			healths << "Health: " << targets.at(i)->getHealth();

			healthString = healths.str();

			textout_ex(buffer, font, healthString.c_str(), (x1 + 20), (y1 + 15), makecol(255, 255, 255), makecol(0, 0, 0));
		}
		else
		{
			healths << "Destroyed";

			healthString = healths.str();

			textout_ex(buffer, font, healthString.c_str(), (x1 + 20), (y1 + 15), makecol(255, 255, 255), makecol(255, 0, 0));
		}
	}

	//Draw health
	//Draw bar chart with population.
}

bool GUI::getMouseState(Sensor *sensor)
{
	//This function checks the user has clicked on a certain position.

	//Do while loops check for release.

	poll_mouse();

	if(mouse_b & 1)
	{
		cout << "Setting x and y" << endl;

		sensor->setXLat(mouse_x);
		sensor->setYLong(mouse_y);

		sensor->setDisplayed(true);

		return true;
	}
	return false;
}

void GUI::getSensorPos(Sensor* sensor)
{
	bool drawSwitch, mouseClick = false;

	show_mouse(buffer);

	cout << "test before while loop" << endl;

	while(!drawSwitch)
	{
		cout << "test before if" << endl;

		cout << "test after poll" << endl;

		//If left button is clicked.
		//IT'S YOU!!!!!!!!!!!!!!!!!!!!!
		while(mouseClick)
		{
			mouseClick = getMouseState(sensor);

			cout << "test" << endl;
		}

		cout << "test after if" << endl;

		drawSwitch = true;
	}

	cout << "test after while loop" << endl;
}

void GUI::drawTrajectories(vector<Sensor> sensors, vector<Target> targets)
{
	//Draw lines from co-ordinate of missile to co-ordinate of target
}

void GUI::drawStats(Statistics * stats)
{
	//Create our string stream to store data.
	stringstream writeIn;

	string writeString;

	rectfill(buffer, 0, 710, 1280, 800, makecol(0, 0, 0));

	//Draw horizantal line to seperate boundary. 701
	hline(buffer, 0, 710, 1280, makecol(255, 255, 255));

	vline(buffer, 250, 710, 800, makecol(255, 255, 255));
	vline(buffer, 495, 710, 800, makecol(255, 255, 255));
	vline(buffer, 790, 710, 800, makecol(255, 255, 255));

	/* Draw Total Missiles.*/
	writeIn << "Total Missiles: " << stats->getTotalMissiles();

	writeString = writeIn.str();

	textout_ex(buffer, font, writeString.c_str(), 50, 720, makecol(255, 255, 255), makecol(0, 0, 0));

	/* Draw total sensors */
	writeIn.str("");

	writeIn << "Total Sensors: " << stats->getTotalSensors();

	writeString = writeIn.str();

	textout_ex(buffer, font, writeString.c_str(), 50, 730, makecol(255, 255, 255), makecol(0, 0, 0));

	/* Draw undetected missiles */
	writeIn.str("");

	writeIn << "Undetected Missiles: " << stats->getUndetectedMiss();

	writeString = writeIn.str();

	textout_ex(buffer, font, writeString.c_str(), 265, 720, makecol(255, 255, 255), makecol(0, 0, 0));

	/* Draw detected missiles */
	writeIn.str("");

	writeIn << "Detected Missiles: " << stats->getDetectedMiss();

	writeString = writeIn.str();

	textout_ex(buffer, font, writeString.c_str(), 265, 735, makecol(255, 255, 255), makecol(0, 0, 0));

	/* Draw average collaterol damage*/
	writeIn.str("");

	writeIn << "Average Target Health: " << stats->getAvgHealth();

	writeString = writeIn.str();

	textout_ex(buffer, font, writeString.c_str(), 510, 720, makecol(255, 255, 255), makecol(0, 0, 0));

	//Draw average missiles detected per sensor
	writeIn.str("");

	writeIn << "Average missiles detected per Sensor: " << stats->getAvgDtctdPerSensor();

	writeString = writeIn.str();

	textout_ex(buffer, font, writeString.c_str(), 800, 720, makecol(255, 255, 255), makecol(0, 0, 0));

	/* Satellite Tracking amount*/
	writeIn.str("");

	writeIn << "Satellite Tracking Total: " << stats->getSatTrackTotal();

	writeString = writeIn.str();

	textout_ex(buffer, font, writeString.c_str(), 800, 735, makecol(255, 255, 255), makecol(0, 0, 0));

	//Clear string stream
	writeIn.str("");

}

void GUI::guiHandler()
{
	draw_sprite(buffer, mouse_sprite, mouse_x, mouse_y);
	blit(buffer, screen, 0, 0, 0, 0, 1280, 800);
	clear(buffer);

	//cout << "Clearing buffer for new write..." << endl;
}

Menu::Menu()
{
	//Initialisation menu bits here.
}

Menu::~Menu()
{
	//Destructor stuff here
}

int Menu::getNumSensors()
{
	int numSensors;

	char finished;

	bool checkFinished;

		while(!checkFinished)
		{
			//Read in sensors and check within total amount.
			sensors:

				cout << "Enter the number of sensors you require: ";
				cin >> numSensors;

				if((numSensors > MAX_SENSORS) || numSensors == 0)
					cout << "The number of sensors you entered exceeds the maximum allowed of: " << MAX_SENSORS << " sensors." << endl;

				cout << "The number of sensors you entered is: " << numSensors << ". Is this correct?(y/n): ";

				cin >> finished;

				if(finished == 'y')
				{
					cout << "Parameters received..." << endl;
					checkFinished = true;
				}
				else if(finished == 'n')
				{
					cout << "Returning to selection menu..." << endl;
					goto sensors;
				}
				else if(finished != ('y' || 'n'))
				{
					cout << "Incorrect selection: Returning to selection menu..." << endl;
					goto sensors;
				}

				finished = NULL;
		}

	return numSensors;
}

int Menu::getNumMissiles()
{
	int numMissiles;

		char finished;

		bool checkFinished;

		while(!checkFinished)
		{
			//Read in missiles and check within total amount.
			missiles:

				cout << "Enter the number of missiles you require: ";
				cin >> numMissiles;

				if((numMissiles > MAX_MISSILES) || numMissiles == 0)
					cout << "The number of missiles you entered exceeds the maximum allowed of: " << MAX_MISSILES << " missiles." << endl;

			cout << "The number of missiles you entered is: " << numMissiles << ". Is this correct?(y/n): ";

			cin >> finished;

			if(finished == 'y')
			{
				cout << "Parameters received..." << endl;
				checkFinished = true;
			}
			else if(finished == 'n')
			{
				cout << "Returning to selection menu..." << endl;
				goto missiles;
			}
			else if(finished != ('y' || 'n'))
			{
				cout << "Incorrect selection: Returning to selection menu..." << endl;
				goto missiles;
			}
		}

	cout << "Number of missiles: " << numMissiles << endl;

	return numMissiles;
}

int Menu::getSensorRange()
{
	int numRange;

	char finished;

	bool checkFinished;

	while(!checkFinished)
	{
		radar:

			cout << "Enter the range for the sensors: ";
			cin >> numRange;

			if((numRange > MAX_RADAR) || (numRange == 0))
			{
				cout << "The range you entered is not within the allowed range: (1 - 100)" << endl;
			}

			cout << "The range you entered is: " << numRange << ". Is this correct(y/n): ";

			cin >> finished;

			if(finished == 'y')
			{
				cout << "Parameters received..." << endl;
				checkFinished = true;
			}
			else if(finished == 'n')
			{
				cout << "Returning to selection menu..." << endl;
				goto radar;
			}
			else if(finished != ('y' || 'n'))
			{
				cout << "Incorrect selection: Returning to selection menu..." << endl;
				goto radar;
			}

			cout << "The range for each radar is: " << numRange << "." << endl;
	}
	return numRange;
}

bool Menu::checkRandomPos()
{
	bool latLong = false;

	char checkPos;

	bool checkFinished;

	while(!checkFinished)
	{
		positions:

		cout << "You can choose to randomly place Sensors, or assign positions yourself." << endl;
		cout << "Enter for either (r)andom or (u)ser assigned(r/u): ";

		cin >> checkPos;

		if(checkPos == 'r')
		{
			latLong = false;
			checkFinished = true;
		}
		else if(checkPos == 'u')
		{
			latLong = true;
			checkFinished = true;
		}
		else
		{
			cout << "Incorrect selection: Options are 'r' or 'u'." << endl;
			goto positions;
		}
	}

	return latLong;
}
