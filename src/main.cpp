//============================================================================
// Name        : playerRobotControl.cpp
// Author      : Raphael Ferreira
// Version     : 2.0
// Copyright   : Use a vontz, mas mantenha a autoria =)
// Description : FollowBot using PlayerCC API and Stage for the simulation
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

        for (;;) {
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
                player_pose2d_t initialSpeed = {FORWARD_MAX_SPEED, 0.0, TURN_MAX_SPEED};

                /* actually moving */
                moveToTarget(actualPosition, initialSpeed, &pp);
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
