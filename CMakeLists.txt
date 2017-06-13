# 
# Author: <gfxcc_stevens@outlook.com>
# created: 2017-06-07

PROJECT(analyze)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
MESSAGE(STATUS "Project: ${PROJECT_NAME}")
file(GLOB_RECURSE header ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE source ${PROJECT_SOURCE_DIR}/src/*.cc)

# -----------------------------------------------
# COMPILE FLAG
# -----------------------------------------------

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# -----------------------------------------------
# STATIC LIBRARY
# -----------------------------------------------

include_directories(
  /usr/include/cppconn/
  ${PROJECT_SOURCE_DIR}/thirdparty/crk/include/
  ${PROJECT_SOURCE_DIR}/thirdparty/boost/include/
  )

link_directories(${PROJECT_SOURCE_DIR}/thirdparty/crk/lib/)

add_executable(analyze ${source})
target_link_libraries(analyze
  mysqlcppconn
  crk
  )
