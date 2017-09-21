#include <stdio.h>
#include <stdlib.h>

typedef struct tPacote {
    unsigned int N;
    unsigned int totBytes;
    char** bytes;
} tPacote;

typedef struct vPacote {
    unsigned int n;
    struct tPacote* p;
} vPacote;

int lerPacotes(FILE* input, unsigned int TRIGGER, tPacote* P, unsigned int* n);
//void imprimirVetor(struct tPacote* vPacote, unsigned int nPacote);
void imprimirOrdenado(FILE* output, tPacote* P, unsigned int* n, unsigned int* CONT_PAC, unsigned int* CONT_IMP);
void imprimirPacote(FILE* output, tPacote* P, unsigned int* n);
void removerPacote(tPacote* P, unsigned int* n);

void heapify (struct tPacote* V, unsigned int T, unsigned int i);
void troca (struct tPacote* V, unsigned int P, unsigned int i);
int pai (int i);
int direito (int i);
int esquerdo (int i);
void ordenarPacotes(struct tPacote* vPacotes, unsigned int nPacotes);

int main(int argc, char* argv[])
{
    //------------------//
    // TRATAR ARQUIVOS
    //------------------//
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    
    if (input == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    //------------------//
    // EXECUTAR
    //------------------//
    
    //Declarar contadores
    unsigned int CONT_PAC = 0, CONT_IMP = 0, TOTAL = 0, TRIGGER = 0;
    unsigned int EXISTE_PACOTE = 1;
    fscanf(input, "%i %i", &TOTAL, &TRIGGER);
    vPacote vPacote; vPacote.n = 0; vPacote.p = (tPacote*)malloc(sizeof(tPacote) * TOTAL);
    
    while (EXISTE_PACOTE)
    {
        EXISTE_PACOTE = lerPacotes(input, TRIGGER, vPacote.p, &vPacote.n);
        ordenarPacotes(vPacote.p, vPacote.n);
        imprimirOrdenado(output, vPacote.p, &vPacote.n, &CONT_PAC, &CONT_IMP);
    }
    
    fclose(input);
    fclose(output);
    return 0;
    
}

void imprimirOrdenado(FILE* output, tPacote* P, unsigned int* n, unsigned int* CONT_PAC, unsigned int* CONT_IMP)
{
    if (P[0].N == *CONT_PAC)
    {
        fprintf(output, "[%i] ", *CONT_IMP);
        
        while (P[0].N == *CONT_PAC)
        {
            imprimirPacote(output, &P[0], CONT_PAC);
            removerPacote(P, n);
            heapify(P, *n, 0);
        }
        
        fprintf(output, "\n");
        (*CONT_IMP)++;
    }
}

void imprimirPacote(FILE* output, tPacote* P, unsigned int* CONT)
{
    for (int i = 0; i < P->totBytes; i++)
        fprintf(output, "%s ", P->bytes[i]);
    (*CONT)++;
}

void removerPacote(tPacote* P, unsigned int* n)
{
    unsigned int ULT = *n-1;
    P[0] = P[ULT];
    (*n)--;
}

int lerPacotes(FILE* input, unsigned int TRIGGER, tPacote* P, unsigned int* n)
{
    int x;
    for (int i = 0; i < TRIGGER; i++)
    {
        x = *n;
        
        if (fscanf(input, "%u %u", &P[x].N, &P[x].totBytes) == EOF)         //Ler N. do pacote e n. de bytes que o pacote contém.
            return 0;                                                       //Se acabar arquivo, a leitura falha. EXISTE_PACOTE = 0;
        
        P[x].bytes = (char**)malloc(sizeof(char*) * P[x].totBytes);         //Alocar vetor de bytes dentro do pacote.
        
        for (int k = 0; k < P[x].totBytes; k++)                             //Alocar espaço para bytes e ler cada um.
        {
            P[x].bytes[k] = (char*)malloc(20);
            fscanf(input, "%s", P[x].bytes[k]);
        }
        
        (*n)++;
    }
    
    return 1;
}

void ordenarPacotes(struct tPacote* vPacotes, unsigned int nPacotes)
{
    int T = nPacotes-2;
    int N = (T/2);                      //Indíce do último nó com filhos.
    for (int i = N; i >= 0; i--)        //Começa com o último nó com filhos e decresce até a raiz.
        heapify(vPacotes, nPacotes, i);
}

int esquerdo (int i) {
    return (2*i) + 1;
}

int direito (int i) {
    return (2*i) + 2;
}

int pai (int i) {
    return (i-1)/2;
}

void troca (struct tPacote* V, unsigned int P, unsigned int i)
{
    tPacote temp = V[i];
    V[i] = V[P];
    V[P] = temp;
}

void heapify (struct tPacote* V, unsigned int T, unsigned int i)
{
    int P = i;
    int E = esquerdo(i);
    int D = direito(i);
    
    if ((E < T) && (V[E].N < V[P].N)) P = E;
    if ((D < T) && (V[D].N < V[P].N)) P = D;
    if (P != i)
    {
        troca(V, P, i);
        heapify(V, T, P);
    }
}