#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct package {
	int num;
	int tam;
	char packs[2000];	
}pacote;
void troca(pacote *vetor,int P,int i){
	pacote aux=vetor[P];
	vetor[P]=vetor[i];
	vetor[i]=aux;
}
void heapify(pacote *vetor, int i, int T){
	
	int P=i;
	int E=2*i+1;
	int D=2*i+2;
	if (E<T){
		if (vetor[E].num < vetor[P].num){
			P=E;
		}
	}
	if (D<T){
		if (vetor[D].num < vetor[P].num){
			P=D;
		}
	}
	if (P!=i){
		troca(vetor,P,i);
		heapify(vetor,P,T);
	}
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
	int total_pct,frequencia;
	int i;
	int imprime=0;
	int qtd_vezes_lidos=0;
	int indice=0;
	int controlador_de_linha=0;
	int controlador_de_indice=1;	
	int linha=0;
	pacote *pac;
	fscanf(input,"%d",&total_pct);
	//TOTAL DOS PACOTES ENVIADOS
	int quebra_while=0;
	fscanf(input,"%d",&frequencia);
	//QUANTIDADE MINIMA DE PACOTES 
	pac=(pacote*)malloc(sizeof(pacote)*total_pct);
	//INICIAR A LEITURA DOS PACOTES
	int len;
	while (!quebra_while){
		if (qtd_vezes_lidos+frequencia<total_pct){
			for (i=0;i<frequencia;i++){
				fscanf(input,"%d ",&pac[indice].num);
				fscanf(input,"%d ",&pac[indice].tam);
				fgets(pac[indice].packs,2000,input);
				len=strlen(pac[indice].packs);
				
				if (pac[indice].packs[len-1] == '\n'){
					pac[indice].packs[len-1]='\0';
				}
				indice++;
				qtd_vezes_lidos++;
			}
		}
		else{
			for (i=0;i<(total_pct%frequencia);i++){
				fscanf(input,"%d ",&pac[indice].num);
				fscanf(input,"%d ",&pac[indice].tam);
				fgets(pac[indice].packs,2000,input);
				len=strlen(pac[indice].packs);
				
				if (pac[indice].packs[len-1] == '\n'){
					pac[indice].packs[len-1]='\0';
				}
				indice++;
				qtd_vezes_lidos++;
				quebra_while++;
			}
		}
		
		for (i=(indice-1)/2;i>=0;i--){
			heapify(pac,i,indice);
		}
		controlador_de_indice=1;
		controlador_de_linha=0;
		// REMOVE ++++++++=@#$@#$K@#$@#M$@M$K@#K$#K%$$%K%$KK$
		
		for (i=imprime;(i==pac[0].num);i++){
			if (controlador_de_indice){
				fprintf(output,"[%d]",linha);
				linha++;
				controlador_de_indice=0;
			}
			fprintf(output," %s",pac[0].packs);
			
			pac[0]=pac[indice-1];
			heapify(pac,0,indice);
			indice--;
			imprime++;
			controlador_de_linha=1;
		}
		if (controlador_de_linha)	fprintf(output,"\n");
	}
			
			
			 
return 0;
}
