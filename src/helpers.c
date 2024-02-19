#include "../include/header.h"

void messageReciever(int *clientfd) {
  char buffer[256] = {0};

  struct pollfd fds[2] = {{0, POLLIN, 0}, {*clientfd, POLLIN, 0}};

  for (;;) {
    poll(fds, 2, 100);

    if (fds[0].revents & POLLIN) {
      readAndSend(*clientfd, buffer);
    } else if (fds[1].revents & POLLIN) {
      if (recv(*clientfd, buffer, 255, 0) == 0) {
        perror("Recv failed");
        exit(EXIT_FAILURE);
      }
      printf("%d: %s", *clientfd, buffer);
    }
  }
}

void readAndSend(int clientfd, char *buffer) {
  read(0, buffer, 255);
  send(clientfd, buffer, 255, 0);
  memset(buffer, 0, sizeof(*buffer));
}

void closeFds(int count, ...) {
  va_list ap;
  int i = 0;
  va_start(ap, count);

  for (i = 1; i <= count; i++) {
    close(*va_arg(ap, int *));
  }

  va_end(ap);
}
