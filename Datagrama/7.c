#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Pacote{
	int num;
	char* string;
}Pacote;

//Função para achar o filho da esquerda
int esq(int i){
	return (i*2)+1;
}

//Função para achar o filho da direita
int dir(int i){
	return (i*2)+2;
}

//Função q faz a troca no heap.
void troca(Pacote* a, int pai, int i){
	Pacote aux = a[pai];
	a[pai] = a[i];
	a[i] = aux;
}

void hpfMin(Pacote* a, unsigned int T, unsigned int i) {
	unsigned int P = i;
	unsigned int E = esq(i);
	unsigned int D = dir(i);
	if(E < T && a[E].num < a[P].num){
		P = E;
	}
	if(D < T && a[D].num < a[P].num){ 
		P = D;
	}
	
	if(P != i) {
		troca(a, P, i);
		hpfMin(a, T, P);
	}
}

void construcao(Pacote* a, unsigned int tamanho){
	unsigned int i;
	unsigned int j = 0;
	
	do{
		i = ((tamanho-1)/2)-j;
		hpfMin(a, tamanho, i);
		j++;
	}while(i != 0);
}

int main(int argc, char* argv[]){
	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	
	if(arqInput != NULL){
		int cap;
		int numPacote;
		fscanf(arqInput, "%d %d\n", &cap, &numPacote);
		
		Pacote* pacote = (Pacote*) malloc(cap*sizeof(Pacote));
		
		int i, l;
		
		for(i = 0; i < cap; i++){
			pacote[i].string = (char*) malloc(sizeof(char)*2000);
		}
		
		char c;
		int sizeString;

		int j = 0;
		int x = 0;
		int cont = 0;
		for(i = 0; i < cap; i++){
			if(j == numPacote){
				j = 0;
				construcao(pacote, i);
				i--;
				if(x == pacote[0].num){
					fprintf(arqOutput, "[%d] ", cont);
					cont++;
					while(x == pacote[0].num){
						fprintf(arqOutput, "%s ", pacote[0].string);
						troca(pacote, 0, i);
						hpfMin(pacote, i, 0);
						i--;
						cap--;
						x++;
					}
					fprintf(arqOutput, "\n");
				}
			}else{
				fscanf(arqInput, "%d %d ", &(pacote[i].num), &sizeString);
				memset(pacote[i].string, 0, sizeof(char)*255);
				
				l = 0;
				do{
					c = fgetc(arqInput);
					if(c != '\n' & c != EOF){
						pacote[i].string[l] = c;
						l++;
					}
				}while(c != '\n' & c != EOF);
				
				j++;
			}
		}
		
		if(i != 0){
			construcao(pacote, i);
			fprintf(arqOutput, "[%d] ", cont);
			while(i != 0){
				i--;
				fprintf(arqOutput, "%s ", pacote[0].string);
				troca(pacote, 0, i);
				hpfMin(pacote, i, 0);
			}
		}
	}else{
		printf("Erro ao tentar abrir o arquivo.");
	}
	
	return 0;
}