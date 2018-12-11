/**
 * @file main.cpp
 * @author Luís Eduardo Luz Silva - 15/0137885 (lightguy875@github.com)
 * @author Gabriel Augusto Correia - 15/0126000 (GustoMelchior@github.com)
 * @brief 
 * @version 0.1
 * @date 2018-12-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include "parser.h"
#include "comm.h"
#include "spider.h"

#define LOCAL_HOST_STR 		"127.0.0.1"
#define QUIT_URL		"http://127.0.0.2/"
#define MAXBUFFSIZE		5000 
#define PROXY_PORT_DEFAULT	8228
#define MAX_CLIENT_REQUEST	5

#define HTTP_MSG_OK	"HTTP/1.0 200 OK\r\n\r\n"

#define forever	while(1)

/**
 * @brief Print de segurança 
 * 
 */
void auxPrint( char* );

/**
 * @brief Função principal do programa
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main( int argc, char* argv[] )
{
	int proxyPort, sock, otherSock;
	struct sockaddr_in proxyAddr, clientAddr;
	struct hostent *server;
	int clientLength, requestLength;
	int sockOpt;
	char request[MAXBUFFSIZE], URL[MAXBUFFSIZE], 
		host[MAXBUFFSIZE], buf[MAXBUFFSIZE];
	char fileName[256], tmpUrl[256], ip[256];
	char *reply;
	std::FILE *requestFile, *replyFile, *spiderFile;
	urlNode* list; // "spider"

	// Entrada do listen	
	proxyPort = PROXY_PORT_DEFAULT;

	// Seleção manual da porta do proxy
	if( argc == 3 )
	{
		// -p ou -P
		if( std::strcmp( argv[1], "-p" ) == 0 )
		{
			proxyPort = std::atoi( argv[2] ); 
		}
		else if( std::strcmp( argv[1], "-P" ) == 0 )
		{
			proxyPort = std::atoi( argv[2] );
		}
	}

	// Escuta o browser até que QUIT_URL seja requisitada
	forever {
		// Cria socket de entrada
		sock = socket( AF_INET, SOCK_STREAM, 0 );
		if( sock < 0 )
		{ 
			printf("Falha ao criar socket.\n");
			exit(1);
		}

		std::memset(&proxyAddr,0,sizeof(proxyAddr));

		proxyAddr.sin_family = AF_INET; // IPv4

		proxyAddr.sin_addr.s_addr = inet_addr(LOCAL_HOST_STR); // Localhost
		proxyAddr.sin_port = htons( proxyPort ); // Porta do servidor

		// Evita erros de bind
		sockOpt = 1; // Opção booleana
	if( setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&sockOpt,sizeof(int)) == -1 ) { printf("Falha ao selecionar opcao do socket.\n"); exit(1); }

		if( bind(sock, (struct sockaddr*)&proxyAddr,sizeof(proxyAddr)) < 0) {
			printf("Falha ao realizar binding do socket\n"); exit(1); }

		printf("Faca uma requisicao de pagina pelo navegador.\n");
		// Escuta requisição do browser
		listen( sock, MAX_CLIENT_REQUEST );

		clientLength = sizeof( clientAddr );
		otherSock = accept(sock,(struct sockaddr*)&clientAddr,(socklen_t*)&clientLength);
		if(otherSock<0)
		{
			printf("Erro ao aceitar requisicao.\n");
			exit(1);
		};
		close(sock);

		// Lê o request do socket
		std::memset(&request,0,MAXBUFFSIZE);
		if( read(otherSock, request, MAXBUFFSIZE) < 0 ) ; // Tratar erro aqui
		printf("Requisicao do Browser: \n\n");
		auxPrint(request);
		printf("\n\n");
		
		requestLength = std::strlen(request)+1;
		RequestURL( request, requestLength, URL, MAXBUFFSIZE );
		if( std::strcmp(URL,QUIT_URL)==0 )
		{
			printf("Requisicao da URL de saida (%s)\nDesligando proxy...\n",QUIT_URL); 
			break;
		}
		printf("URL: ");
		auxPrint(URL);

		printf("\n\n");

		sendRequest( );

		if( (replyFile = fopen("/proxy/reply.txt","rb"))==NULL) exit(1);
		memset(buf,0,MAXBUFFSIZE);
		while( fread(buf,1,sizeof(buf),replyFile)==sizeof(buf))
			send(otherSock,buf,sizeof(buf),0);
		fclose( replyFile );

		// Envia OK ao navegador
		send(otherSock, HTTP_MSG_OK, 19, 0);

		// Spider
		list = NULL;

	        RequestHost( request, sizeof(request), host, MAXBUFFSIZE);
		printf("Host: ");
		auxPrint(host);
		printf("\n\n");

		printf("Spider:\n");
		printf("\n\n");
		Spider( URL, host, &list );
		system("mkdir -p ./proxy");
		memset( fileName, 0, 256 );
		memset( tmpUrl, 0, 256 );
		GetRequestParent( URL, fileName, 256 );
		RemoveHTTPFromUrl( fileName, tmpUrl, 256 );
		memset( fileName, 0, 256 );
		std::strcpy( fileName, "./proxy/");
		std::strcat( fileName, tmpUrl );
		std::strcat( fileName, ".log" );
		spiderFile = fopen( fileName, "wb" );

		fclose( spiderFile );
		close(otherSock);
	}
}

/**
 * @brief Não usa-se printf por motivos de segurança
 * 
 * @param buf 
 */
void auxPrint( char* buf )
{
	char* c = buf;
	while( c[0] != '\0' )
	{
		std::putc(c[0],stdout);
		c++;
	}
}
