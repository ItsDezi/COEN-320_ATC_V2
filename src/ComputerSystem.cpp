#include "ComputerSystem.h"
#include <iostream>
#include <pthread.h>
#include <cmath>
#include "AircraftData.h"
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>

//#include <sys/neutrino.h>
//#include <sys/dispatch.h>
//#include "MPData.h"

//Constructor:
ComputerSystem::ComputerSystem(int periodicComputations): periodicComputations_(periodicComputations)
{

    //
    // // Receive information about aircraft from message passing:
    // vector<AircraftData> info;

    //  for (int i = 0; i < info.size(); i++){
    //         info[i].data.ID = info.ID;
    //         info[i].data.x = info.x;
    //         info[i].data.y = info.y;
    //         info[i].data.z = info.z;
    //     }

}

//Destructor
ComputerSystem::~ComputerSystem(){
    
    //use stop to stop the function called detectViolations
    stopPeriodicComputations();
}

// //Function to start Periodic Computation to check for violations
// void ComputerSystem::startPeriodicComputations(){
//     pthread_create(&detectViolations, NULL, ComputerSystem::computeViolations, this);
// }

//Function to stop Periodic Computation to check for violations
void ComputerSystem::stopPeriodicComputations(){
    pthread_join(detectViolations,NULL);
}

 //Compute time interval has only one parameter which is a vector of aircraftData and this comes from the server. 
    //Message passing. 
    //Compute violation for three minutes. 
    //this is bc we have to check the time and then we have to do compute violations. 
    //we have to check from 0 -> 180.
    //


//Calculate future position and then pass to computeViolations to predict violations 
void ComputerSystem::calculateFuturePosition(AircraftData* aircraft, double time_ ) {
    double speed_x = aircraft->xSpeed;
    double speed_y = aircraft->ySpeed;
    double speed_z = aircraft->zSpeed;
    
    //double time_ = 180; // time interval in seconds from t0 -> t0 + 180
    
    //Calculte new position based on the aircraft speed and variable time
    //use -> to access AircraftData struct 
    //update the position of an aircraft based on its current time and speed. 
    //takes current position and do addition to the multiplication of its speed and current time and store in position_x. 
    aircraft->x = aircraft->x + speed_x * 180;
    aircraft->y = aircraft->y + speed_y * 180;
    aircraft->z = aircraft->z + speed_z * 180;
}


bool ComputerSystem::computeViolations(vector<AircraftData>& aircraft) {
    bool violationDetected = false;

        // Receive data from message passing channel:

 // to check for Violations: ( Check for constraints )
        for (int i = 0; i < aircraft.size(); i++) {
            for (int j = i + 1; j < aircraft.size(); j++) {

                // Calculate future position if t != current time based on speed (as vector and time)  
                // as parameters and returns new position:
                calculateFuturePosition(&aircraft[i], 180);
                calculateFuturePosition(&aircraft[j], 180);

                //Retrieve updated positions from calculateFuturePosition function: 
                double position_i_x = aircraft[i].x;
                double position_i_y = aircraft[i].y;
                double position_i_z = aircraft[i].z;
                double position_j_x = aircraft[j].x;
                double position_j_y = aircraft[j].y;
                double position_j_z = aircraft[j].z;

                double position_x = abs(aircraft[i].x - aircraft[j].x); 
                double position_y = abs(aircraft[i].y - aircraft[j].y); 
                double position_z = abs(aircraft[i].z - aircraft[j].z); 
                double distance_x = sqrt((position_x * position_x)); 
                double distance_y = sqrt((position_y * position_y)); 
                double distance_z = sqrt((position_z * position_z)); 
                double distance_total = sqrt((position_x * position_x) + (position_y * position_y) + (position_z * position_z));
    
                if (position_x < 3000 || position_y < 3000 || position_z < 1000) {
                    violationDetected = true;
                    cout << "WARNING! Violation detected between aircrat ID " << aircraft[i].ID << " and aircraft ID "<< aircraft[j].ID << endl; 
                    cout << "The distance between them is:  " << distance_total << endl; 
                   
                    //Show axis violation:
                    if (position_x < 3000) {
                        cout << "Violation is on X-axis: The distance in the X-axis is: " << distance_x << endl;
                    }
                    if (position_y < 3000) {
                        cout << "Violation is on Y-axis: The distance in the Y-axis is: " << distance_y << endl;
                    }
                    if (position_z < 1000) {
                        cout << "Violation is detected on the Z-axis: The distance in the Z-axis is:  " << distance_z << endl;
                    }
                }
            }
        }
    
    return violationDetected;
    cout << "No violations detected" << endl; 
}


//we are iterating over the time interval from  0 to 180 seconds
// and for each iteration we are calling the computeViolations function
// with the aircraft vector and the current time interval.
// If any violations occur in the next 180 sec the computeViolations function will take care of it.
void ComputerSystem::computeViolationsFor3Minutes(vector<AircraftData>& aircraft) {
    for (int i = 0; i < 180; i++) {
        // Check for violations in the next 180 seconds
        bool violationDetected = computeViolations(aircraft);

        if (violationDetected) {
            // If a violation is detected, break out of the loop and exit the function
            cout << "Violation detected in 180 seconds" << endl;
            break;
        }

        // Calculate future positions for all aircraft
        for (int j = 0; j < aircraft.size(); j++) {
            calculateFuturePosition(&aircraft[j], 1);
        }
    }
}

