#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE * output;

typedef struct palavra{
    int prioridade;
    char codigo[20];
}palavra;

typedef struct Veiculo{
    struct palavra *cod;
    int tamanho;
}Veiculo;

void copiar(palavra * V1 , palavra *V2 ,  int n){
int i;
for (i=0 ; i<n ; i++){
    V1[i] = V2[i];
}
}

void intercalar(palavra * S, palavra *E, int ini, int meio, int fim) {
    int i = ini, j = meio + 1, k = ini;
    while(i <= meio && j <= fim) {
        if(E[i].prioridade < E[j].prioridade ) S[k++] = E[i++] ;
            else S[k++] = E[j++];
    }
    if(i > meio) copiar(&S[k], &E[j], fim - j + 1);
        else copiar(&S[k], &E[i], meio - i + 1);
            copiar(&E[ini], &S[ini], fim - ini + 1);

}

void mergesort(palavra *S, palavra *E, int ini, int fim) {
    int meio = ini + (fim - ini) / 2;
    if(ini < fim) {
        mergesort(S, E, ini, meio);
        mergesort(S, E, meio + 1, fim);
    }
    intercalar(S, E, ini, meio, fim);
}

void imprime(palavra *I , int n, int ind){
 int i;
 fprintf(output,"[V%d]",ind);
 for(i=0 ; i<n ; i++){
        fprintf(output," %s",I[i].codigo);

 }
fprintf(output,"\n");
}

int main(int argc, char* argv[]){

    // Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);

    int q_veiculo,capacidade,q_pacotes, i;
    char temp[20];
    int cont_capacidade,soma=0;
    int ind=0,j=0;
    int prioridade;
    palavra *aux;

    FILE *input = fopen (argv[1],"r");
    output = fopen(argv[2],"w");

    fscanf(input,"%d %d",&q_veiculo,&capacidade);
    Veiculo *frota = (Veiculo *) malloc ( sizeof (Veiculo )*(q_veiculo));

    fscanf(input,"%d",&q_pacotes);

    frota[ind].cod = (palavra *) malloc ( sizeof (palavra )*(capacidade));

    for(i=0 ; i<q_pacotes ; i++){
        fscanf(input,"%s %d",temp,&cont_capacidade);
        soma=soma+cont_capacidade;
        if(temp[0]=='E') prioridade = 1 ;
        if(temp[0]=='P') prioridade = 2 ;
        if(temp[0]=='X') prioridade = 3 ;

        if(soma<=capacidade){
            strcpy(frota[ind].cod[j].codigo,temp);
            frota[ind].cod[j].prioridade = prioridade ;
            j++;
            if(i == q_pacotes - 1 ){
                frota[ind].tamanho=j;
                aux =(palavra *) malloc ( sizeof (palavra )*(frota[ind].tamanho));
                mergesort(aux,frota[ind].cod,0,j-1);
                imprime(frota[ind].cod,frota[ind].tamanho,ind);
            }
        }else{
            frota[ind].tamanho=j;
            aux =(palavra *) malloc ( sizeof (palavra )*(frota[ind].tamanho));
            mergesort(aux,frota[ind].cod,0,j-1);
            imprime(frota[ind].cod,frota[ind].tamanho,ind);
            j=0;
            soma = cont_capacidade;
            ind++;

            if(ind >= q_veiculo){
             ind = 0 ;
            }else{
            frota[ind].cod = (palavra *) malloc ( sizeof (palavra )*(capacidade));
            }
            strcpy(frota[ind].cod[j].codigo,temp);
            frota[ind].cod[j].prioridade = prioridade ;
            j++;
        }

    }



    fclose(input);
	fclose(output);
return 0;
}
