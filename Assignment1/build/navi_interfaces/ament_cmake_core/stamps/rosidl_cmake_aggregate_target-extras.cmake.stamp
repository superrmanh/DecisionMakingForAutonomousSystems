# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target navi_interfaces::navi_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${navi_interfaces_TARGETS}.
if(navi_interfaces_TARGETS AND NOT TARGET navi_interfaces::navi_interfaces)
  add_library(navi_interfaces::navi_interfaces INTERFACE IMPORTED)
  set_target_properties(navi_interfaces::navi_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${navi_interfaces_TARGETS}")
endif()
