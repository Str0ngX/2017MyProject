#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024
#define M 256
int main(int argc,char *argv[])
{
	char cmd[N];
	char command[M][M] = {{'\0'}};
	int i = 0;
	int j = 0;
	int k = 0;
	gets(&cmd);
	puts(cmd);
	for(i = 0;cmd[i]!='\0';i++)
	{
		command[j][k]=cmd[i];
		k++;
		if(cmd[i]==' ')
		{
			command[j][k] = '\0';
			k = 0;
			j++;
		}
	}
	for(i = 0;i <= j;i++)
	{
		puts(command[i]);
	}
	return 0;
}
