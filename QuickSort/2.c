#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dados{
	int tamanho;
	int contador;
	int *conteudo;
	int tecnica;
}dados;
struct dados *acesso;
int PP=0,PM=1,PA=2,HP=3,HM=4,HA=5;
int houver_leitura=1,linha=0;
FILE *input;
FILE *output;

void troca(int a,int b,int tecnica){
	int temp=acesso[tecnica].conteudo[a];
	acesso[tecnica].conteudo[a]=acesso[tecnica].conteudo[b];
	acesso[tecnica].conteudo[b]=temp;
	acesso[tecnica].contador+=1;
}
void randomic(int inicio,int fim,int tecnica){	
	int aux=acesso[tecnica].conteudo[inicio];  // aux=v[inicio];
	
	if (acesso[tecnica].conteudo[inicio] < 0)	// tratamento do |V[ini]|
		aux=acesso[tecnica].conteudo[inicio] * (-1);

	int i=inicio+ (aux % (fim-inicio+1));
	
	switch (tecnica){
		case 2:	troca(i,fim,tecnica);
			break;
		case 5: troca(i,inicio,tecnica);
			break;

	}
}
void mediana(int inicio,int fim,int tecnica){
	int aux,i,j,v[3],a,b,c;
	a=((fim-inicio+1)/4)+inicio;
	b=((fim-inicio+1)/2)+inicio;
	c=(3*(fim-inicio+1)/4)+inicio;
	v[0]=acesso[tecnica].conteudo[a];
	v[1]=acesso[tecnica].conteudo[b];
	v[2]=acesso[tecnica].conteudo[c];
	for (i=0;i<3;i++){			// ordenando o vetor pra mandar 
		for (j=0;j<3;j++){		// a mediana (v[1]) por parametro
			if (v[i]<v[j]){		// na troca
				aux =v[i];
				v[i]=v[j];
				v[j]=aux;
			}
		}
	}	
	switch (tecnica){
/*PM*/	case 1:	
			/***/if (v[1]==acesso[tecnica].conteudo[a])	troca(a,fim,tecnica);	// troca v[1] pelo fim
			else if (v[1]==acesso[tecnica].conteudo[b]) troca(b,fim,tecnica);
			else if (v[1]==acesso[tecnica].conteudo[c]) troca(c,fim,tecnica);
			break;
/*HM*/	case 4:
			/***/if (v[1]==acesso[tecnica].conteudo[a])	troca(a,inicio,tecnica);	// troca v[1] pelo fim
			else if (v[1]==acesso[tecnica].conteudo[b]) troca(b,inicio,tecnica);
			else if (v[1]==acesso[tecnica].conteudo[c]) troca(c,inicio,tecnica);
			break;
		default: printf("algo de errado nao esta certo");
	}
}
void malloc_conteudo(int T){
	for (int i=0;i<6;i++){	
		acesso[i].conteudo=malloc(sizeof(int) * T);
		acesso[i].contador=0;
		acesso[i].tecnica=i;
	}
}	

int particionar(int inicio,int fim,int tecnica){
	int pivo;				
	pivo = acesso[tecnica].conteudo[fim];
	int i = inicio-1,j;
	for(j=inicio;j<fim;j++){
		if( acesso[tecnica].conteudo[j] <= pivo) {
			i++;
			troca(i,j,tecnica);
		}
	}
	troca(i+1,fim,tecnica);
	return i+1;
}
int hoare(int inicio, int fim,int tecnica){
	int pivo = acesso[tecnica].conteudo[inicio];
	int i = inicio;
	int j = fim;
	while(i < j){
		while(j > i && acesso[tecnica].conteudo[j] >= pivo) j--;
		while(i < j && acesso[tecnica].conteudo[i] < pivo) i++;
		if(i < j)	troca(i,j,tecnica);
	}
	return j;
}
void quicksort(int inicio,int fim,int tecnica){
	int pivo;
	acesso[tecnica].contador++;
	if (inicio<fim){
		/***/if(tecnica==PP){
			pivo = particionar(inicio,fim,tecnica);
			quicksort(inicio, pivo-1,tecnica);
			quicksort(pivo + 1, fim,tecnica);
		}
		else if(tecnica==PM){
			mediana(inicio,fim,tecnica);
			pivo = particionar(inicio,fim,tecnica);
			quicksort(inicio, pivo-1,tecnica);
			quicksort(pivo +1, fim,tecnica);
		}
		else if(tecnica==PA){
			randomic(inicio,fim,tecnica);	
			pivo = particionar(inicio,fim,tecnica);
			quicksort(inicio, pivo-1,tecnica);
			quicksort(pivo + 1, fim,tecnica);
		}
		else if (tecnica==HP){
		    pivo = hoare(inicio,fim,tecnica);
			quicksort(inicio,pivo,tecnica);
			quicksort(pivo + 1,fim,tecnica);
		}
		else if (tecnica==HM){
			mediana(inicio,fim,tecnica);
			pivo = hoare(inicio,fim,tecnica);
			quicksort(inicio, pivo,tecnica);
			quicksort(pivo + 1, fim,tecnica);
		}
		else if (tecnica==HA){
			randomic(inicio,fim,tecnica);	
			pivo = hoare(inicio,fim,tecnica);
			quicksort(inicio,pivo,tecnica);
			quicksort(pivo + 1,fim,tecnica);
		}
	}
}
void preenche_outros(int tamanho){
	int *aux=malloc(sizeof(int) * tamanho);
	for (int i=0;i<tamanho;i++)	aux[i]=acesso[0].conteudo[i];
	
	for (int i=1;i<6;i++){
		for (int j=0;j<tamanho;j++){
			acesso[i].conteudo[j]=aux[j];
		}
	}
	free(aux);
}
void constroi_quicksort(){
	for (int i=0;i<6;i++)	quicksort(0,acesso[i].tamanho-1,i);
}
void imprime(){
	int i,j;
	for (i=1;i<6;i++){
		for (j=i; j>0 && acesso[j-1].contador > acesso[j].contador;j--){
			dados temp=acesso[j-1];
			acesso[j-1]=acesso[j];
			acesso[j]=temp;
		}
	}
	fprintf(output,"[%d]",linha++);
	fprintf(output," N(%d)",acesso[0].tamanho);
	int a=0,b=0,c=0,d=0,e=0,f=0;
	for (int i=0;i<6;i++){
		/***/if (acesso[i].tecnica==PP && !a){
			fprintf(output," PP(%d)",acesso[i].contador);
			a++;
		}
		else if (acesso[i].tecnica==PM && !b){
			fprintf(output," PM(%d)",acesso[i].contador);
			b++;
		}
		else if (acesso[i].tecnica==PA && !c){
			fprintf(output," PA(%d)",acesso[i].contador);
			c++;
		}
		else if (acesso[i].tecnica==HP && !d){
			fprintf(output," HP(%d)",acesso[i].contador);
			d++;
		}
		else if (acesso[i].tecnica==HM && !e){
			fprintf(output," HM(%d)",acesso[i].contador);
			e++;
		}
		else if (acesso[i].tecnica==HA && !f){
			fprintf(output," HA(%d)",acesso[i].contador);
			f++;
		}
		if (i==5)	fprintf(output,"\n");
	}
	
}
int main(int argc,char *argv[]){
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	int i,j;
	int qtd_total_vetores;	
	int tamanho;
	fscanf(input,"%d",&qtd_total_vetores);
	while (houver_leitura){
		acesso=malloc(sizeof(dados) *6);
		fscanf(input,"%d",&tamanho);
		
		for (i=0;i<6;i++)	acesso[i].tamanho=tamanho;
		//printf("antes malloc_conteudo\n");
		malloc_conteudo(tamanho);
		//printf("depois malloc_conteudo\n");
		for (j=0;j<tamanho;j++){
			fscanf(input,"%d ",&acesso[0].conteudo[j]);
		}
		//printf("antes preenche outros\n");
		preenche_outros(tamanho);
		//printf("antes constroi quicksort\n");
		constroi_quicksort();
		//printf("depois quicksort\n");
		imprime();
		free(acesso);
		//printf("%d\n",d++);
		houver_leitura=(!feof(input));
		//printf("%d\n",houver_leitura);
	}
	
	return 0;
}


















