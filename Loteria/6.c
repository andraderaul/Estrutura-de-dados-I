#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvore{
	char hexa[17];
	int acertos;	
}arvore;
struct arvore *heapMAX;
struct arvore *heapMIN;
//pai
unsigned int pai(int i){
	return ((i-1)/2);
}
//filho esquerdo
unsigned int fesq(int i){
	return ((2*i)+1);
}
//filho direito
unsigned int fdir(int i){
	return ((2*i)+2);
}
//MAX
void heapifyMAX(arvore* V, unsigned int T, unsigned int i) {
	int auxiliar=0;
	char aux[17] = {0};
	unsigned int P = i;
	unsigned int E = fesq(i);
	unsigned int D = fdir(i);
	if(E < T && V[E].acertos > V[P].acertos){
		P = E;
	}	
	if(D < T && V[D].acertos > V[P].acertos){
		P = D;
	}
	if(P != i) {
		auxiliar = V[P].acertos; //aux pra salvar o num acertos
		strcpy(aux,V[P].hexa); //aux para salvar o nome
		V[P].acertos = V[i].acertos; // V[P] recebe V[pai do pai = avô]
		strcpy(V[P].hexa,V[i].hexa);// aux copia nome do avo pro pai
		V[i].acertos = auxiliar; //pai do pai recebe aux
		strcpy(V[i].hexa,aux);//pai do pai recebe nome aux
		heapifyMAX(V, T, P); //heapi no pai p
		
	}
}
//MIN
void heapifyMIN(arvore* V, unsigned int T, unsigned int i) {
	int auxiliar=0;
	char aux[17] = {0};
	unsigned int P = i;
	unsigned int E = fesq(i);
	unsigned int D = fdir(i);
	if(E < T && V[E].acertos < V[P].acertos){
		P = E;
	}	
	if(D < T && V[D].acertos < V[P].acertos){
		P = D;
	}
	if(P != i) {
		auxiliar = V[P].acertos; //aux pra salvar o num acertos
		strcpy(aux,V[P].hexa); //aux para salvar o nome
		V[P].acertos = V[i].acertos; // V[P] recebe V[pai do pai = avô]
		strcpy(V[P].hexa,V[i].hexa);// aux copia nome do avo pro pai
		V[i].acertos = auxiliar; //pai do pai recebe aux
		strcpy(V[i].hexa,aux);//pai do pai recebe nome aux
		heapifyMIN(V, T, P); //heapi no pai p
				
	}
}	
//REMOVE E IMPRIME MAX
void removeimprimeMAX(arvore* V, unsigned int T, unsigned int premio, FILE* output){
	int maior=0, aux,i=0;
	aux = V[0].acertos;
	if(V[0].acertos>1)
		fprintf(output,"Faixa: %d acertos\n",V[0].acertos); //pegando heap max	
	else
		fprintf(output,"Faixa: %d acerto\n",V[0].acertos);
	
	while(aux==V[0].acertos){
		fprintf(output,"%s\n",V[0].hexa);
		if(aux==V[0].acertos){
			maior++;
			V[0].acertos = V[T-1].acertos;
			V[T-1].acertos = '\0';
			T = T-1;
			heapifyMAX(V,T,i);
		}
	}
	if(maior>1)
		fprintf(output,"%d ganhadores de R$%d\n",maior,((premio/2)/maior));
	else
		fprintf(output,"%d ganhador de R$%d\n",maior,((premio/2)/maior));
	fprintf(output,"\n");		
}
//REMOVE E IMPRIME MIN
void removeimprimeMIN(arvore* V, unsigned int T, unsigned int premio, FILE* output){
int menor = 0,aux,i=0;
	aux = V[0].acertos;	
	
	if(V[0].acertos>1)
		fprintf(output,"Faixa: %d acertos\n",V[0].acertos); //pegando heap max	
	else
		fprintf(output,"Faixa: %d acerto\n",V[0].acertos); //pegando heap max	
			
	while(aux==V[0].acertos){
		fprintf(output,"%s\n",V[0].hexa);
		if(aux==V[0].acertos){
			menor++;
			V[0].acertos = V[T-1].acertos;
			V[T-1].acertos = '\0';
			T = T-1;
			heapifyMIN(V,T,i);
		}	
	}
	if(menor>1)
		fprintf(output,"%d ganhadores de R$%d",menor,((premio/2)/menor));
	else
		fprintf(output,"%d ganhador de R$%d",menor,((premio/2)/menor));
	
}
int main(int argc, char* argv[]){	
		printf("Quantidade de argumentos: %i\n", argc);
		printf("Nome do programa: %s\n\n", argv[0]);
		printf("Arquivo de entrada: %s\n", argv[1]);
		printf("Arquivo de saida: %s\n", argv[2]);
	//	FILE* input = fopen(argv[1],"r"); //LEITURA DO ARQUIVO
	//	FILE* output = fopen(argv[2],"w");
		
		
		FILE* input = fopen("inputsite.txt","r");
		FILE* output = fopen("output.txt","w");
	
	unsigned int premio, qtda,i=0,j=0,y=0,acertou=0,z=0;
	int *vetsorteado; //vetor com os numeros sorteados
	int *vetaposta; //vetor com os numeros apostados
	char codhexa[17]; //codigo em hexa;
	fscanf(input,"%d %d",&premio,&qtda);
	heapMAX = (arvore*)malloc(sizeof(arvore)*qtda);
	heapMIN = (arvore*)malloc(sizeof(arvore)*qtda);
	vetsorteado = (int*)malloc(sizeof(int)*10);	
	vetaposta = (int*)malloc(sizeof(int)*15);
	
	for(i=0;i<10;i++){
		fscanf(input,"%d",&vetsorteado[i]); //lendo os numeros sorteados
	}	
	
	for(i=0;i<qtda;i++){
		acertou =0;
		fscanf(input,"%s",codhexa);
		for(j=0;j<15;j++){
			fscanf(input,"%d",&vetaposta[j]);			
		}
		for(y=0;y<10;y++){
			for(z=0;z<15;z++){
				if(vetsorteado[y] == vetaposta[z])
					acertou++;
			}
		}
		//MAX
		strcpy(heapMAX[i].hexa,codhexa);
		heapMAX[i].acertos = acertou;		
		//MIN
		strcpy(heapMIN[i].hexa,codhexa);
		heapMIN[i].acertos = acertou;
	}
	for (i=qtda-1;i!=-1;i--){	
	//	printf("%d\n",i);		
		heapifyMIN(heapMIN,qtda,i); //MIN
		heapifyMAX(heapMAX,qtda,i); //MAX		
	}
/*	printf("MAX MIN\n");
	for(i=0;i<qtda;i++){
		printf("%d %d\n",heapMAX[i].acertos,heapMIN[i].acertos);
	}*/
	
	
	
	removeimprimeMAX(heapMAX,qtda,premio,output);
	removeimprimeMIN(heapMIN,qtda,premio,output);	
	
	//printf("FACIL DEMAIS");
	//esse pode ser o mais certos
return 0;
}
