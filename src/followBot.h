/*
 * followBot.h
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#ifndef FOLLOWBOT_H_
#define FOLLOWBOT_H_

#include "utils.h"

#define N_SENSORS 180
#define N_MEAS_BUFFERS 3

extern double targX, targY;

void initVariables();
bool acquireTarget(PlayerCc::RangerProxy *rp);

#endif /* FOLLOWBOT_H_ */
