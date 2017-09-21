#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    int flag = 0 ;
    int cond = 0 ;
    int indice = 0;
    int barran = 0;

    FILE * output;


    typedef struct Pacote{
        int tamanho;
        int chave;
        char conteudo[2500];
    }Pacote;
    Pacote *aux;

    void muda(Pacote *v,int pai, int mf){
        Pacote temp;
        temp = v[pai]; //salva em aux
        v[pai]=v[mf];// troca o pai pelo filho
        v[mf]=temp;//posicao de maior filho recebe aux
    }

    void heapfy(Pacote * hm , unsigned int iu , int t){
        int pai=iu;
        int fe=(2*iu)+1; // esquerda
        int fd=(2*iu)+2; // direita

        if(fe<t){
            if(hm[fe].chave<hm[pai].chave){
                pai=fe;
            }
        }
        if(fd<t){
            if(hm[fd].chave<hm[pai].chave){
                pai=fd;
            }
        }
        if(pai!=iu){
            muda(hm,iu,pai);
            heapfy(hm,pai,t);
        }
    }

    void removeimprime(){
        int x=1; //mudei a logica do x pq se nao fica igual ao meu

        while(flag == aux[0].chave){
            if(x){
                fprintf(output,"[%d]",barran);
                barran++;
               x=0;
            }
            fprintf(output,"%s",aux[0].conteudo);
            aux[0]= aux[indice-1];
            heapfy(aux,0,indice);
            flag++;
            indice--;            
        }
		if(!x){
            fprintf(output," \n");

		}
   }


  void copiar_aux(Pacote *pacote, int frequencia){

    int i,iu;
    for (i=0;i<frequencia;i++){
        aux[indice].chave = pacote[i].chave;
        aux[indice].tamanho = pacote[i].tamanho;
        strcpy(aux[indice].conteudo,pacote[i].conteudo);
        indice++;
    }
    if(cond == 1 ){
    for (iu=(indice-1)/2;iu>=0;iu--){
        heapfy(aux,iu,indice);
    }
    }
    cond = 0 ;
   removeimprime();
   }

    int main(int argc, char* argv[]){

    // Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);

        int qtd_pct,freq;
        int i=0;
        int cont=0;

        Pacote *pacote;

        FILE *input = fopen(argv[1],"r");
        output = fopen(argv[2],"w");

        fscanf(input,"%d %d",&qtd_pct,&freq);

        pacote = (Pacote*) malloc ( sizeof (Pacote)*(qtd_pct)); // vetor de pacotes
        aux = (Pacote*) malloc ( sizeof (Pacote)*(qtd_pct)); // vetor de pacotes

        while(i<qtd_pct/freq){ // while que determina a rodada geral

            while(cont<freq){ // while pra rodar de dois em dois, ou quando o numero for impar rodar mais uma vez
                    fscanf(input,"%d %d",&pacote[cont].chave,&pacote[cont].tamanho);
                    fscanf(input,"%[^\n]*c",pacote[cont].conteudo);
                    if(pacote[cont].chave == flag) cond = 1 ;
                    cont++;
            } // fim while dois em dois
            i++;
            copiar_aux(pacote,freq);
            cont=0; // contador de frequencia;
            cond=0;
        }

    while(cont < qtd_pct % freq ){ // while pra rodar de dois em dois, ou quando o numero for impar rodar mais uma vez
        fscanf(input,"%d %d",&pacote[cont].chave,&pacote[cont].tamanho);
        fscanf(input,"%[^\n]*c",pacote[cont].conteudo);
        if(pacote[cont].chave == flag) cond = 1 ;
        cont++;

    } // fim while dois em dois
    copiar_aux(pacote,qtd_pct%freq);

    fclose(input);
	fclose(output);
return 0;
}
