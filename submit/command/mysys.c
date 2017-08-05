#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
// mysys.c
int mysys(const char* cmdstr)
{
	pid_t pid;
	int status;
	if(cmdstr == NULL){
		return 1;
	}
	pid = fork();
	if(pid == 0){
		execl("/bin/sh", "sh", "-c", cmdstr, (char*)0);
		exit(127);
	}
	else{
		wait(&status);
	}
	return status;
}

int main()
{
	printf("---------------------------\n");
	mysys("echo HELLO WORLD");
	printf("---------------------------\n");
	mysys("ls /");
	printf("---------------------------\n");
	return 0;
}

