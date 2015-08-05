//============================================================================
// Name        : playerRobotControl.cpp
// Author      : Raphael Ferreira
// Version     :
// Copyright   : Don't fuck me without kissing me!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

#include <time.h>
#include "followBot.h"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        /*Setting up robot and sensors*/
        initVariables();

        /* Stalker Robot */
        PlayerCc::PlayerClient stalker("localhost", 6666);
        PlayerCc::RangerProxy rp(&stalker, 1);
        PlayerCc::Position2dProxy pp(&stalker, 0);

        pp.SetMotorEnable(true);
        int stalkerState = LOOKING_FOR_TARGET;

        for (; ;) {
            pp.SetSpeed(0,0);
            stalker.Read();

            /* state 0 - looking for target */
            if (stalkerState == LOOKING_FOR_TARGET){
                if (acquireTarget(&rp)) {
                    if (debugMode) cout << "no target\n\n";
                }
                else {
                    if (debugMode) cout << "target acquired at Dis: " << targDis << " Yaw: " << targYaw << "\n\n";
                    stalkerState = MOVING_TO_TARGET;
                }
            }

            /* state 1 - setting speed */
            if (stalkerState == MOVING_TO_TARGET) {
                player_pose2d_t actualPosition = {pp.GetXPos(), pp.GetYPos(), pp.GetYaw()};

                /* initial speed */
                player_pose2d_t initialSpeed = {10.0, 0.0, 5.0};

                /* actually moving */
                pp.GoTo(targetPosition(actualPosition, targDis, targYaw), initialSpeed);
                sleep(1);

                /* reset calculations */
                initVariables();
            }

            /* reset state */
            pp.SetSpeed(0, 0);
            stalkerState = LOOKING_FOR_TARGET;
        }
    }

    catch (PlayerCc::PlayerError &e) {
        std::cerr << e << std::endl;
        return -1;
    }
}
