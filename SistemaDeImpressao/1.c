#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tDoc {
    char nome[51];
    int pgs;
} tDoc;

typedef struct tDocPilha {
    tDoc doc;
    struct tDocPilha *prox;
} tDocPilha;

typedef struct tDocFila {
    tDoc doc;
    struct tDocFila *prox;
} tDocFila;

typedef struct tImp {
    char nome[51];
    tDoc doc;
    int x;
    struct tImp *prox;
    tDocPilha *pilha;
} tImp;

typedef struct tPilha {
    tDocPilha *topo;
    int total;
} tPilha;

typedef struct tFila {
    tDocFila *inicial;
    tDocFila *final;
} tFila;

typedef struct tLista {
    tImp *inicial;
    tImp *final;
} tLista;

tLista lista;
tFila fila;
tPilha pilha;

void criarLista(FILE* input, int nImp);
void criarFila(FILE* input, int nDocs);
void executarImpressao(FILE* output);
int chamarDoc(FILE* output, tImp *atual);
int liberarImp(tImp *atual);
void empilharLocal(FILE* output, tImp* atual);
void empilharGlobal(tImp* atual);
void imprimirPilha(FILE* output);
void liberarPilhaGlobal(void);
void liberarPilhaLocal(tImp *atual);

int main(int argc, char* argv[]) {

    //ABRIR ARQUIVOS
    FILE* input = fopen(argv[1],"r");
    FILE* output = fopen(argv[2],"w");
    
    if (input == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    //CRIAR LISTA DE IMPRESSORAS
    int nImp;
    fscanf(input, "%i", &nImp);
    criarLista(input, nImp);
    
    //CRIAR FILA DE DOCUMENTOS
    int nDocs;
    fscanf(input, "%i", &nDocs);
    criarFila(input, nDocs);
    
    //CRIAR PILHA GLOBAL
    pilha.topo = NULL;
    
    executarImpressao(output);
    imprimirPilha(output);
    liberarPilhaGlobal();
    
    fclose(input);
    fclose(output);
    return 0;
}

void executarImpressao(FILE* output) {
    
    tImp *atual = lista.inicial;
    while (1) {
    INICIO:
        if (atual -> x == -1 || atual -> x == 0) { //Se a impressora estiver disponível.
            if (atual -> x == 0) //Se a impressora estiver disponível porque um documento acabou de ser impresso.
                empilharGlobal(atual);
            if (chamarDoc(output, atual)) { //Se não houver mais documentos na fila.
                if (liberarImp(atual)) //Se não houver mais impressoras trabalhando.
                    return;
                atual = atual -> prox;
                goto INICIO;
            }
        }
        atual -> x--;
        atual = atual -> prox;
    }
}

void empilharGlobal(tImp* atual) {
    //Caso do primeiro elemento.
    if (pilha.topo == NULL) {
        pilha.topo = (tDocPilha*)malloc(sizeof(tDocPilha));
        pilha.topo -> doc = atual -> doc;
        pilha.topo -> prox = NULL;
        pilha.total = pilha.topo -> doc.pgs;
    }
    else {
        tDocPilha* temp = pilha.topo;
        pilha.topo = (tDocPilha*)malloc(sizeof(tDocPilha));
        pilha.topo -> doc = atual -> doc;
        pilha.topo -> prox = temp;
        pilha.total += pilha.topo -> doc.pgs;
        temp = NULL;
    }
}

void imprimirPilha(FILE* output) {
    tDocPilha* imprimir = pilha.topo;
    fprintf(output, "%ip\n", pilha.total);
    while (imprimir != NULL) {
        fprintf(output, "%s-%ip\n", imprimir -> doc.nome, imprimir -> doc.pgs);
        imprimir = imprimir -> prox;
    };
}

void empilharLocal(FILE* output, tImp* atual) {
    
    if (atual -> pilha == NULL) {//Caso do primeiro elemento.
        atual -> pilha = (tDocPilha*)malloc(sizeof(tDocPilha));
        atual -> pilha -> doc = atual -> doc;
        atual -> pilha -> prox = NULL;
    }
    else { //O resto dos elementos.
        tDocPilha* temp = atual -> pilha;
        atual -> pilha = (tDocPilha*)malloc(sizeof(tDocPilha));
        atual -> pilha -> doc = atual -> doc;
        atual -> pilha -> prox = temp;
        temp = NULL;
    }
    
    //Imprimir o nome da impressora e os documentos que estão na pilha,
    //toda vez que um novo documento é carregado na impressora.
    tDocPilha* imprimir = atual -> pilha;
    fprintf(output, "[%s] ", atual -> nome);
    while (imprimir != NULL) {
        fprintf(output, "%s-%ip", imprimir -> doc.nome, imprimir -> doc.pgs);
        if (imprimir -> prox == NULL)
            break;
        fprintf(output, ", ");
        imprimir = imprimir -> prox;
    };
    fprintf(output, "\n");
}

int liberarImp(tImp *atual) {
    //Se essa for a única impressora da lista.
    if (lista.inicial == lista.final)
    {
        lista.final = NULL;
        lista.inicial = NULL;
        liberarPilhaLocal(atual);
        free(atual);
        return 1; //Retorno especial que indica que todas as impressões já foram feitas.
    }
    else {
        //Se essa impressora for a primeira da lista.
        if (atual == lista.inicial) {
            lista.inicial = lista.inicial -> prox;
            lista.final -> prox = lista.inicial;
        }
        else {
            //Se essa não for a única nem a primeira impressora, vc precisa da anterior. Procure.
            tImp* ant = lista.inicial;
            while (ant -> prox != atual)
                ant = ant -> prox;
            
            //Se essa impressora for a última da lista.
            if (atual == lista.final) {
                lista.final = ant;
                lista.final -> prox = lista.inicial;
            }
            else
                ant -> prox = atual -> prox;
        }
        liberarPilhaLocal(atual);
        free(atual);
        atual = NULL;
        return 0; //Retorno de sucesso.
    }
}

void liberarPilhaGlobal(void) {
    tDocPilha *temp;
    while (pilha.topo != NULL) {
        temp = pilha.topo;
        pilha.topo = pilha.topo -> prox;
        free(temp);
    }
}

void liberarPilhaLocal(tImp *atual) {
    tDocPilha *temp;
    while (atual -> pilha != NULL) {
        temp = atual -> pilha;
        atual -> pilha = atual -> pilha -> prox;
        free(temp);
    }
}

int chamarDoc(FILE* output, tImp *atual) {
    if (fila.inicial == NULL)
        return 1; //Retorno de erro.
    else
    {
        //Load doc into printer
        atual -> doc = fila.inicial -> doc;
        atual -> x = atual -> doc.pgs;
        
        //Remove doc from queue
        tDocFila *temp = fila.inicial;
        fila.inicial = fila.inicial -> prox;
        free(temp);
        temp = NULL;
        empilharLocal(output, atual);
        return 0; //Retorno de sucesso.
    }
}

void criarFila(FILE* input, int nDocs) {
    
    //Criar primeiro elemento.
    fila.inicial = (tDocFila*)malloc(sizeof(tDocFila));
    fscanf(input, "%s %i", fila.inicial -> doc.nome, &fila.inicial -> doc.pgs);
    fila.final = fila.inicial;
    fila.final -> prox = NULL;
    
    //Criar todos os outros elementos - loop de nDocs-1.
    for (int i = 0; i < (nDocs-1); i++) {
        fila.final -> prox = (tDocFila*)malloc(sizeof(tDocFila));
        fila.final = fila.final -> prox;
        fscanf(input, "%s %i", fila.final -> doc.nome, &fila.final -> doc.pgs);
        fila.final -> prox = NULL;
    }
    
    //Ponteiro para o final da fila não será mais usado.
    fila.final = NULL;
}

void criarLista(FILE* input, int nImp) {
    
    //Criar primeiro elemento.
    lista.inicial = (tImp*)malloc(sizeof(tImp));
    fscanf(input, "%s", lista.inicial -> nome);
    lista.final = lista.inicial;
    lista.final -> x = -1;
    lista.final -> prox = lista.inicial;
    lista.final -> pilha = NULL;
    
    //Criar todos os outros elementos - loop de nImp-1.
    for (int i = 0; i < (nImp-1); i++) {
        lista.final -> prox = (tImp*)malloc(sizeof(tImp));
        lista.final = lista.final -> prox;
        fscanf(input, "%s", lista.final -> nome);
        lista.final -> x = -1;
        lista.final -> prox = lista.inicial;
        lista.final -> pilha = NULL;
    }
}