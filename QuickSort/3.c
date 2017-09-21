#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    int cont=0;

    typedef struct Vetores{
        char nome[5];
        int tamanho;
        int *vetor;
        int desempenho;
    }Vetores;

    typedef struct imprime{
        Vetores imp[7];
    }imprime;

    void trocar(int *V ,  int *V2){
    cont++;
    int aux;
    aux = *V;
    *V = *V2;
    *V2 = aux;
    }

    void trocar_insercao(int *V ,  int *V2){
    int aux;
    aux = *V;
    *V = *V2;
    *V2 = aux;
    }

    void ordenacao_por_insercao(int *V, int n) {
        int i, j;
        for(i = 1; i < n; i = i + 1)
            for(j = i; j > 0 && V[j - 1] > V[j]; j--)
                trocar_insercao(&V[j], &V[j - 1]);
    }

    void trocar_insercao_fim(Vetores *V,int a ,int b){
       Vetores aux;
       aux.desempenho = V[a].desempenho;
       strcpy(aux.nome,V[a].nome);

       V[a].desempenho = V[b].desempenho;
       strcpy(V[a].nome,V[b].nome);

        V[b].desempenho = aux.desempenho;
       strcpy(V[b].nome,aux.nome);


    }

    void ordenacao_por_insercao_fim(Vetores *V, int n) {
        int i, j;
        for(i = 1; i < n; i = i + 1)
            for(j = i; j > 0 && V[j - 1].desempenho > V[j].desempenho; j--)
                trocar_insercao_fim(V,j,j - 1);
    }

   //PARTICIONAMENTO PADRÃO

    int particionar(int *V, int inicio, int fim) {
        int pivo = V[fim];
        int i = inicio - 1, j;
        for(j = inicio; j < fim; j++) {
            if(V[j] <= pivo) {
                i = i + 1;
                trocar(&V[i], &V[j]);
            }
        }
    trocar(&V[i + 1], &V[fim]);
    return i + 1;
    }

    void quicksort(int *V, int inicio, int fim) {
        cont++;
        if(inicio < fim) {
            int pivo = particionar(V, inicio, fim);
            quicksort(V, inicio, pivo - 1);
            quicksort(V, pivo + 1, fim);
        }
    }

    /*******************************************************/

    // RANDOMICO

    int randomico(int *V, int inicio, int fim) {
        int a;
        int i;
        if (V[inicio]<0){
          a = -V[inicio];
        }else{
         a = V[inicio];
        }

        i = inicio+a%(fim-inicio+1);
        trocar(&V[fim], &V[i]);
        return particionar(V, inicio, fim);
    }

    void quicksort_rand(int *V, int inicio, int fim) {
        cont++;
        if(inicio < fim) {
            int pivo = randomico(V, inicio, fim);
            quicksort_rand(V, inicio, pivo - 1);
            quicksort_rand(V, pivo + 1, fim);
        }
    }

    /*******************************************************/

    // MEDIANA

    void mediana(int V[],int inicio,int fim){ //achando a mediana

//	contador(variante,K); //cont

	int n = (fim-inicio)+1;
	int a = (n/4)+inicio;
	int b = (n/2)+inicio;
	int c = ((3*n)/4)+inicio;

	int Y[] = {V[a],V[b],V[c]};

	ordenacao_por_insercao(Y,3);

			if(Y[1]==V[a])
				trocar(&V[a],&V[fim]);
			else if (Y[1]==V[b])
				trocar(&V[b],&V[fim]);
			else
				trocar(&V[c],&V[fim]);

}

    void quicksort_med(int *V, int inicio, int fim) {
        cont++;
        if(inicio < fim) {
            mediana(V,inicio,fim);
            int pivo = particionar(V, inicio, fim);
            quicksort_med(V, inicio, pivo - 1);
            quicksort_med(V, pivo + 1, fim);
        }
    }

    /*******************************************************/

    // HOARE PADRÃO

    int hoare(int *V, int inicio, int fim) {
        int pivo = V[inicio];
        int i = inicio;
        int j = fim;

        while(i < j) {
            while(j > i && V[j] >= pivo) j--;
                while(i < j && V[i] < pivo) i++;

                    if(i < j) trocar(&V[i], &V[j]);
        }
    return j;
    }

    void quicksort_hoare(int *V, int inicio, int fim) {
        cont++;
        if(inicio < fim) {
            int pivo = hoare(V, inicio, fim);
            quicksort_hoare(V, inicio, pivo);
            quicksort_hoare(V,pivo+1, fim);
        }
    }

    /*******************************************************/

    // HOARE RANDOMICO

    int randomico_hoare(int *V, int inicio, int fim) {
        int a;
        int i;
        if (V[inicio]<0){
          a = -V[inicio];
        }else{
         a = V[inicio];
        }
        i = inicio + a % (fim - inicio + 1);
        trocar(&V[inicio], &V[i]);
        return hoare(V, inicio, fim);
    }

    void quicksort_hoare_rand(int *V, int inicio, int fim) {
        cont++;
        if(inicio < fim) {
            int pivo = randomico_hoare(V, inicio, fim);
            quicksort_hoare_rand(V, inicio, pivo);
            quicksort_hoare_rand(V, pivo + 1, fim);
        }
    }

  /*******************************************************/

  // HOARE MEDIANA
    void mediana_de_3_hoare(int *V,int inicio, int fim){

	int n = (fim-inicio)+1;
	int a = (n/4)+inicio;
	int b = (n/2)+inicio;
	int c = ((3*n)/4)+inicio;

	int Y[] = {V[a],V[b],V[c]};

	ordenacao_por_insercao(Y,3);

			if(Y[1]==V[a])
				trocar(&V[a],&V[inicio]);
			else if (Y[1]==V[b])
				trocar(&V[b],&V[inicio]);
			else
				trocar(&V[c],&V[inicio]);
}

    void quicksort_hoare_med(int *V, int inicio, int fim) {
       cont++;
       if(inicio < fim) {
            mediana_de_3_hoare(V,inicio,fim);
            int pivo = hoare(V, inicio, fim);
            quicksort_hoare_med(V, inicio, pivo );
            quicksort_hoare_med(V, pivo + 1, fim);
        }
    }

  /*******************************************************/

    int main(int argc, char* argv[]){

    // Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);

    Vetores *temp;
    Vetores *PP;
    Vetores *PM;
    Vetores *PA;
    Vetores *HP;
    Vetores *HM;
    Vetores *HA;


    int q_vetores, i , j ;

    FILE * input = fopen(argv[1],"r");
    FILE * output = fopen(argv[2],"w");

    fscanf(input,"%d",&q_vetores);
    temp = (Vetores*) malloc ( sizeof (Vetores)*(q_vetores));
    PP = (Vetores*) malloc ( sizeof (Vetores)*(q_vetores));
    PM = (Vetores*) malloc ( sizeof (Vetores)*(q_vetores));
    PA = (Vetores*) malloc ( sizeof (Vetores)*(q_vetores));
    HP = (Vetores*) malloc ( sizeof (Vetores)*(q_vetores));
    HM = (Vetores*) malloc ( sizeof (Vetores)*(q_vetores));
    HA = (Vetores*) malloc ( sizeof (Vetores)*(q_vetores));

    imprime *fim = (imprime*) malloc ( sizeof (imprime)*(q_vetores));

    for(i=0 ; i<q_vetores ; i++){
        fscanf(input,"%d",&temp[i].tamanho);

        PP[i].tamanho=temp[i].tamanho;
        strcpy(PP[i].nome,"PP");
        PP[i].vetor = (int*) malloc ( sizeof (int)*(temp[i].tamanho));

        PM[i].tamanho=temp[i].tamanho;
        strcpy(PM[i].nome,"PM");
        PM[i].vetor = (int*) malloc ( sizeof (int)*(temp[i].tamanho));

        PA[i].tamanho=temp[i].tamanho;
        strcpy(PA[i].nome,"PA");
        PA[i].vetor = (int*) malloc ( sizeof (int)*(temp[i].tamanho));

        HP[i].tamanho=temp[i].tamanho;
        strcpy(HP[i].nome,"HP");
        HP[i].vetor = (int*) malloc ( sizeof (int)*(temp[i].tamanho));

        HM[i].tamanho=temp[i].tamanho;
        strcpy(HM[i].nome,"HM");
        HM[i].vetor = (int*) malloc ( sizeof (int)*(temp[i].tamanho));

        HA[i].tamanho=temp[i].tamanho;
        strcpy(HA[i].nome,"HA");
        HA[i].vetor = (int*) malloc ( sizeof (int)*(temp[i].tamanho));

        temp[i].vetor =(int*) malloc ( sizeof (int)*(temp[i].tamanho));

            for(j=0 ; j<temp[i].tamanho ; j++){
                fscanf(input,"%d",&temp[i].vetor[j]);
                PP[i].vetor[j] = temp[i].vetor[j];
                PM[i].vetor[j] = temp[i].vetor[j];
                PA[i].vetor[j] = temp[i].vetor[j];
                HP[i].vetor[j] = temp[i].vetor[j];
                HM[i].vetor[j] = temp[i].vetor[j];
                HA[i].vetor[j] = temp[i].vetor[j];
            }
    }

    for(i=0 ; i<q_vetores ; i++){
       quicksort(PP[i].vetor,0,(PP[i].tamanho)-1); // Funciona
        PP[i].desempenho = cont;
        //printf("PP : %d - ",cont);
        cont = 0;

        quicksort_med(PM[i].vetor,0,(PM[i].tamanho)-1);
        PM[i].desempenho = cont;
       // printf("PM : %d - ",cont);
        cont = 0;

       quicksort_rand(PA[i].vetor,0,(PA[i].tamanho)-1); // funciona
        PA[i].desempenho = cont;
         //printf("PA : %d - ",cont);
        cont = 0;

        quicksort_hoare(HP[i].vetor,0,(HP[i].tamanho)-1);
        HP[i].desempenho = cont;
        // printf("HP : %d - ",cont);
        cont = 0;

        quicksort_hoare_med(HM[i].vetor,0,(HM[i].tamanho)-1);
        HM[i].desempenho = cont;
        // printf("HM : %d - ",cont);
        cont = 0;

        quicksort_hoare_rand(HA[i].vetor,0,(HA[i].tamanho)-1);
        HA[i].desempenho = cont;
        //printf("HA : %d \n\n",cont);
        cont = 0;

        fim[i].imp[0].desempenho =PP[i].desempenho;
        fim[i].imp[0].tamanho=PP[i].tamanho;
        strcpy(fim[i].imp[0].nome,PP[i].nome);

        fim[i].imp[1].desempenho =PM[i].desempenho;
        fim[i].imp[1].tamanho=PM[i].tamanho;
        strcpy(fim[i].imp[1].nome,PM[i].nome);

        fim[i].imp[2].desempenho =PA[i].desempenho;
        fim[i].imp[2].tamanho=PA[i].tamanho;
        strcpy(fim[i].imp[2].nome,PA[i].nome);

        fim[i].imp[3].desempenho =HP[i].desempenho;
        fim[i].imp[3].tamanho=HP[i].tamanho;
        strcpy(fim[i].imp[3].nome,HP[i].nome);

        fim[i].imp[4].desempenho =HM[i].desempenho;
        fim[i].imp[4].tamanho=HM[i].tamanho;
        strcpy(fim[i].imp[4].nome,HM[i].nome);

        fim[i].imp[5].desempenho =HA[i].desempenho;
        fim[i].imp[5].tamanho=HA[i].tamanho;
        strcpy(fim[i].imp[5].nome,HA[i].nome);

    }

    for(i=0 ; i<q_vetores ; i++){
       ordenacao_por_insercao_fim(fim[i].imp,6);

        fprintf(output,"[%d] N(%d)",i,fim[i].imp[0].tamanho);
        fprintf(output," %s(%d)",fim[i].imp[0].nome,fim[i].imp[0].desempenho);
        fprintf(output," %s(%d)",fim[i].imp[1].nome,fim[i].imp[1].desempenho);
        fprintf(output," %s(%d)",fim[i].imp[2].nome,fim[i].imp[2].desempenho);
        fprintf(output," %s(%d)",fim[i].imp[3].nome,fim[i].imp[3].desempenho);
        fprintf(output," %s(%d)",fim[i].imp[4].nome,fim[i].imp[4].desempenho);
        fprintf(output," %s(%d)\n",fim[i].imp[5].nome,fim[i].imp[5].desempenho);
    }


    fclose(input);
	fclose(output);
    return 0;
    }
