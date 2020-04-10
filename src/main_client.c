#include "func_client.h"

int main(int argc, char *argv[]) {
    pthread_t id[NUM_THREADS];
    int i = 0;
    while(i < NUM_THREADS) {
        pthread_create(&id[i], NULL, client, NULL);
        i++;
    }
    
    i = 0;
    while(i < NUM_THREADS) {
        pthread_join(id[i], NULL);
        i++;
    }
    return 0;
}
