/*
 * followBot.h
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#ifndef FOLLOWBOT_H_
#define FOLLOWBOT_H_

#include "utils.h"

#define STOP_COLLISION_DISTANCE 0.4
#define MAX_ANGLE_FOR_FRONT_COLLISION 30

int acquireTarget(PlayerCc::RangerProxy *rp, list<botState>& measurements);
void stalkBot(double *spd, double *tr);
void avoidObstacles(PlayerCc::RangerProxy  *rp, double *spd, double *tr);

#endif /* FOLLOWBOT_H_ */
