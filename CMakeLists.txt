cmake_minimum_required(VERSION 2.8.3)
project(map_pose_publisher)
find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs tf)
catkin_package()
include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(map_pose_publisher src/map_pose_publisher.cpp)
target_link_libraries(map_pose_publisher ${catkin_LIBRARIES})
#add_dependencies(map_pose_publisher)

