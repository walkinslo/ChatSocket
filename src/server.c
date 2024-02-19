#include "../include/header.h"

int main() {

  int clientfd, serverfd;
  setupServer(&clientfd, &serverfd);
  messageReciever(&clientfd);

  closeFds(2, &clientfd, &serverfd);
  return 0;
}

void setupServer(int *clientfd, int *serverfd) {
  struct sockaddr_in address;
  int opt = 1;
  socklen_t addrlen = sizeof(address);

  if ((*serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(*serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, addrlen)) {
    perror("Socket options");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = 0;

  if (bind(*serverfd, (struct sockaddr *)&address, addrlen) < 0) {
    perror("Bind failed");
    exit(1);
  }

  if (listen(*serverfd, 5)) {
    perror("Too many connections");
    exit(EXIT_FAILURE);
  }

  if ((*clientfd = accept(*serverfd, (struct sockaddr *)&address, &addrlen)) <
      0) {
    perror("Accept failed");
    exit(EXIT_FAILURE);
  }
}
