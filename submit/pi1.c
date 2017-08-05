#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define LEN 10000

struct result{
	float sum;
};

float answer;
void *subThread()
{
	int i;
	float j;
	struct result *result;
	float sum1 = 0,sum2 = 0,sum = 0;
	for(i = LEN / 2 + 1;i<=LEN;i++){
		j = i;
		if(i % 2 == 0){
			sum1 += 1 / (2 * j - 1);
		}
		//
		if(i % 2 == 1){
			sum2 += 1 / (2 * j - 1);
		}
		//
	}
	sum = sum2 - sum1;
	result = malloc(sizeof(result));
	result->sum = sum;
	//
	printf("sub pi = %f\n",sum);
	return result;
}

void parThread()
{
	int i;
	float j;
	float sum1 = 0,sum2 = 0,sum = 0;
	for(i = 1;i<=LEN / 2;i++){
		j = i;
		if(i % 2 == 0){
			sum1 += 1 / (2 * j - 1);
		}
		if(i % 2 == 1){
			sum2 += 1 / (2 * j - 1);
		}
	}
	sum = sum2 - sum1;
	answer += sum;
	printf("par_answer pi = %f\n",answer);
}

int main(int argc,char *argv[])
{
	answer = 0;
	pthread_t sub;
	pthread_create(&sub,NULL,subThread,NULL);
	parThread();
	struct result *result;
	pthread_join(sub,(void **)&result);
	answer += result->sum;
	printf("pi = %f\n",answer * 4);
	return 0;
}

