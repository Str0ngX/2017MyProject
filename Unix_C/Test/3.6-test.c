#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
	int fd;
	char buf[] = "00000";
	char buf2[100];
	fd = open("a.txt", O_RDWR, 0777);
	if(lseek(fd, 5, SEEK_SET) == -1) {
		printf("error set\n");
	}
	if(write(fd, buf, 5) != 5) {
		printf("error write\n");
	}

	lseek(fd, 0, SEEK_SET);
	if(read(fd, buf2, 100) != -1) {
		printf("%s\n", buf2);
	}
	close(fd);
	return 0;
}
