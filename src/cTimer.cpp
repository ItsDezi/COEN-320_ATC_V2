#include "cTimer.h"
pthread_mutex_t mutex1; // declare the mutex variable

cTimer::cTimer(uint32_t period_sec, uint32_t period_msec, uint32_t offset_sec,uint32_t offset_msec ) {
	const int signal = SIGALRM;
	count = 0;
	sigemptyset(&sig_set); // initialize a signal set
	sigaddset(&sig_set, signal); // add SIGALRM to the signal set
	sigprocmask(SIG_BLOCK, &sig_set, NULL); //block the signal
	pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


	/* set the signal event a timer expiration */
	memset(&sig_event, 0, sizeof(struct sigevent));
	sig_event.sigev_notify = SIGEV_SIGNAL;
	sig_event.sigev_signo = signal;



	if (timer_create(CLOCK_REALTIME, &sig_event, &timer_id) == -1){
		std::cerr << "Timer, Init error : " << errno << "\n";
	}

	set_timer(period_sec,1000000* period_msec,offset_sec,1000000* offset_msec);//Set the timer offset and period (both expressed in sec and nsec)
}
cTimer::cTimer() {}


cTimer::~cTimer() {
	// TODO Auto-generated destructor stub
    //pthread_mutex_destroy(&mutex1); // destroy the mutex
}

void cTimer::set_timer(uint32_t p_sec, uint32_t p_nsec, uint32_t o_sec, uint32_t o_nsec ){
	timer_spec.it_value.tv_sec = o_sec;
	timer_spec.it_value.tv_nsec = o_nsec;
	timer_spec.it_interval.tv_sec = p_sec;
	timer_spec.it_interval.tv_nsec = p_nsec;
	timer_settime(timer_id, 0, &timer_spec, NULL);//Start the timer
}

void cTimer::wait_next_activation() {
    pthread_mutex_lock(&mutex1); // lock the mutex
	int dummy;
	/* suspend calling process until a signal is pending */
	count++;
	//std::cout<<count;
	  /*pthread_mutex_lock(&mutex);
	  pthread_cond_signal(&cond);
	  pthread_mutex_unlock(&mutex);*/
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));

	sigwait(&sig_set, &dummy);
    pthread_mutex_unlock(&mutex1); // unlock the mutex
	//int getID = MsgRecieve(chid, &msg_buffer, sizeof(msg_buffer), NULL);
}


