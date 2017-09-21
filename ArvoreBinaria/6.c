#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arquivo{
	char nome[51];
	char tipo[3];
	int tamanho;
	int id;
	struct Arquivo* d;
	struct Arquivo* e;
}Arquivo;

typedef struct Raiz{
	Arquivo* pai;
}Raiz;

void buscarInserir(Arquivo* pai, Arquivo filho){
	if(strcmp(pai->nome, filho.nome) == 0){
		if(strcmp(pai->tipo, "rw") == 0){
			strcpy(pai->tipo, filho.tipo);
			pai->tamanho = filho.tamanho;
			pai->id = filho.id;
		}
	}else if(strcmp(pai->nome, filho.nome) > 0){//Indo para a esquerda
		if(pai->e == NULL){
			pai->e = (Arquivo*) malloc(sizeof(Arquivo));
			*(pai->e) = filho;
		}else{
			buscarInserir(pai->e, filho);
		}
	}else{//Indo para a direita
		if(pai->d == NULL){
			pai->d = (Arquivo*) malloc(sizeof(Arquivo));
			*(pai->d) = filho;
		}else{
			buscarInserir(pai->d, filho);
		}
	}
}

void add(Raiz* raiz, Arquivo filho){
	if(raiz->pai == NULL){
		Arquivo* a = (Arquivo*) malloc(sizeof(Arquivo));
		*a = filho;
		raiz->pai = a;
	}else{
		buscarInserir(raiz->pai, filho);
	}
}

void printEPD(Arquivo* pai, FILE* arqOutput){
	if(pai != NULL){
		printEPD(pai->e, arqOutput);
		
		if(pai->tamanho == 1){
			fprintf(arqOutput, "%d %s %s %d byte\n", pai->id, pai->nome, pai->tipo, pai->tamanho);
		}else{
			fprintf(arqOutput, "%d %s %s %d bytes\n", pai->id, pai->nome, pai->tipo, pai->tamanho);
		}
		
		printEPD(pai->d, arqOutput);
	}
}

void printPED(Arquivo* pai, FILE* arqOutput){
	if(pai != NULL){
		if(pai->tamanho == 1){
			fprintf(arqOutput, "%d %s %s %d byte\n", pai->id, pai->nome, pai->tipo, pai->tamanho);
		}else{
			fprintf(arqOutput, "%d %s %s %d bytes\n", pai->id, pai->nome, pai->tipo, pai->tamanho);
		}
		
		printPED(pai->e, arqOutput);
		printPED(pai->d, arqOutput);
	}
}

void printEDP(Arquivo* pai, FILE* arqOutput){
	if(pai != NULL){
		printEDP(pai->e, arqOutput);
		printEDP(pai->d, arqOutput);
		
		if(pai->tamanho == 1){
			fprintf(arqOutput, "%d %s %s %d byte\n", pai->id, pai->nome, pai->tipo, pai->tamanho);
		}else{
			fprintf(arqOutput, "%d %s %s %d bytes\n", pai->id, pai->nome, pai->tipo, pai->tamanho);
		}
	}
}

int main(int argc, char* argv[]){
	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	
	if(arqInput != NULL){
		int numArquivo;
		fscanf(arqInput, "%d", &numArquivo);
		
		Raiz raiz;
		raiz.pai = NULL;
		
		int i;
		Arquivo aux;
		for(i = 0; i < numArquivo; i++){
			memset(aux.nome, 0, sizeof((aux.nome)));
			memset(aux.tipo, 0, sizeof((aux.tipo)));
			aux.e = NULL;
			aux.d = NULL;
			aux.id = i;
			
			fscanf(arqInput, "%s %s %d", aux.nome, aux.tipo, &(aux.tamanho));
			
			add(&raiz, aux);
		}
		
		fprintf(arqOutput, "EPD:\n");
		printEPD(raiz.pai, arqOutput);
		fprintf(arqOutput, "PED:\n");
		printPED(raiz.pai, arqOutput);
		fprintf(arqOutput, "EDP:\n");
		printEDP(raiz.pai, arqOutput);
	}else{
		printf("Erro ao abrir o arquivo.");
	}
	
	fflush(arqInput);
	fclose(arqInput);
	fflush(arqOutput);
	fclose(arqOutput);
	return 0;
}