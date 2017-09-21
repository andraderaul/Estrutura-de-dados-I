#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	int numeroPacote;
	int tamanhoPacote;
	char *palavras;
}Elemento;
Elemento *pacote;
void troca(Elemento **p, int x, int y){
	int auxNumero, auxTamanho;
	char auxString[513];
	auxNumero = (*p)[x].numeroPacote;
	(*p)[x].numeroPacote = (*p)[y].numeroPacote;
	(*p)[y].numeroPacote = auxNumero;
	auxTamanho = (*p)[x].tamanhoPacote;
	(*p)[x].tamanhoPacote = (*p)[y].tamanhoPacote;
	(*p)[y].tamanhoPacote = auxTamanho;
	strcpy(auxString, (*p)[x].palavras);
	strcpy((*p)[x].palavras, (*p)[y].palavras);
	strcpy((*p)[y].palavras, auxString);
}
int k;
void heapify(Elemento **p, unsigned int T, unsigned int i){
	unsigned int pai = i;
	unsigned int esquerda = (2*i)+1;
	unsigned int direita = (2*i)+2;
	if(esquerda < T && (*p)[esquerda].numeroPacote > (*p)[pai].numeroPacote)
		pai = esquerda;
	if(direita < T && (*p)[direita].numeroPacote > (*p)[pai].numeroPacote)
		pai = direita;
	if(pai != i){
		troca(&(*p), pai, i);
		heapify(p, T-1, pai);
	}
}
void construir(Elemento **p, int T){
	for(int i=T/2; i>=0; i--){
		heapify(&(*p), T, i);
	}
}
void heapsort(Elemento **p,int n) {
	construir(&(*p), n);
	int i;
	for(i = n-1; i>0; i--) {
		troca(&(*p) ,0, i);
		heapify(&(*p), i, 0);
	}
}
int main(){
	FILE* input = fopen("input.txt", "r");
	FILE* output = fopen("output.txt", "w");
	int totalPacote;
	int flag=0;
	fscanf(input, "%d ", &totalPacote);
	int qtdPacote;
	fscanf(input, "%d ", &qtdPacote);

	pacote = (Elemento*) malloc (sizeof(Elemento)*24567);
	int j=0, i=0;
	//char ch;
	int jjjj=0;
	int parametro=0, cont=0;
	while(jjjj < totalPacote){
		for(i=0; i<qtdPacote && j<totalPacote; i++){
			jjjj++;
			printf("%d\n",jjjj);
			fscanf(input, "%d %d ", &pacote[j].numeroPacote, &pacote[j].tamanhoPacote);
			pacote[j].palavras = (char*) malloc (sizeof(char)*pacote[j].tamanhoPacote*4);
			fscanf(input, "%[^\n]s%*c", pacote[j].palavras);
			if(pacote[j].numeroPacote == parametro){
				flag=1;
			}
			j++;
		}
		if(flag){
		
			heapsort(&pacote, 24567);
			
			fprintf(output, "[%d] ", cont);
			for(k=parametro; k<j; k++){
			////	if(k!=pacote[k].numeroPacote){
				//	break;
				//}
				if (k+1 == j || k+1!=pacote[k+1].numeroPacote)
					fprintf(output, "%s\n", pacote[k].palavras);
				else 
					fprintf(output, "%s ", pacote[k].palavras);
			}
			parametro=k;
			flag=0;
			cont++;

		}
	}
}
