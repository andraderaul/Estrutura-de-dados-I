#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct pacote{
	int posicao;
	int tamanho;
	char conteudo[1600];
}pacote;
struct pacote *acesso;
struct pacote *aux;
int imprime_global=0,ind=0,linha=0,achou_elemento=0,quantidade_TOTAL;
FILE *input;
FILE *output;
void start();
void malloca(int a,int b);
void leitura(int frequencia,int qtd_pacotes);
void heapify(int i, int T);
void remover();
void troca_heapify_decremento();
void enfileirar(int frequencia);
void start();
int main (int argc, char *argv[]){
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	start();
	return 0;
}
void start(){
	int qtd_pacotes,frequencia;
	fscanf(input,"%d ",&qtd_pacotes);
	quantidade_TOTAL=qtd_pacotes;
	fscanf(input,"%d ",&frequencia);
	malloca(frequencia,qtd_pacotes);
	leitura(frequencia,qtd_pacotes);
}
void leitura(int frequencia,int qtd_pacotes){
	int i,j;
	for (j=0;j<(qtd_pacotes/frequencia);j++){
		for (i=0;i<frequencia && !feof(input);i++){
			fscanf(input,"%d ",&aux[i].posicao);
			fscanf(input,"%d ",&aux[i].tamanho);
			//fscanf(input,"%[^\n]*c",aux[i].conteudo);
			fgets(aux[i].conteudo,1600, input);
			if (aux[i].posicao==imprime_global)	
				achou_elemento=1;
			
			if (aux[i].conteudo[strlen(aux[i].conteudo)-1]=='\n')	
				aux[i].conteudo[strlen(aux[i].conteudo)-1]='\0';
				
		}			
		enfileirar(frequencia);
	}	
	
	for (i=0;i<qtd_pacotes%frequencia;i++){
		fscanf(input,"%d%d ",&aux[i].posicao,&aux[i].tamanho);
		//fscanf(input,"%[^\n]*c",aux[i].conteudo);
		fgets(aux[i].conteudo,1600, input);
		if (aux[i].conteudo[strlen(aux[i].conteudo)-1]=='\n')	
			aux[i].conteudo[strlen(aux[i].conteudo)-1]='\0';
	}
	achou_elemento=1;
	enfileirar(qtd_pacotes%frequencia);
}
void enfileirar(int frequencia){
	int i,j;
	for (i=0;i<frequencia;i++){
		acesso[ind]=aux[i];
		ind++;
	}
	if (achou_elemento){
		for (j=(ind-1)/2;j>=0;j--){
			heapify(j,ind);
		}
		remover();
		achou_elemento=0;
	}
}
void heapify(int i, int T){
	int P,E,D;
	P=i;E=2*i+1;D=2*i+2;
	if (E<T && acesso[E].posicao < acesso[P].posicao)	P=E;
	if (D<T && acesso[D].posicao < acesso[P].posicao)	P=D;			
	if (P!=i){
		pacote temp;								
		temp=acesso[i];		
		acesso[i]=acesso[P];		
		acesso[P]=temp;				
		heapify(P,T);
	}
}
void remover(){
	int primeira_rodada=1;
	int controle_linha=0;
	while(acesso[0].posicao == imprime_global){
		if (primeira_rodada){	
			fprintf(output,"[%d]",linha);
			linha++;
			primeira_rodada=0;
		}
		//while (acesso[0].posicao==imprime_global){
		fprintf(output," %s",acesso[0].conteudo);
		troca_heapify_decremento();
		if (imprime_global-1==quantidade_TOTAL)		controle_linha=1;
	//	}
	}
	if (!controle_linha)	fprintf(output,"\n");
}
void malloca(int a,int b){
	aux=malloc(a * sizeof(pacote));
	acesso=malloc(b * sizeof(pacote));
}
void troca_heapify_decremento(){
	acesso[0]=acesso[ind-1];
	heapify(0,ind);
	ind--;
	imprime_global++;
}
