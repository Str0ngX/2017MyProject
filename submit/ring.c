#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 2
int count = 0;
pthread_t workers[N + 1];
pthread_t init_id;
int finalData;

struct param
{
	int data;
};

void *addmm(void *arg)
{
	count++;
	sleep(1);
	struct param *param = (struct param *)arg;
	pthread_t id;
	printf(":");
	printf("%d",param->data);
	printf("\n");

	if(count < N){
		param->data++;
		pthread_create(&id,NULL,addmm,param);
		pthread_join(id,NULL);
		return NULL;
	}
	else{
		param->data++;
		finalData = param->data;
		return NULL;
	}
}

int main(int argc,char *argv[])
{
	struct param mparam;
	mparam.data = 1;
	struct result *result;
	while(1){
		pthread_create(&init_id,NULL,addmm,&mparam);
		pthread_join(init_id,(void **)&result);
		mparam.data = finalData;
	}
	return 0;
}


