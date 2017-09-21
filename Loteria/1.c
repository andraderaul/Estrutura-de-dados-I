#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

struct bilhete {
    uint64_t cod;
    unsigned int acertos;
};

struct bilheteFila {
    uint64_t cod;
    struct bilheteFila *prox;
};

struct key {
    uint64_t cod;
    unsigned int n[16];
    unsigned int acertos;
};

struct heap {
    struct bilhete *p;
    unsigned int tam;
};

struct fila {
    struct bilheteFila *ini;
    struct bilheteFila *ult;
    unsigned int faixa;
    unsigned int tam;
};

enum {
    nSorteados = 10,
    nApostas = 15,
    tMax = 1,
    tMin = 0,
};

//Manutenção da estrutura do heap.
unsigned int esquerdo (unsigned int i);
unsigned int direito (unsigned int i);
unsigned int pai (unsigned int i);
void troca (struct bilhete* V, unsigned int P, unsigned int i);
void heapifyMax (struct bilhete* V, unsigned int T, unsigned int i);
void heapifyMin (struct bilhete* V, unsigned int T, unsigned int i);

//Leitura da entreda.
void lerBilhete (FILE* input, struct key* key);
void contarAcertos (unsigned int* sorteados, struct key* key);
unsigned int busca(unsigned int valor, unsigned int* sorteados);
void inserirBilhete (struct key* key, struct heap* heap);
void construirHeap (struct heap* heap, unsigned int hTipo);

//Cálculo da ganhadores.
void calcularFaixa(struct fila* fila, struct heap* heap, unsigned int hTipo);
void procurarGanhadores(unsigned int REF, struct fila* fila, struct heap* heap, unsigned int hTipo);
void inserirFila(struct bilhete* bilhete, struct fila* fila);
void removerElemento(struct heap* heap, unsigned int hTipo);

//Etc.
void imprimir (struct heap* heap);
void imprimirResultado(FILE* output, struct fila* fila, unsigned int premio);
void freeFila (struct fila* fila);

int main(int argc, char* argv[]) {
    
    //***************************//
    // ABRIR ARQUIVO
    //***************************//
    
//    FILE* input = fopen("/Users/Aryella/Desktop/ED1/2_Unidade/Loteria/prof.loteria.input.txt","r");
//    FILE* output = fopen("/Users/Aryella/Desktop/ED1/2_Unidade/Loteria/me.output.txt","w");
    
    FILE* input = fopen(argv[1],"r");
    FILE* output = fopen(argv[2],"w");
    if (input == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    //***************************//
    // LEITURA DO PRÉMIO
    //***************************//
    
    unsigned int premio = 0, nBilhetes = 0;
    unsigned int* sorteados = malloc(nSorteados * sizeof(unsigned int));
    
    fscanf(input, "%u %u", &premio, &nBilhetes);
    
    for (int i = 0; i < nSorteados; i++)
        fscanf(input, "%u", &sorteados[i]);
    
    sorteados[nSorteados] = '\0';
    
    //***************************//
    // CRIAR HEAPS E PILHAS MÍN E MAX
    //***************************//
    
    struct heap* heapMax = (struct heap*)malloc(sizeof(struct heap));
    heapMax -> p = (struct bilhete*)malloc((nBilhetes+1)*sizeof(struct bilhete));
    heapMax -> tam = 0;
    
    struct heap* heapMin = (struct heap*)malloc(sizeof(struct heap));
    heapMin -> p = (struct bilhete*)malloc((nBilhetes+1)*sizeof(struct bilhete));
    heapMin -> tam = 0;
    
    struct fila* filaMin = (struct fila*)malloc(sizeof(struct fila));
    struct fila* filaMax = (struct fila*)malloc(sizeof(struct fila));
    filaMin -> ini = NULL; filaMax -> ini = NULL;
    filaMin -> tam = 0; filaMax -> tam = 0;
    
    //***************************//
    // LEITURA  DOS BILHETES
    //***************************//
    
    struct key* key = (struct key*)malloc(sizeof(struct key));
    
    for (int k = 0; k < nBilhetes; k++)
    {
        lerBilhete(input, key);
        contarAcertos(sorteados, key);
        inserirBilhete(key, heapMax);
        inserirBilhete(key, heapMin);
    }
    
    //***************************//
    // CALCULAR PRÉMIO
    //***************************//
    
    //MÁXIMO
    construirHeap(heapMax, tMax);
    calcularFaixa(filaMax, heapMax, tMax);
    imprimirResultado(output, filaMax, (premio/2));
    
    //MÍNIMO
    construirHeap(heapMin, tMin);
    calcularFaixa(filaMin, heapMin, tMin);
    imprimirResultado(output, filaMin, (premio/2));
    
    fclose(input);
    fclose(output);
    
    return 0;
}

void construirHeap (struct heap* heap, unsigned int hTipo)
{
    unsigned int T = (heap->tam); //Tamanho do vetor;
    unsigned int N = ((T-2)/2); //Indíce do último nó com filhos.
    struct bilhete* V = heap->p; //Vetor de bilhetes.
    
    //Começa com o último nó com filhos e decresce até a raiz.
    if (hTipo == tMax)
    {
        for (int i = N; i >= 0; i--)
            heapifyMax(V, T, i);
    }
    else
    {
        for (int i = N; i >= 0; i--)
            heapifyMin(V, T, i);
    }
}

void contarAcertos (unsigned int* sorteados, struct key* key) {
    unsigned int cont = 0;
    
    for (int i = 0; i < nApostas; i++) //Para cada número apostado...
        cont += busca(key -> n[i], sorteados); //Some o resultado (0 ou 1) ao contador.
    
    key -> acertos = cont;
}

unsigned int busca(unsigned int valor, unsigned int* sorteados) {
    int inf = 0;
    int sup = nSorteados-1;
    int i = (inf + sup)/2;
    
    while ((sorteados[i] != valor) && (inf <= sup))
    {
        if (sorteados[i] < valor)
            inf = i + 1;
        else
            sup = i - 1;
        
        i = (inf + sup)/2;
    }
    
    if (sorteados[i] == valor)
        return 1;
    else
        return 0;
}

void lerBilhete (FILE* input, struct key* key) {
    fscanf(input, "%" SCNx64, &key -> cod); //Ler código do bilhete em hexa.
    
    for (int i = 0; i < nApostas; i++) //Ler os números apostados em cada bilhete.
        fscanf(input, "%u", &key -> n[i]);
    
    key -> n[nApostas] = '\0'; //Terminar vetor de apostas.
}

unsigned int esquerdo (unsigned int i) {
    return (2*i) + 1;
}

unsigned int direito (unsigned int i) {
    return (2*i) + 2;
}

unsigned int pai (unsigned int i) {
    return (i-1)/2;
}

void troca (struct bilhete* V, unsigned int P, unsigned int i) {
    struct bilhete temp = V[i];
    V[i] = V[P];
    V[P] = temp;
}

void heapifyMax (struct bilhete* V, unsigned int T, unsigned int i) {
    unsigned int P = i;
    unsigned int E = esquerdo(i);
    unsigned int D = direito(i);
    
    if((E < T) && (V[E].acertos > V[P].acertos)) P = E;
    if((D < T) && (V[D].acertos > V[P].acertos)) P = D;
    if (P != i)
    {
        troca(V, P, i);
        heapifyMax(V, T, P);
    }
}

void heapifyMin (struct bilhete* V, unsigned int T, unsigned int i) {
    unsigned int P = i;
    unsigned int E = esquerdo(i);
    unsigned int D = direito(i);
    
    if((E < T) && (V[E].acertos < V[P].acertos)) P = E;
    if((D < T) && (V[D].acertos < V[P].acertos)) P = D;
    if (P != i)
    {
        troca(V, P, i);
        heapifyMin(V, T, P);
    }
}

void inserirBilhete (struct key* key, struct heap* heap) {
    unsigned int T = heap->tam;
    struct bilhete* V = heap->p;
    
    V[T].cod = key->cod;
    V[T].acertos = key->acertos;
    heap->tam++;
}

void inserirFila(struct bilhete* bilhete, struct fila* fila) {
    struct bilheteFila* novo = (struct bilheteFila*)malloc(sizeof(struct bilheteFila));
    if (novo == NULL) exit(1);
    
    if (fila -> ini == NULL)
        fila -> ini = novo;
    else
        fila -> ult -> prox = novo;
    
    fila -> ult = novo;
    novo -> cod = bilhete -> cod;
    novo -> prox = NULL;
    fila -> tam++;
}

void removerElemento(struct heap* heap, unsigned int hTipo) {
    unsigned int Ult = (heap->tam)-1;
    struct bilhete* V = heap->p;
    
    V[0] = V[Ult];
    heap->tam--;
    
    if (hTipo == tMax)
        heapifyMax(V, heap->tam, 0);
    else
        heapifyMin(V, heap->tam, 0);
}

void procurarGanhadores(unsigned int REF, struct fila* fila, struct heap* heap, unsigned int hTipo) {
    struct bilhete* bilhete = &(heap -> p[0]); //Renomear elemento da raiz.
    while (bilhete -> acertos == REF) //Verificar o elemento da raiz.
    {
        inserirFila(bilhete, fila); //Inserir na fila de ganhadores.
        removerElemento(heap, hTipo); //Remover ganhador atual e chamar o próximo para a raiz.
    }
}

void calcularFaixa(struct fila* fila, struct heap* heap, unsigned int hTipo) {
    unsigned int REF = heap -> p[0].acertos; //Número de acertos do bilhete do topo do heap vira a referência.
    fila -> faixa = REF; //A faixa de acerto dos ganhadores.
    
    procurarGanhadores(REF, fila, heap, hTipo);
}

void imprimirResultado(FILE* output, struct fila* fila, unsigned int premio) {
    //Imprimir ganhadores.
    if ((fila -> faixa) > 1)
        fprintf(output, "Faixa: %i acertos\n", fila -> faixa);
    else
        fprintf(output, "Faixa: %i acerto\n", fila -> faixa);
    
    struct bilheteFila* temp = fila -> ini;
    while (temp != NULL)
    {
        fprintf(output, "%016" PRIx64 "\n", temp -> cod);
        temp = temp -> prox;
    }
    
    //Calcular prêmio.
    unsigned int nGanhadores = fila -> tam;
    if (nGanhadores > 1)
    {
        unsigned int premioFinal = (premio/nGanhadores);
        fprintf(output, "%i ganhadores de R$%i\n", nGanhadores, premioFinal);
    }
    else
        fprintf(output, "1 ganhador de R$%i\n", premio);
    
    fprintf(output, "\n");
}