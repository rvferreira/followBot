//============================================================================
// Name        : playerRobotControl.cpp
// Author      : Raphael Ferreira
// Version     :
// Copyright   : Don't fuck me without kissing me!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
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

			/*motor habilitation*/
			pp.SetMotorEnable (true);
			behav.speed = 0;
			behav.turnrate = 0;

			for(;;)
			{
				/*Reading sensors and acquiring targets*/
				while (!acquireTarget(&rp)){
					target.Read();
				}

				/*Setting behavior acording to read data*/
				stalkBot(&rp, &behav);

				/*print out the new speeds*/
//				std::cout 	<< "Speed: " 		<< behav.speed << "  "
//							<< "Turn speed: " 	<< behav.turnrate
//							<< std::endl;

				/*robot speed setting up*/
				pp.SetSpeed(behav.speed, behav.turnrate);
			}

		}
		catch (PlayerCc::PlayerError & e)
		{
			/*Exception treatment*/
			std::cerr << e << std::endl;
			return -1;
		}
		return 0;
}
