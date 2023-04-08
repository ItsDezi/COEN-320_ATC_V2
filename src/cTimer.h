#ifndef CTIMER_H_
#define CTIMER_H_

#include <stdio.h>
#include <iostream>
#include <time.h>

#include <sync.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <stdint.h>
#include <chrono>
#include <thread>
#include <pthread.h>
//#include "pthread.h"
//#include "conditionalvariables.h"

//pthread_mutex_t mutex1; // declare the mutex variable
class cTimer {
	timer_t timer_id;
	struct sigevent sig_event;
	sigset_t sig_set;
	struct itimerspec timer_spec;
	struct timespec tv;

public:
	cTimer();
	int count;
	cTimer(uint32_t,uint32_t,uint32_t,uint32_t);
	~cTimer();
	void set_timer(uint32_t,uint32_t,uint32_t,uint32_t);
	void wait_next_activation();

};

#endif /* CTIMER_H_ */
