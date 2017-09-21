#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char nome[51];
	char orgaoPessoa[51];
	int idade;
	int hora[3];
	int prioridade;
}Pessoa;
Pessoa pessoa;
typedef struct {
	char orgao[51];
	int qtdAtendente;
	Pessoa *vetorPessoa;
}Elemento;
Elemento *elemento;
void remocao(Pessoa *pessoa, int x, int y){
	//nome, orgao, idade, hora, prioridade;
	pessoa[x].idade = pessoa[y].idade;
	pessoa[x].prioridade = pessoa[y].prioridade;
	pessoa[x].hora[0] = pessoa[y].hora[0];
	pessoa[x].hora[1] = pessoa[y].hora[1];
	pessoa[x].hora[2] = pessoa[y].hora[2];
	strcpy(pessoa[x].nome,pessoa[y].nome);
	strcpy(pessoa[x].orgaoPessoa,pessoa[y].orgaoPessoa);
}
void troca(Pessoa *pessoa, int x, int y){
	char nome[51];
	char orgaoPessoa[51];
	int idade;
	int hora[3];
	int prioridade;
	strcpy(nome, pessoa[x].nome);
	strcpy(pessoa[x].nome, pessoa[y].nome);
	strcpy(pessoa[y].nome, nome);
	strcpy(orgaoPessoa, pessoa[x].orgaoPessoa);
	strcpy(pessoa[x].orgaoPessoa, pessoa[y].orgaoPessoa);
	strcpy(pessoa[y].orgaoPessoa, orgaoPessoa);
	idade = pessoa[x].idade;
	pessoa[x].idade = pessoa[y].idade;
	pessoa[y].idade = idade;
	for(int i=0; i<3;i++){
		hora[i]=pessoa[x].hora[i];
		pessoa[x].hora[i] = pessoa[y].hora[i];
		pessoa[y].hora[i] = hora[i];
	}
	prioridade = pessoa[x].prioridade;
	pessoa[x].prioridade = pessoa[y].prioridade;
	(pessoa[y].prioridade) = prioridade;
}
void heapify(Pessoa *vetor, unsigned int T, unsigned int i){
	//int k;
	unsigned int pai = i;
	unsigned int esquerda = (2*i)+1;
	unsigned int direita = (2*i)+2;
	if(esquerda < T && vetor[esquerda].prioridade > vetor[pai].prioridade)
		pai = esquerda;
	else if(esquerda < T && vetor[esquerda].prioridade == vetor[pai].prioridade){
		if((vetor[esquerda].hora[0] < vetor[pai].hora[0]) || (vetor[esquerda].hora[0] == vetor[pai].hora[0] && vetor[esquerda].hora[1] <
			vetor[pai].hora[1])
			|| (vetor[esquerda].hora[0] == vetor[pai].hora[0] && vetor[esquerda].hora[1] == vetor[pai].hora[1] &&
			vetor[esquerda].hora[2] < vetor[pai].hora[2]))
			
			pai=esquerda;
		}
	
	if(direita < T && vetor[direita].prioridade > vetor[pai].prioridade) 
		pai = direita;
	else if(direita < T && vetor[direita].prioridade == vetor[pai].prioridade){
		if((vetor[direita].hora[0] < vetor[pai].hora[0]) ||
			(vetor[direita].hora[0] == vetor[pai].hora[0] && vetor[direita].hora[1] < vetor[pai].hora[1]) ||
			(vetor[direita].hora[0] == vetor[pai].hora[0] && vetor[direita].hora[1] == vetor[pai].hora[1] &&
		    vetor[direita].hora[2] < vetor[pai].hora[2]))
			pai=direita;
	}
	if(pai != i){
		troca(vetor, pai, i);
		heapify(vetor, T-1, pai);
	}
}
int main(int argc, char* argv[]){
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	char ch;
	int *contOrgaos;
	int j=0;
	int qtdOrgaos, qtdPessoas;
	fscanf(input, "%d %d ", &qtdOrgaos, &qtdPessoas);
	elemento = (Elemento*) malloc (sizeof(Elemento)*qtdOrgaos);
	contOrgaos = (int*) malloc (sizeof(int)*qtdOrgaos);
	for(int i=0;i<qtdOrgaos;i++) {
		fscanf(input, "%s %d ", elemento[i].orgao, &elemento[i].qtdAtendente);
		contOrgaos[i]=0;
	}
	int c = 2;
	fscanf(input, "%d ", &qtdPessoas);
	for(int i=0;i<qtdOrgaos;i++)
	elemento[i].vetorPessoa = (Pessoa*) malloc (sizeof (Pessoa)*100); 
	for(int i=0; i<qtdPessoas; i++){
		while(ch != ':'){
			ch = fgetc(input);
			pessoa.orgaoPessoa[j] = ch;
			j++;
		}
		pessoa.orgaoPessoa[j-1]='\0';
		j=0;
		ch='\0';
		while(ch != '-'){
			ch=fgetc(input);
			pessoa.nome[j]=ch;
			j++;
		}
		pessoa.nome[j-1]='\0';
		j=0;
		fscanf(input,"%d%*c%d%*c%d%*c%d ", &pessoa.idade, &pessoa.hora[0], &pessoa.hora[1], &pessoa.hora[2]);
		if(pessoa.idade >= 60) pessoa.prioridade = 1;
		else pessoa.prioridade = 0;
		for(int k=0;k<qtdOrgaos; k++){
			if(strcmp(elemento[k].orgao, pessoa.orgaoPessoa) == 0){
				elemento[k].vetorPessoa[contOrgaos[k]] = pessoa;
				contOrgaos[k]++;
				if(contOrgaos[k]+2 == 100){
					elemento[k].vetorPessoa = (Pessoa*) realloc (elemento[k].vetorPessoa, sizeof(Pessoa)*100*c);
					c++;
				}
			}
		}
		
	}
	int b=0;
	for(int i=0;i<qtdOrgaos;i++){
		for(b=contOrgaos[i]-1; b>=0;b--){
			heapify(elemento[i].vetorPessoa, contOrgaos[i], b);
		}
	}
	
	int atend=0;
	char aux[51];
	int contPessoas=1;
	int cont=0;
	for(int i=0;i<qtdOrgaos;i++){
		contPessoas=0;
		if(contOrgaos[i]!=0)
		fprintf(output, "[%s] ", elemento[i].orgao);
		atend = elemento[i].qtdAtendente;
		while(atend!=0){
			if(contOrgaos[i] != 0){
				strcpy(aux, elemento[i].vetorPessoa[contOrgaos[i]-1].nome);
				if(strcmp(aux, elemento[i].vetorPessoa[contOrgaos[i]-1].nome)==0){
					if(contPessoas+1 == elemento[i].qtdAtendente || contOrgaos[i]-1 ==0){
						fprintf(output, "%s\n", elemento[i].vetorPessoa[0].nome);	
					}
					else
						fprintf(output, "%s, ", elemento[i].vetorPessoa[0].nome);	
				}
				remocao(elemento[i].vetorPessoa, 0, contOrgaos[i]-1);
				heapify(elemento[i].vetorPessoa, contOrgaos[i]-1, 0);
				
				contOrgaos[i]--;
				contPessoas++;
				cont++;
			}
			atend--;
	//		
		}
		if(i+1 == qtdOrgaos && cont<qtdPessoas){
			i=-1;
		}
	}
	fclose(input);
	fclose(output);
	return 0;
}	
