#include "common.h"

char data[256];
void main() {
    printf("Hello from client\n");

    mkfifo(FIFO, 0666);
    int fd = open(FIFO, O_RDONLY);

    while (1) {
        // Read from pipe
        if (read(fd, data, sizeof(data)))
            printf("%s", data);
        fflush(stdout);
    }
}
