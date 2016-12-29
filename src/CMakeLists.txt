cmake_minimum_required(VERSION 3.6)
project(ex2ap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cpp Point.cpp Point.h Node.cpp Node.h Matrix.cpp
        Matrix.h Grid.h BFS.cpp BFS.h NodeMatrix.cpp NodeMatrix.h Driver.cpp Driver.h Passenger.h
        Passenger.cpp TaxiCab.cpp TaxiCab.h Trip.h Trip.cpp LuxuryCab.cpp LuxuryCab.h StandardCab.cpp
        StandardCab.h Statistics.cpp Statistics.h Person.cpp Person.h TaxiCenter.cpp TaxiCenter.h Vehicle.cpp
        Vehicle.h TripCreator.cpp TripCreator.h TaxiCreator.cpp TaxiCreator.h DriverCreator.cpp DriverCreator.h
        Menu.cpp Menu.h Ride.cpp Ride.h
        sockets/Socket.cpp sockets/Udp.cpp sockets/Tcp.cpp
        client.cpp server.cpp)


add_library(core ${SOURCE_FILES} main.cpp)
#add_library(sockets ${core_sockets})

#add_executable(ex1 ${SOURCE_FILES} main.cpp mainTest.cpp)
add_executable(ex1 ${SOURCE_FILES}  main.cpp)
target_link_libraries(ex1 ${Boost_LIBRARIES})

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server sockets)
target_link_libraries(client sockets)
