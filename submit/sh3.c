#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
int screen=0;
int keyboard=0;
int _echo(char param[][10], int n)
{
	int i=0;
	for(i=0;i<n;i++){
		printf("%s ",param[i]);
	}
	printf("\n");
	return 0;
}
int _ls(char param[][10],int n)
{
	DIR *dirptr;
	char curdir[20];
	if(n==0){
		getcwd(curdir,20);
		dirptr=opendir(curdir);
	}
	else{
		dirptr=opendir(param[0]);
	}
	struct dirent* ptr;
	while((ptr=readdir(dirptr))!=NULL){
		if(ptr->d_name[0] != '.'){		
			printf("%s\t",ptr->d_name);
		}
	}
	printf("\n");
	closedir(dirptr);
	return 0;
}
int _cd(char param[][10],int n)
{
	char cont[30];
	chdir(param[0]);
	getcwd(cont,30);
	printf("Switch to : %s\n",cont);
	return 0;
}
int _pwd(char param[][10],int n)
{
	char cont[30];
	getcwd(cont,30);
	printf("Corrent Workspace : %s\n",cont);
	return 0;
}
int _newexit(char param[][10],int n)
{
	exit(0);
	return 0;
}
int _cat(char param[][10],int n)
{
	int fread=open(param[0],O_RDONLY);
	char buff;
	while(read(fread, &buff, 1)){
		printf("%c",buff);
	}
	return 0;
}
int main()
{
	char toexce[6][5]={"echo", "ls", "cd", "pwd", "exit", "cat"};
	int fd[2];
	pipe(fd);
	while(1){
		char paramlist[10][10];
		char content[30];
		char relin[10]={0};
		char relout[10]={0};
		int i,j,k;
		int infd,outfd;
		int flag=0;
		int deli;
		pid_t pid;
		int status;
		int cmdstart,cmdend;

		printf("Shell Version 0.1 . ");
		printf("Current Content: ");
		getcwd(content,30);
		puts(content);	

		char cmdstr[100];
		fgets(cmdstr,100,stdin);
		cmdstr[strlen(cmdstr)-1]=0;
		for(k=0;k<strlen(cmdstr);k++){
			if(cmdstr[k]=='|'){
				flag=1;
				deli=k;
				break;
			}			
		}

		if(flag==1){
			pid=fork();
			if(pid==0){
				cmdstart=0;
				cmdend=deli;
			}	
			else{
				wait(&status);
				cmdstart=deli+1;
				cmdend=strlen(cmdstr);
			}
		}
		else{
			cmdstart=0;
			cmdend=strlen(cmdstr);
		}
		for(k=cmdstart;k<cmdend;k++){
			if(cmdstr[k]=='<'){
			strcpy(relin, cmdstr+k+1);
			break;
			}
		}		
		if(relin[0]!=0){
			infd=open(relin, O_RDONLY);
			dup2(0, keyboard);
			dup2(infd, 0);
		}

		for(k=cmdstart;k<cmdend;k++){
			if(cmdstr[k]=='>'){
				strcpy(relout, cmdstr+k+1);
				break;
			}
		}
		if(relout[0]!=0){
			outfd=open(relout, O_CREAT|O_RDWR, 0666);	
			dup2(1, screen);
			dup2(outfd, 1);
		}
		char execmd[10];
		char* param;
		param=strtok(cmdstr+cmdstart, " ");
		strcpy(execmd, param);

		j=0;
		while((param=strtok(NULL, " "))){
			if(param[0]=='<'||param[0]=='>'){
				continue;
			}
			if(param[0]=='|'){
				break;
			}
			strcpy(paramlist[j++], param);
		}
		for(i=0; i<6; i++){
			if(strcmp(execmd, toexce[i])==0){
				break;
			}
		}
		switch(i){
			case 0: _echo(paramlist,j); dup2(screen, 1); break;
			case 1: _ls(paramlist,j); dup2(screen, 1); break;
			case 2: _cd(paramlist,j); break;
			case 3: _pwd(paramlist,j); break;
			case 4: _newexit(paramlist,j); break;
			case 5: _cat(paramlist,j); dup2(screen, 1); break;
			default: break;
		}

		if(pid==0){
			exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

