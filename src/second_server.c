#include "func_serv.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0), size_addr = sizeof(struct sockaddr_in);
    struct sockaddr_in server_addr;

    if(sock == -1)
        handle_error("socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);


    if(bind(sock, (struct sockaddr *) &server_addr, size_addr) == -1)        
        handle_error("bind");

    if(listen(sock, BACKLOG) == -1)
        handle_error("listen");

    int i = 0, cash = NUM_THREADS;
    int *mas_sock = (int *)malloc(sizeof(int) * cash);
    pthread_t *id = (pthread_t *)malloc(sizeof(pthread_t) * cash);
    while(1) {
        if(i >= cash) {
            cash += NUM_THREADS;
            id = (pthread_t *)realloc(id, sizeof(pthread_t) * cash);
            mas_sock = (int *)realloc(mas_sock, sizeof(int) * cash);
        }
        mas_sock[i] = accept(sock, NULL, 0);
        printf("Accepted %d\n", i);
        pthread_create(&id[i], NULL, server, (void *)&mas_sock[i]);
        i++;
    }

    i = 0;
    while(i < NUM_THREADS) {
        pthread_join(id[i], NULL);
        i++;
    }

    close(sock);
    return 0;
}
