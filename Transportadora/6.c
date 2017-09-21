#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tempresa{
	
	unsigned int qtdveic;
	unsigned int pesomax;	
	unsigned int qtdcarga;
	unsigned int xp;
	unsigned int ec;
	unsigned int pt;
		
}tempresa;

typedef struct tentrega{

	unsigned int prioridade;
	unsigned int ordposte;
	char carga[255];
	unsigned int pesocarg;
	
}tentrega;
void copiar(tentrega S[],tentrega E[], int n){
	int i=0;
	
	for(i=0;i<n;i++){
		S[i] = E[i];
	}

}
void intercalar(tentrega S[], tentrega E[], int ini, int meio, int fim) {
	int i = ini, j = meio + 1, k = ini;
	
	while(i <= meio && j <= fim) {
		if(E[i].prioridade < E[j].prioridade)
			S[k++] = E[i++];
		else 
			S[k++] = E[j++];
	}
	if(i > meio) 
		copiar(&S[k], &E[j], fim - j + 1);
	else
		copiar(&S[k], &E[i], meio - i + 1);
	
	copiar(&E[ini], &S[ini], fim - ini + 1);
}

void mergesort(tentrega S[], tentrega E[], int ini, int fim) {
	int meio = ini + (fim - ini) / 2;
	if(ini < fim) {
		mergesort(S, E, ini, meio);
		mergesort(S, E, meio + 1, fim);
	}
	intercalar(S, E, ini, meio, fim);
}


void imprime(tentrega *E, tempresa V,int n, int ref, int carro,FILE* output){
	int i = 0;
	
	fprintf(output,"[V%d] ",carro);
	for(i  = ref; i<n; i++){
		fprintf(output,"%s",E[i].carga);
		if(i<n-1){
			fprintf(output," ");
		}
	}
	fprintf(output,"\n");
	
}


int main(int argc, char* argv[]) {
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");	
	
//	FILE* input = fopen("input.txt","r");
//	FILE* output = fopen("output.txt","w");
	
	int xp=0,ec=0,pt=0;
	struct tentrega *entrega;
	struct tentrega *aux;
	struct tempresa empresa;
	fscanf(input,"%d %d",&empresa.qtdveic,&empresa.pesomax);
	fscanf(input,"%d",&empresa.qtdcarga);
	
	entrega = (tentrega*)malloc(sizeof(tentrega)*empresa.qtdcarga+1);
	aux = (tentrega*)malloc(sizeof(tentrega)*empresa.qtdcarga+1);
	
	int peso = 0, cont =0, ref = 0, i = 0, carro = 0;
	
	i = 0;
	do{
		if(i!=empresa.qtdcarga)
			fscanf(input,"%s %d",entrega[i].carga,&entrega[i].pesocarg);
		
		entrega[i].ordposte = i; //ordem de postagem
		
		if(entrega[i].carga[0] == 'E'){
			entrega[i].prioridade = 1;   //minima
			ec++;
		}
		if(entrega[i].carga[0] == 'P'){
			entrega[i].prioridade = 2;   //media
			pt++;
		}
		if(entrega[i].carga[0] == 'X'){
			entrega[i].prioridade = 3; //max
			xp++;
		}		
			
		if(i>0){ // somatorio dos pesos ate que alcance o peso maximo			
			peso = peso + entrega[i-1].pesocarg;	
		//	printf("%d\n",peso);				
			if(empresa.pesomax>=peso){ //enquanto somatorio dos pesos for menor que peso maixmo 
				cont++; //conte quantos pacotes foram alocados no caminhao
			}
			if((peso+entrega[i].pesocarg)>empresa.pesomax){//tive q tirar o >= pq tava quebrando antes de ser o valor q eu queria (GDB<3)	
				mergesort(aux,entrega,ref,cont-1); //mergesort
				imprime(entrega,empresa,cont,ref,carro,output); //
				ref = cont;	//ref pega o cont pois preciso dele pra delimitar a impressao
				peso = 0; //quando entrar aqui peso tem q ser atualizado pra zero
				carro++; // e outro carro/veiculo é acionado				
			}
			if(carro>empresa.qtdveic-1){
				carro = 0;
			}
		}
	//	printf("%d %d\n",i,cont);
		i++;	
	}while(i<empresa.qtdcarga+1);	

	if(peso>0){
		mergesort(aux,entrega,ref,cont-1); //mergesort
		imprime(entrega,empresa,cont,ref,carro,output);
	}
	
	entrega = NULL;
	free(entrega);
	aux = NULL;
	free(aux);
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa
		
return 0;
}				
