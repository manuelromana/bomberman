#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>

int load_server(int *my_socket, char *hostname, char *portname);
int create_track_client(int *my_socket, int max_client, int clients_array[]);
int load_client(int *mysocket, char *hostname, char *portname);
int read_client(int client);

#endif