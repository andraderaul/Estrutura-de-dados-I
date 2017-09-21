#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct vetores{ //vetor original
	
	int tam;	
	int *vetor;
	
}vetores;
typedef struct tecnicas{//vetores das tecnicas e suas variantes
	
	int variante;
	int *vetor;
	int cont;
	char nome[3];
		
}tecnicas;

void contador(int variante, tecnicas* K){//contadores
	if(variante<3){ //particionar
		switch(variante){
			case 0:
				K[0].cont++;
			break;
			case 1:
				K[1].cont++;
			break;
			case 2:
				K[2].cont++;
			break;
		}	
	}
	else{ //hoare
		switch(variante){
			case 10:
				K[3].cont++;
			break;
			case 11:
				K[4].cont++;
			break;
			case 12:
				K[5].cont++;
			break;
		}	
	}
}
void trocar(int *x, int *y, int variante, tecnicas* K){ //troca
	
	contador(variante,K); //cont
	
	int aux;	
	aux = *x;
	*x = *y;
	*y = aux;
} 
void troca(int *x, int *y){ //troca do ordenacao por insercao
	
	int aux;	
	aux = *x;
	*x = *y;
	*y = aux;
} 
void ordenacao_por_insercao(int V[], int n) { //ordenacao por insercao
	
	int i, j;
	for(i = 1; i < n; i = i+1)
		for(j = i; j > 0 && V[j-1] > V[j]; j--)
			troca(&V[j], &V[j-1]);
}
void ordenacaostruct(tecnicas* V, int n) { //ordenacao por insercao
	
	int i, j;
	int aux;
	char str[3];
//	tecnicas aux;
	
	for(i = 1; i < n; i = i+1){
		for(j = i; j > 0 && V[j-1].cont > V[j].cont; j--){
			
			aux = V[j].cont;
			V[j].cont = V[j-1].cont;
			V[j-1].cont = aux;	
			
			strcpy(str,V[j].nome);
			strcpy(V[j].nome,V[j-1].nome);
			strcpy(V[j-1].nome,str);
			
		}
	}

}
void randomico(int V[], int inicio, int fim, int variante,tecnicas* K) { //randomico

	int a = V[inicio];	
	int aux;

	aux = abs(a);
	
	int i = inicio + (aux % (fim-inicio+1));
		switch(variante){
			case 2:			
				trocar(&V[fim],&V[i],variante,K);
			break;
			case 12:
				trocar(&V[inicio],&V[i],variante,K);
			break;	
		}
}
void mediana (int V[],int inicio,int fim,int variante, tecnicas* K){ //achando a mediana
	
//	contador(variante,K); //cont
	
	int n = (fim-inicio)+1;
	int a = (n/4)+inicio;
	int b = (n/2)+inicio;
	int c = ((3*n)/4)+inicio;
	
	int Y[] = {V[a],V[b],V[c]};
	
	ordenacao_por_insercao(Y,3);
	
	switch(variante){
		case 1:
			
			if(Y[1]==V[a])
				trocar(&V[a],&V[fim],variante,K);
			else if (Y[1]==V[b])
				trocar(&V[b],&V[fim],variante,K);
			else 
				trocar(&V[c],&V[fim],variante,K);		
		
		break;
		
		case 11:
		
			if(Y[1]==V[a])
				trocar(&V[a],&V[inicio],variante,K);
			else if (Y[1]==V[b])
				trocar(&V[b],&V[inicio],variante,K);
			else
				trocar(&V[c],&V[inicio],variante,K);
		
		break;
	
	}
	
		
}
int particionar(int V[], int inicio, int fim,int variante,tecnicas* K) { //particionar
	
	int pivo = V[fim];
		
	int i = inicio - 1, j;
	
	for(j = inicio; j < fim; j++) {
		if(V[j] <= pivo) {
			i = i + 1;
			trocar(&V[i], &V[j],variante,K);
		}
	}
		trocar(&V[i + 1], &V[fim],variante,K);
	return i + 1;
}
void quicksort(int V[], int inicio, int fim, int variante, tecnicas* K){ //quicksort
	
	int pivo;
	
	contador(variante,K); //cont
	
	if(inicio < fim) {
		switch(variante){
		
		case 0:
			pivo = particionar(V, inicio, fim, variante,K);
		break;
		
		case 1:
			mediana(V,inicio,fim,variante,K);
			pivo = particionar(V, inicio, fim, variante,K);
		break;
		
		case 2:
			randomico(V,inicio,fim,variante,K);
			pivo = particionar(V, inicio, fim, variante,K);
		break;	
	}
		quicksort(V, inicio, pivo - 1,variante,K);
		quicksort(V, pivo + 1, fim,variante,K);
	}
}
int hoare(int V[], int inicio, int fim,int variante, tecnicas* K) { //hoare
	
	int pivo = V[inicio];
	
	int i = inicio;
	int j = fim;
	
	while(i < j) {
		while(j > i && V[j] >= pivo) j--;
		while(i < j && V[i] < pivo) i++;
			if(i < j) trocar(&V[i], &V[j],variante,K);
	}
return j;
}
void quicksorthoare(int V[], int inicio, int fim,int variante, tecnicas* K) { //quicksorthoare
	
	int  pivo;
	
	contador(variante, K); //cont
	
	if(inicio < fim) {
		
		switch(variante){
		
		case 10:
			pivo = hoare(V, inicio, fim,variante,K);
		break;
		
		case 11:
			mediana(V,inicio,fim,variante,K);
			pivo = hoare(V, inicio, fim,variante,K);
		break;
		
		case 12:
			randomico(V,inicio,fim,variante,K);
			pivo = hoare(V, inicio, fim,variante,K);
		break;	
	}		
		quicksorthoare(V, inicio, pivo,variante,K);
		quicksorthoare(V, pivo + 1, fim,variante,K);
	}
}
void imprime(tecnicas* K, int indice,int t,FILE* output){//imprime
	int i;
	
	ordenacaostruct(K, 6);
	fprintf(output,"[%d] ", indice);
	fprintf(output,"N(%d) ",t);
	for(i = 0; i<6; i++ ){
		fprintf(output,"%s(%d)",K[i].nome,K[i].cont);
		if(i!=5){
			fprintf(output," ");
		}
	}
	fprintf(output,"\n");
	
	
}
void copiavetor(tecnicas* K, vetores v){ //copia v pra k	
	
	int j=0;		
	for(j=0;j<v.tam;j++){
		//quicksort particionado
		K[0].vetor[j] = v.vetor[j];
		K[1].vetor[j] = v.vetor[j];
		K[2].vetor[j] = v.vetor[j];
		//quicksort hoare
		K[3].vetor[j] = v.vetor[j];
		K[4].vetor[j] = v.vetor[j];
		K[5].vetor[j] = v.vetor[j];		
		}

}
void chamaordenacao(tecnicas* K, vetores v ){//chama quicksort e quicksorthoare
	
	quicksort(K[0].vetor,0,v.tam-1,K[0].variante,K);
	quicksorthoare(K[3].vetor,0,v.tam-1,K[3].variante,K);	
				
	quicksort(K[1].vetor,0,v.tam-1,K[1].variante,K);
	quicksorthoare(K[4].vetor,0,v.tam-1,K[4].variante,K);
				
	quicksort(K[2].vetor,0,v.tam-1,K[2].variante,K);
	quicksorthoare(K[5].vetor,0,v.tam-1,K[5].variante,K);

}
void addvariante(tecnicas* K){ //define as seis variantes
		
		//quicksort particionado
		K[0].variante = 0; 
		K[1].variante = 1;
		K[2].variante = 2;
		
		//quicksort hoare
		K[3].variante = 10;
		K[4].variante = 11;
		K[5].variante = 12;
		
		strcpy(K[0].nome,"PP"); 
		strcpy(K[1].nome,"PM");
		strcpy(K[2].nome,"PA");
		
		//quicksort hoare
		strcpy(K[3].nome,"HP"); 
		strcpy(K[4].nome,"HM");
		strcpy(K[5].nome,"HA");
		
	
}
void zerandocontador(tecnicas* K){ //zerando os contadores antes de recomeçar o loop
	int j=0;
	for(j=0;j<6;j++){
			K[j].cont = 0;
	}
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
	
	int numtotalvetor, i = 0, j = 0, indice = 0;
	struct vetores v;
	struct tecnicas *K;	

	fscanf(input,"%d",&numtotalvetor); //numero total de vetores
		
	for(i = 0; i<numtotalvetor;i++){
		
		K = (tecnicas*)malloc(sizeof(tecnicas)*6); // malloc das tecnicas		
		fscanf(input,"%d",&v.tam); //tamanho do vetor		
		v.vetor = (int*)malloc(sizeof(int)*v.tam); 	//malloc do tamanho do vetor 		
		for(j=0;j<6;j++){
			K[j].vetor = (int*)malloc(sizeof(int)*v.tam); //malloc nos vetores de tecnicas
		}		
		addvariante(K); //funcao q define as variantes e coloca os nomes
		for(j = 0; j<v.tam;j++){
			fscanf(input,"%d",&v.vetor[j]);
		}		
		copiavetor(K,v);	//copia do v para o k e suas seis variantes		
		chamaordenacao(K,v); //ordena as seis variantes existentes em K
		imprime(K, indice,v.tam,output);//imprime os contadores das seis variantes já ordenados
		zerandocontador(K); //zerando todos os contadores antes de recomeçar o laço
		indice++;			
		K = NULL;
		free(K);			
	}
	
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa
	
return 0;
}
