cmake_minimum_required(VERSION 3.9)

project (cppmetrics)

set (CPACK_GENERATOR TGZ)
set (CPACK_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG OFF)
find_package(Threads REQUIRED)

set (cppmetrics_VERSION_MAJOR 0)
set (cppmetrics_VERSION_MINOR 2)
set (cppmetrics_VERSION_PATCH 0)
set (cppmetrics_VERSION_TAG "")
set (cppmetrics_VERSION "${cppmetrics_VERSION_MAJOR}.${cppmetrics_VERSION_MINOR}.${cppmetrics_VERSION_PATCH}${cppmetrics_VERSION_TAG}")
set(CPACK_PACKAGE_VERSION ${cppmetrics_VERSION})
include(CPack)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
      cmake_policy(SET CMP0004 NEW)
    endif(COMMAND cmake_policy)
endif()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Winit-self -Wno-unused-local-typedef -m64 -pipe")

if(DEFINED INCLUDE_SYSTEM_DIRS)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include")
    SET (EXTRA_LD_FLAGS "-L/usr/lib")
endif()

#set(ASIO_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/deps/asio/asio/include)
#add_definitions(-DASIO_STANDALONE)

set (cppmetrics_global_EXTERNAL_HEADERS
  src/cppmetrics/cppmetrics.h
)

set (cppmetrics_SOURCES
  src/cppmetrics/core/histogram.cpp
  src/cppmetrics/core/meter.cpp
  src/cppmetrics/core/metric_registry.cpp
  src/cppmetrics/core/timer_context.cpp
  src/cppmetrics/core/timer.cpp
  src/cppmetrics/core/ewma.cpp
  src/cppmetrics/core/exp_decay_sample.cpp
  src/cppmetrics/core/snapshot.cpp
  src/cppmetrics/core/uniform_sample.cpp
)

set (cppmetrics_core_EXTERNAL_HEADERS
  src/cppmetrics/core/counter.h
  src/cppmetrics/core/histogram.h
  src/cppmetrics/core/gauge.h
  src/cppmetrics/core/meter.h
  src/cppmetrics/core/metered.h
  src/cppmetrics/core/metric.h
  src/cppmetrics/core/metric_registry.h
  src/cppmetrics/core/reporter.h
  src/cppmetrics/core/timer.h
  src/cppmetrics/core/timer_context.h
  src/cppmetrics/core/exp_decay_sample.h
  src/cppmetrics/core/sample.h
  src/cppmetrics/core/snapshot.h
  src/cppmetrics/core/uniform_sample.h
  src/cppmetrics/core/sampling.h
  src/cppmetrics/core/types.h
)


set (cppmetrics_HEADERS
  src/cppmetrics/core/ewma.h
  ${cppmetrics_core_EXTERNAL_HEADERS}
)

set (DIST_INCLUDE_DIR include/cppmetrics)


if(DEFINED GLOG_DIR)
    set (GLOG_INCLUDE_DIR ${GLOG_DIR}/include)
    set (GLOG_LIB_DIR ${GLOG_DIR}/lib)
endif()

include_directories (src ${ASIO_INCLUDE_DIRS} ${GLOG_INCLUDE_DIR} ${GTEST_DIR})
link_directories (${GLOG_LIB_DIR} ${GTEST_DIR})
install (FILES ${cppmetrics_global_EXTERNAL_HEADERS} DESTINATION ${DIST_INCLUDE_DIR})
install (FILES ${cppmetrics_core_EXTERNAL_HEADERS} DESTINATION ${DIST_INCLUDE_DIR}/core)

# Static library
add_library (cppmetrics STATIC ${cppmetrics_HEADERS} ${cppmetrics_SOURCES})
install (TARGETS cppmetrics DESTINATION lib)

# Shared library
add_library (cppmetricsshared SHARED ${cppmetrics_HEADERS} ${cppmetrics_SOURCES})
#target_link_libraries (cppmetricsshared ${GLOG_LD_FLAGS})
install (TARGETS cppmetricsshared DESTINATION lib)

# Examples
add_executable(testmain example/main.cpp)
target_link_libraries(testmain cppmetrics Threads::Threads)

