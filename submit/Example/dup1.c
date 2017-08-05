#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int fd;
	fd = open("log.txt",O_CREAT | O_RDWR,0666);
	write(fd,"Hello",6);
	close(fd);
	return 0;
}

