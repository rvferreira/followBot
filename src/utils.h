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

player_pose2d_t targetPosition(player_pose2d_t stalkerPosition, double targDis, int targYawDegree);

#endif /* UTILS_H_ */
