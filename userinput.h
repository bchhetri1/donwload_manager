#pragma once
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

extern int custom;
extern int notGui;

void storeCustomDestinations(char* line);

void loadURL(char* line);

int checkHeading(char* line, int* category);

int setOptions();

void initialize();

void saveToConfigFile(char* url, char* dir);

void initializeSocket();

char* getDirectoryFromUrl(char* url);

void callDaemonToDownload(char* url, char* dir, char* time); 

void update();

//void download(char* fileURL);
//int main(){}
void downloadFromFile(char* fileName);

void cleanLine(char* line);

void run_program(char* flag, char* argument);

void print_help();

void err_opening_config_file();

void err_file_not_found();

void err_downloading_from_url();
