#include "ros/ros.h"
#include<iostream>
#include<sys/io.h>
#include<stdio.h>
#include<ctime>
#include "geometry_msgs/Twist.h"
#include<cmath>


bool forwardfun(long iters)
{
    unsigned int indexp = 0x4e;
    unsigned int datap = 0x4f;
    unsigned char temp;
    iopl(3);
    // init GPIO
    outb(0x87, indexp);
    outb(0x87, indexp);
    outb(0x07, indexp);
    outb(0x09, datap);
    outb(0x2c, indexp);
    temp = (unsigned char)inb(datap);
    temp = 0x1f;
    //    temp = 0x03;
    outb(temp, datap);
    outb(0x30, indexp);
    outb(0x02, datap);
    
    for (int iter=1; iter<=iters; iter++)
    {
        outb(0xf0, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xde;
        outb(temp, datap);
        outb(0xf1, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xde;
        outb(temp, datap);
        usleep(50);

        outb(0xf0, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xde;
        outb(temp, datap);
        outb(0xf1, indexp);
        temp = (unsigned char)inb(datap);
        temp |= 0x21;
        outb(temp, datap);
        usleep(50);
    }
    return true;
    
}

bool rightfun(long iters)
{
    
    unsigned int indexp = 0x4e;
    unsigned int datap = 0x4f;
    unsigned char temp;
    iopl(3);
    // init GPIO
    outb(0x87, indexp);
    outb(0x87, indexp);
    outb(0x07, indexp);
    outb(0x09, datap);
    outb(0x2c, indexp);
    temp = (unsigned char)inb(datap);
    temp = 0x1f;
    //    temp = 0x03;
    outb(temp, datap);
    outb(0x30, indexp);
    outb(0x02, datap);
    
    for (int iter = 1; iter<=iters; iter++)
    {
        outb(0xf0, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xfe;
        outb(temp, datap);
        outb(0xf1, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xfe;
        outb(temp, datap);
        usleep(50);

        outb(0xf0, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xfe;
        outb(temp, datap);
        outb(0xf1, indexp);
        temp = (unsigned char)inb(datap);
        temp |= 0x01;
        outb(temp, datap);
        usleep(50);
    }
    return true;
    
}

bool leftfun(long iters)
{
    
    unsigned int indexp = 0x4e;
    unsigned int datap = 0x4f;
    unsigned char temp;
    iopl(3);
    // init GPIO
    outb(0x87, indexp);
    outb(0x87, indexp);
    outb(0x07, indexp);
    outb(0x09, datap);
    outb(0x2c, indexp);
    temp = (unsigned char)inb(datap);
    temp = 0x1f;
    //    temp = 0x03;
    outb(temp, datap);
    outb(0x30, indexp);
    outb(0x02, datap);
    
    for (int iter=1; iter<=iters; iter++)
    {
        outb(0xf0, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xdf;
        outb(temp, datap);
        outb(0xf1, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xdf;
        outb(temp, datap);
        usleep(50);

        outb(0xf0, indexp);
        temp = (unsigned char)inb(datap);
        temp &= 0xdf;
        outb(temp, datap);
        outb(0xf1, indexp);
        temp = (unsigned char)inb(datap);
        temp |= 0x20;
        outb(temp, datap);
        usleep(50);
    }
    return true;
}


void movebase(const geometry_msgs::Twist::ConstPtr& msg)
{
    // linear iterations
    double _rev = 0.39;
    double linear = double(msg->linear.x);
    double cir = linear/_rev;
    int iters_lin = int(cir * 6400);
    
    // angular iterations
    double angle = double(msg->angular.z);
    // right or left? set a symbol to represent
    int symb = 1;
    if (angle<0)
    {
        symb = 0;
        angle = abs(angle);
    }
    double _ang = 70;
    int iters_ang = (long)(angle/_ang)*6400;
    
    // firstly, we should rotate our robot
    if (symb=1)
    {
        bool mission = leftfun(iters_ang);
        if (mission)
        {
            std::cout << "rotation complete!\n";
            bool linsymb = forwardfun(iters_lin);
            if (linsymb)
            {
                std::cout << "mission complete!\n";
            }
            else
            {
                std::cout << "mission failed!\n";
            }
        }
        else
        {
            std::cout << "mission(r) failed.\n";
        }
    }
    else
    {
        bool mission = rightfun(iters_ang);
        if (mission)
        {
            std::cout << "rotation complete!\n";
            bool linsymb = forwardfun(iters_lin);
            if (linsymb)
            {
                std::cout << "mission complete!\n";
            }
            else
            {
                std::cout << "mission failed!\n";
            }
        }
        else
        {
            std::cout << "mission(r) failed.\n";
        }
    }
    
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "motorcontroll");
    ros::NodeHandle node_obj2;
    ros::Subscriber motor_sub = node_obj2.subscribe("/cmd_vel", 1, movebase);
    ros::spin();
    return 0;
}
