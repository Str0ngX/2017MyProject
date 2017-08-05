#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define LEN 100000
#define MAX_WORKERS 100

struct param{
	int start;
	int end;
};

struct result{
	float sum;
};

void *compute(void *arg)
{
	int i;
	float j;
	struct param *myparam;
	myparam = (struct param *)arg;
	int start = myparam->start;
	int end = myparam->end;

//	printf("%d\t%d\n",myparam->start,myparam->end);
	struct result *myresult;
	float sum1 = 0,sum2 = 0,sum = 0;
	for(i = start; i <= end; i++){
		j = i;
		if(i % 2 == 0){
			sum1 += 1 / (2 * j - 1);
		}
		if(i % 2 == 1){
			sum2 += 1 / (2 * j - 1);
		}
	}
	myresult = malloc(sizeof(struct result));
	sum = sum2 - sum1 ;
	myresult->sum = sum;
//	printf("the part of pi: %f\n",myresult->sum);
	return myresult;
}

int main(int argc,char *argv[])
{
	int thread_num = 1;
	struct param myparams[MAX_WORKERS + 1];
	pthread_t workers[MAX_WORKERS];
	printf("Please input thread number:");
	scanf("%d",&thread_num);
	int i;
	myparams[0].start = 0;
	myparams[0].end = 0; 

	for(i = 1; i <= thread_num - 1; i++){
		struct param *myparam;
		myparam = &myparams[i];
		myparam->start = myparams[i - 1].end + 1;
		myparam->end = myparams[i].start + (LEN / thread_num) - 1;
	//	printf("%d\t%d\n",myparam->start,myparam->end);
		pthread_create(&workers[i - 1],NULL,compute,&myparams[i]);
	}
	myparams[thread_num].start = myparams[thread_num - 1].end + 1;
	myparams[thread_num].end = LEN;
	pthread_create(&workers[thread_num - 1],NULL,compute,&myparams[thread_num]);

	int j;
	float sum = 0;
	for(j = 0; j < thread_num; j++){
		struct result *myresult;
		pthread_join(workers[j],(void **)&myresult);
		sum += myresult->sum;
	//	printf("the %dth pi : %f\n",j + 1,sum);
		free(myresult);
	}

	printf("pi = %f\n",sum * 4);
	return 0;
}

