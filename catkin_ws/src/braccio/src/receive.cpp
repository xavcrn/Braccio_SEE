#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include <time.h>

#include "ros/ros.h"
#include "pr2_controllers_msgs/JointTrajectoryAction.h"


#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include <RF24/nRF24L01.h>
    
using namespace std;

#define deb0 3.14159  // 180°
#define deb1 2.26893  // 130°
#define deb2 2.26893  // 130°
#define deb3 2.26893  // 130°
#define deb4 2.26893  // 130°
#define deb5 1.5708   //  90°

#define sendPeriod 0.1 // 10Hz

struct data {
	short ID;
	short x;
	short y;
	short mode;
	short action;
	short file;
} receivedData;

int main(int argc, char const *argv[])
{
    ros::init(argc, argv, "receive_eggs");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<pr2_controllers_msgs::JointTrajectoryAction>("eggs_target_pos", 1000);
    ros::Rate loop_rate(20);

    RF24 radio(25,0);
    RF24Network network(radio);
    const uint16_t motherNode = 00;
    const uint16_t myNode = motherNode;
   
    //inits radio
    radio.begin();
    radio.startListening();
    network.begin(108, myNode);

    pr2_controllers_msgs::JointTrajectoryAction goal;
    
    goal.trajectory.joint_names.push_back("r_shoulder_pan_joint");
    goal.trajectory.joint_names.push_back("r_shoulder_lift_joint");
    goal.trajectory.joint_names.push_back("r_upper_arm_roll_joint");
    goal.trajectory.joint_names.push_back("r_elbow_flex_joint");
    goal.trajectory.joint_names.push_back("r_forearm_roll_joint");
    goal.trajectory.joint_names.push_back("r_wrist_flex_joint");
    goal.trajectory.joint_names.push_back("r_wrist_roll_joint");
    
    goal.trajectory.points.resize(1);

    goal.trajectory.points[0].positions.resize(7);
    goal.trajectory.points[0].positions[0] = 0;
    goal.trajectory.points[0].positions[1] = 0;
    goal.trajectory.points[0].positions[2] = 0;
    goal.trajectory.points[0].positions[3] = 0;
    goal.trajectory.points[0].positions[4] = 0;
    goal.trajectory.points[0].positions[5] = 0;

    goal.trajectory.points[0].time_from_start = ros::Duration(sendPeriod);

    ros::Time lastSentTime = ros::Time::now();

    while(ros::ok()){
        network.update();

        while(ros::ok() && network.available()){
            RF24NetworkHeader nHeader;
            
            network.read(nHeader, &receivedData, sizeof(receivedData));
            
            cout << receivedData.ID << endl;
            
            switch (receivedData.ID)
            {
            case 0:
                goal.trajectory.points[0].positions[0] = (receivedData.x * deb0 * 2) / 256 - deb0;
                goal.trajectory.points[0].positions[1] = (receivedData.y * deb1 * 2) / 256 - deb1;
                break;
            
            case 1:
                goal.trajectory.points[0].positions[2] = (receivedData.x * deb2 * 2) / 256 - deb2;
                goal.trajectory.points[0].positions[3] = (receivedData.y * deb3 * 2) / 256 - deb3;
                break;

            case 2:
                goal.trajectory.points[0].positions[4] = (receivedData.x * deb4 * 2) / 256 - deb4;
                goal.trajectory.points[0].positions[5] = (receivedData.y * deb5) / 256;
                break;

            default:
                ROS_ERROR("Unexpected ID : %d",receivedData.ID);
                break;
            }

            // Send goal at 1/sendPeriod Hz
            if(ros::Time::now() - lastSentTime >= ros::Duration(sendPeriod)){
                pub.publish(goal);
                lastSentTime = ros::Time::now();
            }            
   	    }
        ROS_ERROR("Egg connection lost");
    }
    return 0;
}
