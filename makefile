
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = Serialization.h core_classes/Point.cpp core_classes/Point.h core_classes/Node.cpp
        core_classes/Node.h core_classes/Matrix.cpp core_classes/Matrix.h core_classes/Grid.h core_classes/BFS.cpp
        core_classes/BFS.h core_classes/NodeMatrix.cpp core_classes/NodeMatrix.h persons/Driver.cpp persons/Driver.h
        persons/Passenger.h persons/Passenger.cpp cabs/TaxiCab.cpp cabs/TaxiCab.h Trip.h Trip.cpp cabs/LuxuryCab.cpp
        cabs/LuxuryCab.h cabs/StandardCab.cpp cabs/StandardCab.h Statistics.cpp Statistics.h persons/Person.cpp
        persons/Person.h TaxiCenter.cpp TaxiCenter.h cabs/Vehicle.cpp cabs/Vehicle.h creators/TripCreator.cpp
        creators/TripCreator.h creators/TaxiCreator.cpp creators/TaxiCreator.h creators/DriverCreator.cpp
        creators/DriverCreator.h Menu.cpp Menu.h Ride.cpp Ride.h Clock.cpp Clock.h
server:
	g++ -std=c++0x server.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o server.out
# (for example)
client:
	g++ -std=c++0x client.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o client.out
