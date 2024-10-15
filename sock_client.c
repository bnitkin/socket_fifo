#include "common.h"

char data[256];
void main() {
    printf("Hello from client\n");

    // Create socket
    int rx_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (rx_sock < 0) {
        perror("socket");
        return;
    }

    int optval = 1;
    if (setsockopt(rx_sock, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval))) {
        perror("setsockopt reuseport");
        return;
    }

    // Assign receive port
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_BROADCAST;
    int status = bind(rx_sock, (struct sockaddr*) &addr, sizeof(addr));

    while (1) {
        // Read from pipe
        int size = recv(rx_sock, data, sizeof(data), 0);
        if (size) {
            data[size] = '\0';
            printf("%s", data);
            fflush(stdout);
        } else {
            perror("recvfrom");
        }
    }
}
