#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Estrutura Documento que tem um ponteiro para o proximo, na ideia de criar uma lista.
typedef struct Documento{
	char nome[50];
	int numPagina;
	int numPaginaImp;
	struct Documento* prox;
}Documento;

//Estrutura impressora com um ponteiro de Documento para armazenar a cabeça da lista
typedef struct Impressora{
	char nome[50];
	char status;//A variavel status quando for '1' significa que esta em uso e quando for '0' implica que não está em uso
	Documento* primeiro;
}Impressora;

//Fila de documentos em Vetor.
typedef struct Fila{
	int capacidade;
	int inicio;
	int tamanho;
	Documento* vetDoc;
}Fila;

//Pilha de documentos em Vetor.
typedef struct Pilha{
	int capacidade;
	int topo;
	Documento* vetDoc;
}Pilha;

int main(int argc, char* argv[]){
	int numPaginaImp = 0;//Variavel para contar quantas páginas foram impressas
	int numImp, numDoc;//Variaveis para armazenar o número de impressoras e documentos no arquivo.
	int i;//Variavel de controle.

	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	
	//Lento o número de impressoras q o programa terá e lendo os nomes das impresoras.
	fscanf(arqInput, "%d\n", &numImp);
	Impressora* impressora = (Impressora*) malloc(sizeof(Impressora)*numImp);
	
	for(i = 0; i < numImp; i++){
		fscanf(arqInput, "%s\n", impressora[i].nome);
		impressora[i].status = '0';
		impressora[i].primeiro = NULL;
	}
	//Fim da leitura
	
	//Inicio da leitura do número de arquivos, os nomes dos mesmos, suas páginas e armazenando na fila.
	fscanf(arqInput, "%d\n", &numDoc);
	Fila fila;
	fila.vetDoc = (Documento*) malloc(sizeof(Documento)*numDoc);
	fila.capacidade = numDoc;
	fila.inicio = 0;
	fila.tamanho = 0;
	
	for(i = 0; i < numDoc; i++){
		fscanf(arqInput, "%s %d\n", fila.vetDoc[i].nome, &(fila.vetDoc[i].numPagina));
		numPaginaImp += fila.vetDoc[i].numPagina;
		fila.vetDoc[i].prox = NULL;
		fila.vetDoc[i].numPaginaImp = 0;
		fila.tamanho += 1;
	}
	//Fim da leitura
	
	//Iniciando pilha
	Pilha pilha;
	pilha.capacidade = numDoc;
	pilha.topo = -1;
	pilha.vetDoc = (Documento*) malloc(sizeof(Documento)*numDoc);
	
	//Inicio do sistema de distribuição para as impressoras e empilhamento dos arquivos já impressos.
	int indice;
	int menorNumPagina;
	while(fila.tamanho != 0){
		indice = -1;
		for(i = 0; i < numImp; i++){
			if(impressora[i].status == '0'){
				indice = i;
				break;
			}
		}
		
		if(indice != -1){
			if(impressora[indice].primeiro == NULL){
				impressora[indice].primeiro = &fila.vetDoc[fila.inicio];
				fprintf(arqOutput, "[%s] %s-%dp\n", impressora[indice].nome, impressora[indice].primeiro->nome, impressora[indice].primeiro->numPagina, impressora[indice].primeiro->numPaginaImp);
				impressora[indice].status = '1';
			}else{
				//Adicionando um novo documento a impressora q esta livre.
				Documento* aux = impressora[indice].primeiro;
				impressora[indice].primeiro = &fila.vetDoc[fila.inicio];
				impressora[indice].primeiro->prox = aux;
				
				//Empilhando
				pilha.topo += 1;
				pilha.vetDoc[pilha.topo] = (*aux);
				
				aux = impressora[indice].primeiro;
				fprintf(arqOutput, "[%s] ", impressora[indice].nome);
				while(aux != NULL){
					if(aux->prox != NULL){
						fprintf(arqOutput, "%s-%dp, ", aux->nome, aux->numPagina, aux->numPaginaImp);
					}else{
						fprintf(arqOutput, "%s-%dp\n", aux->nome, aux->numPagina, aux->numPaginaImp);
					}
					aux = aux->prox;
				}
				
				impressora[indice].status = '1';
			}
		}else{
			indice = 0;
			menorNumPagina = impressora[indice].primeiro->numPagina-impressora[indice].primeiro->numPaginaImp;
			for(i = 1; i < numImp; i++){
				if(impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp < menorNumPagina){
					menorNumPagina = impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp;
					indice = i;
				}
			}
			
			for(i = 0; i < numImp; i++){
				impressora[i].primeiro->numPaginaImp += menorNumPagina;
			}

			
			//Adicionando um novo documento a impressora q esta livre.
			Documento* aux = impressora[indice].primeiro;
			impressora[indice].primeiro = &fila.vetDoc[fila.inicio];
			impressora[indice].primeiro->prox = aux;
			
			//Empilhando
			pilha.topo += 1;
			pilha.vetDoc[pilha.topo] = (*aux);
			
			aux = impressora[indice].primeiro;
			fprintf(arqOutput, "[%s] ", impressora[indice].nome);
			while(aux != NULL){
				if(aux->prox != NULL){
					fprintf(arqOutput, "%s-%dp, ", aux->nome, aux->numPagina, aux->numPaginaImp);
				}else{
					fprintf(arqOutput, "%s-%dp\n", aux->nome, aux->numPagina, aux->numPaginaImp);
				}
				aux = aux->prox;
			}
			
			for(i = 0; i < numImp; i++){
				if(impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp == 0){
					impressora[i].status = '0';
				}
			}
		}
		

		fila.inicio = (fila.inicio + 1) % fila.capacidade;
		fila.tamanho -= 1;
	}
	
	int tf = 0;
	do{
		tf = 0;
		menorNumPagina = 0;
		for(i = 0; i < numImp; i++){
			if(impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp != 0){
				menorNumPagina = impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp;
				indice = i;
				tf = 1;
				break;
			}
		}
		
		if(tf == 1){
			//Pegando o menorNumPagina
			for(i = 0; i < numImp; i++){
				if(impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp != 0){
					if(impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp < menorNumPagina){
						menorNumPagina = impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp;
						indice = i;
					}
					impressora[i].status = '1';
				}else{
					impressora[i].status = '0';
				}
					
			}
			
			//Empilhando
			Documento* aux = impressora[indice].primeiro;
			pilha.topo += 1;
			pilha.vetDoc[pilha.topo] = (*aux);
			
			impressora[indice].primeiro->numPaginaImp += menorNumPagina;
			impressora[indice].status = '0';
			
			for(i = 0; i < numImp; i++){
				if(impressora[i].status == '1'){
					impressora[i].primeiro->numPaginaImp += menorNumPagina;
					if(impressora[i].primeiro->numPagina-impressora[i].primeiro->numPaginaImp == 0){
						aux = impressora[i].primeiro;
						pilha.topo += 1;
						pilha.vetDoc[pilha.topo] = (*aux);
						impressora[i].status = '0';
					}else{
						impressora[i].status = '1';
					}
				}
			}
		}
	}while(tf == 1);
	
	fprintf(arqOutput, "%d\n", numPaginaImp);
	while(pilha.topo > -1){
		fprintf(arqOutput, "%s-%dp\n", pilha.vetDoc[pilha.topo].nome, pilha.vetDoc[pilha.topo].numPagina);
		pilha.topo -= 1;
	}
	
	fflush(arqInput);
	fclose(arqInput);
	system("pause");
	return 0;
}