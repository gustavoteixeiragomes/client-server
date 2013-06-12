CC = gcc

CFLAGS = -Wall -g

RM = rm -f
SET = -lm -o


clean:
	@echo " --- Executando make clean --- "
	@$(RM) cliente.o msg_headers.o tp_socket.o cliente servidor.o servidor

cliente:
	@echo " --- COMPILANDO $@ --- "
	@$(CC) $(CFLAGS) cliente.c msg_headers.c tp_socket.c $(SET) $@

servidor:
	@echo " --- COMPILANDO $@ --- "
	@$(CC) $(CFLAGS) servidor.c msg_headers.c tp_socket.c $(SET) $@

all:
	@echo " --- Executando make clean --- "
	@$(RM) cliente.o msg_headers.o tp_socket.o cliente servidor.o servidor
	@echo " --- COMPILANDO cliente --- "
	@$(CC) $(CFLAGS) cliente.c msg_headers.c tp_socket.c $(SET) cliente
	@echo " --- COMPILANDO servidor --- "
	@$(CC) $(CFLAGS) servidor.c msg_headers.c tp_socket.c $(SET) servidor

