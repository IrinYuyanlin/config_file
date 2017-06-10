cmake_minimum_required(VERSION 2.8.3)
project(motorctrl)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  std_msgs
  geometry_msgs
)

catkin_package(
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(topic_publisher src/topic_publisher.cpp)
add_executable(topic_subscriber src/topic_subscriber.cpp)

target_link_libraries(topic_publisher
   ${catkin_LIBRARIES}
 )
target_link_libraries(topic_subscriber
   ${catkin_LIBRARIES}
 )


