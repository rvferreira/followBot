/*
 * followBot.h
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#ifndef FOLLOWBOT_H_
#define FOLLOWBOT_H_

#include <player-3.0/libplayerc++/playerc++.h>

struct behavior {
	double speed;
	double turnrate;
} behav;

struct reading {
	double intensity[180];
};

int acquireTarget(PlayerCc::RangerProxy *rp);
void stalkBot(PlayerCc::RangerProxy *rp, behavior *bh);

#endif /* FOLLOWBOT_H_ */
