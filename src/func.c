#include "func.h"

void handle_error(char *mess) {
    perror(mess);
    exit(EXIT_FAILURE);
}
