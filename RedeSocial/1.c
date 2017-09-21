#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//GLOBAL VARIABLES
typedef struct elemento {
    char nome[51];
    struct elemento *prox;
    struct elemento *ant;
} elemento;

typedef struct tLista {
    elemento *inicio;
    elemento *ultimo;
} tLista;

//PROTOTYPES
void inserir(tLista *lista, char nome[51], FILE* output);
void imprimir(tLista *lista, char nome[51], FILE* output);
void remover(tLista *lista, char nome[51], FILE* output);
void limpar(tLista *lista);

int main(int argc, char* argv[]) {
    
    FILE* input = fopen(argv[1],"r");
    FILE* output = fopen(argv[2],"w");
    
    if (input == NULL)
    {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }
    else
        printf("Arquivo aberto com sucesso!\n");
    
    tLista Lista;
    tLista *lista = &Lista;
    lista -> inicio = NULL;
    lista -> ultimo = NULL;
    
    char com[10];
    char nome[51];
    int i = 0;
    char c = '0';
    
    while (fscanf(input, "%s%*c", com) != EOF)
    {
        //Read full name.
        i = 0;
        c = '0';
        while ((fscanf(input, "%c", &c) != EOF) && (c != '\n'))
        {
            nome[i] = c;
            i++;
        }
        nome[i] = 0; //Terminate string manually.
        
        if (strcmp(com, "ADD") == 0)
            inserir(lista, nome, output);
        else if (strcmp(com, "SHOW") == 0)
            imprimir(lista, nome, output);
        else if (strcmp(com, "REMOVE") == 0)
            remover(lista, nome, output);
        else {
            //printf("Erro ao interpretar linha!\n");
            fprintf(output,"Erro ao interpretar linha!\n");
            exit(1);
        }
        
    }
    
    fclose(input);
    fclose(output);
    limpar(lista);
    input = NULL;
    output = NULL;
    lista = NULL;
    
    return 0;
}

void limpar(tLista *lista) {
    
    elemento* temp = lista -> inicio;
    lista -> ultimo -> prox = NULL;
    
    while (lista->inicio != NULL) {
        lista -> inicio = lista -> inicio -> prox;
        free(temp);
        temp = lista -> inicio;
    };
    
    lista -> inicio = NULL;
    lista -> ultimo = NULL;
}

void inserir(tLista *lista, char nome[50], FILE* output) {
    
    if (lista -> inicio == NULL) //Caso especial da lista estar vazia. Insira nome e saia da função.
    {
        lista -> inicio = (elemento*)malloc(sizeof(elemento));
        if (lista -> inicio == NULL)
            exit(1);
        strcpy(lista -> inicio -> nome, nome);
        lista -> inicio -> ant = lista -> inicio;
        lista -> inicio -> prox = lista -> inicio;
        lista -> ultimo = lista -> inicio;
        //printf("[%s] ADD-OK\n", nome);
        fprintf(output, "[%s] ADD-OK\n", nome);
        return;
    }
    
    /** Passar por toda a lista ->  Se encontrar o mesmo nome
     que vc ta tentando inserir, imprima mensagem de erro e saia da função.
     Se a lista acabar e vc não achar um nome idêntico, insira o nome novo. **/
    
    elemento *atual = NULL;
    atual = lista -> inicio;
    do
    {
        if (strcmp(atual -> nome, nome) == 0) {
            fprintf(output, "[%s] ADD-ERROR\n", nome);
            //printf("[%s] ADD-ERROR\n", nome);
            return;
        }
        else
            atual = atual -> prox;
    } while (atual != lista -> inicio);
    
    
    lista -> ultimo -> prox = (elemento*)malloc(sizeof(elemento));
    if (lista -> ultimo -> prox == NULL)
        exit(1);
    lista -> ultimo -> prox -> ant = lista -> ultimo;
    lista -> ultimo = lista -> ultimo -> prox;
    strcpy(lista -> ultimo -> nome, nome);
    lista -> ultimo -> prox = lista -> inicio;
    lista -> inicio -> ant = lista -> ultimo;
    fprintf(output, "[%s] ADD-OK\n", nome);
    //printf("[%s] ADD-OK\n", nome);
}

void imprimir(tLista *lista, char nome[50], FILE* output) {
    
    if (lista -> inicio != NULL) //Se a lista estiver vazia, erro!
    {
        elemento *atual = lista -> inicio;
        
        /** Passar por toda a lista -> Se achar nome, imprima e saia da função.
         Se não, imprima mensagem de erro. **/
        do {
            if (strcmp(atual -> nome, nome) == 0)
            {
                fprintf(output, "[%s]<-[%s]->[%s]\n", atual->ant->nome, atual->nome, atual->prox-> nome);
                //printf("[%s]<-[%s]->[%s]\n", atual->ant->nome, atual->nome, atual->prox-> nome);
                return;
            }
            else
                atual = atual -> prox;
        } while (atual != lista -> inicio);
    }
    
    fprintf(output, "[%s] SHOW-ERROR\n", nome);
    //printf("[%s] SHOW-ERROR\n", nome);
}

void remover(tLista *lista, char nome[50], FILE* output) {
    elemento *temp = NULL;
    elemento *atual = lista -> ultimo;
    
    /** Passar por toda a lista -> Se achar nome, remova e saia da função.
     Se não, imprima mensagem de erro. **/
    do
    {
        if (strcmp(atual -> prox -> nome, nome) == 0)
        {
            temp = atual -> prox; //Store item to be deleted in temp pointer.
            atual -> prox = temp -> prox; //Link previous and next items together.
            temp -> prox -> ant = atual; //Link previous and next items together.
            //printf("[%s] REMOVE-OK\n", nome);
            fprintf(output, "[%s] REMOVE-OK\n", nome);
            
            if (temp == lista -> inicio)
                lista -> inicio = lista -> inicio -> prox;
            if (temp == lista -> ultimo)
                lista -> ultimo = lista -> ultimo -> ant;
            
            free(temp);
            temp = NULL;
            atual = NULL;
            return;
        }
        else
            atual = atual -> prox;
        
    } while (atual -> prox != lista -> inicio);
    
    //printf("[%s] REMOVE-ERROR\n", nome);
    fprintf(output, "[%s] REMOVE-ERROR\n", nome);
}