#include "func_serv.h"

void *server(void *p) {
    int *tmp = (int *)p;
    int sock = *tmp;
    char buf[BUFSIZE];
    ssize_t numRead = recv(sock, buf, BUFSIZE, 0);
    if(numRead == -1)
        handle_error("recv");
    puts(buf);
    if(send(sock, buf, numRead, 0) == -1)
        handle_error("send");
    close(sock);
}
