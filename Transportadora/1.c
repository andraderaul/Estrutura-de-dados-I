#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tVeiculo {
    unsigned int capPacotes;
    unsigned int cargaTot;
    unsigned int nPacotes;
    char** p;
} tVeiculo;

void limpar(tVeiculo* V, unsigned int T);
unsigned int lerPacote(FILE* input, char** cod, unsigned int* peso);
void inserirPacote(tVeiculo* V, char* cod, unsigned int peso);
void imprimir(FILE* output, int n, tVeiculo* V);

void mergesort1(char** S, char** E, int ini, int fim);
void ordenarPacotes(char** E, int N);
void intercalar(char** S, char** E, int ini, int meio, int fim);
void copiar(char** A, char** B, int N);
int menorQue(char* I, char* J);

enum {espacoInicial = 100};

int main (int argc, char* argv[])
{
    //------------------//
    // ABRIR ARQUIVO
    //------------------//
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    
    if (input == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    //------------------//
    // LER ARQUIVO
    //------------------//
    
    //Criar estruturas de veículos e pacotes.
    unsigned int nVeiculos, capCarga, nPacotes;
    fscanf(input, "%i %i %i", &nVeiculos, &capCarga, &nPacotes);
    
    //CRIAR VEÍCULOS
    tVeiculo* vVeiculo = (tVeiculo*)malloc(sizeof(tVeiculo)*nVeiculos); //Allocar vetor para todos os veículos
    for (int i = 0; i < nVeiculos; i++) //Para cada veículo...
    {
        vVeiculo[i].p = (char**)malloc(sizeof(char*)*espacoInicial); //Allocar vetor para todos os pacotes
        vVeiculo[i].capPacotes = espacoInicial; //Capacidade de pacotes é inicialmente igual a 100;
        for (int k = 0; k < espacoInicial; k++) //Alocar 15 bytes para o código de cada pacote
        {
            vVeiculo[i].p[k] = (char*)malloc(15);
        }
    }
    
    //------------------//
    // LER ARQUIVO
    //------------------//
    
    char* tempCod = (char*)malloc(15);                              //Temp string.
    unsigned int tempPeso = 0;                                      //Temp peso.
    unsigned int existirPacotes = 1, existePacoteEmEspera = 0;      //Flags
    
    LOOP_MAIS_EXTERNO:
    while (existirPacotes)
    {
        limpar(vVeiculo, nVeiculos); //Para que, em cada loop, cada veiculo começe do zero.
        for (int i = 0; i < nVeiculos; i++) //Passe por veículos
        {
            while (vVeiculo[i].cargaTot <= capCarga) //Enquanto cap total não for atingida...
            {
                //** Se houver um pacote que foi lido no loop anterior, mas não coube no veículo anterior, este pacote está em espera e será inserido no veículo atual. Se não houver, leia o próximo pacote. **//
                
                if (!existePacoteEmEspera)
                {
                    existirPacotes = lerPacote(input, &tempCod, &tempPeso); //Ler pacote retorna 1 = sucesso, 0 = falha.
                    if (!existirPacotes)
                    {
                        ordenarPacotes(vVeiculo[i].p, vVeiculo[i].nPacotes);
                        imprimir(output, i, &vVeiculo[i]);
                        goto LOOP_MAIS_EXTERNO;
                    }
                }
                
                if ((vVeiculo[i].cargaTot + tempPeso) <= capCarga) //Se pacote não exceder carga...
                {
                    //Se realloc for necessário
                    if (vVeiculo[i].nPacotes >= vVeiculo[i].capPacotes)
                    {
                        int temp = vVeiculo[i].capPacotes;
                        vVeiculo[i].capPacotes = 2 * temp;
                        vVeiculo[i].p = (char**)realloc(vVeiculo[i].p, sizeof(char*) * vVeiculo[i].capPacotes);
                        for (int k = temp; k < vVeiculo[i].capPacotes; k++)
                            vVeiculo[i].p[k] = (char*)malloc(15);
                    }
                    
                    inserirPacote(&vVeiculo[i], tempCod, tempPeso);
                    existePacoteEmEspera = 0;
                }
                else
                {
                    existePacoteEmEspera = 1;
                    ordenarPacotes(vVeiculo[i].p, vVeiculo[i].nPacotes);
                    imprimir(output, i, &vVeiculo[i]);
                    break;
                }
            }
        }
    }
    
    return 0;
}

void ordenarPacotes(char** E, int N)
{
    char** S = (char**)malloc(sizeof(char*) * N);
    for (int i = 0; i < N; i++)
        S[i] = (char*)malloc(15);
    
    mergesort1(S, E, 0, N-1);
    
    for (int i = 0; i < N; i++)
        free(S[i]);
    free(S);
}

void mergesort1(char** S, char** E, int ini, int fim)
{
    int meio = ini + (fim - ini) / 2;
    if (ini < fim)
    {
        mergesort1(S, E, ini, meio);
        mergesort1(S, E, meio + 1, fim);
    }
    intercalar(S, E, ini, meio, fim);
}

int menorQue(char* I, char* J)
{
    if (I[0] < J[0])
        return 1;
    
    return 0;
}

void copiar(char** A, char** B, int N)
{
    for (int i = 0; i < N; i++)
        strcpy(A[i], B[i]);
}

void intercalar(char** S, char** E, int ini, int meio, int fim)
{
    int i = ini, j = meio + 1, k = ini;
    while (i <= meio && j <= fim)
    {
        if (menorQue(E[i], E[j]))
            strcpy(S[k++], E[i++]);
        else
            strcpy(S[k++], E[j++]);
    }
    
    if (i > meio)
        copiar(&S[k], &E[j], fim - j + 1);
    else
        copiar(&S[k], &E[i], meio - i + 1);
    
    copiar(&E[ini], &S[ini], fim - ini + 1);
}

void imprimir(FILE* output, int n, tVeiculo* V)
{
    fprintf(output, "[V%i] ", n);
    for (int i = 0; i < (V->nPacotes); i++)
        fprintf(output, "%s ", V->p[i]);
    fprintf(output, "\n");
}

void inserirPacote(tVeiculo* V, char* cod, unsigned int peso)
{
    unsigned int T = V->nPacotes;
    strcpy(V->p[T], cod);
    V->cargaTot += peso;
    V->nPacotes++;
}

unsigned int lerPacote(FILE* input, char** cod, unsigned int* peso)
{
    if (fscanf(input, "%s %u", *cod, peso) == EOF)
        return 0;
    else
        return 1;
}

void limpar(tVeiculo* V, unsigned int T)
{
    for (int i = 0; i < T; i++)
    {
        V[i].cargaTot = 0;
        V[i].nPacotes = 0;
    }
}