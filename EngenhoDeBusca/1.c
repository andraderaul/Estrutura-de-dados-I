#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tBusca {
    int n;
    char** p;
} tBusca;

struct tServ {
    tBusca **p;
    int n;
    int cap;
};

struct tVaga {
    int existe;
    int serv;
    int pos;
};

struct tBusca lerBusca(FILE* input, struct tBusca temp);
char* lerPalavras(FILE* input);
int gerarChecksum(struct tBusca temp);
void inserirBusca(struct tVaga vaga, struct tBusca busca, struct tServ servidor);
struct tVaga gerarDoubleHash(FILE* output, int checksum, struct tVaga vaga, struct tServ servidor);
struct tVaga verificarServidor(int serv, struct tVaga vaga, struct tServ servidor);
unsigned int doublehash(unsigned int checksum, unsigned int i, unsigned int tam);
void imprimirBusca(FILE* output, int serv, int pos, struct tServ servidor);
void imprimir (FILE* output, int serv, struct tServ servidor);

int main(int argc, char* argv[]) {
    
    //*****************************************//
    //HANDLE FILE
    //*****************************************//
    
    FILE* input = fopen(argv[1],"r");
    FILE* output = fopen(argv[2],"w");
    
    if (input == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    //*****************************************//
    //ALLOCATE MEMORY FOR SERVERS
    //*****************************************//
    
    struct tServ servidor;
    servidor.p = NULL, servidor.n = 0, servidor.cap = 0;
    fscanf(input, "%i %i", &servidor.n, &servidor.cap);
    
    servidor.p = (tBusca**)malloc(servidor.n * sizeof(tBusca*)); //VETOR TOTAL DE SERVIDORES
    for (int i = 0; i < servidor.n; i++) {
        servidor.p[i] = (tBusca*)malloc(servidor.cap * sizeof(tBusca)); //VETOR DE BUSCAS EM CADA SERVIDOR
        
        for (int k = 0; k < servidor.cap; k++)
            servidor.p[i][k].p = NULL; //MAKE ALL SERVER SPACES EMPTY
    }
    
    //*****************************************//
    //MAP SEARCHES TO SERVER
    //*****************************************//
    
    struct tBusca busca;
    busca.p = NULL, busca.n = 0;
    struct tVaga vaga;
    vaga.existe = 0; vaga.pos = 0; vaga.serv = 0;
    
    int nBuscas = 0, checksum = 0;
    fscanf(input, "%i", &nBuscas);
    
    for (int i = 0; i < nBuscas; i++)
    {
        busca = lerBusca(input, busca);
        checksum = gerarChecksum(busca);
        vaga = gerarDoubleHash(output, checksum, vaga, servidor);
        inserirBusca(vaga, busca, servidor);
        imprimir(output, vaga.serv, servidor);
    }
    
    //*****************************************//
    //FREE ALLOCATED MEMORY
    //*****************************************//
    
    fclose(input);
    fclose(output);
    
    for (int i = 0; i < servidor.n; i++)
    {
        for (int j = 0; j < servidor.cap; j++)
        {
            if (servidor.p[i][j].p != NULL)
            {
                for (int k = 0; k < servidor.p[i][j].n; k++)
                {
                    free(servidor.p[i][j].p[k]);
                }
                free(servidor.p[i][j].p);
            }
        }
        free(servidor.p[i]);
    }
    free(servidor.p);

    return 0;
}
         
struct tBusca lerBusca(FILE* input, struct tBusca temp)
{
    //Renomear variaveis para faciliar compreensão.
    char** busca = temp.p;
    int nPalavras = temp.n;

    fscanf(input, "%i%*c", &nPalavras);
    busca = (char**)malloc(nPalavras * sizeof(char*));

    for (int i = 0; i < nPalavras; i++)
        busca[i] = lerPalavras(input);

    temp.p = busca;
    temp.n = nPalavras;
    return temp;
}
 
char* lerPalavras(FILE* input)
{
    char* busca = (char*)malloc(101);
    fscanf(input, "%s", busca);
    return busca;
}
 
int gerarChecksum(struct tBusca temp)
{
    //Renomear variaveis para faciliar compreensão.
    int nPalavras = temp.n;
    char** busca = temp.p;

    int checksumTotal = 0, checksumParcial = 0, k = 0;

    for (int i = 0; i < nPalavras; i++)
    {
        checksumParcial = busca[i][0];
        k = 1;
        while (busca[i][k] != '\0')
        {
            if (isalnum(busca[i][k]))
                checksumParcial = checksumParcial ^ busca[i][k];
            k++;
        }
        
        if (i == 0)
            checksumTotal = checksumParcial;
        else
            checksumTotal = checksumTotal ^ checksumParcial;
    }
    return checksumTotal;
}
 
struct tVaga verificarServidor(int serv, struct tVaga vaga, struct tServ servidor)
{
    for (int pos = 0; pos < servidor.cap; pos++)
    {
        if (servidor.p[serv][pos].p == NULL)
        {
            vaga.existe = 1;
            vaga.serv = serv;
            vaga.pos = pos;
            return vaga;
        }
    }

    vaga.existe = 0;
    return vaga;
}
 
struct tVaga gerarDoubleHash(FILE* output, int checksum, struct tVaga vaga, struct tServ servidor)
{
    int i = 0;
    while (1)
    {
        int hash = doublehash(checksum, i, servidor.n);
        vaga = (verificarServidor(hash, vaga, servidor));
        
        if (vaga.existe)
        {
            if (i != 0)
                fprintf(output, "S%i\n", hash);
            //printf("S%i\n", hash);
            
            return vaga;
        }
        else
        {
            if (i == 0)
                fprintf(output, "S%i->", hash);
            //printf("S%i->", hash);
            
            i++;
        }
    }
}
 
unsigned int doublehash(unsigned int checksum, unsigned int i, unsigned int tam)
{
    unsigned int hash1 = (7919 * checksum);
    unsigned int hash2 = i * (104729 * checksum + 123);
    unsigned int x = (hash1 + hash2) % tam;
    return x;
}
 
void inserirBusca(struct tVaga vaga, struct tBusca busca, struct tServ servidor)
{
    servidor.p[vaga.serv][vaga.pos].p = busca.p;
    servidor.p[vaga.serv][vaga.pos].n = busca.n;
}
 
void imprimirBusca(FILE* output, int serv, int pos, struct tServ servidor)
{
    int nPalavras = servidor.p[serv][pos].n;

    for (int palavra = 0; palavra < nPalavras; palavra++)
    {
        if (palavra == nPalavras - 1) {
            fprintf(output, "%s", servidor.p[serv][pos].p[palavra]);
            //printf("%s", servidor.p[serv][pos].p[palavra]);
        }
        else
        {
            fprintf(output, "%s ", servidor.p[serv][pos].p[palavra]);
            //printf("%s ", servidor.p[serv][pos].p[palavra]);
        }
    }
}
 
void imprimir (FILE* output, int serv, struct tServ servidor)
{
    fprintf(output, "[S%i] ", serv); //Imprima o servidor de destino.
    //printf("[S%i] ", serv);

    for (int pos = 0; pos < servidor.cap; pos++) //Passe por todas as posições do servidor.
    {
        imprimirBusca(output, serv, pos, servidor);
        
        //Se essa for a últ posição OU a próxima posição não estiver ocupada...
        if (pos == (servidor.cap - 1) || servidor.p[serv][pos+1].p == NULL)
        {
            fprintf(output, "\n"); //Quebre a linha e saia da função.
            //printf("\n");
            return;
        }
        else
        {
            //printf(", ");
            fprintf(output, ", ");
        }
    }
}