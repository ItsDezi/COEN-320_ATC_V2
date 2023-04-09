#ifndef COMPUTERSYSTEM_H_
#define COMPUTERSYSTEM_H_
#define _DEFAULT_SOURCE
#include <iostream>
#include <vector>
#include <pthread.h>
#include "AircraftData.h"
//#include "aircraft.h"
//#include "Radar.cpp"
//#include "DataDisplay.h"
using namespace std;



class ComputerSystem {

public:

    //constructor: We need to know the number of aircrafts in the air to determine if any violations occur 
	ComputerSystem(int periodicComputations);
	
    //Destructor:
	~ComputerSystem();
    
    //To start the pthread for periodic computations to detect violations
    void startPeriodicComputations(); 
    
    //To stop the pthread for periodic computations to detect violation
    void stopPeriodicComputations(); 

	//To calculate and detect Violations
    //const : to not modify contents in aricraft. 
    // This function only reads -> no need to modify anything
    bool computeViolations(vector<AircraftData> &aircraft);
		
    //To emit an alert in case a violation occurs
	void sendViolationAlert();
   
    //To calculate periodic computations
    void periodicComputations(); 
   
    //Function to calculate future position: 
    void calculateFuturePosition(AircraftData* aircraft, double time_);

    //Function to calculate the prediction for the next 3 minutes: 
    void computeViolationsFor3Minutes(vector<AircraftData>& aircraft); 

private: 

    vector<AircraftData> aircraft;

    //bool for computeViolations function: 
    bool violationDetected ;

    //pthread to detect alert to operator: 
    pthread_t detectViolations;
   
    // //Radar Instance 
    // Radar& radar;

    // //DataDisplay Instance: 
    // DataDisplay dataDisplay;

    int numberAircrafts;

    int periodicComputations_; 
    
};

#endif
