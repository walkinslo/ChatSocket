#ifndef __HEADER_H__
#define __HEADER_H__

/* Порт, который открывает сервер, и по которому общается клиент
* TODO:
* - сделать изменяемым при запуске сервера и клиента.
*/
#define PORT 9999

#include <arpa/inet.h>

/* Заголовочный файл, которыцй нужен для setsockopt на macos */
#ifdef __APPLE_CC__
#include <netinet/in.h>
#endif

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* для memset (обнуление буфера) */
#include <sys/socket.h>
#include <unistd.h>
#include <stdarg.h>

/* Вспомогательные функции */
void messageReciever(int *clientfd);
void readAndSend(int clientfd, char *buffer);
void closeFds(int count, ...);

/* Функции сервера */
void setupServer(int *clientfd, int *serverfd);

/* Функции клиента */
void setupClient(int *clientfd);

#endif
