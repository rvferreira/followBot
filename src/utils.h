/*
 * utils.h
 *
 *  Created on: Mar 12, 2015
 *      Author: rferreira
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <player-3.0/libplayerc++/playerc++.h>
#include <math.h>

#define PI 3.14159265

enum robotStates {
    LOOKING_FOR_TARGET,
    MOVING_TO_TARGET,
    LOCKED
};

extern int debugMode;

double relativeX(int sensor, double meas);
double relativeY(int sensor, double meas);
double relativeYaw(double yDiff, double xDiff);


#endif /* UTILS_H_ */
