#ifndef PROXY_HEADERS
#define PROXY_HEADERS
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>
#include <netdb.h>


char * converter_requisicao_para_string(struct Requestdeparse * req);
int criarsocket_servidor(char *endereçoPC, char *Portapc);
void escreversocket_para_servidor(const char * buff_para_servidor, int  sockfd , int tamanho_buffer);
void escreversocket_para_cliente(const char* buff_para_servidor, int sockfd , int tamanho_buffer);
void escrever_para_cliente(int clienteFD , int ServidorFD);
void * dados_do_cliente(void * sockid);
#endif

