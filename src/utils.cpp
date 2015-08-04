/*
 * utils.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: rferreira
 */

#include "utils.h"

int debugMode = 0;

double relativeX(int sensor, double meas){
    return ((8.0 - meas) * cos(sensor * PI / 180.0));
}

double relativeY(int sensor, double meas){
    return ((8.0 - meas) * sin(sensor * PI / 180.0));
}

double relativeYaw(double yDiff, double xDiff){
    return atan2(yDiff, xDiff);
}