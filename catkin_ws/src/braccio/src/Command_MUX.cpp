#include <sstream>
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "pr2_controllers_msgs/JointTrajectoryAction.h"

bool eggControl = false; //egg control is desactivate by default

void eggChange(std_msgs::Bool msg);
void eggTargetUpdate(pr2_controllers_msgs::JointTrajectoryAction msg);
void IKTargetUpdate(pr2_controllers_msgs::JointTrajectoryAction msg);

ros::Publisher* pub;
ros::NodeHandle n;

int main(int argc, char* argv[]){
    ros::init(argc, argv, "Command_MUX");
    ros::Publisher robotPos_pub = n.advertise<pr2_controllers_msgs::JointTrajectoryAction>("robot_target_pos", 5);
    pub = &robotPos_pub;
    ros::Subscriber command_sub = n.subscribe("command_source",5, eggChange);
    ros::Subscriber egg_target_pos_sub = n.subscribe("egg_target_pos",5,eggTargetUpdate);
    ros::Subscriber IK_target_pos_sub = n.subscribe("IK_target_pos",5,IKTargetUpdate);
    ROS_INFO("Command_MUX initialized");
    ros::spin();
}

void eggChange(std_msgs::Bool msg){
    eggControl = msg.data;
}

void eggTargetUpdate(pr2_controllers_msgs::JointTrajectoryAction msg){
    if(eggControl){
        pub->publish(msg);
    }
}

void IKTargetUpdate(pr2_controllers_msgs::JointTrajectoryAction msg){
    if(!eggControl){
        pub->publish(msg);
    }
}