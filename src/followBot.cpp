/*
 * followBot.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: rferreira
 */

#include "followBot.h"

using namespace std;

double targX, targY, targYaw;

double lastMeasurements[N_MEAS_BUFFERS][N_SENSORS];
double lastMeasDifferences[N_MEAS_BUFFERS - 1][N_SENSORS];

int activatedSensors[N_ACTIVATIONS_TO_LOCK];
double activadedSensorsMeasures[N_ACTIVATIONS_TO_LOCK];

void initVariables() {
    int i, j;

    targX = 0;
    targY = 0;

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
    for (i = 1; i < N_ACTIVATIONS_TO_LOCK; i++) {
        activatedSensors[i] = activatedSensors[i - 1];
        activadedSensorsMeasures[i] = activadedSensorsMeasures[i - 1];
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

    for (i = 0; i < N_MEAS_BUFFERS - 1; i++) {
        associatedSensor = -1;
        maxAbsDifferenceOnMeasurements = 0;
        for (j = 0; j < N_SENSORS; j++) {
            lastMeasDifferences[i][j] = lastMeasurements[i][j] - lastMeasurements[i + 1][j];
            if (std::abs(lastMeasDifferences[i][j]) > maxAbsDifferenceOnMeasurements) {
                maxAbsDifferenceOnMeasurements = std::abs(lastMeasDifferences[i][j]);
                associatedSensor = j;
            }
        }
        if (1)
            cout << "MAX DIFF OF: " << maxAbsDifferenceOnMeasurements << " AT: " << associatedSensor << "\n\n";
        rotateASQueue();
        activatedSensors[0] = associatedSensor;
        activadedSensorsMeasures[0] = maxAbsDifferenceOnMeasurements;
    }

    /* target movement identification */

    for (i = 0; i < N_ACTIVATIONS_TO_LOCK; i++) {
        if (activatedSensors[i] == -1) return 1;
    }

    targY = rp->GetYPos();
    targX = rp->GetXPos();

    double oldTargY = rp->GetYPos();
    double oldTargX = rp->GetXPos();

    targYaw = 0;

    return 0;
}