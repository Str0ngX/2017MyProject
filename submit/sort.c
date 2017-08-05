#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LEN 10

int array[LEN] = {0,3,8,6,2,9,7,5,1,4};

struct param{
	int *arr;
};

void *sort(void *arg)
{
	struct param *mypara;
	mypara = (struct param *)arg;
	int i = 0;
	int j = 0;
	int min = 0;
	int temp = 0;
	for(i = LEN / 2; i < LEN - 1; i++){
		min = i;
		for(j = i; j < LEN; j++){
			if(mypara->arr[min] > mypara->arr[j]){
				min = j;
			}

		}
		temp = mypara->arr[min];
		mypara->arr[min] = mypara->arr[i];
		mypara->arr[i] = temp;
	}
}

void merge(){
	int i = 0;
	int a[LEN / 2];
	int b[LEN / 2];
	for(i = 0; i < LEN / 2; i++){
		a[i] = array[i];
		b[i] = array[i + LEN / 2];
	}

	int tm = 0;
	int ti = 0;
	int tj = 0;

	while(ti < LEN / 2 && tj < LEN / 2){
		if(a[ti] < b[tj]){
			array[tm] = a[ti];
			ti++;
		}
		else{
			array[tm] = b[tj];
			tj++;
		}
		tm++;
	}
}

int main(int argc,char *argv[])
{
	struct param param;
	param.arr = array;
	int ti = 0;
	int tj = 0;
	int tmin = 0;

	for(ti = 0; ti < LEN / 2; ti++){
		tmin = ti;
		for(tj = ti; tj < LEN / 2; tj++){
			if(array[tmin] > array[tj]){
				tmin = tj;
			}
		}
		int temp = array[tmin];
		array[tmin] = array[ti];
		array[ti] = temp;
	}
	pthread_t worker_tid;
	pthread_create(&worker_tid,NULL,&sort,&param);
	pthread_join(worker_tid,NULL);
	merge();
	int i = 0;
	for(i = 0; i < LEN; i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	return 0;
}

	


