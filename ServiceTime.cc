#include "ServiceTime.h"
#include <ctime>

time_t getCurrentTime() {
	time_t current_time;
	time(&current_time);
	return current_time;
}
