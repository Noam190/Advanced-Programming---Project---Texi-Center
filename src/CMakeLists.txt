cmake_minimum_required(VERSION 3.6)
project(Taxi-Center)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cpp core_classes/Point.cpp core_classes/Point.h core_classes/Node.cpp core_classes/Node.h
        core_classes/Matrix.cpp core_classes/Matrix.h core_classes/Grid.h core_classes/BFS.cpp core_classes/BFS.h
        core_classes/NodeMatrix.cpp core_classes/NodeMatrix.h persons/Driver.cpp persons/Driver.h persons/Passenger.h
        persons/Passenger.cpp cabs/TaxiCab.cpp cabs/TaxiCab.h Trip.h Trip.cpp cabs/LuxuryCab.cpp cabs/LuxuryCab.h
        cabs/StandardCab.cpp cabs/StandardCab.h Statistics.cpp Statistics.h persons/Person.cpp persons/Person.h
        TaxiCenter.cpp TaxiCenter.h cabs/Vehicle.cpp cabs/Vehicle.h creators/TripCreator.cpp creators/TripCreator.h
        creators/TaxiCreator.cpp creators/TaxiCreator.h creators/DriverCreator.cpp creators/DriverCreator.h
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