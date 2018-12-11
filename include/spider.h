/**
 * @file parser.h
 * @author Luís Eduardo Luz Silva - 15/0137885 (lightguy875@github.com)
 * @author Gabriel Augusto Correia - 15/0126000 (GustoMelchior@github.com)
 * @brief Funções básicas do spyder
 * @version 0.1
 * @date 2018-12-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef SPIDER_H
#define SPIDER_H

typedef struct urlNode 
{
	char url[MAXBUFFSIZE];
	struct urlNode *prev, *next, *parent;
	int depth;
} urlNode;

void AddNode( urlNode** head, urlNode* parent, char* url );
void DeleteListURL( urlNode** head );
int Find( urlNode* list, char* url );
void Spider( char* url, char* host, urlNode** list );

#endif//SPIDER_H
