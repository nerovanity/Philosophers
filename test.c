#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

int fgettimeofday(struct timeval *tv, struct timezone *tz)
{
	struct timeval tv1;
	gettimeofday(&tv1, NULL);
	return (tv1.tv_sec * 1000 + tv1.tv_usec / 1000);
}

void n3esse(int m)
{
	usleep(m * 1000);
}

int main ()
{
	int start = fgettimeofday(NULL, NULL);
	printf("%d\n",start);
	n3esse(1000);
	int end = fgettimeofday(NULL, NULL);
	printf("%d", end - start);
	return 0;
}