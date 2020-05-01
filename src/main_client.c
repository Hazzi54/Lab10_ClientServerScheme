#include "func_client.h"

int main(int argc, char *argv[]) {
    pthread_t id[NUM_THREADS];
    int i;
    i = 0;
    if(strcmp(argv[1], "-tcp") == 0) {
        while(i < NUM_THREADS) {
            pthread_create(&id[i], NULL, client_tcp, NULL);
            i++;
        }
    }
    else if(strcmp(argv[1], "-udp") == 0) {
        while(i < NUM_THREADS) {
            pthread_create(&id[i], NULL, client_udp, NULL);
            i++;
        }
    }
    i = 0;
    while(i < NUM_THREADS) {
        pthread_join(id[i], NULL);
        i++;
    }
    return 0;
}
