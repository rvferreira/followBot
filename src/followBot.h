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
#define N_ACTIVATIONS_TO_LOCK 2

#define FORWARD_MAX_SPEED 20.0
#define TURN_MAX_SPEED 10.0
#define SLEEP_MOVING_TIME 0.5

#define MIN_SAFETY_DISTANCE 0.6

extern double targDis;
extern int targYaw;

void initVariables();
bool acquireTarget(PlayerCc::RangerProxy *rp);
void moveToTarget(player_pose2d_t actualPosition, player_pose2d_t initialSpeed, PlayerCc::Position2dProxy *pp);

#endif /* FOLLOWBOT_H_ */
