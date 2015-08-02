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

void initVariables(){
    int i, j;

    targX = 0;
    targY = 0;

    for (i = 0; i < N_MEAS_BUFFERS; i++){
        for (j = 0; j < N_SENSORS; j++){
            lastMeasurements[i][j] = 0;
        }
    }
}

void rotateLMQueue(){
    int i, j;
    for (j = 0; j < N_SENSORS; j++){
        for (i = N_MEAS_BUFFERS - 1; i > 0; i--){
            lastMeasurements[i][j] = lastMeasurements[i - 1][j];
        }
    }
}

bool acquireTarget(PlayerCc::RangerProxy *rp){
    /* update measurements array */
    cout << lastMeasurements[0][0] << "\n" << lastMeasurements[1][0] << "\n" <<  lastMeasurements[2][0] << "\n\n";

    int i, j;
    rotateLMQueue();
    for (i = 0; i < N_SENSORS; i++){
        lastMeasurements[0][i] = (*rp)[90];
    }

    /* looking for movement */
    for (i = 0; i < N_MEAS_BUFFERS - 1; i++){
        for (j = 0; j < N_SENSORS; j++){
            lastMeasDifferences[i][j] = lastMeasurements[i][j] - lastMeasurements[i + 1][j];
        }
    }

    return 1;
}