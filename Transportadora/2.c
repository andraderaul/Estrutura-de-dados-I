#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct dados{
	int peso;
	int prioridade;
	int chegada;
	char codigo[21];
}dados;
// GLOBAIS =====================
int ind=0,veiculo=0;
dados aux;
struct dados *vetor;
FILE *input;
FILE *output;
int chegada=0;
//================================
void alocando_vetor(int n);
void start();
void inserir();
void leitura();
void removerr(int tamanho_total, int qtd_veiculo, int carga_maxima);

//================================
int main(int argc, char *argv[]){
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
	int qtd_pacotes, qtd_veiculos, carga_maxima;
	fscanf(input,"%d%d",&qtd_veiculos,&carga_maxima);
	fscanf(input,"%d ",&qtd_pacotes);
	alocando_vetor(qtd_pacotes);
	leitura();
	removerr(qtd_pacotes,qtd_veiculos,carga_maxima);
}
void leitura(){
	while (!feof(input)){
		fscanf(input,"%s",aux.codigo);
		fscanf(input,"%d ",&aux.peso);
		if (aux.codigo[strlen(aux.codigo)-1]=='\n'){
			aux.codigo[strlen(aux.codigo)-1]='\0';
		}
		aux.chegada=chegada;
		switch (aux.codigo[0]){
			case 'E':		
				aux.prioridade=1;
				break;
			case 'P': 
				aux.prioridade=2;
				break;
			case 'X':
				aux.prioridade=3;
				break;
		}				
		inserir(); 
		chegada++;
	}
}	
void alocando_vetor(int n){
	vetor=malloc(sizeof(dados) * n);
}
void inserir(){
	vetor[ind]=aux;
	ind++;
}
void removerr(int tamanho_total,int qtd_veiculo,int carga_maxima){
	int houver_elementos=1,houver_espaco=1,temp=0,i=0,m=0,n,o,j;
	while (houver_elementos){
		houver_espaco=1;
		temp=0;
		m=0;
		fprintf(output,"[V%d]",veiculo);
		if (veiculo+1==qtd_veiculo) 	veiculo=0;	
		else veiculo++;
		while(houver_espaco){
			if (temp+vetor[i].peso <= carga_maxima && i<tamanho_total){
				temp+=vetor[i].peso;
				i++;	//i   = fim
				m++;	//i-m = inicio
			}
			else break;
		}
		dados temp;
		for (n=i-m;n<i;n++){
			for (o=i-m;o<i;o++){
				if (vetor[n].prioridade <= vetor[o].prioridade && i<tamanho_total){
					if (vetor[n].prioridade == vetor[o].prioridade){
						if (vetor[n].chegada > vetor[o].chegada){
							temp=vetor[n];
							vetor[n]=vetor[o];
							vetor[o]=temp;
						}
					}
					else{
						temp=vetor[n];
						vetor[n]=vetor[o];
						vetor[o]=temp;
					}
				}
			}
		}
		for (j=(i-m);j<i;j++){
			if (j<tamanho_total)	fprintf(output," %s",vetor[j].codigo);
		}	
		if (i>=tamanho_total)	break;
		else fprintf(output,"\n");
		
	}
}
