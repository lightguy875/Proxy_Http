#include "proxy.h"
#include <QScrollArea>
#include <string>
#include <stdio.h>

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
/*
proxy::~proxy( void )
{
    wait( );
}*/
