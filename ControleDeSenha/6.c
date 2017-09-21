#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Tempo{
	int hh;
	int mm;
	int ss;
}Tempo;

typedef struct Pessoa{
	char nome[51];
	Tempo t;
	int prioridade;
}Pessoa;

typedef struct Orgao{
	char nome[51];
	int cap;
	int maxFila;
	Pessoa* fila;
	int tamanho;
}Orgao;

//Função para saber se um horario é maior ou menor q outro.
//Retorna a < b = -1, a > b = 1, a == b = 0.
int tmpcmp(Tempo a, Tempo b){
	if(a.hh == b.hh){
		if(a.mm == b.mm){
			if(a.ss == b.ss){
				return 0;
			}else if(a.ss < b.ss){
				return -1;
			}else{
				return 1;
			}
		}else if(a.mm < b.mm){
			return -1;
		}else{
			return 1;
		}
	}else if(a.hh < b.hh){
		return -1;
	}else{
		return 1;
	}
}

//Função para achar o filho da esquerda
int esq(int i){
	return (i*2)+1;
}

//Função para achar o filho da direita
int dir(int i){
	return (i*2)+2;
}

//Função q faz a troca no heap.
void troca(Pessoa* a, int pai, int i){
	Pessoa aux = a[pai];
	a[pai] = a[i];
	a[i] = aux;
}

void hpf(Pessoa* a, unsigned int T, unsigned int i) {
	unsigned int P = i;
	unsigned int E = esq(i);
	unsigned int D = dir(i);
	
	if(E < T && a[E].prioridade == a[P].prioridade){
		if(tmpcmp(a[P].t, a[E].t) > 0){
			P = E;
		}
	}else if(E < T && a[E].prioridade > a[P].prioridade){
		P = E;
	}
	
	if(D < T && a[D].prioridade == a[P].prioridade){
		if(tmpcmp(a[P].t, a[D].t) > 0){
			P = D;
		}
	}else if(D < T && a[D].prioridade > a[P].prioridade){ 
		P = D;
	}
	
	if(P != i) {
		troca(a, P, i);
		hpf(a, T, P);
	}
}

void construcao(Pessoa* a, unsigned int tamanho){
	unsigned int i;
	unsigned int j = 0;
	
	do{
		i = ((tamanho-1)/2)-j;
		hpf(a, tamanho, i);
		j++;
	}while(i != 0);
}

//Função para achar o indice de algum órgão.
int buscaOrgao(Orgao* o, char org[51], int t){
	int i = -1;
	for(i = 0; i < t; i++){
		if(strcmp(o[i].nome, org) == 0){
			break;
		}
	}
	
	return i == t ? -1 : i;
}

void remover(Pessoa* a, unsigned int tamanho){
	if(a != NULL){
		a[0] = a[tamanho-1];
		hpf(a, tamanho-1, 0);
	}
}

int main(int argc, char* argv[]){
	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	
	if(arqInput != NULL){
		int numOrgao;
		int numPessoa;
		fscanf(arqInput, "%d\n", &numOrgao);
		
		Orgao* vetOrgao = (Orgao*) malloc(sizeof(Orgao)*numOrgao);
		
		int i;
		
		//Iniciando o vetor de Órgão
		for(i = 0; i < numOrgao; i++){
			fscanf(arqInput, "%s %d\n", vetOrgao[i].nome, &(vetOrgao[i].cap));
			vetOrgao[i].fila = (Pessoa*) malloc(sizeof(Pessoa)*200);
			vetOrgao[i].maxFila = 200;
			vetOrgao[i].tamanho = 0;
		}
		//Fim da Iniciando.
		
		fscanf(arqInput, "%d\n", &numPessoa);
		
		//Iniciando a leitura das pessoas.
		char org[51];
		char c;
		int j;
		int idade;
		Pessoa aux;
		int indice;
		for(i = 0; i < numPessoa; i++){
			//Lendo o órgão a quem a pessoa quer atendimento.
			memset(org, 0, sizeof(org));
			j = 0;
			do{
				c = fgetc(arqInput);
				if(c != ':'){
					org[j] = c;
					j++;
				}
			}while(c != ':');
			
			memset(aux.nome, 0, sizeof((aux.nome)));
			//Lendo o nome da pessoa.
			j = 0;
			do{
				c = fgetc(arqInput);
				if(c != '-'){
					aux.nome[j] = c;
					j++;
				}
			}while(c != '-');
			
			//Lendo a idade da pessoa e definindo sua prioridade e lendo a data.
			fscanf(arqInput, "%d-%d:%d:%d\n", &idade, &(aux.t.hh), &(aux.t.mm), &(aux.t.ss));
			if(idade < 60){
				aux.prioridade = 0;
			}else{
				aux.prioridade = 1;
			}
			
			indice = buscaOrgao(vetOrgao, org, numOrgao);
			if(indice != -1){
				if(vetOrgao[indice].tamanho < vetOrgao[indice].maxFila){
					vetOrgao[indice].fila[vetOrgao[indice].tamanho] = aux;
					vetOrgao[indice].tamanho++;					
				}else{
					vetOrgao[indice].fila = (Pessoa*) realloc(vetOrgao[indice].fila, (vetOrgao[indice].maxFila*2)*sizeof(Pessoa));
					vetOrgao[indice].maxFila = vetOrgao[indice].maxFila*2;
					
					vetOrgao[indice].fila[vetOrgao[indice].tamanho] = aux;
					vetOrgao[indice].tamanho++;
				}
			}
		}
		//Fim da Leitura;
		
		//Construção dos heap.
		for(i = 0; i < numOrgao; i++){
			construcao(vetOrgao[i].fila, vetOrgao[i].tamanho);
		}
		//Fim da construção
		
		i = 0;
		int k;
		while(i < numPessoa){
			for(j = 0; j < numOrgao; j++){
				if(vetOrgao[j].tamanho > 0){
					fprintf(arqOutput, "[%s] ", vetOrgao[j].nome);
					for(k = 0; k < vetOrgao[j].cap; k++){
						if(vetOrgao[j].tamanho > 0){
							if(k+1 == vetOrgao[j].cap | vetOrgao[j].tamanho-1 == 0){
								fprintf(arqOutput, "%s\n", vetOrgao[j].fila[0].nome);
							}else{
								fprintf(arqOutput, "%s, ", vetOrgao[j].fila[0].nome);
							}
							
							remover(vetOrgao[j].fila, vetOrgao[j].tamanho);
							vetOrgao[j].tamanho--;
							i++;
						}
					}
				}
			}
		}
	}else{
		printf("Erro ao tentar abrir o arquivo.");
	}
	return 0;
}