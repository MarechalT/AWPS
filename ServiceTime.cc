#include "ServiceTime.h"
#include <ctime>
#include <sys/select.h>	//select()

time_t getCurrentTime() {
	time_t current_time;
	time(&current_time);
	return current_time;
}


void hibernate(int s) {
	struct timeval t;
	t.tv_sec = s;
	t.tv_usec = 0;
	select(0, NULL, NULL, NULL, &t);
}
