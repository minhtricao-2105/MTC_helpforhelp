cmake_minimum_required(VERSION 3.0.2)
project(test_cpp)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  OpenCV REQUIRED
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES test_cpp
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}_line_off src/clipper.cpp src/sample.cpp)
add_executable(${PROJECT_NAME}_node src/main.cpp src/clipper.cpp src/sample.cpp)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
