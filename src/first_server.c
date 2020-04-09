#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0), size_addr = sizeof(struct sockaddr_un);
    if(sock == -1)
        handle_error("socket");

    if(remove(SOCKNAME) == -1 && errno != ENOENT)
        handle_error("remove");
    
    struct sockaddr_un my_addr;
    memset(&my_addr, 0, size_addr);
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, SOCKNAME, sizeof(my_addr.sun_path));

    if(bind(sock, (struct sockaddr *) &my_addr, size_addr) == -1)        
        handle_error("bind");

    if(listen(sock, BACKLOG) == -1)
        handle_error("listen");

    ssize_t numRead;
    int new_sock;
    char buf[BUFSIZE];
    while(1) {
        new_sock = accept(sock, NULL, 0);
        numRead = recv(new_sock, buf, BUFSIZE, 0);
        if(numRead == -1)
            handle_error("recv");
        puts(buf);
        if(send(new_sock, buf, numRead, 0) == -1)
            handle_error("send");
        close(new_sock);
    }

    close(sock);
    return 0;
}
