#include "func_client.h"

int k = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *client_udp() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0), size_addr = sizeof(struct sockaddr_in);
    struct sockaddr_in server_addr, new_server_addr;

    if(sock == -1)
        handle_error("socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    char buf[BUFSIZE] = "MESSAGE", buf2[BUFSIZE], byte = 'H';

    if(sendto(sock, &byte, sizeof(byte), 0, (struct sockaddr *)&server_addr, size_addr) == -1)
        handle_error("sendto");

    if(recvfrom(sock, &byte, sizeof(byte), 0, (struct sockaddr *)&new_server_addr, &size_addr) == -1)
        handle_error("recvfrom");

    if(sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&new_server_addr, size_addr) == -1)
        handle_error("sendto");

    if(recvfrom(sock, buf2, BUFSIZE, 0, (struct sockaddr *)&new_server_addr, &size_addr) == -1)
        handle_error("recvfrom");
    
    pthread_mutex_lock(&mut);
    printf("%d %s\n", k, buf2);
    k++;
    pthread_mutex_unlock(&mut);
    close(sock);
}

void *client_tcp(void *ptr) {
    int sock = socket(AF_INET, SOCK_STREAM, 0), size_addr = sizeof(struct sockaddr_in);
    struct sockaddr_in server_addr;

    if(sock == -1)
        handle_error("socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    if(connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1)
        handle_error("connect");

    char buf[BUFSIZE] = "MESSAGE", buf2[BUFSIZE], byte = 'H';

    if(send(sock, &byte, sizeof(byte), 0) == -1)
        handle_error("send");

    if(send(sock, buf, sizeof(buf), 0) == -1)
        handle_error("send");

    if(recv(sock, buf2, sizeof(buf2), 0) == -1)
        handle_error("recv");
    
    pthread_mutex_lock(&mut);
    printf("%d %s\n", k, buf2);
    k++;
    pthread_mutex_unlock(&mut);
    close(sock);
}
