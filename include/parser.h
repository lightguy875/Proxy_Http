/**
 * @file parser.h
 * @author Luís Eduardo Luz Silva - 15/0137885 (lightguy875@github.com)
 * @author Gabriel Augusto Correia - 15/0126000 (GustoMelchior@github.com)
 * @brief Definição de funções do parser
 * @version 0.1
 * @date 2018-12-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

#ifndef MAXBUFFSIZE
#define MAXBUFFSIZE 5000
#endif//MAXBUFFSIZE

#define HTMLHEADERSIZE	2000
/**
 * @brief Estrutura do header html
 * 
 */
typedef struct htmlHeader {
	char header[HTMLHEADERSIZE];
	int size;
	char name[256];
} htmlHeader;

int CountChar( char* string, char symb, int size );
void GetString( char* string, int pos, char haltSgn, char* buf, int bufSize, char* rtn, int rtnSize );
void RequestURL( char* buf, int bufSize, char* url, int urlSize );
void RequestHost( char* buf, int bufSize, char* host, int hostSize );
void GetName( char* url, char* name, int nameSize );
void RemoveHTTPFromUrl( char* url_in, char* url_out, int outSize );
void GetHtmlHeader( char* buf, int bufSize, htmlHeader* header );
void GetPath( char* url, char* path, int pathSize );
void GetRequestParent( char *url, char *rtn, int rtnSize );

#endif//PARSER_H
