# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# Prof. Aloysio de Castro Pinto Pedroza
# Sistemas Operacionais - Turma 2008/2
# Author: Vinícius Figueiredo Ferrão
# Description: Default Makefile

CC = gcc #Compiler
LD = gcc #Link-editor

CFLAGS = -march=prescott -O2 -pipe -Wall -c
LFLAGS = -Wl,-O1 -Wall -o

# Executables
EXECS = server client

# Objects
OBJSERVER = server.o functions.o
OBJCLIENT = client.o functions.o

# Librarys
#LIBNCURSES = -lncurses
#LIBCRYPT = -lcrypt

# Rules
.c.o:
	$(CC) $(CFLAGS) $<

all: $(EXECS)

server: $(OBJSERVER)
	$(LD) $(LFLAGS) $@ $(OBJSERVER) 

client: $(OBJCLIENT)
	$(LD) $(LFLAGS) $@ $(OBJCLIENT)

clean:
	rm -f *.o
	rm -f *.c~
	rm -f *.h~
	rm -f *.html~
	rm -f *.exe*
