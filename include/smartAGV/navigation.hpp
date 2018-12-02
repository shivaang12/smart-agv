/********************************************************************
 *   MIT License
 *  
 *   Copyright (c) 2018 Shivang Patel
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 ********************************************************************/

/** @file navigation.hpp
 *  @brief Definition of class Navigation
 *
 *  This file contains definitions of class Navigation which navigates robot/AGV to 
 *  pre-defined locations and controls robot's movements to go forward, backward,
 *  turn left or right, or stop.
 *
 *  @author Shivang Patel
*/

#include <ros/ros.h>
#include <ros/timer.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

/**
 *  @typedef MoveBaseClient
 *
 *  @brief Actionlib client of Mobilebase
*/
typedef
actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

/**
 *  @brief Class definition of Navigation class
*/
class Navigation {
 public:
  void intialize(ros::NodeHandle &);
  void goTO(geometry_msgs::Pose);
  void abortMove(void);
  void forward(void);
  void back(void);
  void left(void);
  void right(void);
  void stop(void);

 private:
  ros::Publisher movebaseCmdVelPub;
  ros::Subscriber odomSub;
  ros::Time time;
  geometry_msgs::Pose current_pose;
  int direction;
  int angle;
  int start_angle;
  MoveBaseClient mbClient;
  void movebaseCallback(
    const actionlib::SimpleClientGoalState &,
    const move_base_msgs::MoveBaseResult::ConstPtr &
  );
  void odomCallBack(const nav_msgs::Odometry::ConstPtr &);
  void timerCallback(const ros::TimerEvent &);
  double convert2degree(double);
};