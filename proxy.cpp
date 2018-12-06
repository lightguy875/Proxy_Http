#include "proxy.h"
#include <QScrollArea>
#include <string>
#include <stdio.h>
#include <netdb.h>
#include <QtCore>


proxy::proxy( in_port_t p, QObject* parent )
   : QThread(parent)
{
    listenPort = p;

}

const std::string termino = "\r\n\r\n";

void proxy::run( void )
{
    int servSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if( servSocket < 0 )
    {
    }

    struct sockaddr_in servAddr;
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(0); // Any address
    servAddr.sin_port = htons(listenPort);

    int y;
    if((y = bind(servSocket,(struct sockaddr*)&servAddr,sizeof(servAddr))<0))
    {
    }

    int x;
    if( (x = listen(servSocket,MAXPENDING)) < 0 )
    {
    }

    forever
    {
        struct sockaddr_in clntAddr;
        socklen_t clntAddrLen = sizeof(clntAddr);
        // Aguarda conexão
        int clntSock = accept(servSocket,(struct sockaddr*)&clntAddr,&clntAddrLen);
        if( clntSock < 0 )
        {
        }

        char clntName[INET_ADDRSTRLEN];
        if(inet_ntop(AF_INET,&clntAddr.sin_addr.s_addr,clntName,sizeof(clntName))!=0)
        {
        }
        else
        {
        }
        char buffer[BUFSIZE];
        ssize_t numBytesRcvd = recv(clntSock,buffer,256,0);
        printf("%s",buffer);
        /*in_port_t outPort = PORT_DEFAULT+1;
    int outSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in realServAddr;
    memset(&realServAddr,0,sizeof(realServAddr));
    realServAddr.sin_family = AF_INET;
    int rtnval = inet_pton(AF_INET,"127.0.0.1",)*/
        close(clntSock);
    }
}

void proxy::dataFromClient(int* sockid)
{
    char buf[BUFSIZE];
    int newsockfd = *sockid;
    int bitsrecebidos = 0;
    std::string request_msg = "";

}

void proxy::WriteToServerSocket(const char* buffer_to_server, int sockfd, int buff_length)
{
    std::string temp;

    temp.append(buffer_to_server);

    int totalsent = 0;

    int senteach;

    while(totalsent < buff_length){
        if((senteach = send(sockfd, (void *)(buffer_to_server + totalsent),(buff_length - totalsent),0))< 0)
        {
            fprintf(stderr,"Erro para enviar para o servidor ! \n");
            exit(1);
        }
    }
}

void proxy::WriteToClientSocket(const char* buffer_to_client, int sockfd, int buff_length)
{
    std::string temp;

    temp.append(buffer_to_client);

    int totalsent = 0;

    int senteach;

    while(totalsent < buff_length)
        {
        if((senteach = send(sockfd, (void *)(buffer_to_client + totalsent),(buff_length - totalsent),0))< 0)
        {
            fprintf(stderr,"Erro para enviar para o servidor ! \n");
            exit(1);
        }
    }

}
void proxy::writeToClient (int Clientfd, int Serverfd)
{
    int MAX_BUFFER_SIZE = 5000;

    int RECV;
    char buffer[MAX_BUFFER_SIZE];

    while((RECV = recv(Serverfd,buffer,MAX_BUFFER_SIZE,0)) > 0)
    {
        proxy::WriteToClientSocket(buffer,Clientfd,RECV);
        memset(buffer,0,sizeof(buffer));
    }

    if(RECV < 0)
    {
        fprintf(stderr, "Yo..!! Error while recieving from server ! \n");
        exit(1);

    }

}

/*
proxy::~proxy( void )
{
    wait( );
}*/
