//#include "../lib/headers.hpp"
#include <iostream>                                                                                                                           
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

using namespace std;

enum METHOD{GET, POST, HEAD};

typedef struct Request {
    string method;
    string url;
    string host;
    string version;
    string body;
} Request;

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

Request* parseRequest(string& reqstr){
   if(reqstr == ""){
       return NULL;
   }

   Request *req = new Request;
   string fullReqStr = reqstr;
   string buf = ""; 
   int currentPos = 0;
   vector<string> lineVec;
   string currentLine = "";
    
   //pega linha atual
   currentLine = fullReqStr.substr(currentPos,fullReqStr.find('\n'));
   currentPos = fullReqStr.find('\n',currentPos);
   lineVec = split(currentLine, ' ');

   req->method = lineVec[0];
   req->url = lineVec[1];
   req->version = lineVec[2];
    
   //proxima linha
   currentLine = fullReqStr.substr(currentPos,fullReqStr.find('\n'));
   currentPos = fullReqStr.find('\n',currentPos);
   lineVec = split(currentLine, ' ');

   req->host = lineVec[1];

   if(req->method = "POST"){
       cout << "Post ainda nao esta 100%" << endl;
   }

  // currentPos = fullReqStr.find(' ') + 1;
//   cout << currentPos << endl;
//   cout << fullReqStr.find(' ',currentPos) << endl;
   //req->url.assign(fullReqStr.substr(currentPos,fullReqStr.find(' ',currentPos)));


   return req;
}

void datafromclient(int* sockid) {
    int MAX_BUFFER_SIZE = 5000;
    char buf[MAX_BUFFER_SIZE];

    int newsockfd = *sockid;
    int bitsRecebidos = 0;

    string request_message = "";
    
    string termino = "\r\n\r\n";
    while(request_message.find(termino) == string::npos){

        bzero(buf,MAX_BUFFER_SIZE);
        
        int recvd = recv(newsockfd, buf, MAX_BUFFER_SIZE, 0);
        if(recvd < 0){
            printf("Erro ao receber\n");
            exit(1);
        } else if(recvd == 0){
            break;
        } else{
            bitsRecebidos += recvd;

            if(bitsRecebidos > MAX_BUFFER_SIZE){
                MAX_BUFFER_SIZE *=2;
            }
        }
        request_message += buf;
//        cout << endl << "SEPARATE" << endl;
        //cout << buf << endl;
    }
    
    Request *req = parseRequest(request_message);

    cout << "Total request" << endl << request_message << endl;

//    cout << "Method and url" << endl;

//    cout << req->method << endl;
//    cout << req->url << endl;
//    cout << req->version << endl;
//    cout << req->host << endl;

    int serverFd;
     
    delete req;
}

int main(int argc, char const *argv[])
{
    int portNum = 8228;

    if(argv[1] == "-p" || "-P") { 
        if(argv[2] != NULL) {
            portNum = atoi(argv[2]); 
        } 
    }

    int sockfd,newsockfd;

	struct sockaddr_in serv_addr;
    struct sockaddr cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // create a socket
    memset(&serv_addr,0,sizeof serv_addr);
    
    serv_addr.sin_family = AF_INET;     // ip4 family
  	serv_addr.sin_addr.s_addr = INADDR_ANY;  // represents for localhost i.e 127.0.0.1
 	serv_addr.sin_port = htons(portNum);
    
    //binda o socket no server local
    int binded = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (binded <0 ) {
 		printf ("Error on binding! \n");
  		return 1;
    }

    listen(sockfd, 100); // can have maximum of 100 browser requests
    
    int clilen = sizeof(struct sockaddr);
    while(1) {
  		
  		/* A browser request starts here */

  		newsockfd = accept(sockfd,&cli_addr, (socklen_t*) &clilen); 

  		if (newsockfd <0){
  			fprintf(stderr, "ERROR! On Accepting Request ! i.e requests limit crossed \n");
            break;
 		}

 		int pid = fork();

 		if(pid == 0){

            close(sockfd); 
 			//datafromclient((void*)&newsockfd);
            datafromclient(&newsockfd);
//            printf("Recebeu uma conexão!\n");
 			close(newsockfd);
 			exit(0);

 		}else{
 			close(newsockfd);     // pid =1 parent process
 		}

 	}

    close(sockfd); 

    return 0;

}
