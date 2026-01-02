# Compilatore
CC = gcc

# Configurazione lavagna 
SERVER_OUT = lavagna
SERVER_FLAGS = -Wall # Flag warning
SERVER_INC = -I. -Iclasses -Istructs -Ifunctions -Inetwork -Iserver
SERVER_SRC = lavagna.c classes/*.c functions/*.c network/*.c server/*.c

# Configurazione utente
USER_OUT = utente
USER_FLAGS = -Wall # Flag warning
USER_INC = -I. -Inetwork -Iclasses -Iuser
USER_SRC = utente.c network/*.c classes/*.c user/*.c

all: lavagna utente

lavagna:
	$(CC) $(SERVER_FLAGS) $(SERVER_INC) $(SERVER_SRC) -o $(SERVER_OUT)

utente:
	$(CC) $(USER_FLAGS) $(USER_INC) $(USER_SRC) -o $(USER_OUT)

clean:
	rm -f $(SERVER_OUT) $(USER_OUT)

