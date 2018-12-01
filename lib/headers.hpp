#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


extern int sockfd, newsockfd, portno;
extern socklen_t clilen;
extern std::string buffer;
extern struct sockaddr_in serv_addr, cli_addr;
extern int n;
extern int port;