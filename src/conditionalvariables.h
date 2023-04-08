
#ifndef CONDITIONALVARIABLES_H_
#define CONDITIONALVARIABLES_H_
#include "pthread.h"
extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
class conditional_variables {
public:
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	conditional_variables();
	virtual ~conditional_variables();
};

#endif /* CONDITIONALVARIABLES_H_ */
