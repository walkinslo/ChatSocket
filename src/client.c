#include "../include/header.h"

int main() {
  int clientfd;

  setupClient(&clientfd);
  messageReciever(&clientfd);
  closeFds(1, &clientfd);

  return 0;
}

void setupClient(int *clientfd) {
  struct sockaddr_in address;

  if ((*clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = 0;
  address.sin_port = htons(PORT);

  if (connect(*clientfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }
}
