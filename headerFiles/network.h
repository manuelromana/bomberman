#ifndef NETWORK_H
#define NETWORK_H

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>

#define MAXCLIENT 4
#define ARRAYSIZE 32

typedef struct stInfos {
    char choix[ARRAYSIZE];
    char hostname[ARRAYSIZE];
    char portname[ARRAYSIZE];
    int clients_array[MAXCLIENT];
    char *current_text;
    int *my_socket;
} stInfos;

typedef struct stTrackClient {
    int max_sd;
    int new_socket;
    int sd;
} stTrackClient;

int read_client(int client);
int read_server(int server);
int load_server(int *my_socket, char *hostname, char *portname);
int load_client(int *mysocket, char *hostname, char *portname);
void send_key(SDL_Keycode keydown, int mysocket);

void track_client(int *server_socket);
int create_track_client(int *my_socket, int clients_array[]);
int read_client(int client);

void send_key(SDL_Keycode keydown, int mysocket);

void control_event(SDL_Event event, int *step, char **currentText, char *hostname, char *port, int mysocket);
#endif