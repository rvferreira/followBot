/*
 * followBot.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#include "followBot.h"

using namespace std;

Coordinate* targetBot;

int findTarget(list<botState>& measurements) {
	int sensor = -1;
	double maxDistance = 0;

	double **sensorData = (double**) calloc(measurements.size(), sizeof(double*));
	for (unsigned int i = 0; i < measurements.size(); i++) sensorData[i] = (double*) calloc(SENSORS_COUNT, sizeof(double));

	list<botState>::iterator it = measurements.begin();
	for (unsigned int i = 0; i < measurements.size(); i++){
		for (int j=0; j<SENSORS_COUNT; j++){
			sensorData[i][j] = it->sensorData[j];
			if (i>0){
				if (maxDistance < (sensorData[i][j] - sensorData[i-1][j])){
					maxDistance = (sensorData[i][j] - sensorData[i-1][j]);
//					cout << maxDistance << " ";
					if (maxDistance > NOISE_THRESHOLD) {
						sensor = i;
//						cout << "sensor: " << sensor << " , ";
					}
				}
			}
		}
		advance(it, 1);
	}
	cout << endl;

	for (unsigned int i = 0; i<measurements.size(); i++) free(sensorData[i]);
	free(sensorData);

	if (measurements.size() > 2){
		targetBot = new Coordinate(sensorToAngle(sensor), maxDistance);
		cout << targetBot->angle;
		return 1;
	}

	return 0;
}

int acquireTarget(PlayerCc::RangerProxy *rp, list<botState>& measurements) {
	if (measurements.size()<=1) {
//		cout << "mto poucos elementos" << endl;
		return 0;
	}
	else if (targetBot == NULL) {
//		cout << "sem target, mas com " << measurements.size() << " medidas." << endl;
		return (findTarget(measurements));
	}

	return 1;
}

void stalkBot(double *spd, double *tr) {
	*tr = getTurnRate(targetBot->angle);
	*spd = SPEED_SEED_VALUE;
}

void avoidObstacles(PlayerCc::RangerProxy *rp, double *spd, double *tr) {
	Coordinate* front_obstacle;
	front_obstacle = Coordinate::closestCoordinate(rp,
			-(MAX_ANGLE_FOR_FRONT_COLLISION), MAX_ANGLE_FOR_FRONT_COLLISION);

	double distance = front_obstacle->distance - STOP_COLLISION_DISTANCE;

	if (distance < 2)
		*spd = *spd * ((distance > 0) - (0 > distance))
				* pow((distance / 2), 2);
//	cout << *spd << " " << front_obstacle->distance << endl;
}
