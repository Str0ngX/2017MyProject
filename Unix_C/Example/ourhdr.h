/* Our own header, to be include *after* all standard system headers */
#ifndef __ourhdr_h
#define __ourhdr_h
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 4096

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int);

#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *) - 1)
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

char *path_alloc(int *); // 2.2

char open_max(void); //2.3



void err_quit(const char *, ...);
void err_sys(const char *, ...);
void err_dump(const char *, ...);
void err_ret(const char *, ...);





#endif /* __ourhdr_h */
