##########################
# 311124283   208388850  #
# birkame     simonoa    #
##########################

all: Server.out Client.out

Server.out: server.o Serialization.o Point.o Node.o Matrix.o Grid.o BFS.o NodeMatrix.o Driver.o Passenger.o TaxiCab.o Trip.o LuxuryCab.o StandardCab.o Statistics.o Person.o TaxiCenter.o Vehicle.o TripCreator.o TaxiCreator.o DriverCreator.o Menu.o Ride.o Clock.o Socket.o Udp.o
	g++ -g -o Server.out server.o Serialization.o Point.o Node.o Matrix.o Grid.o BFS.o NodeMatrix.o Driver.o Passenger.o TaxiCab.o Trip.o LuxuryCab.o StandardCab.o Statistics.o Person.o TaxiCenter.o Vehicle.o TripCreator.o TaxiCreator.o DriverCreator.o Menu.o Ride.o Clock.o Socket.o Udp.o -lboost_serialization

Client.out: client.o Serialization.o Point.o Node.o Matrix.o Grid.o BFS.o NodeMatrix.o Driver.o Passenger.o TaxiCab.o Trip.o LuxuryCab.o StandardCab.o Statistics.o Person.o TaxiCenter.o Vehicle.o TripCreator.o TaxiCreator.o DriverCreator.o Menu.o Ride.o Clock.o Socket.o Udp.o
	g++ -g -o client.out server.o Serialization.o Point.o Node.o Matrix.o Grid.o BFS.o NodeMatrix.o Driver.o Passenger.o TaxiCab.o Trip.o LuxuryCab.o StandardCab.o Statistics.o Person.o TaxiCenter.o Vehicle.o TripCreator.o TaxiCreator.o DriverCreator.o Menu.o Ride.o Clock.o Socket.o Udp.o -lboost_serialization

server.o: src/server.cpp
	g++ -g -c src/server.cpp

clock.o: src/clock.cpp src/clock.h
    g++ -g -c -std=c++0x src/clock.cpp


BFS.o: src/core/BFS.cpp src/core/BFS.h src/core/Grid.h src/core/Node.h
	g++ -g -c -std=c++0x src/core/BFS.cpp

Driver.o: src/persons/Driver.cpp src/persons/Driver.h src/persons/Person.h src/Trip.h
	g++ -g -c -std=c++0x src/persons/Driver.cpp

DriverCreator.o: src/creators/DriverCreator.cpp src/creators/Driver.h
	g++ -g -c -std=c++0x src/creators/DriverCreator.cpp

LuxuryCab.o: src/cabs/LuxuryCab.cpp src/cabs/LuxuryCab.h src/cabs/TaxiCab.h
	g++ -g -c -std=c++0x src/cabs/LuxuryCab.cpp

Matrix.o: src/core/Matrix.cpp src/core/Matrix.h src/core/Grid.h src/core/NodeMatrix.h
	g++ -g -c -std=c++0x src/core/Matrix.cpp

Menu.o: src/Menu.cpp src/Menu.h DriverCreator.h TripCreator.h TaxiCenter.h src/core/Grid.h
	g++ -g -c -std=c++0x src/Menu.cpp

Node.o: src/core/Node.cpp src/core/Node.h
	g++ -g -c -std=c++0x src/core/Node.cpp

NodeMatrix.o: src/core/NodeMatrix.cpp src/core/NodeMatrix.h src/core/Node.h src/core/Point.h
	g++ -g -c -std=c++0x src/core/NodeMatrix.cpp

Passenger.o: src/persons/Passenger.cpp src/persons/Passenger.h Point.h src/persons/Person.h
	g++ -g -c -std=c++0x src/persons/Passenger.cpp

Person.o: src/persons/Person.cpp src/persons/Person.h Point.h
	g++ -g -c -std=c++0x src/persons/Person.cpp

Point.o: src/core/Point.cpp src/core/Point.h src/core/Node.h
	g++ -g -c -std=c++0x src/core/Point.cpp

Ride.o: src/Ride.cpp src/Ride.h src/Trip.h src/persons/Driver.h src/cabs/TaxiCab.h
	g++ -g -c -std=c++0x src/Ride.cpp

StandardCab.o: src/cabs/StandardCab.cpp src/cabs/StandardCab.h src/cabs/TaxiCab.h
	g++ -g -c -std=c++0x src/cabs/StandardCab.cpp

Statistics.o: src/Statistics.cpp src/Statistics.h src/persons/Person.h
	g++ -g -c -std=c++0x src/Statistics.cpp

TaxiCab.o: src/cabs/TaxiCab.cpp src/cabs/TaxiCab.h src/cabs/Vehicle.h
	g++ -g -c -std=c++0x src/cabs/TaxiCab.cpp

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h src/persons/Driver.h TaxiCab.h Trip.h Ride.h
	g++ -g -c -std=c++0x TaxiCenter.cpp

TaxiCreator.o: TaxiCreator.cpp TaxiCreator.h src/cabs/TaxiCab.h
	g++ -g -c -std=c++0x TaxiCreator.cpp

Trip.o: Trip.cpp Trip.h src/core/Point.h
	g++ -g -c -std=c++0x Trip.cpp

TripCreator.o: TripCreator.cpp TripCreator.h Trip.h src/core/Matrix.h
	g++ -g -c -std=c++0x TripCreator.cpp

Vehicle.o: src/cabs/Vehicle.cpp src/cabs/Vehicle.h
	g++ -g -c -std=c++0x src/cabs/Vehicle.cpp

Socket.o: Sockets/Socket.h Sockets/Socket.cpp
	g++ -g -c -std=c++0x Sockets/Socket.cpp

Udp.o: Sockets/Udp.h Sockets/Udp.cpp Sockets/Socket.h Sockets/Socket.cpp
	g++ -g -c -std=c++0x Sockets/Udp.cpp

clean:
	rm -f *.o a.out
