#include "func_serv.h"

int main(int argc, char *argv[]) {
    int i = 0, **fd = (int **)malloc(SERVERS * sizeof(int *));
    pid_t parent = getpid(), child_pid[SERVERS];
    while(i < SERVERS) {                     // creation of processes
        fd[i] = (int *)malloc(2 * sizeof(int));
        pipe(fd[i]);
        child_pid[i] = fork();
        if(child_pid[i] != 0) {
            close(fd[i][0]);
        }
        else {
            CloseAll(fd, i);  // close all previous descriptors
            runServer(fd[i][0], i + 1);
            exit(EXIT_SUCCESS);
        }
        i++;
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0), size_addr = sizeof(struct sockaddr_in);
    struct sockaddr_in server_addr, last_addr;

    if(sock == -1)
        handle_error("socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);


    if(bind(sock, (struct sockaddr *) &server_addr, size_addr) == -1)        
        handle_error("bind");


    i = 0;
    int j = 0, cash = SERVERS;
    char byte;
    struct sockaddr_in *client_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in) * cash);
    while(1) {
        if(i >= cash) {
            cash += SERVERS;
            client_addr = (struct sockaddr_in *)realloc(client_addr, sizeof(struct sockaddr_in) * cash);
        }

        if(recvfrom(sock, &byte, sizeof(byte), 0, (struct sockaddr *)&client_addr[i], &size_addr) == -1)
            handle_error("recvfrom");
        printf("Accepted %d\n", i);

        if(write(fd[j][1], &client_addr[i], size_addr) == -1)
            handle_error("write");
        
        i++;
        j++;
        if(j == SERVERS)
            j = 0;
    }
    close(sock);
    CloseAll(fd, SERVERS - 1);
    free(fd);
    free(client_addr);

    i = 0;
    while(i < SERVERS) {
        waitpid(child_pid[i], NULL, 0);
        i++;
    }
    return 0;
}
