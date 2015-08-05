/*
 * followBot.h
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#ifndef FOLLOWBOT_H_
#define FOLLOWBOT_H_

#include "utils.h"
#include <stdlib.h>
#include <iomanip>

#define N_SENSORS 180
#define N_MEAS_BUFFERS 3
#define N_ACTIVATIONS_TO_LOCK 3

extern double targDis;
extern int targYaw;

void initVariables();
bool acquireTarget(PlayerCc::RangerProxy *rp);

#endif /* FOLLOWBOT_H_ */
