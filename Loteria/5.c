#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Num sorteiro: 28
//Num aposta: 44
typedef struct Apostador{
	int numAposta[15];
	char id[17];
	int numAcerto;
}Apostador;

//Função para achar o pai
int p(int i){
	return (i-1)/2;
}

//Função para achar o filho da esquerda
int esq(int i){
	return (i*2)+1;
}

//Função para achar o filho da direita
int dir(int i){
	return (i*2)+2;
}

//Função de troca
void t(Apostador* a, unsigned int pai, unsigned int filho){
	int numAposta[15];
	char id[17] = {0};
	int numAcerto = a[pai].numAcerto;
	strcpy(id, a[pai].id);
	numAposta[0] = a[pai].numAposta[0];
	numAposta[1] = a[pai].numAposta[1];
	numAposta[2] = a[pai].numAposta[2];
	numAposta[3] = a[pai].numAposta[3];
	numAposta[4] = a[pai].numAposta[4];
	numAposta[5] = a[pai].numAposta[5];
	numAposta[6] = a[pai].numAposta[6];
	numAposta[7] = a[pai].numAposta[7];
	numAposta[8] = a[pai].numAposta[8];
	numAposta[9] = a[pai].numAposta[9];
	numAposta[10] = a[pai].numAposta[10];
	numAposta[11] = a[pai].numAposta[11];
	numAposta[12] = a[pai].numAposta[12];
	numAposta[13] = a[pai].numAposta[13];
	numAposta[14] = a[pai].numAposta[14];
	
	a[pai] = a[filho];
	
	a[filho].numAposta[0] = numAposta[0];
	a[filho].numAposta[1] = numAposta[1];
	a[filho].numAposta[2] = numAposta[2];
	a[filho].numAposta[3] = numAposta[3];
	a[filho].numAposta[4] = numAposta[4];
	a[filho].numAposta[5] = numAposta[5];
	a[filho].numAposta[6] = numAposta[6];
	a[filho].numAposta[7] = numAposta[7];
	a[filho].numAposta[8] = numAposta[8];
	a[filho].numAposta[9] = numAposta[9];
	a[filho].numAposta[10] = numAposta[10];
	a[filho].numAposta[11] = numAposta[11];
	a[filho].numAposta[12] = numAposta[12];
	a[filho].numAposta[13] = numAposta[13];
	a[filho].numAposta[14] = numAposta[14];
	strcpy(a[filho].id, id);
	a[filho].numAcerto = numAcerto;
	
}

void hpfMax(Apostador* a, unsigned int T, unsigned int i) {
	unsigned int P = i;
	unsigned int E = esq(i);
	unsigned int D = dir(i);
	if(E < T && a[E].numAcerto > a[P].numAcerto){
		P = E;
	}
	if(D < T && a[D].numAcerto > a[P].numAcerto){ 
		P = D;
	}
	
	if(P != i) {
		t(a, P, i);
		hpfMax(a, T, P);
	}
}

void hpfMin(Apostador* a, unsigned int T, unsigned int i) {
	unsigned int P = i;
	unsigned int E = esq(i);
	unsigned int D = dir(i);
	if(E < T && a[E].numAcerto < a[P].numAcerto){
		P = E;
	}
	if(D < T && a[D].numAcerto < a[P].numAcerto){ 
		P = D;
	}
	
	if(P != i) {
		t(a, P, i);
		hpfMin(a, T, P);
	}
}

void addMax(Apostador* a, unsigned int tamanho){
	unsigned int i;
	unsigned int j = 0;
	
	do{
		i = ((tamanho-1)/2)-j;
		hpfMax(a, tamanho, i);
		j++;
	}while(i != 0);
}

void addMin(Apostador* a, unsigned int tamanho){
	unsigned int i;
	unsigned int j = 0;
	
	do{
		i = ((tamanho-1)/2)-j;
		hpfMin(a, tamanho, i);
		j++;
	}while(i != 0);
}

void remover(Apostador* a, unsigned int tamanho){
	if(a != NULL){
		a[0] = a[tamanho-1];
	}
}

int main(int argc, char* argv[]){
	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	int numPremio;
	int numApostador;
	int i, j, k;
	int tamanhoMax = 0, tamanhoMin = 0;
	int numSorteio[10];
	
	fscanf(arqInput, "%d", &numPremio);
	fscanf(arqInput, "%d", &numApostador);
	
	fscanf(arqInput, "%d %d %d %d %d %d %d %d %d %d", &numSorteio[0], &numSorteio[1], &numSorteio[2], &numSorteio[3], &numSorteio[4], &numSorteio[5], &numSorteio[6], &numSorteio[7], &numSorteio[8], &numSorteio[9]);
	
	Apostador* aMax = (Apostador*) malloc(sizeof(Apostador)*numApostador);
	Apostador* aMin = (Apostador*) malloc(sizeof(Apostador)*numApostador);
	
	for(k = 0; k < numApostador; k++){
		fscanf(arqInput, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", aMax[k].id, &(aMax[k].numAposta[0]), &(aMax[k].numAposta[1]), &(aMax[k].numAposta[2]), &(aMax[k].numAposta[3]), &(aMax[k].numAposta[4]), &(aMax[k].numAposta[5]), &(aMax[k].numAposta[6]), &(aMax[k].numAposta[7]), &(aMax[k].numAposta[8]), &(aMax[k].numAposta[9]), &(aMax[k].numAposta[10]), &(aMax[k].numAposta[11]), &(aMax[k].numAposta[12]), &(aMax[k].numAposta[13]), &(aMax[k].numAposta[14]));
		
		aMax[k].numAcerto = 0;
		
		for(i = 0; i < 10; i++){
			for(j = 0; j < 15; j++){
				if(numSorteio[i] == aMax[k].numAposta[j]){
					aMax[k].numAcerto++;
					break;
				}
			}
		}
		
		aMin[k] = aMax[k];
	}
	
	addMax(aMax, numApostador);
	
	
	
	tamanhoMax = numApostador;
	tamanhoMin = numApostador;
	//Max
	int maxAcerto = aMax[0].numAcerto;
	i = 1;
	
	fprintf(arqOutput, "Faixa: %d acertos\n", aMax[0].numAcerto);
	fprintf(arqOutput, "%s\n", aMax[0].id);
	remover(aMax, tamanhoMax);
	tamanhoMax--;
	hpfMax(aMax, tamanhoMax, 0);

	while(aMax[0].numAcerto == maxAcerto){
		fprintf(arqOutput, "%s\n", aMax[0].id);
		remover(aMax, tamanhoMax);
		tamanhoMax--;
		hpfMax(aMax, tamanhoMax, 0);
		i++;
	}
	
	if(i > 1){
		fprintf(arqOutput, "%d ganhadores de R$%d\n", i, (numPremio/2)/i);
	}else{
		fprintf(arqOutput, "1 ganhador de R$%d\n", (numPremio/2));
	}
	//
	
	fprintf(arqOutput, "\n");
	
	/*
	for(i = 0; i < numApostador; i++){
		fprintf(arqOutput, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", aMax[i].id, aMax[i].numAposta[0], aMax[i].numAposta[1], aMax[i].numAposta[2], aMax[i].numAposta[3], aMax[i].numAposta[4], aMax[i].numAposta[5], aMax[i].numAposta[6], aMax[i].numAposta[7], aMax[i].numAposta[8], aMax[i].numAposta[9], aMax[i].numAposta[10], aMax[i].numAposta[11], aMax[i].numAposta[12], aMax[i].numAposta[13], aMax[i].numAposta[14]);
	}*/
	
	
	addMin(aMin, numApostador);

	//Min
	int minAcerto = aMin[0].numAcerto;
	i = 1;
	
	if(minAcerto > 0){
		fprintf(arqOutput, "Faixa: %d acertos\n", aMin[0].numAcerto);
	}else{
		fprintf(arqOutput, "Faixa: %d acerto\n", aMin[0].numAcerto);
	}
	
	fprintf(arqOutput, "%s\n", aMin[0].id);
	aMin[0] = aMin[tamanhoMin-1];
	tamanhoMin--;
	hpfMin(aMin, tamanhoMin, 0);

	while(aMin[0].numAcerto == minAcerto){
		fprintf(arqOutput, "%s\n", aMin[0].id);
		aMin[0] = aMin[tamanhoMin-1];
		tamanhoMin--;
		hpfMin(aMin, tamanhoMin, 0);
		i++;
	}
	
	if(i > 1){
		fprintf(arqOutput, "%d ganhadores de R$%d\n", i, (numPremio/2)/i);
	}else{
		fprintf(arqOutput, "1 ganhador de R$%d", (numPremio/2));
	}
	//

	fflush(arqInput);
	fflush(arqOutput);
	fclose(arqInput);
	fclose(arqOutput);
	return 0;
}