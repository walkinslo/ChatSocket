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
    int serverfd, new_sock;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    char buffer[256] = {0};

    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("No ports available");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0;
    address.sin_port = htons(PORT);

    if (bind(serverfd, (struct sockaddr *)&address, sizeof(address))) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("%d", serverfd);

    if (listen(serverfd, 10)) {
        perror("Too many connections");
        exit(EXIT_FAILURE);
    }

    if ((new_sock = accept(serverfd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("Couldn't accept the request");
        exit(EXIT_FAILURE);
    }

    struct pollfd fds[2] = {
        {
            0,
            POLLIN,
            0
        },
        {
            new_sock,
            POLLIN,
            0
        }
    };

    for (;;) {
        poll(fds, 2, 50000);

        if (fds[0].revents & POLLIN) {
            read(0, buffer, 255);
            send(new_sock, buffer, 255, 0);
            memset(buffer, 0, sizeof(buffer));
        } else if (fds[1].revents & POLLIN) {
            if (recv(new_sock, buffer, 255, 0) == 0) {
                exit(EXIT_FAILURE);
            }

            printf("[%d]: %s\n", new_sock, buffer);
        }
    }

    close(new_sock);
    close(serverfd);
    return 0;
}
