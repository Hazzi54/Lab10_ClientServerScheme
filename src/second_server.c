#include "func_serv.h"

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
