/*
 * utils.h
 *
 *  Created on: Mar 12, 2015
 *      Author: rferreira
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SENSORS_COUNT 180
#define NOISE_THRESHOLD 0.1

#define TURN_RATE_SEED_VALUE 0.03
#define SPEED_SEED_VALUE 10

#include <player-3.0/libplayerc++/playerc++.h>
#include <list>
#include <math.h>

using namespace std;

class botState {
public:
	double sensorData[SENSORS_COUNT];
	double speed;
	double turnrate;

	botState(PlayerCc::RangerProxy *rp);
	int operator==(const botState &rhs) const;
	int operator<(const botState &rhs) const;
};

class Coordinate {
public:
	double angle;
	double distance;

	Coordinate(int angle, double distance);
	static Coordinate* closestCoordinate(PlayerCc::RangerProxy *rp, int initialAngle, int finalAngle);

	friend ostream& operator<<(ostream& output, Coordinate *coord){
		output << "angle: " << coord->angle << " distance: " << coord->distance << endl;
		return output;
	}
};

double avrg(double *array, int init, int end);
double getTurnRate(int angle);
int angleToSensor(int angle);
int sensorToAngle(int sensor);
void readSensors(PlayerCc::RangerProxy *rp, list<botState>&);



#endif /* UTILS_H_ */
