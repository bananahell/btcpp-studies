cmake_minimum_required(VERSION 3.8)
project(pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav2_util REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(nav2_core REQUIRED)
find_package(nav2_behavior_tree REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(behaviortree_cpp_v3 REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

set(TARGET_DEPENDS
  rclcpp
  behaviortree_cpp_v3
  rclcpp_action
  nav2_msgs
  nav2_util
  nav2_core
  nav2_behavior_tree
  geometry_msgs
  std_msgs
  tf2
  tf2_geometry_msgs
)

install(DIRECTORY
  behavior_trees launch
  DESTINATION share/${PROJECT_NAME}
)

set(BEHAVIOR_SOURCES
  src/bt_executor.cpp
  src/publisher_node.cpp
  src/subscriber_node.cpp
  include/bt_executor.h
  include/publisher_node.h
  include/subscriber_node.h
)

include_directories(include)
add_executable(bt_executor src/bt_executor.cpp ${BEHAVIOR_SOURCES})
ament_target_dependencies(bt_executor ${TARGET_DEPENDS})
target_link_libraries(bt_executor ${YAML_CPP_LIBRARIES})

install(TARGETS
  bt_executor
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
