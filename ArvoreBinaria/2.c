#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE*output;
struct elemento{
	struct elemento* direita;
	struct elemento* esquerda;
	char *string;
	char *tipo;
	int tamanho;
	int cont;
	};
typedef struct elemento elemento;

void inserir (elemento **p, char *string, char*tipo, int tamanho, int cont){
		if(*p==NULL){
			*p = (elemento*) malloc (sizeof(elemento));
			(*p)->direita=NULL;
			(*p)->esquerda=NULL;
			(*p)->string = (char*) malloc (sizeof(char)*51);
			strcpy((*p)->string, string);
			(*p)->tipo = (char*) malloc (sizeof(char)*2);
			strcpy((*p)->tipo, tipo);
			(*p)->tamanho = tamanho;
			(*p)->cont = cont;
		}	
	else if ((strcmp(string,(*p)->string)) < 0){
		inserir(&(*p)->esquerda, string, tipo, tamanho, cont);
		}
	else if((strcmp(string,(*p)->string)) > 0){
		inserir(&(*p)->direita, string, tipo, tamanho, cont);
	}
	else if((strcmp(string,(*p)->string))==0){
		if(strcmp((*p)->tipo,"rw")==0){
			strcpy((*p)->tipo, tipo);
			(*p)->tamanho = tamanho;
			(*p)->cont = cont;
		}
	}
}
void EPD(elemento *p){
	if(p!=NULL){
		EPD(p->esquerda);
		if(p->tamanho != 1)
		fprintf(output,"%d %s %s %d bytes\n", p->cont, p->string, p->tipo, p->tamanho);
		else 
		fprintf(output,"%d %s %s %d byte\n", p->cont, p->string, p->tipo, p->tamanho);
		EPD(p->direita);	
	}
}
void PED(elemento *p){
	if(p!=NULL){
		if(p->tamanho != 1)
		fprintf(output,"%d %s %s %d bytes\n", p->cont, p->string, p->tipo, p->tamanho);
		else 
		fprintf(output,"%d %s %s %d byte\n", p->cont, p->string, p->tipo, p->tamanho);
		PED(p->esquerda);
		PED(p->direita);	
	}
}
void EDP(elemento *p){
	if(p!=NULL){
		EDP(p->esquerda);
		EDP(p->direita);
		if(p->tamanho != 1)
		fprintf(output,"%d %s %s %d bytes\n", p->cont, p->string, p->tipo, p->tamanho);
		else 
		fprintf(output,"%d %s %s %d byte\n", p->cont, p->string, p->tipo, p->tamanho);
	}
}
int main(int argc, char* argv[]) {
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	output = fopen("outputarvore.txt", "w");
	FILE* input = fopen("inputarvore.txt", "r");
	int qtdArq=0;
	fscanf(input, "%d ", &qtdArq);
	elemento *arvore=NULL;
	char *string, *tipo;
	int tamanho=0;
	string = (char*) malloc (sizeof(char)*51);
	tipo = (char*) malloc (sizeof(char)*2);
	for(int i=0; i<qtdArq;i++){
		fscanf(input, "%s %s %d ", string, tipo, &tamanho);
		inserir(&arvore, string, tipo, tamanho, i);
		string[0] = '\0';
		tipo[0] = '\0';
		tamanho=0;
	}
	fprintf(output,"EPD:\n");
	EPD(arvore);
	fprintf(output,"PED:\n");
	PED(arvore);
	fprintf(output,"EDP:\n");
	EDP(arvore);
	
	fclose(output);
	fclose(input);
	return 0;
}
