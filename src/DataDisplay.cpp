#include <iostream>
#include <vector>
#include "AircraftData.h"
#include "ComputerSystem.h"
#include "DataDisplay.h"
using namespace std; 



void DataDisplay::displayAircraftData(const vector<AircraftData> aircraftData)  {
    for (const AircraftData& aircraft : aircraftData) {
        cout << "Aircraft ID: " << aircraft.ID << endl;
        cout << "Arrival time: " << aircraft.arrivalTime << endl;
        cout << "Position (x, y, z): " << aircraft.x << ", " << aircraft.y << ", " << aircraft.z << endl;
        cout << "Speed (x, y, z): " << aircraft.xSpeed << ", " << aircraft.ySpeed << ", " << aircraft.zSpeed << endl;
        cout << " -----------------------------------" << endl; 
    }
}
