/*
 * utils.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: rferreira
 */

#include "utils.h"

int debugMode = 0;

player_pose2d_t targetPosition(player_pose2d_t stalkerPosition, double targDis, int targYawDegree){
    int targYaw = ((int) (stalkerPosition.pa * 180.0 / PI)) + targYawDegree;
    double targX = stalkerPosition.px + targDis * cos(targYaw * PI / 180.0);
    double targY = stalkerPosition.py + targDis * sin(targYaw * PI / 180.0);

    player_pose2d_t tp = {targX, targY, (double) targYaw};
    return tp;
}

double relativeYaw(double yDiff, double xDiff){
    return atan2(yDiff, xDiff);
}