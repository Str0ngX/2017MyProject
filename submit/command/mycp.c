#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
	int fread=open(argv[1], O_RDONLY);
	int fwrite=creat(argv[2],0666);
	char cread;
	while(read(fread, &cread,1)){
		write(fwrite, &cread, 1);
	}
	return 0;
}

