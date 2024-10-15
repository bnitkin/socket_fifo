#include <string.h>
#include "common.h"

char train[][10] = {"chugga ", "choo ", "\b!!\n"};

void main() {
    printf("Hello from server\n");

    init();
    int fd = open(FIFO, O_WRONLY);
    char* str;

    int i = 0;
    while (1) {
        usleep(100000);
        // Generate some text.
        i++;
        if (i<9) str = train[0];
        else if (i<11) str = train[1];
        else if (i<12) {
            str = train[2];
            i = 0;
        }

        // Print for sanity.
        printf("%s", str);
        fflush(stdout);

        // Send over pipe.
        write(fd, str, strlen(str)+1);
    }
}
