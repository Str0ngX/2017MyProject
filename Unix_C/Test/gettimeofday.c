#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
	struct timeval start, end;
	gettimeofday( &start, NULL); /* start time of testing */
	double timeuse;
	int j;
	for(j = 0; j < 1000000; j++) {
		printf("%d\r",j);
	}
	gettimeofday( &end, NULL); /* end time of testing */
	timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
	timeuse /= 1000000;
	printf("运行时间为：%f\n",timeuse);
	return 0;
}

