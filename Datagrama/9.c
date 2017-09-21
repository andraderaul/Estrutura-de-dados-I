#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tpacote{
	
	int numpac;
	int tampac;
	char dados[513][5];	//vetor de struct
	
}tpacote;

typedef struct tflags{
	
	int indice;
	int parametro;
	int linha;
	
}tflags;

struct tflags aux; //salvador da patria

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
//heapfeels
void heapify(tpacote* V, unsigned int T, unsigned int i) {
	
	tpacote aux;
	unsigned int P = i;
	unsigned int E = fesq(i);
	unsigned int D = fdir(i);
	
	if(E < T && V[E].numpac < V[P].numpac){
		P = E;
	}	
	if(D < T && V[D].numpac < V[P].numpac){
		P = D;
	}
	if(P != i) {
		aux = V[i];
		V[i] = V[P];
		V[P] = aux;
		heapify(V,T,P);				
	}
}
void heapsort (tpacote* V, FILE* output){
	
	int cont = 0,c=0;
	
	while(V[0].numpac == aux.parametro){	
		if(cont==0){
			fprintf(output,"[%d] ",aux.linha);
			aux.linha++;			
			cont++;
		}
		
	for(c=0;c<V[0].tampac;c++){
		fprintf(output,"%s", V[0].dados[c]);
		if((V[0].tampac-1)!=c){ // para imprimir o " "
			fprintf(output," ");
		}			
	}		
	V[0]= V[aux.indice-1];
	heapify(V,aux.indice,0);
			
	aux.parametro++;
	aux.indice--;
	
		if(V[0].numpac == aux.parametro){ //para imprimir o " "
			fprintf(output," ");	
		} 
	}
	if(cont!=0){
		fprintf(output," \n");	
	}	
}
int main(int argc, char* argv[]) {
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	
//	FILE* input = fopen("input.txt","r");
//	FILE* output = fopen("output.txt","w");
	
	int ntotalpac, qtdpac;
	int i = 0, j = 0,y = 0,k = 0, p = 0;
	struct tpacote *pacotes;
	
	fscanf(input,"%d %d",&ntotalpac,&qtdpac);
	
	pacotes = (tpacote*)malloc(sizeof(tpacote)*ntotalpac);
 
	
	for(i=0; i<ntotalpac/qtdpac;i++){
		for(y=0;y<qtdpac;y++){
			
			fscanf(input,"%d %d",&pacotes[aux.indice].numpac, &pacotes[aux.indice].tampac);
			
			if(pacotes[aux.indice].numpac == aux.parametro){ //flag para reduzir o heapify
				p++;
			}
		
			for(j=0; j<pacotes[aux.indice].tampac;j++){
				fscanf(input,"%s ",pacotes[aux.indice].dados[j]);
			}
			aux.indice++;
		}
		
		if(p!=0){ // caso p != 0, encontrou o numero e da heapify
			for(k=(aux.indice-1)/2; k>=0;k--){
				heapify(pacotes,aux.indice,k);		
			}
			p = 0;
		}
		
		heapsort(pacotes,output);	
				
	}
	
	for(i=0; i<(ntotalpac%qtdpac);i++){
			
			fscanf(input,"%d %d",&pacotes[aux.indice].numpac, &pacotes[aux.indice].tampac);
			
			
			for(j=0; j<pacotes[aux.indice].tampac;j++){
				fscanf(input,"%s ",pacotes[aux.indice].dados[j]);
			}
			aux.indice++;

	}	
	for(k=(aux.indice-1)/2; k>=0;k--){
			heapify(pacotes,aux.indice,k);		
	}	
		heapsort(pacotes,output);	
	
	pacotes = NULL;
	free(pacotes);	
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa	
		
return 0;
}

