/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Aloysio de Castro Pinto Pedroza
 * Sistemas Operacionais - Turma 2008/2
 * Author: Vinicius Figueiredo Ferrao 
 * Description: Main client
 */

#include "const.h"
#include "functions.h"

#include <stdio.h>
#include <sys/socket.h> /*socket(); connect(); send(); recv()*/
#include <arpa/inet.h> /*sockaddr_in; inet_addr()*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in broadcastAddr;
    unsigned short broadcastPort;
    char recvString[MAXRECVSTRING+1];
    int recvStringLen;

    /*Check command line arguments*/
    if (argc > 2) {
        fprintf(stderr,"Usage: %s <Broadcast Port>\n", argv[0]);
        exit(ERROR_INVALID_ARGS);
    }

    /*Port protection stack*/
    if (argv[1] != NULL) {
        broadcastPort = atoi(argv[1]);
        if (broadcastPort < MIN_PORT_RANGE || broadcastPort > MAX_PORT_RANGE) {
            printf("Listen port is out of permitted range: %i-%i.\n",MIN_PORT_RANGE,MAX_PORT_RANGE);
            exit(ERROR_OUT_OF_PORT_RANGE);
        }
    } else
        broadcastPort = DEFAULT_PORT;
    printf("Listening on port: %i\n\n",broadcastPort);    
    
    /*Client receive loop*/
    for (;;) {

        /*Create a UDP socket*/
        if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
            DieWithError("socket() function failed");

        /*Construct bind structure*/
        memset(&broadcastAddr, 0, sizeof(broadcastAddr));
        broadcastAddr.sin_family = AF_INET;
        broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        broadcastAddr.sin_port = htons(broadcastPort);

        /*Bind to the broadcast port*/
        if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
            DieWithError("bind() function failed");

        /*Receive a single datagram from the server*/
        if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
            DieWithError("recvfrom() function failed");

        recvString[recvStringLen] = '\0';
        printf("Received: %s\n", recvString);
        
        /*Code executions*/
        if (strcmp(recvString,"killclients") == 0) {
            printf("Terminate signal received!\n");
            exit(OK);
        }
        
        if (strcmp(recvString,"reboot") == 0) {
            printf("Reboot signal received!\n");
            printf("Sending all know reboot commands to Operational System\n");
            if (system("sudo reboot") != 0)
                printf("System Call has failed!\n");
            if (system("devcon reboot") != 0)
                printf("System Call has failed!\n");
            if (system("rundll32 shell32.dll,SHExitWindowsEx 2") != 0)
                printf("System Call has failed!\n");
            exit(OK);
        }
        
        if (strcmp(recvString,"poweroff") == 0) {
            printf("Poweroff signal received!\n");
            printf("Sending all know poweroff commands to Operational System\n");
            if (system("sudo poweroff") != 0)
                printf("System Call has failed!\n");
            if (system("sudo shutdown -p now") != 0)
                printf("System Call has failed!\n");
            if (system("devcon poweroff") != 0)
                printf("System Call has failed!\n");
            if (system("rundll32 shell32.dll,SHExitWindowsEx 8") != 0)
                printf("System Call has failed!\n");
            exit(OK);
        }

        close(sock);
    }
    /*Ohh my god; I will never be here*/
}

