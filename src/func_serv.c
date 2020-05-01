#include "func_serv.h"

void *server(void *p) {
    int *sock = (int *)p;
    char buf[BUFSIZE];
    ssize_t numRead = recv(*sock, buf, BUFSIZE, 0);
    if(numRead == -1)
        handle_error("recv");

    if(send(*sock, buf, numRead, 0) == -1)
        handle_error("send");
    close(*sock);
}

void CloseAll(int **fd, int n) {
    int i = 0;
    while(i <= n) {
        close(fd[i][1]);
        i++;
    }
}

void runServer(int fd, int n) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        handle_error("sock");
    struct sockaddr_in client_addr;
    char byte = 'H', buf[BUFSIZE];
    int size_addr = sizeof(struct sockaddr_in);
    ssize_t numRead;
    while(1) {
        if(read(fd, &client_addr, size_addr) == -1)
            handle_error("read");

        if(sendto(sock, &byte, sizeof(byte), 0, (struct sockaddr *)&client_addr, size_addr) == -1)
            handle_error("sendto");

        numRead = recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr *)&client_addr, &size_addr);
        if(numRead == -1)
            handle_error("recvfrom");

        printf("%d SERV\n", n);
        if(sendto(sock, buf, numRead, 0, (struct sockaddr *)&client_addr, size_addr) == -1)
            handle_error("sendto");
    }
    close(fd);
    close(sock);
}
