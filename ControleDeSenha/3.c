#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dados{
	char orgao[51];
	char nome[51];
	int idade;
	int chegada;
	int prioridade; // 1 = 60+    0 = 60-
	int freq;
}dados;
typedef struct fila{
	struct dados* cliente;
	int tamanho;
	int tamanho_remove;
	int construir;
}fila;
typedef struct orgaos{
	char organizacao[51];
	int frequencia;
}orgaos;
// variaveis e contadores globais
struct fila *acesso;
struct orgaos* comparador;
int *tamanho_vetores;
int houver_impressao=1;
//int T;
FILE *input;
FILE *output;
// 
void contadores();
void malloc_qtdorgao(int n);
void malloc_acesso(int quantidade_de_orgaos);
void construir_todos(char orgao[51],char nome[51],int idade,int chegou,int qtd_orgao);
int dibre(int hora, int minuto, int segundo);
void aplica_heapify(int i,int qtd_orgao);
void heapify(int i,int x,int T); // i é a posição atual, x a fila atual, T o tamanho
void print_remove(int qtd_orgao,int qtd_pessoa);
void ler_os_lixos(){
	int aux,i;
	char lixo[51];
	int lixo_int;
	fscanf(input,"%d",&aux);
	for (i=0;i<aux;i++){
	    fscanf(input,"%s %d",lixo,&lixo_int);
		tamanho_vetores[i]=0;		// zerando vetor
	}
	fscanf(input,"%d",&lixo_int);
	char preencher;
	char orgao[51];
	int hora,idade,minuto,segundo,x;
	for (i=0;i<lixo_int;i++){	
		fscanf(input,"%c",&preencher);
		for (x=0;preencher!=58;x++){	// tabela ascii ':' -> 58  								
			fscanf(input,"%c",&preencher);							
			if (preencher==58){														
				orgao[x]='\0';
				break;
			}
			orgao[x]=preencher;   // encadeando string
		}
		for (x=0;x<aux;x++){
			if (strcmp(orgao,comparador[x].organizacao)==0){
				tamanho_vetores[x]=tamanho_vetores[x]+1;
				break;
			}
		}
		for (x=0;preencher!=45;x++){		// tabela ascii '-' -> 45
			fscanf(input,"%c",&preencher);
			if (preencher==45){
				break;
			}
		}
		if (i+1==lixo_int) break;
		fscanf(input,"%d",&idade);
		fscanf(input,"%*c%d%*c%d%*c%d",&hora,&minuto,&segundo);
	}
}
int main (int argc, char *argv[]){
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	int qtd_orgao,qtd_pessoas,i;
	fscanf(input,"%d",&qtd_orgao);
	malloc_qtdorgao(qtd_orgao);	// cria o vetor comparador do tamanho qtd_orgaos
	for (i=0;i<qtd_orgao;i++){
		fscanf(input,"%s",comparador[i].organizacao);	// armazenando o info dos orgaos para comparar depois
		fscanf(input,"%d",&comparador[i].frequencia);
	}
	int posicaotemp=ftell(input);
	fseek(input,0,SEEK_SET);
	ler_os_lixos(); // funçao que vai contar o tamanho necessario pra cada vetor
	fseek(input,posicaotemp,SEEK_SET);
	malloc_acesso(qtd_orgao); // funçao que vai criar os vetores com seus respectivos tamanhos 
	i=0;
	fscanf(input,"%d",&qtd_pessoas);	
	char orgao[51], nome[51];
	int idade,hora,minuto,segundo;
	char temp;//
	int x=0;
	for(i=0;i<qtd_pessoas;i++){	// leitura caracter por caracter até achar " : ou - " dependendo do caso
		fscanf(input,"%c",&temp);
		for (x=0;temp!=58;x++){	// tabela ascii ':' -> 58  								
			fscanf(input,"%c",&temp); // EX LEITURA->    ORGAO:Nome da pessoa-88-00:00:00
			if (temp==58){	    // se caracter atual seja " : "												
			    orgao[x]='\0'; // fecha string e força a saida do laço interno
				break;
			}
			orgao[x]=temp;   // encadeando string
		}
		for (x=0;temp!=45;x++){		// tabela ascii '-' -> 45
			fscanf(input,"%c",&temp);
			if (temp==45){ 	  // caso caracter atual seja  " - " 
				nome[x]='\0'; // fecha string e força a saida do lado interno
				break;
			}
			nome[x]=temp;	// encadeando string
		}
		fscanf(input,"%d",&idade);
		fscanf(input,"%*c%d%*c%d%*c%d",&hora,&minuto,&segundo);
		construir_todos(orgao,nome,idade,dibre(hora,minuto,segundo),qtd_orgao);
	}
	aplica_heapify(i,qtd_orgao);
	print_remove(qtd_orgao,qtd_pessoas);
	return 0;
}

void aplica_heapify(int i,int qtd_orgao){ // aplica heapify a partir do ultimo nó com filho (tamanho-1)/2
	int j;
	for (i=0;i<qtd_orgao;i++){			
		for ( j= (((acesso[i].tamanho)-1)/2);j>=0;j--){
			heapify(j,i,acesso[i].tamanho);
		}
	}
}
void print_remove(int qtd_orgao,int qtd_pessoa){ // funçao responsavel por printar e remover as pessoas 
	int i,j;
	int tamanhototal=0;
//	int temp=1;
	int controle_de_linha=0;
	while(houver_impressao){
		tamanhototal=0;
		for (i=0;i<qtd_orgao;i++){
			controle_de_linha=1;
			if (acesso[i].tamanho_remove < 0){
				
				controle_de_linha=0;
			}
			else{ 
				fprintf(output,"[%s]",acesso[i].cliente[0].orgao); // se houver cliente na fila
				for (j=0;j<comparador[i].frequencia;j++){
					if (acesso[i].tamanho_remove >=0){		// se ainda houver elementos na fila
						fprintf(output," %s",acesso[i].cliente[0].nome);
						if ((j+1) != comparador[i].frequencia && acesso[i].tamanho_remove != 0) // se nao houver mais elementos ou o elemento a cima 
							fprintf(output,",");												// foi o ultimo nao printar ' , '	
						
						acesso[i].cliente[0]=acesso[i].cliente[acesso[i].tamanho_remove];				
						heapify(0,i,acesso[i].tamanho_remove);
						acesso[i].tamanho_remove--;
					}
				}
			}
			
	
			tamanhototal+=acesso[i].tamanho_remove;
			if (controle_de_linha)
				fprintf(output,"\n");
		}
		if (tamanhototal<=(qtd_orgao *(-1))){
			break;
		}
	}
	
	
}
void heapify(int i,int x,int T){ // funçao que ordena o vetor
	int P,E,D;
	P=i;
	E=(2*i)+1;
	D=(2*i)+2;
	
	if(E<T){  // checando se filho menor que tamanho do vetor 
		// Existem 3 casos. Se 2 idosos checar hora de chegada
		// Se 1 idoso e 1 jovem, idoso prioridade
		// se 2 jovns checar hora de chegada
		if  ((acesso[x].cliente[E].idade >= 60) && (acesso[x].cliente[P].idade >=60)){
			if (acesso[x].cliente[E].chegada < acesso[x].cliente[P].chegada){
				P=E;
			}
		}
		else if ((acesso[x].cliente[E].idade >=60) && (acesso[x].cliente[P].idade <60)){
			P=E;
		}
		else if ((acesso[x].cliente[E].idade <60) && (acesso[x].cliente[P].idade <60)){
			if (acesso[x].cliente[E].chegada < acesso[x].cliente[P].chegada){
				P=E;
			}
		}
	}
	
	if (D<T){// analogamente
		if ((acesso[x].cliente[D].idade >=60) && (acesso[x].cliente[P].idade >=60)){
			if (acesso[x].cliente[D].chegada < acesso[x].cliente[P].chegada){
				P=D;
			}
		}
		else if ((acesso[x].cliente[D].idade >=60) && (acesso[x].cliente[P].idade < 60)){
			P=D;
		}
		else if ((acesso[x].cliente[D].idade <60) && (acesso[x].cliente[P].idade <60)){
			if (acesso[x].cliente[D].chegada < acesso[x].cliente[P].chegada){
				P=D;
			}
		}
	}
	
	if (P != i){	// Caso P tenha sido alterado ao decorrer do programa, troca a posicao de I por P e aplica ordenação recurssivamente 
		dados aux;
		aux=acesso[x].cliente[i];
		acesso[x].cliente[i]=acesso[x].cliente[P];
		acesso[x].cliente[P]=aux;
		heapify(P,x,T);
	}
	
}
int dibre(int hora, int minuto, int segundo){ // função que vai pegar hora minuto e segundo e transformar num unico inteiro
	char auxiliar[51];
	char *p;
	//tratando os 8 casos de haver um zero a esquerda do inteiro e ele sumir
	
	if (hora>=10 && minuto >=10 && segundo>=10){
		sprintf(auxiliar,"%d%d%d",hora,minuto,segundo);
	}                     
	if (hora>=10 && minuto>=10 && segundo<10){
		sprintf(auxiliar,"%d%d0%d",hora,minuto,segundo);
	}
	if (hora>=10 && minuto<10 && segundo>=10){
		sprintf(auxiliar,"%d0%d%d",hora,minuto,segundo);
	}
	if (hora>=10 && minuto<10 && segundo<10){
		sprintf(auxiliar,"%d0%d0%d",hora,minuto,segundo);
	}
	if (hora<10 && minuto>=10 && segundo>=10){
		sprintf(auxiliar,"0%d%d%d",hora,minuto,segundo);
	}
	if (hora<10 && minuto>=10 && segundo<10){
		sprintf(auxiliar,"0%d%d0%d",hora,minuto,segundo);
	}
	if (hora<10 && minuto<10 && segundo>=10){
		sprintf(auxiliar,"0%d0%d%d",hora,minuto,segundo);
	}
	if (hora<10 && minuto<10 && segundo<10){
		sprintf(auxiliar,"0%d0%d0%d",hora,minuto,segundo);
	}
	//int chegou;                                                                
	//chegou=
	return strtol(auxiliar,&p,10);
}
void construir_todos(char orgao[51],char nome[51],int idade,int chegou,int qtd_orgao){ // adiciona todos os elementos em suas respectivas filas
	int indice;
	for (indice=0;indice<qtd_orgao;indice++){ // laço que acha o indice  em que deve ser adicionado
		if (!strcmp(orgao,comparador[indice].organizacao))	break;
	}
	strcpy(acesso[indice].cliente[acesso[indice].construir].orgao,orgao);
	strcpy(acesso[indice].cliente[acesso[indice].construir].nome,nome);
	acesso[indice].cliente[acesso[indice].construir].idade=idade;
	acesso[indice].cliente[acesso[indice].construir].chegada=chegou;
	acesso[indice].cliente[acesso[indice].construir].freq=comparador[acesso[indice].construir].frequencia;
	(acesso[indice].construir)--;
}
void malloc_qtdorgao(int n){	// cria a quantidade de filas, vvetor comparador e vetor com os tamanhos necessarios para cada fila
	acesso=malloc(n * sizeof(fila));
	comparador=malloc(n * sizeof(orgaos));
	tamanho_vetores=malloc(n * sizeof(int));
}
void malloc_acesso(int quantidade_de_orgaos){ // utiliza tamanho_vetor para alocar a quantidade exata de nós para cada fila e atribui os tamanhos na struct
	int i;
	for (i=0;i<quantidade_de_orgaos;i++){
		acesso[i].cliente=malloc(tamanho_vetores[i] * sizeof(dados));
		acesso[i].construir=tamanho_vetores[i]-1;
		acesso[i].tamanho=tamanho_vetores[i];
		acesso[i].tamanho_remove=tamanho_vetores[i]-1;
	}
}


