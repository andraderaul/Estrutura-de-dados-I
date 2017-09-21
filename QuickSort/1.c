#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct tCont {
    int n;
    char t[3];
} tCont;

//Gerais
void trocar(int* a, int* b);
void ordenar(int V[], int n);
void ordenarCont(tCont V[], int n);
void inicializar(tCont V[], int n);

//Quicksorts
void quicksort(int V[], int inicio, int fim, int* cont, int t);
int particionarPadrao(int V[], int inicio, int fim, int* cont);
int particionarHoare(int V[], int inicio, int fim, int* cont);
void mediana(int V[], int inicio, int fim, int* cont, int t);
void aleatorio(int V[], int inicio, int fim, int* cont, int t);

enum global { nSorts = 6 };

enum heuristicas {
    pPadrao = 0,
    pMediana = 1,
    pAleatoria = 2,
    hPadrao = 3,
    hMediana = 4,
    hAleatoria = 5,
};

int main(int argc, char* argv[])
{
    //--------------------//
    // ABRIR ARQUIVO
    //--------------------//
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    
    if (input == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    //--------------------//
    // LEITURA DE ARQUIVO
    //--------------------//
    
    int **X;
    tCont vCont[nSorts];
    inicializar(vCont, nSorts);
    unsigned int nVetores, n;
    X = (int**)malloc(sizeof(int*) * nSorts);
    
    fscanf(input, "%i ", &nVetores);
    for (int i = 0; i < nVetores; i++)
    {
        fscanf(input, "%i ", &n);
        
        //CRIAR (nSorts) VETORES AUXILIARES de tamanho n.
        for (int k = 0; k < nSorts; k++)
            X[k] = (int*)malloc(sizeof(int) * n);
        
        //LER O VETOR (de n posições) SOMENTE UMA VEZ (X[0]) e copiar esse vetor para os outros nSorts auxiliares (X[1] até X[nSorts]).
        for (int k = 0; k < n; k++)
        {
            fscanf(input, "%i ", &X[0][k]);
            for (int j = 1; j < nSorts; j++)
                X[j][k] = X[0][k];
        }
        
        //Para cada tipo de qsort, ordene o vetor aux X[k] e salve o cont no vetor vCont[k] correspondente.
        for (int k = 0; k < nSorts; k++)
            quicksort(X[k], 0, n-1, &vCont[k].n, k);
        
        //Ordernar os tipos de quicksorts por contagem
        ordenarCont(vCont, nSorts);
        fprintf(output, "[%i] N(%i) ", i, n);
        for (int k = 0; k < nSorts; k++)
        {
            fprintf(output, "%s(%i) ", vCont[k].t, vCont[k].n);
            if (k == nSorts-1)
                fprintf(output, "\n");
        }
        
        //Liberar vetores aux usados para nSorts ordenações.
        for (int k = 0; k < nSorts; k++)
        {
            free(X[k]);
            X[k] = NULL;
            inicializar(vCont, nSorts);
        }
    }
    
    return 0;
}

void inicializar(tCont V[], int n)
{
    for (int i = 0; i < n; i++)
    {
        V[i].n = 0;
        
        switch (i) 
        {
            case pPadrao:
                strcpy(V[i].t, "PP");
                break;
            case pMediana:
                strcpy(V[i].t, "PM");
                break;
            case pAleatoria:
                strcpy(V[i].t, "PA");
                break;
            case hPadrao:
                strcpy(V[i].t, "HP");
                break;
            case hMediana:
                strcpy(V[i].t, "HM");
                break;
            case hAleatoria:
                strcpy(V[i].t, "HA");
                break;
            default:
                break;
        } 
    }
}

void trocar(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int V[], int inicio, int fim, int* cont, int t)
{
    (*cont)++;
    
    if (inicio < fim)   //Caso base: se inicio = fim, vetor é unitário e já está ordenado.
    {
        int pivo;
        
        if (t == pMediana || t == hMediana)
            mediana(V, inicio, fim, cont, t);
        else if (t == pAleatoria || t == hAleatoria)
            aleatorio(V, inicio, fim, cont, t);
            
        if (t == pPadrao || t == pMediana || t == pAleatoria)
        {
            pivo = particionarPadrao(V, inicio, fim, cont);
            quicksort(V, inicio, pivo - 1, cont, t);
            quicksort(V, pivo + 1, fim, cont, t);
        }
        else if (t == hPadrao || t == hMediana || t == hAleatoria)
        {
            pivo = particionarHoare(V, inicio, fim, cont);
            quicksort(V, inicio, pivo, cont, t);
            quicksort(V, pivo + 1, fim, cont, t);
        }
    }
}

void aleatorio(int V[], int inicio, int fim, int* cont, int t)
{
    int i = inicio + abs(V[inicio]) % (fim - inicio + 1);
    
    if (t == pAleatoria)
        trocar(&V[i], &V[fim]);
    else
        trocar(&V[i], &V[inicio]);
    
    (*cont)++;
}

void mediana(int V[], int inicio, int fim, int* cont, int t)
{
    int n = (fim - inicio) + 1;
    int a = (n/4) + inicio;
    int b = (n/2) + inicio;
    int c = (3*n)/4 + inicio;
    
    int M[] = {V[a], V[b], V[c]};
    ordenar(M, 3);
    
    if (t == pMediana)
    {
        if (M[1] == V[a])
            trocar(&V[a], &V[fim]);
        else if (M[1] == V[b])
            trocar(&V[b], &V[fim]);
        else
            trocar(&V[c], &V[fim]);
    }
    else
    {
        if (M[1] == V[a])
            trocar(&V[a], &V[inicio]);
        else if (M[1] == V[b])
            trocar(&V[b], &V[inicio]);
        else
            trocar(&V[c], &V[inicio]);
    }
    
    (*cont)++;
}

void ordenar(int V[], int n)
{
    int i, j;
    for (i = 1; i < n; i++)                       //Começe a partir do segundo elemento
    {
        for(j = i; j > 0 && V[j - 1] > V[j]; j--)       //Para cada elemento, varre o vetor da direita p/ esquerda
            trocar(&V[j], &V[j - 1]);                   //Compare cada elemento com o anterior; se o da esquerda for maior q da direita, troque
    }
}

void ordenarCont(tCont V[], int n)
{
    int i, j;
    for (i = 1; i < n; i++)                       //Começe a partir do segundo elemento
    {
        //Para cada elemento, varre o vetor da direita p/ esquerda
        for(j = i; j > 0 && V[j - 1].n > V[j].n; j--)   //Compare cada elemento com o anterior; se o da esquerda for maior q da direita, troque
        {
            tCont temp = V[j-1];
            V[j-1] = V[j];
            V[j] = temp;
        }
    }
}

int particionarPadrao(int V[], int inicio, int fim, int* cont)
{
    int pivo = V[fim];              //O valor do pivô é o valor encontrado na última  posição
    int i = inicio - 1, j;          //i é inicialmente negativo
    for(j = inicio; j < fim; j++)   //j passa pelo vetor, um por um
    {
        if(V[j] <= pivo)
        {
            i++;                    //i é o divisor entre menor e maior
                                    //Se V[j] for menor que pivô, passe ele para o ínice i, que é o marco entre maior e menor.
            trocar(&V[i], &V[j]);
            (*cont)++;
        }
    }
    trocar(&V[i + 1], &V[fim]); //Passar pivô para o meio, inicado por i
    (*cont)++;
    return i + 1;
}

int particionarHoare(int V[], int inicio, int fim, int* cont)
{
    int pivo = V[inicio];
    int i = inicio;
    int j = fim;
    while (i < j)
    {
        while (j > i && V[j] >= pivo) j--;
        while (i < j && V[i] < pivo) i++;
        if (i < j)
        {
            trocar(&V[i], &V[j]);
            (*cont)++;
        }
    }
    return j;
}