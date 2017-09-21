#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct controle{
	char orgao[100];
	int frequencia;
}controle;
typedef struct info{
	int idade;
	int hora;
	int minuto;
	int segundo;
	int freq;
	char nome[51];
	char orgao[51];
}info;
typedef struct filap{
	struct info* acesso;
	int tamanho;
	int quantos_faltam;
	int construcao;
}filap;
void heapify(filap *v,int i,int posicao,int T);

int main (int argc, char* argv[]){
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	int quantidade_de_orgao,quantidade_de_pessoas,i;

	fscanf(input,"%d",&quantidade_de_orgao);

	struct controle *comparador=(controle*)malloc(sizeof(controle) * quantidade_de_orgao);
	int *tamanho_fila=(int*)malloc(sizeof(int)* quantidade_de_orgao);
	for (i=0;i<quantidade_de_orgao;i++){
		fscanf(input,"%s",comparador[i].orgao);
		fscanf(input,"%d",&comparador[i].frequencia);
		tamanho_fila[i]=0;
	}
	fscanf(input,"%d",&quantidade_de_pessoas);
	struct info *auxiliar=(info*)malloc(sizeof(info)* quantidade_de_pessoas);
	char c;
	int cont;
	int indice=0;
	while(!feof(input)){
		c=fgetc(input);
		for (cont=0;cont<51;cont++){
			c=fgetc(input);
			if (c!=':'){
				auxiliar[indice].orgao[cont]=c;
			}
			else{
				auxiliar[indice].orgao[cont]='\0';
				break;
			}
		}
		for (cont=0;cont<51;cont++){
			c=fgetc(input);
			if (c=='-'){
				auxiliar[indice].nome[cont]='\0';
				break;
			}
			else auxiliar[indice].nome[cont]=c;
		}
		fscanf(input,"%d",&auxiliar[indice].idade);
		fscanf(input,"%*c%d%*c%d%*c%d",&auxiliar[indice].hora,&auxiliar[indice].minuto,&auxiliar[indice].segundo);

		for (i=0;i<quantidade_de_orgao;i++){
			if (strcmp(comparador[i].orgao,auxiliar[indice].orgao)==0){
				tamanho_fila[i]+=1;
				break;
			}
		}
		
		indice++;
	}
	struct filap *p=(filap*)malloc(sizeof(filap) *quantidade_de_orgao);		
	for (i=0;i<quantidade_de_orgao;i++){
		p[i].acesso=(info*)malloc(sizeof(info) * tamanho_fila[i]);
		p[i].tamanho=tamanho_fila[i];
		p[i].quantos_faltam=tamanho_fila[i]-1;
		p[i].construcao=0;
	}
	int j;
	for (i=0;i<quantidade_de_pessoas;i++){
		for (j=0;j<quantidade_de_orgao;j++){
			if (strcmp(auxiliar[i].orgao,comparador[j].orgao)==0){
				p[j].acesso[p[j].construcao]=auxiliar[i];
				p[j].construcao+=1;
			}
		}
	}
	
	for (i=0;i<quantidade_de_orgao;i++){
		for (j=((p[i].tamanho-1)/2);j>=0;j--){
			heapify(p,j,i,p[i].tamanho);
		}
	}
	int tamanhototal=0,controle_de_linha;
	while (1){
		tamanhototal=0;
		for (i=0;i<quantidade_de_orgao;i++){
			controle_de_linha=1;
			if (p[i].quantos_faltam < 0){
				controle_de_linha=0;
			}
			else{ 
				fprintf(output,"[%s]",p[i].acesso[0].orgao); // se houver cliente na fila
				for (j=0;j<comparador[i].frequencia;j++){
					if (p[i].quantos_faltam >=0){		// se ainda houver elementos na fila
						fprintf(output," %s",p[i].acesso[0].nome);
						if ((j+1) != comparador[i].frequencia && p[i].quantos_faltam != 0) // se nao houver mais elementos ou o elemento a cima 
							fprintf(output,",");												// foi o ultimo nao printar ' , '	
						
						p[i].acesso[0]=p[i].acesso[p[i].quantos_faltam];				
						heapify(p,0,i,p[i].quantos_faltam);
						(p[i].quantos_faltam)--;
					}
				}
			}
			tamanhototal+=p[i].quantos_faltam;
			if (controle_de_linha)
				fprintf(output,"\n");
		}
		if (tamanhototal<=(quantidade_de_orgao *(-1)))	break;
	}


	return 0;
}

void heapify(filap *v,int i,int posicao,int T){
	int P,E,D;
	P=i;E=2*i+1;D=2*i+2;
	int flag=0;
	if (E<T){
		//================= E idoso P jovem =================================
		if (v[posicao].acesso[E].idade >=60 && v[posicao].acesso[P].idade <60 && !flag){
			P=E;
			flag++;
		}
		// ===================== dois jovens==================================
		if (v[posicao].acesso[E].idade <60 && v[posicao].acesso[P].idade <60 && !flag){
			flag++;
			if (v[posicao].acesso[E].hora < v[posicao].acesso[P].hora){
				P=E;
			}
			else if (v[posicao].acesso[E].hora == v[posicao].acesso[P].hora){
				if (v[posicao].acesso[E].minuto < v[posicao].acesso[P].minuto){
					P=E;
				}
				else if (v[posicao].acesso[E].minuto == v[posicao].acesso[P].minuto){
					if (v[posicao].acesso[E].segundo < v[posicao].acesso[P].segundo){
						P=E;
					}
				}
			}
		}
		//====================== dois idosos=====================================
		if (v[posicao].acesso[E].idade >=60 && v[posicao].acesso[P].idade >=60 && !flag){
			flag++;
			if (v[posicao].acesso[E].hora < v[posicao].acesso[P].hora){
				P=E;
			}
			else if (v[posicao].acesso[E].hora == v[posicao].acesso[P].hora){
				if (v[posicao].acesso[E].minuto < v[posicao].acesso[P].minuto){
					P=E;
				}
				else if (v[posicao].acesso[E].minuto == v[posicao].acesso[P].minuto){
					if (v[posicao].acesso[E].segundo < v[posicao].acesso[P].segundo){
						P=E;
					}
				}
			}
		}	
	}
	flag =0;
	if (D<T){
		//================= E idoso P jovem =================================
		if (v[posicao].acesso[D].idade >=60 && v[posicao].acesso[P].idade <60 && !flag){
			P=D;
			flag++;
		}
		// ===================== dois jovens==================================
		if (v[posicao].acesso[D].idade <60 && v[posicao].acesso[P].idade <60 && !flag){
			flag++;
			if (v[posicao].acesso[D].hora < v[posicao].acesso[P].hora){
				P=D;
			}
			else if (v[posicao].acesso[D].hora == v[posicao].acesso[P].hora){
				if (v[posicao].acesso[D].minuto < v[posicao].acesso[P].minuto){
					P=D;
				}
				else if (v[posicao].acesso[D].minuto == v[posicao].acesso[P].minuto){
					if (v[posicao].acesso[D].segundo < v[posicao].acesso[P].segundo){
						P=D;
					}
				}
			}
		}
		//====================== dois idosos=====================================
		if (v[posicao].acesso[D].idade >=60 && v[posicao].acesso[P].idade >=60 && !flag){
			flag++;
			if (v[posicao].acesso[D].hora < v[posicao].acesso[P].hora){
				P=D;
			}
			else if (v[posicao].acesso[D].hora == v[posicao].acesso[P].hora){
				if (v[posicao].acesso[D].minuto < v[posicao].acesso[P].minuto){
					P=D;
				}
				else if (v[posicao].acesso[D].minuto == v[posicao].acesso[P].minuto){
					if (v[posicao].acesso[D].segundo < v[posicao].acesso[P].segundo){
						P=D;
					}
				}
			}
		}	
	}
	if (P!=i){
		info aux=v[posicao].acesso[i];
		v[posicao].acesso[i]=v[posicao].acesso[P];
		v[posicao].acesso[P]=aux;
		
		heapify(v,P,posicao,T);
	}
}






	
	


