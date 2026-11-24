cmake_minimum_required(VERSION 3.8)
project(gazebo_bbox_plugin)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(gazebo_dev REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(vision_msgs REQUIRED)

add_library(gazebo_bbox_plugin SHARED src/gazebo_bbox_plugin.cpp)

target_include_directories(gazebo_bbox_plugin PUBLIC
  $<BUILD_INTERFACE:${GAZEBO_INCLUDE_DIRS}>
)

target_link_libraries(gazebo_bbox_plugin ${GAZEBO_LIBRARIES})

ament_target_dependencies(gazebo_bbox_plugin
  gazebo_dev
  gazebo_ros
  rclcpp
  vision_msgs
)

install(TARGETS gazebo_bbox_plugin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

# Optional: install example world so it can be launched by package name
install(DIRECTORY worlds
  DESTINATION share/${PROJECT_NAME}
  OPTIONAL
)

ament_export_libraries(gazebo_bbox_plugin)
ament_export_dependencies(gazebo_dev gazebo_ros rclcpp vision_msgs)
ament_package()
