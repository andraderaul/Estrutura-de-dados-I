#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char string[18];
	int acertos;
	int numeros[15];
}Elemento;
Elemento *lowHeap;
Elemento *highHeap;
void highHeapify(Elemento *vetor, unsigned int T, unsigned int i){
	int auxiliar=0;
	char stringAux[17] = {0};
	unsigned int pai = i;
	unsigned int esquerda = (2*i)+1;
	unsigned int direita = (2*i)+2;
	if(esquerda < T && vetor[esquerda].acertos > vetor[pai].acertos)
		pai = esquerda;
	if(direita < T && vetor[direita].acertos > vetor[pai].acertos) 
		pai = direita;
	if(pai != i){
		auxiliar = vetor[i].acertos;
		strcpy(stringAux, vetor[i].string);
		vetor[i].acertos = vetor[pai].acertos;
		strcpy(vetor[i].string, vetor[pai].string);
		vetor[pai].acertos = auxiliar;
		strcpy(vetor[pai].string, stringAux);
		highHeapify(vetor, T, pai);
	}
}
void lowHeapify(Elemento *vetor, unsigned int T, unsigned int i){
	int auxiliar=0;
	char stringAux[17] = {0};
	unsigned int pai = i;
	unsigned int esquerda = (2*i)+1;
	unsigned int direita = (2*i)+2;
	if(esquerda < T && vetor[esquerda].acertos < vetor[pai].acertos) 
		pai = esquerda;
	if(direita < T && vetor[direita].acertos < vetor[pai].acertos) 
		pai = direita;
	if(pai != i){
		auxiliar = vetor[i].acertos;
		strcpy(stringAux, vetor[i].string);
		vetor[i].acertos = vetor[pai].acertos;
		strcpy(vetor[i].string, vetor[pai].string);
		vetor[pai].acertos = auxiliar;
		strcpy(vetor[pai].string, stringAux);
		lowHeapify(vetor, T, pai);
	}
}
int main(int argc, char* argv[]){
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	FILE* input = fopen("input.txt", "r");
	FILE* output = fopen("output.txt", "w");
	int premio, qtdAposta, numSorteado[10], k, j;
	fscanf(input, "%d %d ", &premio, &qtdAposta);
	for(int i=0; i<10; i++){
		fscanf(input, "%d ", &numSorteado[i]);
	}
	lowHeap = (Elemento*) malloc (sizeof(Elemento) * qtdAposta);
	highHeap = (Elemento*) malloc (sizeof(Elemento) * qtdAposta);
	for(int i=0;i<qtdAposta;i++){
		fscanf(input, "%s ", highHeap[i].string);
		strcpy(lowHeap[i].string, highHeap[i].string);
		for(j=0; j<15; j++){
			fscanf(input, "%d ", &highHeap[i].numeros[j]);
			for(k=0; k<10; k++){
				if(numSorteado[k] == highHeap[i].numeros[j]){
					highHeap[i].acertos++;
				}
			}
		}
		lowHeap[i].acertos = highHeap[i].acertos;
	}
	int q, w=0;
	do{
		q = ((qtdAposta-1)/2)-w;
		lowHeapify(lowHeap, qtdAposta, q);
		highHeapify(highHeap, qtdAposta, q);
		w++;
	}while(q!=0);
	for(int i=0;i<qtdAposta-1;i++){
		lowHeapify(lowHeap, qtdAposta, i);
		highHeapify(highHeap, qtdAposta, i);	
	}
	int auxHigh = highHeap[0].acertos, contHigh=1;
	if(auxHigh > 1)
		fprintf(output, "Faixa: %d acertos\n", auxHigh);
	else
		fprintf(output, "Faixa: %d acertos\n", auxHigh);
	fprintf(output, "%s\n", highHeap[0].string);
	for(int i=qtdAposta;i>0; i--){
		highHeap[0].acertos = highHeap[i].acertos;
		strcpy(highHeap[0].string, highHeap[i].string);
		highHeapify(highHeap, i, 0);
		if(auxHigh == highHeap[0].acertos){
			fprintf(output, "%s\n", highHeap[0].string);
			contHigh++;
		}
	}
	if(contHigh>1)
	fprintf(output, "%d ganhadores de R$%d", contHigh, ((premio/2)/contHigh));
	else
	fprintf(output, "%d ganhador de R$%d", contHigh, ((premio/2)/contHigh));
	
	int auxLow = lowHeap[0].acertos, contLow=0;
	if(auxLow > 1)
	fprintf(output, "\n\nFaixa: %d acertos\n", auxLow);
	else
	fprintf(output, "\n\nFaixa: %d acerto\n", auxLow);
	fprintf(output, "%s", lowHeap[0].string);
	for(int i=qtdAposta;i>0; i--){
		lowHeap[0].acertos = lowHeap[i].acertos;
		strcpy(lowHeap[0].string, lowHeap[i].string);
		lowHeapify(lowHeap, qtdAposta, 0);
		if(auxLow == lowHeap[0].acertos){
			fprintf(output, "%s\n", lowHeap[0].string);
			contLow++;
		}
	}
	if(contLow > 1)
		fprintf(output, "%d ganhadores de R$%d", contLow, ((premio/2)/contLow));
	else
		fprintf(output, "%d ganhador de R$%d", contLow, ((premio/2)/contLow));
	
	fclose(input);
	fclose(output);
}
