#include <stdio.h>
#include <unistd.h>

int global = 0;

void child()
{	
	int i;
	for(i = 0;i < 3;i++){
		global++;
		printf("In Child,global = %d\n",global);
		sleep(1);
	}
}

void parent()
{
	int i;
	for(i = 0; i < 3; i++){
		global++;
		printf("In Parent,global = %d\n",global);
		sleep(1);
	}
}

int main(int argc,char *argv[])
{
	pid_t pid;
	pid = fork();
	if(pid == 0){
		child();
	}
	else
	{
		parent();
	}
	return 0;
}
