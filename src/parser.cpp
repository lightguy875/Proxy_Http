/**
 * @file parser.cpp
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
/**
 * @brief Conta a quantidade de characteres de um programa
 * 
 * @param string 
 * @param symb 
 * @param size 
 * @return int 
 */
int CountChar( char* string, char symb, int size )
{
	int count = 0;
	int i;
	for( i = 0; i < size-1; i++ )
		if( string[i] == symb ) count++;
	return count;
}
/**
 * @brief obtem a sting a partir de um objeto, tamanho e posição
 * 
 * @param string 
 * @param pos 
 * @param haltSgn 
 * @param buf 
 * @param bufSize 
 * @param rtn 
 * @param rtnSize 
 */
void GetString( char* string, int pos, char haltSgn, char* buf, int bufSize, char* rtn, int rtnSize )
{
	char *ptr, *idx;
	int j;
	int paramSize = std::strlen(string) + pos;

	memset( rtn, 0,rtnSize );

	ptr = std::strstr( buf, string );

	if( ptr != NULL )
	{
		for( idx = (ptr + paramSize), j=0; idx < (buf + bufSize) && j < rtnSize; idx++)
		{
			if( *idx == haltSgn )
			{
				rtn[j] = '\0';
				break;
			}

			rtn[j] = *idx;
			j++;
		}
	}
}
/**
 * @brief Realiza o Request de uma URL 
 * 
 * @param buf 
 * @param bufSize 
 * @param url 
 * @param urlSize 
 */

void RequestURL( char* buf, int bufSize, char* url, int urlSize )
{
	GetString( "GET", 1, 0x20, buf, bufSize, url, urlSize );

	if( url[0] == '\0' )
	{
		GetString( "POST", 1, 0x20, buf, bufSize, url, urlSize );
	}
}
/**
 * @brief Realiza o request a partir de um host
 * 
 * @param buf 
 * @param bufSize 
 * @param host 
 * @param hostSize 
 */

void RequestHost( char* buf, int bufSize, char* host, int hostSize )
{
	GetString( "Host:", 1, '\r', buf, bufSize, host, hostSize );
}

void GetName( char* url, char* name, int nameSize )
{
	int i, j = 0, slashIndex = 0, slashCounter = 0, urlSize;
	urlSize = std::strlen( url );

	std::memset( name, 0, nameSize );

	for ( i = 0; i < urlSize; i++ )
	{
		if( url[i] == '/' )
		{
			slashIndex = i;
			slashCounter += 1;
		}
	}

	for( i = (slashIndex + 1); i < urlSize && j < nameSize; i++ )
	{
		name[j] = url[i];
		j++;
	}

	if( CountChar( name, '.', nameSize ) == 0 )
		std::memset( name, 0, nameSize );
}
/**
 * @brief Parser para remover string de uma URL
 * 
 * @param url_in 
 * @param url_out 
 * @param outSize 
 */
void RemoveHTTPFromUrl( char* url_in, char* url_out, int outSize )
{
	int inSize = std::strlen( url_in );
	std::memset( url_out, 0, outSize );

	int i;

	if (inSize > 7)
	{
		if (url_in[0] == 'h' && url_in[1] == 't' && url_in[2] == 't' && url_in[3] == 'p' && url_in[4] == ':' && url_in[5] == '/' && url_in[6] == '/' )
		{
			for (i = 6; i <= inSize && (i-6) < outSize; i++)
			{
			        url_out[i-6] = url_in[i];
			}
			return;
		}
	}
	std::strcpy( url_out, url_in );
	if (outSize > 0)
	{
		for(i = (outSize -2); i > 0; i--)
		{
			if(url_out[i] == '/' && url_out[i+1] == '\0')
			{
				url_out[i] = '\0';
				break;
			}
		}

		if(url_out[(outSize-1)] == '/')
			url_out[(outSize-1)] = '\0';
	}

}
/**
 * @brief Obtem o arquivo html a partir de um header HTTP
 * 
 * @param buf 
 * @param bufSize 
 * @param header 
 */
void GetHtmlHeader( char* buf, int bufSize, htmlHeader* header )
{
	htmlHeader* rtn;
	rtn = (htmlHeader*)std::malloc(sizeof(htmlHeader));
	std::memset(rtn->header,0,HTMLHEADERSIZE);
	std::memset(rtn->name,0,256);
	std::FILE *file;
	char name[256];
	
	int i, CrNl, CrNlCount;
	CrNl = CrNlCount = 0;

	for( i = 0; i < bufSize-3; i++ )
	{
		if( buf[i] == '\r' && buf[i+1] == '\n' && buf[i+2] == '\r' && buf[i+3] == '\n' )
		{
			rtn->header[i] = '\r';
			rtn->header[i+1] = '\n';
			rtn->header[i+2] = '\0';
			rtn->size = i+1;
			break;
		}
		rtn->header[i] = buf[i];
	}

	i += 3; // Normaliza

	if( i < bufSize )
	{
		std::strcpy( rtn->name, name );
		file = fopen( name, "w" );

		if( file == NULL ) exit(1); // Erro

		for (;i < bufSize; i++)
		{
			fprintf( file, "%c", buf[i] );
		}

		std::fclose( file );
	}
	else
	{
		rtn->name[0] = '-';
		rtn->name[1] = '1';
		rtn->name[2] = '\0';
	}

	header = rtn;
}
/**
 * @brief Pega o caminho a partir de uma URL
 * 
 * @param url 
 * @param path 
 * @param pathSize 
 */
void GetPath( char* url, char* path, int pathSize )
{
	int i, j, urlSize = std::strlen(url);
	char parent[256], name[256];
	int parentSize, nameSize, pathBoundary;

	std::memset( path, 0, pathSize );

	GetRequestParent( url, parent, 256 );
	GetName( url, name, 256 );

	parentSize = std::strlen( parent );
	nameSize = std::strlen( name );
  	pathBoundary = urlSize - nameSize;

	for ( i = parentSize; i < pathBoundary && j < pathSize; i++, j++)
	{
		path[j] = url[i];
	}
}
/**
 * @brief Obtem o Request de um elemento parente
 * 
 * @param url 
 * @param rtn 
 * @param rtnSize 
 */
void GetRequestParent( char *url, char *rtn, int rtnSize )
{
	int i, slashIndex = 0, slashCounter = 0;
	int urlSize = std::strlen( url );

	std::memset( rtn, 0, rtnSize );

	for( i = 0; i < urlSize; i++ )
	{
		if( url[i] == '/')
		{
			slashCounter += 1;
		}

		if( slashCounter == 3 )
		{
			slashIndex = i;
			break;
		}
	}

	if( slashIndex != 0 )
	{
		for( i = 0; i < slashIndex && i < rtnSize; i++ )
		{
			rtn[i] = url[i];
		}
	}
	else
	{
		std::strcpy( rtn, url );
	}
}

