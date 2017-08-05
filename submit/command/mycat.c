#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc,char *argv[])
{
	int fread = open(argv[1],O_RDONLY);
	char print;
	while(read(fread,&print,1)){
		fprintf(stdout,&print,1);
	}
	fprintf(stdout,"\n");
	return 0;
}
