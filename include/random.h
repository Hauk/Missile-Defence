/*
 * random.h
 *
 *  Created on: 26 Jul 2010
 *      Author: hauk
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <iostream>
#include <fstream>
#include <cmath>

static int getRandom(int limit)
{
	unsigned int rand;
	FILE* randSrc = fopen("/dev/urandom", "r");
	if(fread(&rand, sizeof(rand), 1, randSrc))
	{
		/*std::clog << "getRandom: read from /dev/urandom ok" << std::endl;
		std::clog << "Rand int: " << rand << std::endl;*/
	}
	fclose(randSrc);

	return (rand % limit);
}

static double getRandom(double limit)
{
	int a = getRandom((int) (limit * 100));

	double rand = (double) a / 100.00;

	//std::clog << "Rand double: " << rand << std::endl;

	return rand;
}


#endif /* RANDOM_H_ */
