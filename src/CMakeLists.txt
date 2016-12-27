cmake_minimum_required(VERSION 3.6)
project(ex2ap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES mainTest.cpp Point.cpp Point.h Node.cpp Node.h Matrix.cpp
        Matrix.h Grid.h BFS.cpp BFS.h NodeMatrix.cpp NodeMatrix.h Driver.cpp Driver.h Passenger.h
        Passenger.cpp TaxiCab.cpp TaxiCab.h Trip.h Trip.cpp LuxuryCab.cpp LuxuryCab.h StandardCab.cpp
        StandardCab.h Statistics.cpp Statistics.h Person.cpp Person.h TaxiCenter.cpp TaxiCenter.h Vehicle.cpp
        Vehicle.h TripCreator.cpp TripCreator.h TaxiCreator.cpp TaxiCreator.h DriverCreator.cpp DriverCreator.h
        Menu.cpp Menu.h Ride.cpp Ride.h)


add_library(core ${SOURCE_FILES} mainTest.cpp)
#add_executable(ex1 ${SOURCE_FILES} main.cpp mainTest.cpp)
add_executable(ex1 ${SOURCE_FILES}  mainTest.cpp)
target_link_libraries(ex1 ${Boost_LIBRARIES})

