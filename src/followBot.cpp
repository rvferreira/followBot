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
	return 1;
}

void stalkBot(double *spd, double *tr){
	*tr = getTurnRate(targetBot->angle);
	*spd = SPEED_SEED_VALUE;
}

void avoidObstacles(PlayerCc::RangerProxy  *rp, double *spd, double *tr){
	Coordinate* front_obstacle;
	front_obstacle = Coordinate::closestCoordinate(rp, -(MAX_ANGLE_FOR_FRONT_COLLISION), MAX_ANGLE_FOR_FRONT_COLLISION);

	if (front_obstacle->distance < 2) *spd = *spd * pow((front_obstacle->distance / 2), 2);
	cout << *spd << " " << front_obstacle->distance << endl;
}
