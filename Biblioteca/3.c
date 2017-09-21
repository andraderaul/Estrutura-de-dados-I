#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Livro{
	long long int isbn;
	char autor[52];
	char titulo[102];
}Livro;

int buscaBinaria(Livro* l, int tamanho, long long int valor, int* contBin) {
	int inf = 0, sup = tamanho-1;
	int i = (sup + inf) / 2;
	(*contBin) = 1;
	// Busca iterativa
	while(sup >= inf && l[i].isbn != valor) {
		if(l[i].isbn > valor){
			sup = i - 1;
		}else{
			inf = i + 1;
		}
		i = (sup + inf) / 2;
		(*contBin) += 1;
	}
	
	return (l[i].isbn == valor) ? (i) : (-1);
}

int buscaInterpolada(Livro* l, int tamanho, long long int valor, int* contPol) {
	int inf = 0, sup = tamanho - 1;
	int i = (inf+(l[sup].isbn - l[inf].isbn)%(sup-inf+1));
	
	(*contPol) = 0;
	// Busca iterativa
	while(sup >= inf && l[i].isbn != valor) {
		if(l[i].isbn > valor){
			sup = i - 1;
			(*contPol)++;
		}else{
			inf = i + 1;
			(*contPol)++;
		}
		
		if(sup >= inf){
			i = (inf+(l[sup].isbn - l[inf].isbn)%(sup-inf+1));
		}
	}
	
	return (l[i].isbn == valor) ? (i) : (-1);
}

int main(int argc, char* argv[]){
	int numLivro = 0, numPesquisa = 0;
	int contBin = 0, contPol = 0;
	int i = 0, j = 0, k;
	int indice = 0;
	int numVicBin = 0, numVicPol = 0;
	int mediaBin = 0, mediaPol = 0;
	
	long long int isbn = 0, numBusca = 0;
	
	char linha[156] = {0};
	char autor[52] = {0};
	char titulo[102] = {0};
	
	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	
	if(arqInput != NULL){
		fscanf(arqInput, "%d\n", &numLivro);
		
		Livro* livro = (Livro*) malloc(sizeof(Livro)*numLivro);
		//Lendo livros.
		for(k = 0; k < numLivro; k++){
			fscanf(arqInput, "%lld ", &isbn);
			livro[k].isbn = isbn;
			fgets(linha, sizeof(linha), arqInput);
			
			for(i = 0; i < 156 && linha[i] != '|'; i++){
				autor[i] = linha[i];
			}
			
			j = i+1;
			for(i += 1; i < 156 && linha[i] != '\n'; i++){
				titulo[i-j] = linha[i];
			}
			
			strcpy(livro[k].autor, autor);
			strcpy(livro[k].titulo, titulo);
			
			memset(linha, 0, sizeof(linha));
			memset(autor, 0, sizeof(autor));
			memset(titulo, 0, sizeof(titulo));
		}
		
		//Lendo as pesquisas.
		fscanf(arqInput, "%d\n", &numPesquisa);
		for(i = 0; i < numPesquisa; i++){
			fscanf(arqInput, "%lld\n", &numBusca);
			
			indice = buscaBinaria(livro, numLivro, numBusca, &contBin);
			indice = buscaInterpolada(livro, numLivro, numBusca, &contPol);
			
			if(indice != -1){
				contPol++;
				
				if(contPol == contBin){
					numVicPol++;
				}else if(contBin < contPol){
					numVicBin++;
				}else{
					numVicPol++;
				}
				
				mediaBin += contBin;
				mediaPol += contPol;
				
				fprintf(arqOutput, "[%lld] BINARY: %d, INTERPOLATION: %d\n", livro[indice].isbn, contBin, contPol);
				fprintf(arqOutput, "Author: %s\n", livro[indice].autor);
				fprintf(arqOutput, "Title: %s\n", livro[indice].titulo);
			}else{
				mediaBin += contBin;
				mediaPol += contPol;
				
				if(contPol == contBin){
					numVicPol++;
				}else if(contBin < contPol){
					numVicBin++;
				}else{
					numVicPol++;
				}
				
				fprintf(arqOutput, "[%lld] BINARY: %d, INTERPOLATION: %d\n", numBusca, contBin, contPol);
				fprintf(arqOutput, "ISBN NOT FOUND\n");
			}
		}
		
		mediaBin = mediaBin/numPesquisa;
		mediaPol = mediaPol/numPesquisa;
		
		fprintf(arqOutput, "\n");
		fprintf(arqOutput, "SEARCH RESULTS\n");
		fprintf(arqOutput, "BINARY: %d @ ~%d STEPS\n", numVicBin, mediaBin);
		fprintf(arqOutput, "INTERPOLATION: %d @ ~%d STEPS", numVicPol, mediaPol);
		
	}else{
		printf("Erro ao tentar ler o arquivo.");
	}
	
	system("pause");
	fflush(arqInput);
	fclose(arqInput);
	return 0;
}