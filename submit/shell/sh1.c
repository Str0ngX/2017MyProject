#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define LEN 256
#define WIDTH 256
#define HEIGHT 10

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

int main(int argc,char *argv[])
{
	char command[LEN];
	while(1){
		printf("%s",">>");
		fgets(command,256,stdin);
		command[strlen(command)-1] = '\0';
		if(fork()==0){
			mysys(command);
		}
		else{
			wait(NULL);
		}
	}
	return 0;
}
