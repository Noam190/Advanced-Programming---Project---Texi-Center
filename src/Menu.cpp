//
// Created by noam on 16/12/16.
//

#include "Menu.h"
#include "Serialization.h"
#include "sockets/Udp.h"

template<class T>
T *deserialize(string serial_str) {
    T *p;
    unsigned long x = serial_str.size();
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), x);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s(device);
    boost::archive::binary_iarchive ia(s);
    ia >> p;

    return p;
}


template<class T>
string serialize(T *object) {
    std::string serial_str;

    boost::iostreams::back_insert_device<std::string> insertDevice(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(insertDevice);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();

    return serial_str;
}



//  run the input to the program
void Menu::run(TaxiCenter taxiCenter) {
    getObstacles();
    cin.ignore();

    int option;
    cin >> option;
    while (option != 7) {
        cin.ignore();
        switch (option) {
            case 1: //expecting Driver
                expectingDriver(taxiCenter);
                break;
            case 2: //insert trip
                insertTrip();
                break;
            case 3: //insert taxi
                insertTaxi();
                break;
            case 4: //get the drivers location
                getDriverLocation();
                break;
            case 6: //move all the drivers to driver
                startDrivingAll();
                break;
            case 9: //update clock time
                updateTimeClock();
            case 7: //exit
                return;
            default:
                break;
        }
        cin >> option;
    }
}

//insert a new taxi from the input arguments
void Menu::insertTaxi() {
    char dummy;
    int id, taxiType;
    char manufacturer, color;
    std::cin >> id >> dummy >> taxiType >> dummy >> manufacturer >> dummy >> color;
    //create the taxi
    TaxiCab cab = createTaxi(id, taxiType, manufacturer, color);
    taxiCenter.addTaxiCab(cab);

}

//pass date from server<->client
void Menu::updatesFromClient(TaxiCenter taxiCenter) {
    Udp udp(1, 5555);
    udp.initialize();

    char buffer[1024];
    udp.receiveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp.sendData("sup?");
// deserialize driver
    string serial_str_driver;
    std::cin >> serial_str_driver;
    Driver *d = deserialize<Driver>(serial_str_driver);
    taxiCenter.addDriver(*d);
    TaxiCab taxiCab = taxiCenter.getTaxi(d->getVehicleId());
    //serialize taxi
    string serial_str_vehicle = serialize(&taxiCab);
    //sent back the taxi
    udp.sendData(serial_str_vehicle);
    //serialize trip
    taxiCenter.createRides();
    Trip *trip = taxiCenter.getTrip(d->getId());
    string serial_str_trip=serialize(trip);
    udp.sendData(serial_str_trip);
    serializeClockToClient( taxiCenter);

}

void Menu::serializeClockToClient(TaxiCenter taxiCenter) {
    Udp udp(1, 5555); //TODO NOT SURE WE HAVE TO OPEN NEW UDP
    udp.initialize(); //TODO NOT SURE WE HAVE TO OPEN NEW UDP
    //serialize clock
    Clock * clockForSerialize= &clock;
    string serial_str_clock=serialize(clockForSerialize);
    udp.sendData(serial_str_clock);
}


//expecting a new driver from the client
void Menu::expectingDriver(TaxiCenter taxiCenter){
    int numOfDrivers;
    std::cin>>numOfDrivers;
    int index =1;
    while (index<=numOfDrivers){
        updatesFromClient(taxiCenter);
        index++;
    }

}

//insert a new trip from the input arguments
void Menu::insertTrip() {
    char dummy;
    int id;
    int xStart, yStart, xEnd, yEnd;
    int numOfPass;
    double tariff;
    int timeOfStart;
    std::cin >> id >> dummy >> xStart >> dummy >> yStart >> dummy >> xEnd
             >> dummy >> yEnd >> dummy >> numOfPass >> dummy >> tariff
             >> dummy >>timeOfStart;
    //create the trip
    Trip newTrip = createTrip(grid, id, xStart, yStart, xEnd, yEnd,
                              numOfPass, tariff, timeOfStart);
    taxiCenter.addTrip(newTrip);

}

////insert a new driver from the input arguments
//void Menu::insertDriver() {
//    char dummy;
//    int id, age;
//    char status;
//    int experience, vehicleId;
//    std::cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> vehicleId;
//    Driver d = createDriver(id, age, status, experience, vehicleId);
//    taxiCenter.addDriver(d);
//
//}

//create obstacles from the input arguments
void Menu::getObstacles() {
    int numOfObstacles;
    char dummy;
    int x;
    int y;
    //num of obstacles
    std::cin >> numOfObstacles;
    while (numOfObstacles > 0) {
        std::cin >> x >> dummy  >> y;
        Node* n = new NodeMatrix(x, y);
        grid.addObstacle(n);
        delete n;
        numOfObstacles--;
    }

}

//get the driver location from the input arguments
void Menu::getDriverLocation() {
    int idDriver;
    std::cin >> idDriver;
    std::cout << taxiCenter.getDriverLocation(idDriver);

}

// move all the drivers to the next node in the trip
void Menu::startDrivingAll() {
    taxiCenter.createRides();
    taxiCenter.moveAllRidesToTheEnd();

}


//constructor to a new 
Menu::Menu(TaxiCenter taxiCenter, Matrix grid, Clock clock)
        : grid(grid), taxiCenter(taxiCenter), clock(clock) {
            this->clock=clock;
}

//update clock time
void Menu::updateTimeClock(){
  //  this->clock.addToCurrentTime(1);

    serializeClockToClient(taxiCenter);
}
