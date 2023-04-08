//#include "aircraft.h"
#include <iostream>
#include <string>
#include <string.h>
//#include <pthread>
#include "aircraft.h"
#include <chrono>
//extern int sigwait(const sigset_t *__set, int *__sig);

using namespace std;

//string ID;
//prevClock is to save the last clock value for speed estimations
int arrivalTime, x ,y ,z , xSpeed, ySpeed, zSpeed;//, prevClock;
//Timer * clk;
//thread m_thread;
//AircraftData data;
aircraft::aircraft() {
	// TODO Auto-generated constructor stub
	//m_thread = std::thread(&Clock::run, this);
}
aircraft::aircraft(AircraftData datating)
{
	//const char* ccx = data.ID.c_str();
	//pthread_setname_np(this->thread, ccx);
	data = datating;
	//clk = &clock_in;
	prevClock = datating.arrivalTime;
	//m_thread = thread(&aircraft::run);
}

aircraft::~aircraft() {
	// TODO Auto-generated destructor stub
}

void aircraft::test_print()
{
	//cout<<"Arrival Time: "<< data.arrivalTime<<endl;
	cout<<"ID: "<< data.ID<<endl;
	cout<<"X: "<< data.x<<endl;
	cout<<"Y: "<< data.y<<endl;
	cout<<"Z: "<< data.z<<endl;
	cout<<"X Speed: "<< data.xSpeed<<endl;
	cout<<"Y Speed: "<< data.ySpeed<<endl;
	cout<<"Z Speed: "<< data.zSpeed<<endl;
}
void* aircraft::updatePosition(void* args)//
{
	aircraft* a = (aircraft*) args;
	//cout<<"\nTimer count from update position: "<<a->clk->count<<endl;
	//cTimer timer(1,0,1,0); //initialize, set, and start the 1 second timer
	a->clk = cTimer(1,0,1,0);
	//sleep(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	a->arrived = true;
	while(true)
	{
		//wait for signal from timer
	//cout<<"\nTimer count from update position: "<<a->clk->count<<endl;
	//aircraft a = *c;
	//aircraft *a = this;
	//this->test_print();
	//a->test_print();
	//cout<<"\nupdatePosition is being called at "<<timer.count<<endl;
	cout<<"\nAircraft "<< a->data.ID << " is calling updatePositon at "<<a->clk.count<<" seconds(relative)"<<endl;
	//sleep(2);
	//int t = (1000*(a->clk->count) - a->prevClock);//PROBLEM?!?!?!?!?
	//cout<<"\n clock from aircraft is: "<< a->clk->elapsed();
	//cout<<"\n previous clock count: "<< a->prevClock;
	//a->prevClock = a->clk->count;
	a->data.x += (a->data.xSpeed);
	a->data.y += (a->data.ySpeed);
	a->data.z += (a->data.zSpeed);
	a->test_print();
	  /*pthread_mutex_lock(&mutex);
	  pthread_cond_wait(&cond, &mutex);
	  pthread_mutex_unlock(&mutex);*/
	//int * dummy;
	//a->clk->sigwait(a->clk->sig_set, &dummy);
	//int dummy;
	//cout<<"\nAircraft "<< a->data.ID << " before wait" <<endl;
	//usleep(1);
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	a->clk.wait_next_activation();
	//sigwait(&timer.sig_set, &dummy);
	//cout<<"\nAircraft "<< a->data.ID << " after wait" <<endl;
	//cout.flush();
	}
}
struct thread_args {    /* Used as argument to the start routine thread_start() */
	int period_sec;    //desired period of the thread in seconds
	int period_msec;   //desired period of the thread in milliseconds
};
void aircraft::changeSpeed()//when commands are received from the operator console
{

}
void* aircraft::run(void *a)
{
	while(1 != 0)
	{
		//updatePosition(a);
	}
}

