/*
 * utils.h
 *
 *  Created on: Mar 12, 2015
 *      Author: rferreira
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <player-3.0/libplayerc++/playerc++.h>
#include <list>
#include <math.h>

enum robotStates {
	LOOKING_FOR_TARGET,
	MOVING_TO_TARGET,
	LOCKED
};

extern int debugMode;



#endif /* UTILS_H_ */
