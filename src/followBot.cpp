/*
 * followBot.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#include "followBot.h"

using namespace std;

Destination* targetBot;

int acquireTarget(PlayerCc::RangerProxy *rp, list<botState>& measurements){
	targetBot = new Destination(rp);
	return 1;
}

void stalkBot(double *spd, double *tr){
	*tr = getTurnRate(targetBot->angle);
	cout << targetBot;
}

void avoidObstacles(PlayerCc::RangerProxy  *rp, double *spd, double *tr){

}
