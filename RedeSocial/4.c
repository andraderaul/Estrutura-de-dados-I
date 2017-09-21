#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
	@Weslan Rezende Alves
	@Info - 166 linhas de código sem os comentários e sem os \n

*/

typedef struct Elemento{
	char nome[50];
	struct Elemento* p;
	struct Elemento* a;
}Elemento;

typedef struct Lista{
	Elemento* p;
	Elemento* u;
}Lista;

Elemento* add(Elemento* p, Elemento* u, char nome[50], FILE* arqOutput){
	Elemento* user = (Elemento*) malloc(sizeof(Elemento));
	
	if(p == NULL){
		user->p = user;
		user->a = user;
		strcpy(user->nome, nome);
		fprintf(arqOutput, "[%s] ADD-OK\n", user->nome);
	}else{
		user->p = p;
		user->a = u;
		p->a = user;
		u->p = user;
		
		strcpy(user->nome, nome);
		
		fprintf(arqOutput, "[%s] ADD-OK\n", user->nome);
	}
	
	return user;
}

int busca(Lista* l, char nome[50]){
	Elemento* aux = l->p;
	int i = 0;
	
	if(l->p != NULL){
		do{
			if(strcmp(aux->nome, nome) == 0){
				i = 1;
				break;
			}
			aux = aux->p;
		}while(aux != l->p);
	}else{
		i = 0;
	}

	return i;
}

void show(Lista* l, char nome[50], FILE* arqOutput){
	Elemento* aux = l->p;
	int i = 0;
	if(l->p != NULL){
		do{
			if(strcmp(aux->nome, nome) == 0){
				fprintf(arqOutput, "[%s]<-[%s]->[%s]\n", aux->a->nome, aux->nome, aux->p->nome);
				
				i = 1;
				break;
			}
			aux = aux->p;
		}while(aux != l->p);
		
		if(i == 0){
			fprintf(arqOutput, "[%s] SHOW-ERROR\n", nome);
		}
	}else{
		fprintf(arqOutput, "[%s] SHOW-ERROR\n", nome);
	}
}

void remover(Lista* l, char nome[50], FILE* arqOutput){
	Elemento* aux = l->p;
	int i = 0;
	
	if(l->p != NULL){
		do{
			if(strcmp(aux->nome, nome) == 0){
				if(aux == l->p){
					l->p = aux->p;
					aux->a->p = aux->p;
					aux->p->a = aux->a;
					
					free(aux);
					aux = NULL;
					
					fprintf(arqOutput, "[%s] REMOVE-OK\n", nome);
				}else if(aux == l->u){
					l->u = aux->a;
					aux->a->p = aux->p;
					aux->p->a = aux->a;
					
					free(aux);
					aux = NULL;
					
					fprintf(arqOutput, "[%s] REMOVE-OK\n", nome);
				}else{
					aux->a->p = aux->p;
					aux->p->a = aux->a;
					
					free(aux);
					aux = NULL;
					
					fprintf(arqOutput, "[%s] REMOVE-OK\n", nome);
				}
				
				i = 1;
				break;
			}
			
			aux = aux->p;
		}while(aux != l->p);
		
		if(i == 0){
			fprintf(arqOutput, "[%s] REMOVE-ERROR\n", nome);
		}
	}else{
		fprintf(arqOutput, "[%s] REMOVE-ERROR\n", nome);
	}
}

int main(int argc, char* argv[]){
	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	
	Lista l;
	l.p = NULL;
	l.u = NULL;
	int i;
	
	if(arqInput != NULL && arqOutput != NULL){
		char linha[57] = {0};
		char nome[50] = {0};

		while(fgets(linha, sizeof(linha), arqInput) != NULL){
			switch(linha[0]){
				case 'A':
					for(i = 4; i < 57 && linha[i] != '\n'; i++){
						nome[i-4] = linha[i];
					}
					
					i = busca(&l, nome);
					if(i == 0){
						if(l.p == NULL){
							l.p = add(l.p, l.u, nome, arqOutput);
							l.u = l.p;
						}else{
							l.u = add(l.p, l.u, nome, arqOutput);
						}
					}else{
						fprintf(arqOutput, "[%s] ADD-ERROR\n", nome);
					}
				break;
				
				case 'S':
					for(i = 5; i < 57 && linha[i] != '\n'; i++){
						nome[i-5] = linha[i];
					}
					
					show(&l, nome, arqOutput);
				break;
				
				case 'R':
					for(i = 7; i < 57 && linha[i] != '\n'; i++){
						nome[i-7] = linha[i];
					}
					
					remover(&l, nome, arqOutput);
				break;
			}
			
			memset(&linha, 0, sizeof(linha));
			memset(&nome, 0, sizeof(nome));
		}
	}else{
		printf("Erro ao tentar abrir os Arquivos\n");
	}

	return 0;
}