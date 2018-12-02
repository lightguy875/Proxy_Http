#include "../lib/parser.hpp"

#define DEFAULT_NHDRS 8
#define TAMANHO_REQUEST_MAX 65535
#define TAMANHO_REQUEST_MIN 4

static const char *root_abs_path = "/";

// Função privada de declarações
int Requestdeparse_printar_linha_de_request(struct Requestdeparse * pr , char * buffered,size_t tamanho_buffer,size_t * tmp);

size_t Requestdeparse_requesttamanho_linha(struct Requestdeparse * pr);
/*
Debug() printa se debugg estiver setado em 1

Formato de parametro mesmo que printf

*/
void debug(const char * formato, ...)
{
    va_list args;
    if(debug)
    {
        va_start(args,formato);
        vprintf(stderr, formato , args);
        va_end(args);
    }
}
int HeaderParser_atribuidor(struct Requestdeparse *pr, const char *chave, const char *valor)
{
    struct HeaderParser* ph;
    HeaderParser_remover( pr ,chave);
    if(pr->tamanho_header <= pr->headersusados+1)
    {
        pr->tamanho_header = pr->tamanho_header*2;
        pr->headers = (struct Requestdeparse *)realloc(pr->headers,pr->tamanho_header, pr->tamanho_header * sizeof(struct HeaderParser));
        if(!pr->headers)
            return -1;
    }

    ph = pr->headers + pr->headersusados;
    pr->headersusados += 1;

    ph->chave = (char *)malloc(strlen(chave)+1);
    memcpy(ph->chave,chave,strlen(chave));
    ph->chave[strlen(chave)] = '\0';

}

