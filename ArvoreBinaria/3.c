#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cont=0;
FILE* output;

    typedef struct no{// estrutura da arvore // ok
        int ordem;
        char status[3];
        char nome[60];
        int byte;
        struct no *esquerda;
        struct no *direita;
    }no;

    typedef struct praiz{
        no *ppai;
    }praiz;

    void iniciar(praiz *arv){
        arv->ppai=NULL;
    }

    no *buscarIGUAL(no *arvore, char nome[60]){
    int cmp;
        while (arvore!= NULL) {
            cmp = strcmp(arvore->nome,nome);
       if (cmp>0){// se o nome da arvore for maior que o entrege p/ verificar // nome menor que o da arvore
         arvore = arvore->esquerda; // arvore vai pra esquerda
       }
       if(cmp<0){ // se o nome da arvore for menor que o entrege p/ verificar // nome maior que o da arvore
        arvore = arvore->direita; // arvore caminha para direita
       }
       if(cmp==0){ // quando for igual retorna o nome do maluco

       return &(*arvore); // retorna se encontrou // perguntar a alguem se quebra o laço
       }
    }
    return NULL;
    }

    void inserir(praiz *arv, char nome[60],char status[3],int byte,int cont){

        // crio novo ,
        no *newnome;
        newnome = (no*)malloc(sizeof(no)); // aloco
        //caracteristicas atualizadas
        strcpy(newnome->nome,nome);
        strcpy(newnome->status,status);
        newnome->byte=byte;
        newnome->ordem=cont;

     if(arv->ppai == NULL && cont==0){ // se meu inicio for null( não existe arvore ainda
        arv->ppai=newnome;
        //posições
        newnome->esquerda = NULL; // suas posiçoes recebem null
        newnome->direita= NULL;

     }else{ // se não for vazia

      if(buscarIGUAL(arv->ppai,nome)==NULL){ // se o nome que eu to procurando não foi encontrado
        //printf("aqui não da merda");
        int cmp;
        no *aux=&(*arv->ppai);
        while (aux!= NULL) {
        cmp = strcmp(aux->nome,nome);
        if (cmp>0){// se o nome da arvore for maior que o entrege p/ verificar // nome menor que o da arvore
            if(aux->esquerda==NULL){// a posição a esquerda esta vazia?
                newnome->esquerda = NULL; // suas posiçoes recebem null
                newnome->direita= NULL;
                aux->esquerda= newnome;
                break;
                }else{ //se estiver ocupado
                aux = aux->esquerda; // arvore vai pra esquerda
                }
       }
       if(cmp<0){ // se o nome da arvore for menor que o entrege p/ verificar // nome maior que o da arvore
          if(aux->direita==NULL){// a posição a esquerda esta vazia?
                newnome->esquerda = NULL; // suas posiçoes recebem null
                newnome->direita= NULL;
                aux->direita = newnome;

                break;
                }else{  //se estiver ocupado
                aux = aux->direita; // arvore caminha para direita
                }
       }
    }
      }else{ // se eu encontrei alguem com o mesmo nome;
        no *aux=buscarIGUAL(arv->ppai,nome); //salvo o resultado em aux
            if(strcmp(aux->status,"rw")==0) { // verifico se o status for sw , se for atualiza as seguintes caracteristicas

                aux->byte=byte;
                aux->ordem=cont;
               strcpy(aux->status,status);
            }
        }
    }
}

    void exibirEmOrdem(no *pRaiz){
        if(pRaiz != NULL){
            exibirEmOrdem(pRaiz->esquerda);
                        if(pRaiz->byte>1){
             fprintf(output,"\n%d %s %s %d bytes",pRaiz->ordem,pRaiz->nome,pRaiz->status,pRaiz->byte);
            }else{
            fprintf(output,"\n%d %s %s %d byte",pRaiz->ordem,pRaiz->nome,pRaiz->status,pRaiz->byte);
            }
            exibirEmOrdem(pRaiz->direita);
        }
    }

    void exibirPreOrdem(no *pRaiz){
    if(pRaiz != NULL){
            if(pRaiz->byte>1){
             fprintf(output,"\n%d %s %s %d bytes",pRaiz->ordem,pRaiz->nome,pRaiz->status,pRaiz->byte);
            }else{
            fprintf(output,"\n%d %s %s %d byte",pRaiz->ordem,pRaiz->nome,pRaiz->status,pRaiz->byte);
            }

        exibirPreOrdem(pRaiz->esquerda);
        exibirPreOrdem(pRaiz->direita);
    }
}

    void exibirPosOrdem(no *pRaiz){
    if(pRaiz != NULL){
        exibirPosOrdem(pRaiz->esquerda);
        exibirPosOrdem(pRaiz->direita);
            if(pRaiz->byte>1){
             fprintf(output,"\n%d %s %s %d bytes",pRaiz->ordem,pRaiz->nome,pRaiz->status,pRaiz->byte);
            }else{
            fprintf(output,"\n%d %s %s %d byte",pRaiz->ordem,pRaiz->nome,pRaiz->status,pRaiz->byte);
            }
    }
}

   int main(){

    praiz arv;
    iniciar(&arv);

    char status[3],nome[60];
    int byte;
    int qtdp;
    FILE* input=fopen("input.txt","r"); // abre arquivo
    output=fopen("output.txt","w"); //salva

    fscanf(input,"%d ",&qtdp);

    while(fscanf(input,"%s %s %d",nome,status,&byte)!=EOF ){
       inserir(&arv,nome,status,byte,cont);
       cont++;
       }
    fprintf(output,"EPD:");
    exibirEmOrdem(arv.ppai);
    fprintf(output,"\nPED:");
    exibirPreOrdem(arv.ppai);
    fprintf(output,"\nEDP:");
    exibirPosOrdem(arv.ppai);


   // printf("\nFACIL DEMAIS");

   return 0;
   }
