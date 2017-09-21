#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct infos{
	int peso;
	char codigo[51];
	int prioridade;
	int contador;
}infos;
void llremove(int veiculos,int carga_max, int pacotes, int i,FILE *input,FILE *output,infos aux,infos *vetor){
	int espaco=1,temp=0,m=0,n,o,j;
	i=0;
	int veiculo=0;
	while (1){
		espaco=1;
		temp=0;
		m=0;
		fprintf(output,"[V%d] ",veiculo);
		if (veiculo+1==veiculos) 	veiculo=0;	
		else veiculo++;
		while(espaco){
			if (temp+vetor[i].peso <= carga_max && i<pacotes){
				temp+=vetor[i].peso;
				i++;
				m++;	
			}
			else{
				break;
			}
		}
		for (n=i-m;n<i;n++){
			for (o=i-m;o<i;o++){
				if (vetor[n].prioridade <= vetor[o].prioridade && i<pacotes){
					if (vetor[n].prioridade == vetor[o].prioridade){
						if (vetor[n].contador > vetor[o].contador){
							aux=vetor[n];
							vetor[n]=vetor[o];
							vetor[o]=aux;
						}
					}
					else{
						aux=vetor[n];
						vetor[n]=vetor[o];
						vetor[o]=aux;
					}
				}
			}
		}
		int fim=i;
		int inicio=i-m;
		for (j=inicio;j<fim;j++){
			if (j<pacotes){
				if (j+1==fim){
					fprintf(output,"%s",vetor[j].codigo);
				}
				else fprintf(output,"%s ",vetor[j].codigo);
			}
		}	
		if (i>=pacotes)	break;
		
		fprintf(output,"\n");
		
	}
}
void checar_string(char *nome){
	int len=strlen(nome);
	if (nome[len-1]=='\n')	nome[len-1]='\0';
}
int main(int argc,char* argv[]){
	
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	
	
	int pacotes,veiculos,carga_max;
	fscanf(input,"%d%d",&veiculos,&carga_max);
	fscanf(input,"%d ",&pacotes);
	int i;
	
	infos temp;
	struct infos *vetor=(infos*)malloc(sizeof(infos) *pacotes);
	for (i=0;i<pacotes;i++){
		fscanf(input,"%s",vetor[i].codigo);
		fscanf(input,"%d ",&vetor[i].peso);
		vetor[i].contador=i;
		/***/if (vetor[i].codigo[0]=='E' && vetor[i].codigo[0]=='C')	vetor[i].prioridade=1;
		else if (vetor[i].codigo[0]=='P' && vetor[i].codigo[0]=='T')	vetor[i].prioridade=2;
		else if (vetor[i].codigo[0]=='X' && vetor[i].codigo[0]=='P')	vetor[i].prioridade=3;
		checar_string(vetor[i].codigo);
	}
	llremove(veiculos,carga_max,pacotes,i,input,output,temp,vetor);
	return 0;
}
