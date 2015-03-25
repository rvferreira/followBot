//============================================================================
// Name        : playerRobotControl.cpp
// Author      : Raphael Ferreira
// Version     :
// Copyright   : Don't fuck me without kissing me!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include "followBot.h"

using namespace std;

int main(int argc, char *argv[]) {
	try
	{
		/*Setting up robot and sensors*/

		/* Stalker Robot */
		PlayerCc::PlayerClient target("localhost", 6666);
		PlayerCc::RangerProxy rp(&target, 1);
		PlayerCc::Position2dProxy pp(&target, 0);

		pp.SetMotorEnable (true);

		double speed = 0;
		double turnrate = 0;

		list<botState> measurements;

		for(;;)
		{
			target.Read();

			if (!acquireTarget(&rp, measurements)){
				speed = 0;
				turnrate = 0;
				readSensors(&rp, measurements);
				pp.SetSpeed(speed, turnrate);
			}
			else {
				measurements.clear();
//				stalkBot(&speed, &turnrate);
				avoidObstacles(&rp, &speed, &turnrate);
				pp.SetSpeed(speed, turnrate);
				sleep(1);
				//TODO destroy targetBot instance
			}
		}

	}
	catch (PlayerCc::PlayerError & e)
	{
		std::cerr << e << std::endl;
		return -1;
	}
	return 0;
}
