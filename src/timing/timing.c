/* timing.c
** - Timing functions
*/

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#ifdef _WIN32
#include <mmsystem.h>
#endif

#include "timing.h"

/* 
 * Returns milliseconds no matter what. 
 */
uint64_t timing_get_time(void)
{
#ifdef _WIN32
	return timeGetTime();
#else 
	struct timeval mtv;

	gettimeofday(&mtv, NULL);

	return (uint64_t)(mtv.tv_sec) * 1000 + (uint64_t)(mtv.tv_usec) / 1000;
#endif
}

void timing_sleep(uint64_t sleeptime)
{
	struct timeval sleeper;

	sleeper.tv_sec = 0;
	sleeper.tv_usec = sleeptime * 1000;

	select(1, NULL, NULL, NULL, &sleeper);
}
