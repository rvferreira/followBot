/*
 * followBot.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#include "followBot.h"

using namespace std;

Coordinate* targetBot;

int acquireTarget(PlayerCc::RangerProxy *rp, list<botState>& measurements){
	targetBot = Coordinate::closestCoordinate(rp, -90, 90);
	cout << targetBot;
	return 1;
}

void stalkBot(double *spd, double *tr){
	*tr = getTurnRate(targetBot->angle);
	*spd = SPEED_SEED_VALUE;
	cout << targetBot;
}

void avoidObstacles(PlayerCc::RangerProxy  *rp, double *spd, double *tr){
	//*spd = *spd / 5;
}
