/**
 * @file spider.cpp
 * @author Luís Eduardo Luz Silva - 15/0137885 (lightguy875@github.com)
 * @author Gabriel Augusto Correia - 15/0126000 (GustoMelchior@github.com)
 * @brief 
 * @version 0.1
 * @date 2018-12-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "parser.h"
#include "comm.h"
#include "spider.h"

/**
 * @brief Adiciona um nó na árvore comsiderando o nó pai e o parente
 * 
 * @param head 
 * @param parent 
 * @param url 
 */
void AddNode( urlNode** head, urlNode* parent, char* url )
{
	urlNode *list, *lastNode;

	list = (urlNode*)std::malloc( sizeof(urlNode) );
	if( *head == NULL )
	{
		*head = list;
		(*head)->next = (*head)->prev = NULL;
	}
	else
	{
		lastNode = *head;
		while( lastNode->next != NULL )
			lastNode = lastNode->next;
		list->prev = lastNode;
		lastNode->next = list;
		list->next = NULL;
	}
	std::memset(url,0,std::strlen(url));
	list->parent = parent;
}
/**
 * @brief Apaga a lista de endereços
 * 
 * @param head 
 */
void DeleteListURL(  urlNode** head )
{
	urlNode *aux;

	while (*head != NULL)
	{
		aux = *head;
		*head = (*head)->next;
		free(aux);
	}
}
/**
 * @brief Pesquisa uma URL na lista
 * 
 * @param list 
 * @param url 
 * @return int 
 */
int Find( urlNode* list, char* url )
{
	while( list != NULL )
	{
		if( std::strcmp( url, list->url ) == 0 )
			return 1;
	}

	return 0;
}
/**
 * @brief Realiza a operação de spider a partir de uma URL, lista de nós e um link de host
 * 
 * @param url 
 * @param host 
 * @param list 
 */

void Spider( char* url, char* host, urlNode** list )
{
	char nxtUrl[MAXBUFFSIZE], tmpUrl[MAXBUFFSIZE], tmpLine[MAXBUFFSIZE], parentUrl[MAXBUFFSIZE];
	char *j, *ptr;
	int i, k, tNode, parentSize, depth, w;
	i = depth = 0;

	std::FILE*	fileBuf;
	urlNode *nextNode, *lastVisited;

	std::memset( nxtUrl, 0, MAXBUFFSIZE );
	std::memset( tmpUrl, 0, MAXBUFFSIZE );
	std::memset( tmpLine, 0, MAXBUFFSIZE );
	std::memset( parentUrl, 0, MAXBUFFSIZE );

	AddNode( list, NULL, url ); // Nova lista, sem pai, a partir do link

	lastVisited = NULL;
	nextNode = *list;
	GetRequestParent( url, parentUrl, MAXBUFFSIZE ); // Obtém pai do link

	parentSize = std::strlen( parentUrl );
	if( parentUrl[parentSize] == '/' )
	{
		parentUrl[parentSize] = '\0';
		parentSize--;
	}

	// Remove '/' do final do link, para formatação para processamento
	if( parentUrl[parentSize-1] == '/' )
		parentUrl[parentSize-1] = '\0';

	std::strcpy( nxtUrl, url ); // Copia a URL

	// Enquanto houverem objetos a serem visitados
	while( nextNode != NULL )
	{
		if( depth < (nextNode->depth+1) )
			depth = nextNode->depth + 1;
		if( Find( nextNode, nxtUrl ) == 0 && CountChar( nxtUrl, '#', std::strlen( nxtUrl ) ) == 0 )
		{
		}
		
	}
}
