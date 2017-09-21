#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tpessoas{
	char orgao[51];
	char nome[51];
	unsigned int idade;
	int prioridade;
	unsigned int hora;
	unsigned int min;
	unsigned int seg;
	
}tpessoas;
typedef struct torgao{
	char orgao[51];	
	struct tpessoas *pessoas;
	unsigned int atendentes;
	int qtdpess;
}torgao;
//pai
unsigned int pai(int i){
	return ((i-1)/2);
}
//feels esquerdo
unsigned int fesq(int i){
	return ((2*i)+1);
}
//feels direito
unsigned int fdir(int i){
	return ((2*i)+2);
}
//heapfeels
void heapify(tpessoas* V, unsigned int T, unsigned int i){
	
	tpessoas aux;
	unsigned int P = i;
	unsigned int E = fesq(i); 
	unsigned int D = fdir(i);	
	
	//ESQUERDA
	if(E<T && V[E].prioridade > V[P].prioridade){
		P = E;
	}
	else if(E<T && V[E].prioridade == V[P].prioridade){
		if(V[E].hora < V[P].hora ||
		(V[E].hora == V[P].hora  && V[E].min < V[P].min) ||
		(V[E].hora == V[P].hora && V[E].min == V[P].min &&
		V[E].seg < V[P].seg)){
			P = E;
		}
	}	
	//DIREITA
	if(D<T && V[D].prioridade > V[P].prioridade){
		P = D;
	}
	else if(D<T && V[D].prioridade == V[P].prioridade){
		if(V[D].hora < V[P].hora ||
		(V[D].hora == V[P].hora  && V[D].min < V[P].min) ||
		(V[D].hora == V[P].hora && V[D].min == V[P].min &&
		V[D].seg < V[P].seg)){
			P = D;
		}
	}
				
	if(P!=i){
		aux = V[P];
		V[P] = V[i];
		V[i] = aux;
		heapify(V,T,P);
	}	
}

//removefeels
int removeimprime(torgao* O, tpessoas* V, unsigned int T, unsigned int j,char* orgao,FILE* output){
	int i = 0, aux = 0; 
	
		fprintf(output,"[%s] ",orgao);
		
		while(aux<O[j].atendentes && T>0){
			fprintf(output,"%s",V[0].nome);
			
			V[0] = V[T-1];
			T = T-1;
			
			if(aux<O[j].atendentes-1 && T!=0){
				fprintf(output,", ");
			}			
			O[j].qtdpess--;					
			aux++;
			
			heapify(V,T,i);		
		}
		
	return aux;
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
	
//	FILE* input = fopen("entradas.txt","r");
//	FILE* output = fopen("output.txt","w");
	
	
	int qtdorg,qtdpess, i=0,j=0,cont=0,aux=0;
	struct torgao* org;
	struct tpessoas* pessoas; 
	
	fscanf(input,"%d",&qtdorg);	
	org = (torgao*)malloc(sizeof(torgao)*qtdorg); //malloc quantidade de orgao
	
	for(i=0; i<qtdorg;i++){ //lendo os orgaos e os atendentes
		fscanf(input,"%s %d",org[i].orgao, &org[i].atendentes);		
	}
	
	fscanf(input,"%d",&qtdpess);
	pessoas = (tpessoas*)malloc(sizeof(tpessoas)*qtdpess);
	
	for(i=0; i<qtdpess;i++){
		fscanf(input," %[^:]*c",pessoas[i].orgao);
		fscanf(input,":%[^-]*c",pessoas[i].nome);
		fscanf(input,"-%d-%d:%d:%d",&pessoas[i].idade,&pessoas[i].hora,&pessoas[i].min,&pessoas[i].seg);
		
		if(pessoas[i].idade>=60){
			pessoas[i].prioridade = 1;
		}
		if(pessoas[i].idade<60){
			pessoas[i].prioridade = 0;
		}
	//	printf("%s \n",pessoas[i].nome);		
		
	}
	
	for(i=0;i<qtdorg;i++){ //contando quantas pessoas tem em cada orgao
		for(j=0;j<qtdpess;j++){
			if(strcmp(org[i].orgao,pessoas[j].orgao)==0){
				cont++;
			}	
		}
		org[i].qtdpess = cont;
		org[i].pessoas = (tpessoas*)malloc(sizeof(tpessoas)*cont);
		cont = 0;			
	}
	
	for(j=0;j<qtdorg;j++){
		for(i=0;i<qtdpess;i++){		
			if(strcmp(org[j].orgao,pessoas[i].orgao)==0){
				 org[j].pessoas[aux] = pessoas[i];	 //fazendo ponteiro org.pessoas = pessoas
					aux++;
			}
		}aux=0;		
	}
	
	for(i=0;i<qtdorg;i++){
		for(j = (org[i].qtdpess)-1;j>=0;j--){
			heapify(org[i].pessoas,org[i].qtdpess,j); //heapify
		}	
	}
	
	j=0;	
	int saiudafila=0;	
	do{	
		while(j<qtdorg){ 
			if(org[j].qtdpess>0){ // || aux>org[j].atendentes
				aux = removeimprime(org, org[j].pessoas,org[j].qtdpess, j,org[j].orgao,output);
				fprintf(output,"\n");					
				saiudafila = saiudafila+aux;
				
			//	printf("%d\n",saiudafila);
			}
			j++;		
		}
		j = 0;
						
	}while(saiudafila<qtdpess);
	
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa

return 0;
}
