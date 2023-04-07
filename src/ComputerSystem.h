#ifndef COMPUTERSYSTEM_H_
#define COMPUTERSYSTEM_H_
#define _DEFAULT_SOURCE
#include <iostream>
#include <vector>
#include <pthread.h>
#include <mutex>
#include "AircraftData.h"
//#include "aircraft.h"
//#include "Radar.cpp"
//#include "DataDisplay.h"
using namespace std;



class ComputerSystem {

public:

    //constructor: We need to know the number of aircrafts in the air to determine if any violations occur
	ComputerSystem(Radar& radar, int numberAircrafts, int periodicComputations);

    //Destructor:
	~ComputerSystem();

    //To start the pthread for periodic computations to detect violations
    void startPeriodicComputations();

    //To stop the pthread for periodic computations to detect violation
    void stopPeriodicComputations();

	//To calculate and detect Violations
    void* computeViolations(vector<AircraftData>& aircraft);

    //To display data on Display Data
	void showDataDisplay();

    //To update period
	void updateAircraftPosition();

    //To emit an alert in case a violation occurs
	void sendViolationAlert();

    //To calculate periodic computations
    void periodicComputations();

    //To send updated Data to data display
    void sendDataToDataDisplay(int ID,int x,int y,int z);

    //To send violation message to data display:
    void sendViolationsToDataDisplay(string violation);

    //To receive messages from Operator Console:
   // void receiveMessage(Message message);

    //To send updated xSpeed,ySpeed,zSpeed to Communication system:
    void sendToCommunicationSystem(int ID, int xSpeed, int ySpeed, int zSpeed);

private:

    vector<AircraftData> aircraft;

    //pthread to detect alert to operator:
    pthread_t detectViolations;

    //Boolean function to stop detectViolation Thread:
    bool falseFlag;

    //Radar Instance
    Radar& radar;

    //DataDisplay Instance:
    DataDisplay dataDisplay;

    int numberAircrafts;

    int periodicComputations_;

    //ID thread for detecting Violations:
   // pthread_t detectViolations;

    //pthread to protect shared data:
    pthread_mutex_t aircraftMutex;

    pthread_t aircraftMutex_;

};

#endif
