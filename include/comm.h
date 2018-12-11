/**
 * @file parser.h
 * @author Luís Eduardo Luz Silva - 15/0137885 (lightguy875@github.com)
 * @author Gabriel Augusto Correia - 15/0126000 (GustoMelchior@github.com)
 * @brief Arquivo de definição de funções common
 * @version 0.1
 * @date 2018-12-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef COMM_H
#define COMM_H

int sendRequest( void );
int createSock();
void configAddr(int, struct sockaddr_in *);
int Connect(int, struct sockaddr_in *);
int Receive(int, char *);
int Bind(int, struct sockaddr_in *);
int Accept(int socket);
int Send(int ,char *);
int GetIP(char *, char *);

#endif//COMM_H
