/*
 * followBot.h
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#ifndef FOLLOWBOT_H_
#define FOLLOWBOT_H_

#include "utils.h"

struct reading {
	double intensity[180];
};

int acquireTarget(PlayerCc::RangerProxy *rp);
void stalkBot(PlayerCc::RangerProxy *rp, double *spd, double *tr);
void avoidObstacles(PlayerCc::RangerProxy  *rp, double *spd, double *tr);

#endif /* FOLLOWBOT_H_ */
