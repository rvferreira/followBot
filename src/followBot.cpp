/*
 * followBot.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#include "followBot.h"

using namespace std;

double targDis;
int targYaw;

double lastMeasurements[N_MEAS_BUFFERS][N_SENSORS];
double lastMeasDifferences[N_MEAS_BUFFERS - 1][N_SENSORS];

int activatedSensors[N_ACTIVATIONS_TO_LOCK];
double activatedSensorsMeasures[N_ACTIVATIONS_TO_LOCK];

void initVariables() {
    int i, j;

    targDis = -1;
    targYaw = 0;

    for (i = 0; i < N_MEAS_BUFFERS; i++) {
        for (j = 0; j < N_SENSORS; j++) {
            lastMeasurements[i][j] = 0;
        }
    }

    for (i = 0; i < N_MEAS_BUFFERS - 1; i++) {
        activatedSensors[i] = -1;
    }
}

void rotateASQueue() {
    int i;
    for (i = N_ACTIVATIONS_TO_LOCK - 1; i > 0 ; i--) {
        activatedSensors[i] = activatedSensors[i - 1];
        activatedSensorsMeasures[i] = activatedSensorsMeasures[i - 1];
    }
}

void rotateLMQueue() {
    int i, j;
    for (j = 0; j < N_SENSORS; j++) {
        for (i = N_MEAS_BUFFERS - 1; i > 0; i--) {
            lastMeasurements[i][j] = lastMeasurements[i - 1][j];
        }
    }
}

bool acquireTarget(PlayerCc::RangerProxy * rp) {

    /* update measurements array */

    int i, j;
    rotateLMQueue();
    for (i = 0; i < N_SENSORS; i++) {
        lastMeasurements[0][i] = (*rp)[i];
    }

    /* sensors feeling */

    double maxAbsDifferenceOnMeasurements;
    int associatedSensor;

    i = 0;
    associatedSensor = -1;
    maxAbsDifferenceOnMeasurements = 0;
    for (j = 0; j < N_SENSORS; j++) {
        lastMeasDifferences[i][j] = lastMeasurements[i][j] - lastMeasurements[i + 1][j];
        if (std::abs(lastMeasDifferences[i][j]) > maxAbsDifferenceOnMeasurements) {
            maxAbsDifferenceOnMeasurements = std::abs(lastMeasDifferences[i][j]);
            associatedSensor = j;
        }
    }

    rotateASQueue();
    activatedSensors[0] = associatedSensor;

    activatedSensorsMeasures[0] = lastMeasurements[i][associatedSensor] < lastMeasurements[i + 1][associatedSensor] ?
                                  lastMeasurements[i][associatedSensor] : lastMeasurements[i + 1][associatedSensor];

    if (debugMode){
        cout << activatedSensors[0] << "\t\t" << activatedSensors[1] << "\t\t" << activatedSensors[2] << "\n";
        cout << std::fixed << std::setw(1) << std::setprecision(4) << std::setfill( '0' ) << activatedSensorsMeasures[0] << "\t\t" << activatedSensorsMeasures[1] << "\t\t" << activatedSensorsMeasures[2] << "\n\n";
    }

    /* target movement identification */

    for (i = 0; i < N_ACTIVATIONS_TO_LOCK; i++) {
        if (activatedSensors[i] == -1) return 1;
    }

    targDis = activatedSensorsMeasures[0];
    targYaw = activatedSensors[0] - 90;

    return 0;
}

void moveToTarget(player_pose2d_t actualPosition, player_pose2d_t initialSpeed, PlayerCc::Position2dProxy *pp){
    (*pp).GoTo(targetPosition(actualPosition, targDis, targYaw), initialSpeed);

    //sleeping time as a function of the target distance
    double fittingCurve = log(targDis + 0.34) / log(1.5) + 2.8;
    double dynamicSleepMovingTime = SLEEP_MOVING_TIME * fittingCurve;

    //more sleeping time in case of target getting out of range
    dynamicSleepMovingTime += (int) (std::abs(targYaw) / 45.0);

    //slowdown if target is too close
    if (targDis < MIN_SAFETY_DISTANCE) (*pp).SetSpeed(0.0, (*pp).GetYawSpeed());

    sleep(dynamicSleepMovingTime);

    /* reset calculations */
    initVariables();
}