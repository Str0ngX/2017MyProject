#include <errno.h>
#include <stdarg.h>

#include "ourhdr.h"

static void err_doit(int, const char *, va_list);
char *pname = NULL;

void err_ret(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	return ;
}

void err_sys(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	exit(1);
}

void err_quit(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end(ap);
	exit(1);
}

void err_dump(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	abort(); /* dump core and terminate */                                                                  
	exit(1); /* should not get here */
}


static void err_doit(int errnoflag, const char *fmt, va_list ap) {
	int errno_save;
	char buf[MAXLINE];

	errno_save = errno;
	vsprintf(buf, fmt, ap);
	if(errnoflag) {
		sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
	}
	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
	return;
}

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define PATH_MAX_GUESS 1024 /* If PATH_MAX if indeterminate we're not guaranteed this is adequate */
char *path_alloc(int *size) {
	/* alse return allocated size, if nonnull */
	char *ptr;
	if(pathmax == 0) {
		/* first time through */
		errno = 0;
		if( (pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
			if(errno == 0) {
				pathmax = PATH_MAX_GUESS; /* it's indeterminate */
			}
			else {
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		}
		else {
			pathmax++; /* add one since it's relative to root */
		}
	}
	if( (ptr = malloc(pathmax + 1)) == NULL) {
		err_sys("malloc error for pathname");
	}

	if(size != NULL) {
		*size = pathmax + 1;
	}
	return (ptr);
}

