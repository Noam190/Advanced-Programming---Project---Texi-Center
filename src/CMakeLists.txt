cmake_minimum_required(VERSION 3.6)
project(Taxi-Center)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cpp Point.cpp Point.h Node.cpp Node.h Matrix.cpp
        Matrix.h Grid.h BFS.cpp BFS.h NodeMatrix.cpp NodeMatrix.h Driver.cpp Driver.h Passenger.h
        Passenger.cpp TaxiCab.cpp TaxiCab.h Trip.h Trip.cpp LuxuryCab.cpp LuxuryCab.h StandardCab.cpp
        StandardCab.h Statistics.cpp Statistics.h Person.cpp Person.h TaxiCenter.cpp TaxiCenter.h Vehicle.cpp
        Vehicle.h TripCreator.cpp TripCreator.h TaxiCreator.cpp TaxiCreator.h DriverCreator.cpp DriverCreator.h
        Menu.cpp Menu.h Ride.cpp Ride.h)

set(SOCKETS_FILES sockets/Socket.cpp sockets/Udp.cpp sockets/Socket.h sockets/Udp.h)

add_library(sockets ${SOCKETS_FILES})


add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server sockets)
target_link_libraries(client sockets)

add_executable(source ${SOURCE_FILES} main.cpp)
add_library(core ${SOURCE_FILES} main.cpp)
target_link_libraries(source ${Boost_LIBRARIES})