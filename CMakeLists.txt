cmake_minimum_required(VERSION 3.9)

project (cppmetrics)

set (CPACK_GENERATOR TGZ)
set (CPACK_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

set(CMAKE_CXX_STANDARD 14)

#set(THREADS_PREFER_PTHREAD_FLAG OFF)
find_package(Threads REQUIRED)

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

set (cppmetrics_VERSION_MAJOR 0)
set (cppmetrics_VERSION_MINOR 0)
set (cppmetrics_VERSION_PATCH 1)
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

set(Disruptor_sources
    src/Disruptor/BasicExecutor.cpp
    src/Disruptor/BlockingWaitStrategy.cpp
    src/Disruptor/BusySpinWaitStrategy.cpp
    src/Disruptor/FixedSequenceGroup.cpp
    src/Disruptor/ProcessingSequenceBarrier.cpp
    src/Disruptor/ProducerType.cpp
    src/Disruptor/RoundRobinThreadAffinedTaskScheduler.cpp
    src/Disruptor/Sequence.cpp
    src/Disruptor/SequenceGroups.cpp
    src/Disruptor/SleepingWaitStrategy.cpp
    src/Disruptor/SpinWait.cpp
    src/Disruptor/SpinWaitWaitStrategy.cpp
    src/Disruptor/stdafx.cpp
    src/Disruptor/ThreadPerTaskScheduler.cpp
    src/Disruptor/ThreadHelper_Linux.cpp
    src/Disruptor/ThreadHelper_Windows.cpp
    src/Disruptor/TimeoutBlockingWaitStrategy.cpp
    src/Disruptor/TypeInfo.cpp
    src/Disruptor/Util.cpp
    src/Disruptor/YieldingWaitStrategy.cpp
)

set(Disruptor_headers

    src/Disruptor/AggregateEventHandler.h
    src/Disruptor/AlertException.h
    src/Disruptor/ArgumentException.h
    src/Disruptor/ArgumentNullException.h
    src/Disruptor/ArgumentOutOfRangeException.h
    src/Disruptor/BasicExecutor.h
    src/Disruptor/BatchEventProcessor.h
    src/Disruptor/BlockingQueue.h
    src/Disruptor/BlockingWaitStrategy.h
    src/Disruptor/BuildConfig.h
    src/Disruptor/BusySpinWaitStrategy.h
    src/Disruptor/ClockConfig.h
    src/Disruptor/ConsumerRepository.h
    src/Disruptor/Disruptor.h
    src/Disruptor/EventHandlerGroup.h
    src/Disruptor/EventPoller.h
    src/Disruptor/EventProcessorInfo.h
    src/Disruptor/ExceptionBase.h
    src/Disruptor/ExceptionHandlerSetting.h
    src/Disruptor/ExceptionHandlerWrapper.h
    src/Disruptor/FatalException.h
    src/Disruptor/FatalExceptionHandler.h
    src/Disruptor/FixedSequenceGroup.h
    src/Disruptor/IConsumerInfo.h
    src/Disruptor/ICursored.h
    src/Disruptor/IDataProvider.h
    src/Disruptor/IEventHandler.h
    src/Disruptor/IEventProcessor.h
    src/Disruptor/IEventProcessorFactory.h
    src/Disruptor/IEventSequencer.h
    src/Disruptor/IEventTranslator.h
    src/Disruptor/IEventTranslatorVararg.h
    src/Disruptor/IExceptionHandler.h
    src/Disruptor/IExecutor.h
    src/Disruptor/IgnoreExceptionHandler.h
    src/Disruptor/IHighestPublishedSequenceProvider.h
    src/Disruptor/ILifecycleAware.h
    src/Disruptor/InsufficientCapacityException.h
    src/Disruptor/InvalidOperationException.h
    src/Disruptor/ISequence.h
    src/Disruptor/ISequenceBarrier.h
    src/Disruptor/ISequenced.h
    src/Disruptor/ISequencer.h
    src/Disruptor/ISequenceReportingEventHandler.h
    src/Disruptor/ITaskScheduler.h
    src/Disruptor/ITimeoutHandler.h
    src/Disruptor/IWaitStrategy.h
    src/Disruptor/IWorkHandler.h
    src/Disruptor/MultiProducerSequencer.h
    src/Disruptor/NoOpEventProcessor.h
    src/Disruptor/NotSupportedException.h
    src/Disruptor/Pragmas.h
    src/Disruptor/ProcessingSequenceBarrier.h
    src/Disruptor/ProducerType.h
    src/Disruptor/RingBuffer.h
    src/Disruptor/RoundRobinThreadAffinedTaskScheduler.h
    src/Disruptor/Sequence.h
    src/Disruptor/SequenceGroups.h
    src/Disruptor/Sequencer.h
    src/Disruptor/SingleProducerSequencer.h
    src/Disruptor/SleepingWaitStrategy.h
    src/Disruptor/SpinWait.h
    src/Disruptor/SpinWaitWaitStrategy.h
    src/Disruptor/ThreadPerTaskScheduler.h
    src/Disruptor/ThreadHelper.h
    src/Disruptor/TimeoutBlockingWaitStrategy.h
    src/Disruptor/TimeoutException.h
    src/Disruptor/TypeInfo.h
    src/Disruptor/Util.h
    src/Disruptor/WorkerPool.h
    src/Disruptor/WorkerPoolInfo.h
    src/Disruptor/WorkProcessor.h
    src/Disruptor/YieldingWaitStrategy.h
)

if(DEFINED GLOG_DIR)
    set (GLOG_INCLUDE_DIR ${GLOG_DIR}/include)
    set (GLOG_LIB_DIR ${GLOG_DIR}/lib)
endif()

include_directories (src ${ASIO_INCLUDE_DIRS} ${GLOG_INCLUDE_DIR} ${GTEST_DIR})
link_directories (${GLOG_LIB_DIR} ${GTEST_DIR})
install (FILES ${cppmetrics_global_EXTERNAL_HEADERS} DESTINATION ${DIST_INCLUDE_DIR})
install (FILES ${cppmetrics_core_EXTERNAL_HEADERS} DESTINATION ${DIST_INCLUDE_DIR}/core)

# Static library
add_library (cppmetrics STATIC
    ${cppmetrics_HEADERS}
    ${cppmetrics_SOURCES}
    ${Disruptor_headers}
    ${Disruptor_sources}
)
install (TARGETS cppmetrics DESTINATION lib)

# Shared library
add_library (cppmetricsshared SHARED ${cppmetrics_HEADERS} ${cppmetrics_SOURCES})
#target_link_libraries (cppmetricsshared ${GLOG_LD_FLAGS})
install (TARGETS cppmetricsshared DESTINATION lib)

# Examples
add_executable(testmain example/main.cpp)
target_link_libraries(testmain cppmetrics Threads::Threads ${Boost_LIBRARIES})

