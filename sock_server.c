#include <string.h>
#include "common.h"

char train[][20] = {"the train goes ", "chugga ", "choo ", "\b!!\n"};

void main() {
    printf("Hello from server\n");

    // Create socket
    int bcast_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (bcast_sock < 0) {
        perror("socket");
        return;
    }
    int optval=1;
    if (setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval))) {
        perror("setsockopt");
        return;
    }

    // Build broadcast address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_BROADCAST;

    int i = 0;
    char* str;
    while (1) {
        usleep(50000);
        // Generate some text.
        i++;
        if (i == 1) {
            printf("Server says: ");
            str = train[0];
        }
        else if (i<9) str = train[1];
        else if (i<11) str = train[2];
        else if (i<12) {
            str = train[3];
            i = 0;
        }

        // Print for sanity.
        printf("%s", str);
        fflush(stdout);

        // Send over socket.
        if(sendto(bcast_sock, str, strlen(str), 0,
                  (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            perror("sendto");
            return;
        }
    }
}
