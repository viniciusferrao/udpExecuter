/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Aloysio de Castro Pinto Pedroza
 * Sistemas Operacionais - Turma 2008/2
 * Author: Vinicius Figueiredo Ferrao 
 * Description: Default constants header
 */

#ifndef _CONST_
#define _CONST_

    /*Errorlevel*/
	#define OK 0
	#define ERROR_INVALID_ARGS -1
	#define ERROR_OUT_OF_PORT_RANGE -2
	#define ERROR_FGETS -3
	#define ERROR_DIE_WITH_ERROR -255
	
	/*Port related*/
	#define DEFAULT_PORT 2891
	#define MIN_PORT_RANGE 1024 /*Start port range for UDP socket*/
	#define MAX_PORT_RANGE 65535 /*End port range for UDP socket*/
	#define RANGE_OF_PORTS 1 /*Range of continous ports to broadcast*/

    /*Sockets related*/
    #define RCVBUFSIZE 32 /*Maximum receive buffer*/
	#define MAXRECVSTRING 255  /*Maximum string length to receive*/
	
	/*Messaging related*/
	#define TIME_BETWEEN_MESSAGES 3

#endif

