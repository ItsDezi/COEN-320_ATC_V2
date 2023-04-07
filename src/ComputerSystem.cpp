#include "ComputerSystem.h"
#include <iostream>
#include <pthread.h>
#include <cmath>
#include "AircraftData.h"
#include "aircraft.h"
//#include "Radar.cpp"
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <sys/neutrino.h>
//#include <sys/dispatch.h>
//#include "MPData.h"


//Constructor:
ComputerSystem::ComputerSystem(Radar& radar, int numberAircrafts, int periodicComputations )
    :radar(radar), numberAircrafts(numberAircrafts), periodicComputations_(periodicComputations)
{
    //Retrieve Information about aircraft from radar:
        AircraftData info = radar.getAircraftInformation();

        for (int i = 0; i < info.size(); i++){
            info[i].data.ID = info.ID;
            info[i].data.x = info.x;
            info[i].data.y = info.y;
            info[i].data.z = info.z;
        }
        //to turn off:
        falseFlag = false;

        //Initialize the mutex:
        pthread_mutex_init(&aircraftMutex,NULL);
 }

//Destructor
ComputerSystem::~ComputerSystem(){

    //use stop to stop the function called detectViolations
    stopPeriodicComputations();

}

//Function to start Periodic Computation to check for violations
void* ComputerSystem::startPeriodicComputations(){
    pthread_create(&detectViolations, NULL, &ComputerSystem::computeViolations, this);
}

//Function to stop Periodic Computation to check for violations
void ComputerSystem::stopPeriodicComputations(){
    falseFlag = true;
    pthread_join(detectViolations,NULL);
}

//Function to compute violations
void* ComputerSystem::computeViolations(vector<AircraftData>& aircraft){
    // insert a timer to display a warning 3 minutes before a violation:
    // 3 minutes = 180 seconds
    int timer {0};

    // get the channel ID for message passing
    int channelId = ChannelCreate(0);
    if(channelId == -1){
        cout << "Error creating the channel." << endl;
        return NULL;
    }

    //Start loop to compute violations:
    while(falseFlag == false) {
    AircraftData info = radar.getAircraftInformation();
        // to check for Violations:
        for (int i =0; i < info.size(); i++ ){
            for (int j = i+1; j < info.size();j++){

                int position_x = abs(info[i].data.x - info[j].data.x);
                int position_y = abs(info[i].data.y - info[j].data.y) ;
                int position_z = abs(info[i].data.z - info[j].data.z);
                double distance = sqrt((position_x * position_x) + (position_y * position_y) + (position_z * position_z));
                if (position_x < 3000 || position_y < 3000 || position_z < 1000){
                        if ( timer <= 180){

//                    //output Message to data Display:
//                    //create a message to send to the data display
//                    my_message_t message;
//                    message.type = 1;
//                    sprintf(message.data, "Danger! Safety violation detected between aircraft %d and aricraft %d. The distance between them is: %f", info[i].data.ID, info[j].data.ID, distance);
//
//                    // send the message to the data display using QNX message passing
//                        if(MsgSend(DataDisplay.getMsgChannelID(), &message, sizeof(message), NULL, 0) == -1){
//                            cout << "Error sending message to data display." << endl;
//                            return NULL;
//                        }

                    //Show axis violation:  // idk how to output on which axis.
                    if (position_x < 3000){
                    cout <<" Violation is on X-axis" << endl;
                    }
                    if(position_y < 3000){
                        cout << " Violation on Y-axis" << endl;
                    }
                    if( position_z < 1000){
                        cout << " Violation on Z-axis" << endl;
                     }


                }

                }
            }
        }

        //To keep track of the time that has passed since last violation, we need to increment:
        timer ++;
    }
//    // destroy the channel
//    ChannelDestroy(channelId);
//
//    return NULL;
}

//Function to update position to data display;
void ComputerSystem::updateAircraftPosition(){

    //lock the mutex:
    pthread_mutex_lock(&aircraftMutex);

    AircraftData info = radar.getAircraftInformation();

    for(int i = 0; i < info.size(); i++){


    }

    pthread_mutex_unlock(&aircraftMutex);
}

//void ComputerSystem::receiveMessage(MPData* info){
//
//    name_attach_t *attach;
//    MPData message;
//    int channelID;
//    int receiveID;
//    Message message;
//
//    chid = ChannelCreate(0); //create a new channel and assigns the value to chid variable
//
//    if ((attach = name_attach(NULL, ATTACH_POINT,0)) == NULL) {
//        perror("Error occured while creating the channel");
//    }
//
//    while (true){
//        receiveID = MsgReceive(chid, &message, sizeof(Message),NULL);
//
//        if(receiveID == -1){
//            perror("Failure receiving messages");
//            break;
//        }
//
//        if(receiveID == 0){ //Pulse Received:
//            switch (message.hdr.code){
//                case _PULSE_CODE_DISCONNECT:
//
//                    ConnectDetach(message.hdr.scoid);
//                    break;
//                case _PULSE_CODE_UNBLOCK;
//                    break;
//                    default:
//
//                break;
//            }
//                continue;
//        }
//
//
//
//
//        //change our hexa values:
//            if (message.hdr.type == 0x00) {
//                //speed message received
//                if (message.hdr.subtype == 0x01){
//                    printf("The speed of the aircraft is: %.2f \n",message.info);
//                }
//            }
//
//            else if (message.hdr.subtype == 0x02){
//                //Position message received
//                printf("The aircraft is at position  %.2f m \n",message.info);
//                printf ("\n");
//            }
//            else {
//                MsgError(receiveID, ENOSYS);
//                continue;
//            }
//
//            MsgReply(receiveID, EOK, 0,0);
//        }
//        name_detach(attach, 0);
//        return ;
}








