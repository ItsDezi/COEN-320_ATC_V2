#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "aircraft.h"
#include <list>
#include <vector>
#include <fstream>

using namespace std;
#include "cTimer.h"

struct thread_args {    /* Used as argument to the start routine thread_start() */
	int period_sec;    //desired period of the thread in seconds
	int period_msec;   //desired period of the thread in milliseconds
};
vector<aircraft> read_input(cTimer * timer);
aircraft create_aircraft(string s, cTimer * ptr);

vector<aircraft> aircrafts;

void *thread_start (void *arg) {
	struct thread_args *targs = ( struct thread_args * ) arg;
	cTimer * timerPtr;
	//create radar,computer system, etc threads here
	int period_sec=targs->period_sec;
	int period_msec=targs->period_msec;
	int arrival_index = 0;//goes through vector of aircrafts and marks where in the ordered list the program should start aircraft threads
	int count = 0;
	cTimer timer(period_sec,period_msec,period_sec,period_msec); //initialize, set, and start the 1 second timer
	cTimer timer5Sec(period_sec*5,period_msec*5,period_sec*5,period_msec*5);//initialize, set, and start the 5 second timer
	timerPtr = &timer;
	read_input(timerPtr);
	cout<<"\nSIZE:"<<aircrafts.size();
//	pthread_attr_t attr;
//	/* Initialize attributes */
//	int err_no;
//	err_no = pthread_attr_init(&attr);
//	if (err_no!=0)
//		printf("ERROR from pthread_attr_init() is %d \n", err_no);
//	err_no = pthread_attr_setschedpolicy(&attr,SCHED_SPORADIC);
//	if (err_no!=0)
//		printf("ERROR from pthread_attr_setschedpolicy() is %d \n", err_no);
	while(true){
		//cout<<"\n count: ";
		//count++;
		//pthread_create(&a.thread, NULL, aircraft::updatePosition, &a);
		//cout<<"\nCLK time: "<<timer.count*1000<<endl;

		if((aircrafts[arrival_index].data.arrivalTime <= (timer.count*1000)) && (aircrafts[arrival_index].arrived == false && arrival_index < aircrafts.size()))
		{
			pthread_attr_t attr;
			/* Initialize attributes */
			int err_no;
			err_no = pthread_attr_init(&attr);
			if (err_no!=0)
				printf("ERROR from pthread_attr_init() is %d \n", err_no);
			err_no = pthread_attr_setschedpolicy(&attr,SCHED_SPORADIC);
			if (err_no!=0)
				printf("ERROR from pthread_attr_setschedpolicy() is %d \n", err_no);
			/* Set detach state */
			err_no = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
			if (err_no!=0)
				printf("ERROR from pthread_attr_setdetachstate() is %d \n", err_no);
			int err;
			cout<<"\naircraft "<<aircrafts[arrival_index].data.ID<<" thread is being created "<<"at "<<timer.count<<endl;

			err = pthread_create(&aircrafts[arrival_index].thread, &attr, aircraft::updatePosition, &aircrafts[arrival_index]);
			arrival_index++;
			if (err != 0){
				printf("ERROR when creating the aircraft thread \n");
			}

			//aircrafts.front()
		}

		timer.wait_next_activation();
	}//end_while


	return NULL;
}//end_thread_start()



int main (int argc, char* argv[]) {

	//input arguments of the thread_start routine
	struct thread_args targs;

	targs.period_sec=0;
	targs.period_msec=1000;


	pthread_t thread_id;//ID of the thread
	int err_no;
	err_no = pthread_create(&thread_id, NULL, &thread_start, &targs); //create the thread
	if (err_no != 0){
		printf("ERROR when creating the thread \n");
	}


	err_no = pthread_join(thread_id, NULL); //force the main to wait for the termination of the thread
	if (err_no != 0){
		printf("ERROR when joining the thread\n");
	}
	pthread_exit(EXIT_SUCCESS);
}

vector<aircraft> read_input(cTimer * timerPtr)
{
	//cTimer * timerPtr = NULL;
	//create radar,computer system, etc threads here
	//int period_sec=targs->period_sec;
	//int period_msec=targs->period_msec;
	//cTimer timer(0,1000,0,1000); //initialize, set, and start the 1 second timer
	//timerPtr = &timer;
	string line,s;
	ifstream myfile;
	myfile.open("input.txt");
	aircraft a;
	//create_aircraft("hello,");
	getline(myfile,line);//to ignore first line
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			//cout << line << '\n';
			a = create_aircraft(line, timerPtr);
			//cout<<"\n----------------------\n"<< a.data.ID<<"\n---------------------\n";

			aircrafts.push_back(a);
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	cout<<"\nBefore sort: ";
	for(int i = 0; i< aircrafts.size();i++)
	{
		sleep(0.2);
		cout<<"\nID: "<<aircrafts[i].data.ID<< "\n";
	}
	sort( aircrafts.begin(), aircrafts.end(), []( aircraft &a, aircraft &b){ return (a.data.arrivalTime < b.data.arrivalTime);});
	cout<<"\nFront of aircrafts vector: "<<aircrafts.front().data.ID;

	cout<<"\nAfter sort: ";
	for(int i = 0; i< aircrafts.size();i++)
	{
		sleep(0.2);
		cout<<"\nID: "<<aircrafts[i].data.ID<< "\n";
	}

}

aircraft create_aircraft(string s, cTimer * ptr)
{
	int ID;

	int time, x, y, z, speedX, speedY, speedZ;
	list<int> comma_locations;
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace),
			s.end());
	for(int i=0;i<s.length();i++)
	{
		//cout<<s[i];
		char c = s[i];

		//int res = c.compare(comma);
		if(c==',')
		{
			comma_locations.push_front(i);
		}
	}
	time = stoi(s.substr(0,comma_locations.back()));
	int temp = comma_locations.back();
	//cout<<'\n'<<"time: "<<time;

	comma_locations.pop_back();

	int len = comma_locations.back()-temp-1;
	ID = stoi(s.substr(temp+1, len));
	//cout<<'\n'<<"ID: "<<ID;
	temp = comma_locations.back();

	comma_locations.pop_back();

	len = comma_locations.back()-temp-1;
	x = stoi(s.substr(temp+1, len));
	//cout<<'\n'<<"X: "<<x;
	temp = comma_locations.back();

	comma_locations.pop_back();

	len = comma_locations.back()-temp-1;
	y= stoi(s.substr(temp+1, len));
	//cout<<'\n'<<"Y: "<<y;
	temp = comma_locations.back();

	comma_locations.pop_back();

	len = comma_locations.back()-temp-1;
	z = stoi(s.substr(temp+1, len));
	//cout<<'\n'<<"Z: "<<z;
	temp = comma_locations.back();

	comma_locations.pop_back();

	len = comma_locations.back()-temp-1;
	speedX = stoi(s.substr(temp+1, len));
	//cout<<'\n'<<"Speed X: "<<speedX;
	temp = comma_locations.back();

	comma_locations.pop_back();

	len = comma_locations.back()-temp-1;
	speedY= stoi(s.substr(temp+1, len));
	//cout<<'\n'<<"Speed Y: "<<speedY;
	temp = comma_locations.back();

	comma_locations.pop_back();

	len = comma_locations.back()-temp-1;
	speedZ = stoi(s.substr(temp+1, len));
	//cout<<'\n'<<"Speed Z: "<<speedZ;
	temp = comma_locations.back();

	AircraftData d;
	d = (AircraftData){.ID = ID, .arrivalTime = time, .x = x , .y = y , .z = z , .xSpeed = speedX, .ySpeed = speedY, .zSpeed = speedZ};
	aircraft a = aircraft(d, *ptr);

	return a;
}
