/**
 * @file comm.cpp
 * @author Luís Eduardo Luz Silva - 15/0137885 (lightguy875@github.com)
 * @author Gabriel Augusto Correia - 15/0126000 (GustoMelchior@github.com)
 * @brief Funções básicas do proxy
 * @version 0.1
 * @date 2018-12-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "parser.h"
#include "comm.h"

int sendRequest( void )
{
	int ok, n, sock, numbytes;
	FILE *frequest, *freply;
	char *request, buffer[5000], hostname[500], *tmpBuffer;
	int port = 80, msgSize, firstPack = 1;
	char msgLenth[100];
	struct sockaddr_in server_address;
	struct hostent *server;

	// Criando o diretório
	system("mkdir -p ./proxy");

	// criando arquivos
	if((frequest = fopen("./proxy/request.txt", "r")) == NULL)
		exit(1);

	if((freply = fopen("./proxy/reply.txt", "wb")) == NULL)
		exit(1);
	// captura o tamanho do arquivo em bytes
	fseek(frequest, 0L, SEEK_END);
	numbytes = ftell(frequest);
	// reposiciona no início do arquivo
	fseek(frequest, 0L, SEEK_SET);

	// aloca memória
	request = (char*)calloc(numbytes, sizeof(char));
	if(request == NULL) exit(1);

	// copia texto para o buffer
	fread(request, sizeof(char), numbytes, frequest);
	fclose(frequest);

	RequestHost(request, strlen(request), hostname, sizeof(hostname)-1);

	// Criando socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  	exit(1);

	// Informações do servidor
  if ((server = gethostbyname(hostname)) == NULL)
  	exit(1);

	//configuração do endereço do servidor
	bzero((char *) &server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
			 (char *)&server_address.sin_addr.s_addr,
			 server->h_length);
	server_address.sin_port = htons(port);

	if (connect(sock,(struct sockaddr *)&server_address,sizeof(server_address)) < 0)
		exit(1);

	// Envia a requisição no socket
	if (write(sock,request,strlen(request)) < 0)
		exit(1);

  memset(msgLenth,0,sizeof(msgLenth));

	// Armazena toda a resposta do servidor em files/reply.txt
	while(1)
  {
		bzero(buffer,sizeof(buffer));
		n = read(sock,buffer,sizeof(buffer) - 1);

    if (firstPack == 1)
    {
      GetString("Content-Length:", 1, '\r', buffer, sizeof(buffer), msgLenth, sizeof(msgLenth));

      if (msgLenth[0] != '\0')
        msgSize = atoi(msgLenth);

      tmpBuffer = strstr(buffer, "\r\n\r\n");

      if (tmpBuffer != NULL)
      {
        tmpBuffer += 4;
        n = n - (int)(tmpBuffer - buffer);
      }
      firstPack = 0;
    }

		if(n < 0)
			exit(1);
		if(n > 0){
			printf("%s",buffer);
			fprintf(freply, "%s", buffer);
      msgSize = msgSize - n;

      if (msgSize == 0)
        break;
		}
		if(n == 0)
      break;
	}

  close(sock);
	fclose(freply);
	free(request);
	return ok;
}
/**
 * @brief Create a Sock object
 * 
 * @return int 
 */
int createSock( void )
{
  return socket(AF_INET,SOCK_STREAM,0);
}
/**
 * @brief Configura o endereço do socket criado
 * 
 * @param port 
 * @param address 
 */
void configAddr(int port, struct sockaddr_in * address)
{
  bzero((char *) address, sizeof(*address));
  address->sin_family = AF_INET;
  address->sin_port = htons(port);
  address->sin_addr.s_addr = INADDR_ANY;
}
/**
 * @brief Pega o ip do host
 * 
 * @param hostname 
 * @param ip 
 * @return int 
 */
int GetIP(char hostname[], char *ip){
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ( (he = gethostbyname( hostname ) ) == NULL)
	{
		return -1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for(i = 0; addr_list[i] != NULL; i++)
	{
		strcpy(ip , inet_ntoa(*addr_list[i]) );
	}

	return 0;
}
/**
 * @brief Realiza a conexão tcp
 * 
 * @param socket 
 * @param address 
 * @return int 
 */
int Connect(int socket,struct sockaddr_in * address){
	return connect(socket, (struct sockaddr *) address, sizeof(*address));
}
/**
 * @brief Recepção de dados do mensageiro
 * 
 * @param socket 
 * @param message 
 * @return int 
 */
int Receive(int socket, char * message){
	return read(socket, message, sizeof(message));
}

/**
 * @brief Realiza a junção da porta pelo endereço ip
 * 
 * @param socket 
 * @param address 
 * @return int 
 */
int Bind(int socket, struct sockaddr_in *address){
	return bind(socket, (struct sockaddr *) address, sizeof(*address));
}

/**
 * @brief Aceita a conexão com o sistema 
 * 
 * @param socket 
 * @return int 
 */
int Accept(int socket){
	return accept(socket, NULL, NULL);
}

/**
 * @brief Enviar o socket com uma mensagem
 * 
 * @param socket 
 * @param message 
 * @return int 
 */
int Send(int socket, char * message){
	return send(socket, message, sizeof(message), 0);
}

