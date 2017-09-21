#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    int HP =0;
    int HA =0;
    int HM =0;
    int PP=0;
    int PM=0;
    int PA=0;
typedef struct vets{
    int* vet;
    int tamanho_vet;
}vets;

typedef struct ordenar{
    int contador;
    char nome[10];
    vets *ordenar;
}ordenar;

int randomicoPA( int V[], int inicio,int fim) {
    int aux;
    int i =  inicio + labs(V[inicio])%(fim - inicio + 1);
    //trocar(&V[fim], &V[i]);
    aux = V[i];
    V[i] = V[fim];
    V[fim] = aux;
    PA++;

    return particionarPA(V, inicio, fim);
}
int randomicoHA( int V[], int inicio,int fim) {
    int aux;
    int i =  inicio + labs(V[inicio])%(fim - inicio + 1);
    //trocar(&V[fim], &V[i]);
    aux = V[i];
    V[i] = V[inicio];
    V[inicio] = aux;
    HA++;
    return hoareHA(V, inicio, fim);
}
int medianaPM( int V[], int inicio,int fim) {
    PM++;
    int n = fim - inicio + 1;
    int a = n/4 + inicio;
	int b = n/2 + inicio;
	int c = 3*n/4 + inicio;
	int k = V[a];
	int l = V[b];
	int m = V[c];
    if((k >= m && k <= l)||(k >= l && k <= m)){
        int aux;
        aux = V[a];
        V[a] = V[fim];
        V[fim] = aux;
	}else if((l >= m && l <= k)||(l >= k && l <= m)){
		 int aux;
        aux = V[b];
        V[b] = V[fim];
        V[fim] = aux;
	}else if((m >= l && m <= k)||(m >= k && m <= l)){
		 int aux;
        aux = V[c];
        V[c] = V[fim];
        V[fim] = aux;
	}

    return particionarPM(V, inicio, fim);

}
int medianaHM( int V[], int inicio,int fim) {
    HM++;
    int n = fim - inicio + 1;
    int a = n/4 + inicio;
	int b = n/2 + inicio;
	int c = 3*n/4 + inicio;
	int k = V[a];
	int l = V[b];
	int m = V[c];
    if((k >= m && k <= l)||(k >= l && k <= m)){
        int aux;
        aux = V[a];
        V[a] = V[inicio];
        V[inicio] = aux;
	}else if((l >= m && l <= k)||(l >= k && l <= m)){
		 int aux;
        aux = V[b];
        V[b] = V[inicio];
        V[inicio] = aux;
	}else if((m >= l && m <= k)||(m >= k && m <= l)){
		 int aux;
        aux = V[c];
        V[c] = V[inicio];
        V[inicio] = aux;
	}
    return hoareHM(V, inicio, fim);

}
int particionarPP(int V[],int inicio,int fim) {
        int pivo =  V[fim];
        //int pivo =
        int i = inicio - 1, j,aux;
        for (j = inicio; j < fim; j++) {
            if (V[j] <= pivo) {
                i = i + 1;
                aux = V[i];
                V[i] = V[j];
                V[j] = aux;
                PP++;
            }
        }
        //trocar(&V[i + 1], &V[fim]);
        aux = V[i + 1];
        V[i + 1] = V[fim];
        V[fim] = aux;
        PP++;
        return i + 1;
}
int particionarPM(int V[],int inicio,int fim) {
        int pivo =  V[fim];
        int i = inicio - 1, j,aux;
        for (j = inicio; j < fim; j++) {
            if (V[j] <= pivo) {
                i = i + 1;
                aux = V[i];
                V[i] = V[j];
                V[j] = aux;
                PM++;
            }
        }
        aux = V[i + 1];
        V[i + 1] = V[fim];
        V[fim] = aux;
        PM++;
        return i + 1;
}
int particionarPA(int Vet[],int inicio,int fim) {
        int lol =  Vet[fim];
        int i = inicio - 1, j,aux;
        for (j = inicio; j < fim; j++) {
            if (Vet[j] <= lol) {
                i = i + 1;
                aux = Vet[i];
                Vet[i] = Vet[j];
                Vet[j] = aux;
                PA++;
            }
        }
        //trocar(&V[i + 1], &V[fim]);
        aux = Vet[i + 1];
        Vet[i + 1] = Vet[fim];
        Vet[fim] = aux;
        PA++;
        return i + 1;
}
int hoareHP(int V[],int inicio,int fim) {
    int pivo = V[inicio];
    int i = inicio;
    int j = fim;
    int aux;
    while (i < j) {
        while (j > i && V[j] >= pivo) j--;
        while (i < j && V[i] < pivo) i++;
        if (i < j){
            aux = V[i];
            V[i] = V[j];
            V[j] = aux;
            HP++;

        }
    }
    return j;
}
int hoareHA(int V[],int inicio,int fim) {
    int pivo = V[inicio];
    int i = inicio;
    int j = fim;
    int aux;
    while (i < j) {
        while (j > i && V[j] >= pivo) j--;
        while (i < j && V[i] < pivo) i++;
        if (i < j){
            aux = V[i];
            V[i] = V[j];
            V[j] = aux;
            HA++;

        }
    }
    return j;
}
int hoareHM(int V[],int inicio,int fim) {
    int pivo = V[inicio];
    int i = inicio;
    int j = fim;
    int aux;
    while (i < j) {
        while (j > i && V[j] >= pivo) j--;
        while (i < j && V[i] < pivo) i++;
        if (i < j){
            aux = V[i];
            V[i] = V[j];
            V[j] = aux;
            HM++;

        }
    }
    return j;
}
void quicksortPP( vets * vet,int inicio, int fim) {
        PP++;

        int pivo;
        if(fim > inicio){

            pivo = particionarPP(vet,inicio,fim);
            quicksortPP(vet, inicio, pivo-1);
            quicksortPP(vet, pivo+1, fim);
        }
}
void quicksortPM( vets * vet,int inicio, int fim) {
        PM++;

        int pivo;
        if(fim > inicio){

            pivo = medianaPM(vet,inicio,fim);
            quicksortPM(vet, inicio, pivo-1);
            quicksortPM(vet, pivo+1, fim);
        }
}
void quicksortPA( vets * V,int inicio, int fim) {
        PA++;

        int pivo;
        if(fim > inicio){

            pivo = randomicoPA(V,inicio,fim);
            quicksortPA(V, inicio, pivo-1);
            quicksortPA(V, pivo+1, fim);
        }
}
void quicksortHP( vets * V,int inicio, int fim) {
    HP++;
    int lol;
    if(fim > inicio){
        lol = hoareHP(V,inicio,fim);
        quicksortHP(V, inicio, lol);
        quicksortHP(V, lol+1, fim);
    }
}
void quicksortHA( vets * V,int inicio, int fim) {
    HA++;
    int lol;
    if(fim > inicio){
        lol = randomicoHA(V,inicio,fim);
        quicksortHA(V, inicio, lol);
        quicksortHA(V, lol+1, fim);
    }
}
void quicksortHM( vets * V,int inicio, int fim) {
    HM++;
    int lol;
    if(fim > inicio){
        lol = medianaHM(V,inicio,fim);
        quicksortHM(V, inicio, lol);
        quicksortHM(V, lol+1, fim);
    }
}

void funcao_copiar(int *x, int *y, int tam){int i;
	for( i=0; i<tam; i++){
		x[i] = y[i];
	}
}

 int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
    if(input == NULL){
        printf("Arquivo invalido!\n");
    }else{
        int quant_vet,tamanho_vet,i,j,k;
        fscanf(input,"%d",&quant_vet);
        vets * vetores = (vets*)calloc(quant_vet,sizeof(vets));
        ordenar * tipo_ord = (ordenar*)malloc(6*sizeof(ordenar));
        for(i=0;i<quant_vet;i++){
            fscanf(input,"%d",&tamanho_vet);
            vetores[i].vet  = (int*)calloc(tamanho_vet,sizeof(int));
            vetores[i].tamanho_vet  = tamanho_vet;
            for(j=0;j<tamanho_vet;j++){
                fscanf(input,"%d",&vetores[i].vet[j]);
            }
        }
	for( i=0; i<6; i++)tipo_ord[i].ordenar = (vets *)malloc(sizeof(vets));
	for(i=0;i<quant_vet;i++){
        strcpy(tipo_ord[0].nome, "PP");
        strcpy(tipo_ord[1].nome, "PM");
        strcpy(tipo_ord[2].nome, "PA");
        strcpy(tipo_ord[3].nome, "HP");
        strcpy(tipo_ord[4].nome, "HM");
        strcpy(tipo_ord[5].nome, "HA");
        for( k=0; k<6; k++)tipo_ord[k].contador = 0;
        for( j=0; j<6; j++){
            int lol = vetores[i].tamanho_vet;
			tipo_ord[j].ordenar->vet = (int*)calloc(lol,sizeof(int));
			funcao_copiar(tipo_ord[j].ordenar->vet, vetores[i].vet, vetores[i].tamanho_vet);
			tipo_ord[j].ordenar->tamanho_vet = vetores[i].tamanho_vet;
           if(j==0){
                quicksortPP(tipo_ord[j].ordenar->vet,0,tipo_ord[j].ordenar->tamanho_vet-1);//OK
                tipo_ord[j].contador = PP;
           }
           if(j==1){
                quicksortPM(tipo_ord[j].ordenar->vet,0,tipo_ord[j].ordenar->tamanho_vet-1);//OK
                tipo_ord[j].contador = PM;
           }
           if(j==2){
                quicksortPA(tipo_ord[j].ordenar->vet,0,tipo_ord[j].ordenar->tamanho_vet-1);//OK
                tipo_ord[j].contador = PA;
           }
           if(j==3){
                quicksortHP(tipo_ord[j].ordenar->vet,0,tipo_ord[j].ordenar->tamanho_vet-1);//OK
                tipo_ord[j].contador = HP;
           }
           if(j==4){
                quicksortHM(tipo_ord[j].ordenar->vet,0,tipo_ord[j].ordenar->tamanho_vet-1);//OK
                tipo_ord[j].contador = HM;
           }
           if(j==5){
                quicksortHA(tipo_ord[j].ordenar->vet,0,tipo_ord[j].ordenar->tamanho_vet-1);//OK
                tipo_ord[j].contador = HA;
           }
		}
		HP = 0; HA= 0; HM = 0; PA =0; PM = 0; PP = 0;
    int p, l;
            ordenar * aux2 = (ordenar*)malloc(6*sizeof(ordenar));
            aux2[0].ordenar = (vets *)malloc(sizeof(vets));
            aux2[0].ordenar[0].vet = (int *)malloc(vetores[i].tamanho_vet*sizeof(int));
    for(p = 1; p < 6;p++){
        for(l = p; l > 0 && tipo_ord[l-1].contador > tipo_ord[l].contador ; l--){
            aux2[0] = tipo_ord[l];
            tipo_ord[l] = tipo_ord[l-1];
            tipo_ord[l-1] = aux2[0];
        }
    }
		fprintf(output,"[%d] ",i);
		fprintf(output,"N(%d) ",vetores[i].tamanho_vet);
		for(p = 0; p < 6;p++){
            if(p==5)fprintf(output,"%s(%d)\n",tipo_ord[p].nome,tipo_ord[p].contador);
            else fprintf(output,"%s(%d) ",tipo_ord[p].nome,tipo_ord[p].contador);
        }
	}
    }
    fclose(input);
    fclose(output);
    return 0;
}
