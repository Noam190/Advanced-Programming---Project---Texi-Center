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
	g++ -g -c server.cpp

BFS.o: src/core/BFS.cpp src/core/BFS.h src/core/Grid.h src/core/Node.h
	g++ -g -c -std=c++0x src/core/BFS.cpp

Driver.o: src/persons/Driver.cpp src/persons/Driver.h src/persons/Person.h src/Trip.h
	g++ -g -c -std=c++0x src/persons/Driver.cpp

DriverCreator.o: src/creators/DriverCreator.cpp src/creators/Driver.h
	g++ -g -c -std=c++0x src/creators/DriverCreator.cpp

LuxuryCab.o: LuxuryCab.cpp LuxuryCab.h TaxiCab.h
	g++ -g -c -std=c++0x LuxuryCab.cpp

Matrix.o: Matrix.cpp Matrix.h Grid.h NodeMatrix.h
	g++ -g -c -std=c++0x Matrix.cpp

Menu.o: Menu.cpp Menu.h DriverCreator.h TripCreator.h TaxiCenter.h Grid.h
	g++ -g -c -std=c++0x Menu.cpp

Node.o: Node.cpp Node.h
	g++ -g -c -std=c++0x Node.cpp

NodeMatrix.o: NodeMatrix.cpp NodeMatrix.h Node.h Point.h
	g++ -g -c -std=c++0x NodeMatrix.cpp

Passenger.o: Passenger.cpp Passenger.h Point.h Person.h
	g++ -g -c -std=c++0x Passenger.cpp

Person.o: Person.cpp Person.h Point.h
	g++ -g -c -std=c++0x Person.cpp

Point.o: Point.cpp Point.h Node.h
	g++ -g -c -std=c++0x Point.cpp

Ride.o: Ride.cpp Ride.h Trip.h Driver.h TaxiCab.h
	g++ -g -c -std=c++0x Ride.cpp

StandardCab.o: StandardCab.cpp StandardCab.h TaxiCab.h
	g++ -g -c -std=c++0x StandardCab.cpp

Statistics.o: Statistics.cpp Statistics.h Person.h
	g++ -g -c -std=c++0x Statistics.cpp

TaxiCab.o: TaxiCab.cpp TaxiCab.h Vehicle.h
	g++ -g -c -std=c++0x TaxiCab.cpp

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h Driver.h TaxiCab.h Trip.h Ride.h
	g++ -g -c -std=c++0x TaxiCenter.cpp

TaxiCreator.o: TaxiCreator.cpp TaxiCreator.h TaxiCab.h
	g++ -g -c -std=c++0x TaxiCreator.cpp

Trip.o: Trip.cpp Trip.h Point.h
	g++ -g -c -std=c++0x Trip.cpp

TripCreator.o: TripCreator.cpp TripCreator.h Trip.h Matrix.h
	g++ -g -c -std=c++0x TripCreator.cpp

Vehicle.o: Vehicle.cpp Vehicle.h
	g++ -g -c -std=c++0x Vehicle.cpp

main.o: main.cpp Driver.h Matrix.h TaxiCenter.h Menu.h
	g++ -g -c -std=c++0x main.cpp

Socket.o: Sockets/Socket.h Sockets/Socket.cpp
	g++ -g -c -std=c++0x Sockets/Socket.cpp

Udp.o: Sockets/Udp.h Sockets/Udp.cpp Sockets/Socket.h Sockets/Socket.cpp
	g++ -g -c -std=c++0x Sockets/Udp.cpp

clean:
	rm -f *.o a.out
