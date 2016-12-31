
#include "persons/Driver.h"
#include "core_classes/Matrix.h"
#include "TaxiCenter.h"
#include "Menu.h"
#include "stdlib.h"
int main() {
//    TaxiCenter taxiCenter = TaxiCenter();

    int width, height;
    
    //grid initialize grid and add obstacles if there are any.
    std::cin >> width >> height;
    Matrix grid = Matrix(width, height);
//    Menu menu = Menu(taxiCenter, grid);
    
    //run all the other inputs
//    menu.run();
    return 0;
}
