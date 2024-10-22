#include "common.h"

char data[][20] = {"the train goes ", "chugga ", "choo ", "\b!!\n"};

void main() {
    printf("Hello from server\n");

    // Create socket
    int tx_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (tx_sock < 0) {
        perror("socket");
        return;
    }

    int optval = 1;
    if (setsockopt(tx_sock, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval))) {
        perror("setsockopt reuseport");
        return;
    }
    if (setsockopt(tx_sock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval))) {
        perror("setsockopt broadcast");
        return;
    }

    // Build broadcast address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton("127.255.255.255", &addr.sin_addr.s_addr);
    int status = bind(tx_sock, (struct sockaddr*) &addr, sizeof(addr));

    int i = 0;
    char* str;
    while (1) {
        usleep(50000);
        // Generate some text.
        i++;
        if (i == 1) {
            usleep(150000);
            printf("Server says: ");
            str = data[0];
        }
        else if (i<9) str = data[1];
        else if (i<11) str = data[2];
        else if (i<12) {
            str = data[3];
            i = 0;
        }

        // Print for sanity.
        printf("%s", str);
        fflush(stdout);

        // Send over socket.
        if(sendto(tx_sock, str, strlen(str), 0,
                  (struct sockaddr *) &addr, sizeof(addr)) < 0) {
            perror("sendto");
            return;
        }
    }
}
