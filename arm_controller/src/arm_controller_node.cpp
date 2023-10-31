#include "ros/ros.h"
#include <sstream>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>

void topicCallback(const sensor_msgs::JointState& msg);

int main(int argc, char **argv) {
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nodeHandle;

    ros::Subscriber subscriber = nodeHandle.subscribe("/arm/joint_states", 1, topicCallback);

    ros::Publisher pub_j0 = nodeHandle.advertise<std_msgs::Float64>("PositionJointInterface_J0_controller/command", 1000);
    ros::Publisher pub_j1 = nodeHandle.advertise<std_msgs::Float64>("PositionJointInterface_J1_controller/command", 1000);
    ros::Publisher pub_j2 = nodeHandle.advertise<std_msgs::Float64>("PositionJointInterface_J2_controller/command", 1000);
    ros::Publisher pub_j3 = nodeHandle.advertise<std_msgs::Float64>("PositionJointInterface_J3_controller/command", 1000);

    ros::Rate loop_rate(10);
    int count = 0;

    while (ros::ok()) {

        std_msgs::Float64 msg;
        msg.data=1.0;
        pub_j0.publish(msg);
        pub_j1.publish(msg);
        pub_j2.publish(msg);
        pub_j3.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }

    return 0;
}

void topicCallback(const sensor_msgs::JointState& msg) {
    for (int i=0; i<4; i++) {
    ROS_INFO_STREAM("Position of joint " << i + 1 << ": " << msg.position[i]);
    }
}
