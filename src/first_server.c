#include "func_serv.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0), size_addr = sizeof(struct sockaddr_in);
    struct sockaddr_in server_addr;

    if(sock == -1)
        handle_error("socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);


    if(bind(sock, (struct sockaddr *)&server_addr, size_addr) == -1)        
        handle_error("bind");

    if(listen(sock, BACKLOG) == -1)
        handle_error("listen");

    int new_sock, i = 1;
    ssize_t numRead;
    char buf[BUFSIZE];
    while(i < 300) {
        printf("%d ", i);
        new_sock = accept(sock, NULL, 0);
        server((void *)&new_sock);
        i++;
    }

    close(sock);
    return 0;
}
