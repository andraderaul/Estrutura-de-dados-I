#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int flag=0;// flag para busca
int flagr=0; // flag para rotação
FILE * output;

    typedef struct dic{
        int fb;
        int qtdsin;
        char palavra[60];
        char sinonimos[10][60];
        struct dic *pai;
        struct dic *esquerda;
        struct dic *direita;
    }dic;

    typedef struct praiz{
        dic *ppai;
    }praiz;

    int atualizar_pai(dic *pultimo,praiz *raiz){
        if(pultimo->pai==NULL){
            raiz->ppai=pultimo;
             return 1;
         }
        atualizar_pai(pultimo->pai,raiz);
    return 0;
    }

    int avl_height ( dic *node ) {

    int esq, dir;

    if ( node == NULL ) return -1;

    esq = avl_height ( node->esquerda );
    dir = avl_height ( node->direita );

    if ( esq > dir )
        return esq + 1;
    else
        return dir + 1;
}

    void iniciar(praiz *arv){
        arv->ppai=NULL;
    }

    int fb(dic *upai,praiz *arv);

// TODAS ESSAS FUNÇÕES TEM QUE RECERE O PONTEIRO PARA A RAIZ, POIS EM CADA ROTAÇÃO TEM QUE ATUALIZAR O PAI
    void rotacao_esq(dic* raiz,praiz *arv){
   dic * eixo = raiz->direita;
   // raiz recebe o eixo como pai, e o eixo recebe como pai o pai de raiz
    eixo->pai=raiz->pai;
      if(raiz->pai!=NULL){
        if(flagr==0){// se a rotação for simples
        (raiz->pai)->direita=eixo;
        }
        if(flagr==1){// se a rotação for dupla
         (raiz->pai)->esquerda=eixo;
        }

        flagr=0;
    }
    raiz->pai=eixo;

    //
    raiz->direita=eixo->esquerda;
    eixo->esquerda=raiz;
    raiz=eixo;
    atualizar_pai(raiz->esquerda,arv);
    fb(raiz->esquerda,arv);

 }

    void rotacao_dir(dic* raiz,praiz *arv){
    dic * eixo = raiz->esquerda;
    // raiz recebe o eixo como pai, e o eixo recebe como pai o pai de raiz
    eixo->pai=raiz->pai;

    if(raiz->pai!=NULL){

        if(flagr==0){ // se a rotação for simples
        (raiz->pai)->esquerda=eixo;

        }
        if(flagr==1){ // se a rotação for dupla
         (raiz->pai)->direita=eixo;

        }

    }
    raiz->pai=eixo;
        //
    raiz->esquerda=eixo->direita;
    eixo->direita=raiz;
    raiz=eixo;
   // printf("%s<- %s -> %s",raiz->esquerda->palavra, raiz->palavra,raiz->direita->palavra);
   atualizar_pai(raiz->direita,arv);
   fb(raiz->direita,arv);

 flagr=0;
 }

    void rotacao_esq_dir(dic* raiz,praiz *arv) {
        flagr=1;
        rotacao_esq(raiz->esquerda,arv);
        //rotacao_dir(raiz,arv);

    }

    void rotacao_dir_esq(dic* raiz,praiz *arv) {
        flagr=1;

        rotacao_dir(raiz->direita,arv);
        //rotacao_esq(raiz,arv);

    }

    int fb(dic *upai,praiz *arv){
        while(upai!=NULL){
            upai->fb = avl_height ( upai->direita ) - avl_height ( upai->esquerda); // calculo
            //ROTAÇÃO ESQUERDA
            if(upai->fb==2 && upai->direita->fb==1){
                 // printf("entrou esq \n");
            rotacao_esq(upai,arv);
            break;
            }
            //ROTAÇÃO DIREITA ESQUERDA
            if(upai->fb==2 && upai->direita->fb==-1){
                //printf("entrou  dir esq\n");
            rotacao_dir_esq(upai,arv);
            break;
            }
            //ROTAÇÃO DIREITA
            if(upai->fb==-2 && upai->esquerda->fb==-1){
                //printf("entrou dir \n");
            rotacao_dir(upai,arv);
            break;
            }
            //ROTAÇÃO ESQUERDA DIREITA
            if(upai->fb==-2 && upai->esquerda->fb==1){
                //printf("entrou esq dir\n");
            rotacao_esq_dir(upai,arv);
            break;
            }

            upai=upai->pai;
        }
    return 0;
    }

  // ATÉ AQUI
    void inserir(praiz *arv, char palavra[60],char sino[10][60],int qtd){ // inserção ok
        int i=0;
       // crio novo
        dic *newnome;
        newnome = (dic*)malloc(sizeof(dic)); // aloco
        //printf("inseriu\n");
        //caracteristicas atualizadas
        strcpy(newnome->palavra,palavra);
        newnome->qtdsin=qtd;
        newnome->fb=0;
        for(i=0;i<qtd;i++){
         strcpy(newnome->sinonimos[i],sino[i]);
        }
        if(arv->ppai == NULL){ // se meu inicio for null( não existe arvore ainda

        arv->ppai=&(*newnome);
        //posições
        newnome->esquerda = NULL; // suas posiçoes recebem null
        newnome->direita= NULL;
        newnome->pai=NULL;
     }else{ // se não for vazia
        int cmp;
        dic *aux=&(*arv->ppai);
        while (aux!= NULL) {

        cmp = strcmp(aux->palavra,palavra);
         if(cmp>0){// se o nome da arvore for maior que o entrege p/ verificar // nome menor que o da arvore
            if(aux->esquerda==NULL){// a posição a esquerda esta vazia?
                newnome->esquerda = NULL; // suas posiçoes recebem null
                newnome->direita= NULL;
                newnome->pai=aux;
                aux->esquerda= newnome;
                break;
            }else{ //se estiver ocupado
                aux = aux->esquerda; // arvore vai pra esquerda
            }
        }
        if(cmp<=0){ // se o nome da arvore for menor que o entrege p/ verificar // nome maior que o da arvore
            if(aux->direita==NULL){// a posição a esquerda esta vazia?
                newnome->esquerda = NULL; // suas posiçoes recebem null
                newnome->direita= NULL;
                newnome->pai=aux;
                aux->direita = newnome;
                break;
                }else{  //se estiver ocupado
                aux = aux->direita; // arvore caminha para direita
                }
            }
        } // fim while

    //fb(aux,arv);
    //printf("passou fb\n");
    //atualizar_pai(aux,arv); // atualiza o primeiro pai;


    } //fim else
}

    void buscarIGUAL(dic *arvore, char palavra[60]){  // ta pronto
    int cmp;
    int i=0;
    flag=0;
    while (arvore!= NULL) {
    cmp = strcmp(arvore->palavra,palavra);

    if(cmp==0){ // quando for igual retorna o nome do maluco
        flag = 1;
        fprintf(output,"%s:\n",arvore->palavra);
        fprintf(output,"[");
            for(i=0;i<arvore->qtdsin;i++){
                if(i==(arvore->qtdsin-1)){
                    fprintf(output,"%s",arvore->sinonimos[i]);
                }else{
                    fprintf(output,"%s, ",arvore->sinonimos[i]);
                }

            }
            fprintf(output,"]\n");
            break;
    }else{
        if (cmp>0){// se o nome da arvore for maior que o entrege p/ verificar // nome menor que o da arvore
             fprintf(output,"%s->",arvore->palavra);
            arvore = arvore->esquerda; // arvore vai pra esquerda
                   }else{
           if(cmp<0){ // se o nome da arvore for menor que o entrege p/ verificar // nome maior que o da arvore
            fprintf(output,"%s->",arvore->palavra);
            arvore = arvore->direita; // arvore caminha para direita
        }

        }

    }//fim else

    } // fim while
    if(flag==0){
    fprintf(output,"?:\n");
    fprintf(output,"[-]\n");

    }

    flag=0;
    }

    void exibirPreOrdem(dic *pRaiz){ // não faz parte do programa, só a nivel de teste
       // printf("%s<- %s -> %s\n ",pRaiz->esquerda->palavra, pRaiz->palavra,pRaiz->direita->palavra);
        if(pRaiz != NULL){
            exibirPreOrdem(pRaiz->esquerda);
            printf("\n %s %d ",pRaiz->palavra,pRaiz->fb);
            exibirPreOrdem(pRaiz->direita);
        }
    }

    int main(int argc, char* argv[]){
    printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);

    praiz arv;
    iniciar(&arv);


    int i=0,j=0,tadd,qtdp,tbusca;
    char plraiz[60];
    char sino[10][60];
    char pbusca[60];


    FILE * input = fopen(argv[1],"r");
    output = fopen(argv[2],"w");
    fscanf(input,"%d ",&tadd);

    while(i<tadd){


   fscanf(input,"%s",plraiz);
   fscanf(input,"%d",&qtdp);


   while(j<qtdp){
    fscanf(input,"%s",sino[j]);


   j++;
   }
inserir(&arv,plraiz,sino,qtdp);
j=0;
i++;
}
fscanf(input,"%d",&tbusca);
i=0;
//exibirPreOrdem(arv.ppai);
//printf("\n%s",arv.ppai->palavra);
//printf("\n");

while(i<tbusca){
fscanf(input,"%s",pbusca);
buscarIGUAL(arv.ppai,pbusca);
i++;
}
//printf("\n");

//buscarIGUAL(arv.ppai,"cabalho");
fclose(input);
fclose(output);

return 0;
}
