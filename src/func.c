#include "func.h"

void handle_error(char *mess) {
    perror(mess);
    exit(EXIT_FAILURE);
}

int k = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *client() {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock == -1)
        handle_error("socket");

    struct sockaddr_un my_addr;
    int size_addr = sizeof(struct sockaddr_un);
    
    memset(&my_addr, 0, size_addr);
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, SOCKNAME, sizeof(my_addr.sun_path) - 1);

    if(connect(sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_un)) == -1)
        handle_error("connect");

    char buf[BUFSIZE] = "HERE\n";
    int numRead = strlen(buf);
    //numRead = read(STDIN_FILENO, buf, BUFSIZE);
    if(send(sock, buf, numRead, 0) == -1)
        handle_error("send");

    if(recv(sock, buf, BUFSIZE, 0) == -1)
        handle_error("recv");
    
    pthread_mutex_lock(&mut);
    printf("%d %s\n", k, buf);
    k++;
    pthread_mutex_unlock(&mut);
    close(sock);
}
