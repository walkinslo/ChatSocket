#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>


#include <stdio.h>


#define PORT 6969

int main() {
    int clientfd, flag;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    char buffer[256] = {0};

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0;
    address.sin_port = htons(PORT);

    if ((flag = connect(clientfd, (struct sockaddr *)&address, sizeof(address))) <= 0) {
        printf("%d", clientfd);
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    struct pollfd fds[2] = {
        {
            0,
            POLLIN,
            0
        },
        {
            clientfd,
            POLLIN,
            0
        }
    };

    for (;;) {
        poll(fds, 2, 50000);

        if (fds[0].revents & POLLIN) {
            read(0, buffer, 255);
            send(clientfd, buffer, 255, 0);
            memset(buffer, 0, sizeof(buffer));
        } else if (fds[1].revents & POLLIN) {
            if (recv(clientfd, buffer, 255, 0) == 0) {
                exit(EXIT_FAILURE);
            }

            printf("[%d]: %s\n", clientfd, buffer);
        }
    }

    close(clientfd);
    return 0;
}
