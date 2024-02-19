CC = gcc-13
BUILD = ./build
SRC = ./src
HEADERS = ./include
CFLAGS = -Wall -Werror -Wextra -std=c11

.PHONY = all rebuild clean

SRC_SERVER = $(SRC)/server.c
SRC_CLIENT = $(SRC)/client.c
SRC_HELPERS = $(SRC)/helpers.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_HELPERS = $(SRC_HELPERS:.c=.o)

HEADER = $(HEADERS)/header.h

all: client server

client: $(OBJ_CLIENT) $(OBJ_HELPERS)
	$(CC) $^ -o $(BUILD)/client

server: $(OBJ_SERVER) $(OBJ_HELPERS)
	$(CC) $^ -o $(BUILD)/server

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(SRC)/*.o
	rm $(BUILD)/*

rebuild: clean all
