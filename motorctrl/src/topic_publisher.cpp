#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include<iostream>
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "motorcommand");
	ros::NodeHandle node_obj;
	ros::Publisher command_pub = node_obj.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
        ros::Rate rate(10);
	while(ros::ok())
	{
		geometry_msgs::Twist msg;
                msg.linear.x = 1;
                msg.angular.z = 60;
		command_pub.publish(msg);
		ros::spinOnce();
                rate.sleep();
	}
}
