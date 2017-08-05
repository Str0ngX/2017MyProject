#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[])
{
	while(1)
	{
		printf("MyShell$>>");
		char command[256][256] = {{'\0'}};
		char cmd[1024];
		gets(&cmd);
		//printf("%s\n%d\n",cmd,strlen(cmd)+1);
		//int len = 0;
		//len = strlen(cmd);
		int i = 0;
		int k = 0;
		int j = 0;
		for(i = 0;cmd[i]!='\0';i++)
		{
			if(cmd[i]==' '||cmd[i]=='\0')
			{
				command[j][k] = '\0';
			//	printf("%s\n",command[j]);
				j++;
				k = 0;
			}
			else
			{
				command[j][k] = cmd[i];
				k++;
			}
			if(cmd[i]=='\0')
			{
				j++;
				command[j][0] = '\0';
				k = 0;
			}
		}
		if(strcmp(command[0],"echo")==0)
		{
			printf("%s",command[1]);

		//	for(i = 5+strlen(command[1]);cmd[i]!='\0';i++)
		//		puts(cmd[i]);
			char *p = cmd[5];
			puts(*p);
		}
	/*	int xi = 0;
		while(command[xi][0]!='\0')
		{
			printf("%s ",command[i]);
			xi++;
		}
	*/
	/*	if(strcmp(command[0],"echo")==0)
		{	
			int i = 1;
			while(command[i][0]!='\0')
			{
				printf("%s ",command[i]);
				i++;
			}
			for(i = 4;cmd[i]!='\0';i++)
			{
				printf("%s",cmd[i]);
			}
		}
	*/
	}
	return 0;
}
