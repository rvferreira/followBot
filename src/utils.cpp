/*
 * utils.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: rferreira
 */

#include "utils.h"

double avrg(double *array, int init, int end){
	double sum = 0;
	for (int i = init; i <= end; i++){
		sum += array[i];
	}
	return (sum/(end + 1 - init));
}

void readSensors(PlayerCc::RangerProxy *rp, list<botState>& readingsArray){
	botState* actualReading = new botState(rp);
	readingsArray.push_back(*actualReading);
}

Coordinate::Coordinate(int angle, double distance){
	this->angle = angle;
	this->distance = distance;
}

Coordinate* Coordinate::closestCoordinate(PlayerCc::RangerProxy *rp, int initialAngle, int finalAngle){
	Coordinate* toReturn = 0;
	double min_distance = 8;
	int related_sensor;
	for (int i = angleToSensor(initialAngle); i < angleToSensor(finalAngle); i++){
		if (rp->GetRange(i) < min_distance){
			min_distance = rp->GetRange(i);
			related_sensor = i;
		}
	}

	*toReturn = Coordinate((90 - related_sensor), min_distance);

	return toReturn;
}

int angleToSensor(int angle){
	return -(angle + 90);
}

botState::botState(PlayerCc::RangerProxy *rp){
	this->speed = 0;
	this->turnrate = 0;
	for (int i = 0; i < SENSORS_COUNT; i++){
		this->sensorData[i] = rp->GetRange(i);
	}
}

int botState::operator==(const botState &rhs) const{
	for (int i = 0; i < SENSORS_COUNT; i++){
		if (fabs(this->sensorData[i] - rhs.sensorData[i]) > NOISE_THRESHOLD) return 0;
	}
	return 1;
}

int botState::operator<(const botState &rhs) const{
	for (int i = 0; i < SENSORS_COUNT; i++){
		if (fabs(this->sensorData[i] - rhs.sensorData[i]) > NOISE_THRESHOLD) return 1;
	}
	return 0;
}

double getTurnRate(int angle){
	return (TURN_RATE_SEED_VALUE * -(angle^2));
}
