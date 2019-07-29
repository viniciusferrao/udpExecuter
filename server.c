/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Aloysio de Castro Pinto Pedroza
 * Sistemas Operacionais - Turma 2008/2
 * Author: Vinicius Figueiredo Ferrao 
 * Description: Main server loop
 */

#include "const.h"
#include "functions.h"

#include <stdio.h>
#include <sys/socket.h> /*socket(); bind(); connect()*/
#include <arpa/inet.h> /*sockaddr_in; inet_ntoa()*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in broadcastAddr[RANGE_OF_PORTS];
    char *broadcastIP;
    unsigned short broadcastPort;
    char *sendString;
    int broadcastPermission;
    unsigned int sendStringLen;

    /*Check command line arguments*/
    if (argc < 2 || argc > 3) {
        fprintf(stderr,"Usage: %s <IP Address> [Port]\n", argv[0]);
        exit(ERROR_INVALID_ARGS);
    }

    /*Port protection stack*/
    if (argv[2] != NULL) {
        broadcastPort = atoi(argv[2]);
        if (broadcastPort < MIN_PORT_RANGE || broadcastPort > MAX_PORT_RANGE) {
            printf("Broadcast port is out of permitted range: %i-%i.\n",MIN_PORT_RANGE,MAX_PORT_RANGE);
            exit(ERROR_OUT_OF_PORT_RANGE);
        }
    } else
        broadcastPort = DEFAULT_PORT;
    printf("Broadcasting on port: %i\n\n",broadcastPort);
    
    /*Set broadcasting network IP address*/
    broadcastIP = argv[1];
    
    /*Create socket for sending/receiving data*/
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() function failed");

    /*Set socket to broadcast*/
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
          sizeof(broadcastPermission)) < 0)
        DieWithError("setsockopt() function failed");

    /*Initialize local address structure*/
    memset(&broadcastAddr[0], 0, sizeof(broadcastAddr[0]));
    broadcastAddr[0].sin_family = AF_INET;
    broadcastAddr[0].sin_addr.s_addr = inet_addr(broadcastIP);
    broadcastAddr[0].sin_port = htons(broadcastPort);

    /*Server main loop*/
    for (;;) {	
        printf("Message to send: ");
        sendString = (char*) malloc(sizeof(char)*20);
        if (fgets(sendString,20,stdin) == NULL) {
           printf("Error getting message from standard input.\n");
           exit(ERROR_FGETS);
        }
        sendStringLen = strlen(sendString);
        sendString[sendStringLen-1]='\0'; /*Remove shitty jumpline with fgets()*/

        /*Time to send message*/
        if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr[0], sizeof(broadcastAddr[0])) != sendStringLen)
            DieWithError("sendto() sent a different number of bytes than expected");
        
        /*Wait time to avoid network flooding*/
        sleep(TIME_BETWEEN_MESSAGES);     
    }
    /*Ohh my god; I will never be here*/
}

