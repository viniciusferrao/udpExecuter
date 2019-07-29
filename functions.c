/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Aloysio de Castro Pinto Pedroza
 * Sistemas Operacionais - Turma 2008/2
 * Author: Vinicius Figueiredo Ferrao 
 * Description: Ancillary functions
 */

#include "const.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void DieWithError(char *errorMessage) {
    perror(errorMessage);
    exit(ERROR_DIE_WITH_ERROR);
}

