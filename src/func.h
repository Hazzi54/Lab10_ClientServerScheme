#ifndef _CLIENTSERVER_FUNC
#define _CLIENTSERVER_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SOCKNAME "/tmp/us_xfr"
#define BUFSIZE 100
#define BACKLOG 5

void handle_error(char *);
void *client();

#endif
