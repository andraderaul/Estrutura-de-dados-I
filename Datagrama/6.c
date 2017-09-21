#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Wesley_Pack{
    int num_pack;
    int tampack;
    char ** bytes_pack;
}Wesley_Pack;

unsigned int esquerda (int i){
    return (2*i)+1;
}
unsigned int direita (int i){
    return (2*i)+2;
}
unsigned int pai ( int i){
    return (i-1)/2;
}
void sharingan(Wesley_Pack * Viciado,unsigned int pai, unsigned int i,Wesley_Pack * aux) {
    aux[0] = Viciado[i];
    Viciado[i] = Viciado[pai];
    Viciado[pai] = aux[0];
}
void heapifyMinimo(Wesley_Pack * Viciado,unsigned int tamanho, unsigned int i,Wesley_Pack * aux) {
    unsigned int pai = i;
    unsigned int esquerdaloka = esquerda(i);
    unsigned int direitaloka = direita(i);
    if(esquerdaloka < tamanho && Viciado[esquerdaloka].num_pack > Viciado[pai].num_pack) pai = esquerdaloka;
    if(direitaloka < tamanho && Viciado[direitaloka].num_pack > Viciado[pai].num_pack) pai = direitaloka;
    if(pai != i) {
    sharingan(Viciado, pai, i,aux);
    heapifyMinimo(Viciado, tamanho, pai,aux);
    }
}
int atual = 0;
int imprimido = 0;
 int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
    if(input == NULL){
        printf("Arquivo invalido!\n");
    }else{
        int packpages, packpagesler,i,j,w,tam_pack,ate,orde = 0;
        fscanf(input,"%d ",&packpages);
        fscanf(input,"%d\n",&packpagesler);
        Wesley_Pack * Wes = (Wesley_Pack*)malloc(sizeof(Wesley_Pack)*packpages);
        Wesley_Pack * aux = (Wesley_Pack*)calloc(sizeof(Wesley_Pack),packpages);
        char packs[512][15] = {0};
        int fubuki = packpagesler;
        for(i=0;i<packpages;i++){
            fscanf(input,"%d",&Wes[i].num_pack);
            fscanf(input,"%d",&tam_pack);
            Wes[i].tampack = tam_pack;
            Wes[i].bytes_pack = (char**)malloc(sizeof(char*)*tam_pack);
            for(j=0;j<tam_pack;j++){
                Wes[i].bytes_pack[j] = (char*)malloc(sizeof(char)*15);
            }
            for(j=0;j<tam_pack;j++){
                fscanf(input,"%s",&packs[j][0]);
            }
            for(j=0;j<tam_pack;j++) strcpy(Wes[i].bytes_pack[j],packs[j]);
            memset(packs, 0, sizeof(packs));
            orde++;
            if(orde == packpagesler || fubuki + 1 == packpages){
                for(w = (fubuki-1)/2 ; w >= 0; w--) heapifyMinimo(Wes,fubuki,w,aux);
                for(w = fubuki-1; w >= 0; w--) {
                  aux[0] = Wes[0];
                   Wes[0] = Wes[w];
                   Wes[w] = aux[0];
                   heapifyMinimo(Wes,w,0,aux);
                }
                int flag_imprimido = 0;
                int entrou = 0;
                for (ate = 0; ate < fubuki ; ate++){
                    if(Wes[ate].num_pack == atual){
                        entrou = 1;
                       if(flag_imprimido == 0){
                            fprintf(output,"[%d] ",imprimido);
                            flag_imprimido = 1;
                            imprimido++;
                       }
                    for(j=0;j<Wes[ate].tampack;j++)  fprintf(output,"%s ",Wes[ate].bytes_pack[j]);
                    atual++;
                    }else{
                        if(entrou == 1)fprintf(output,"\n");
                        entrou = 0;
                    }
                }
                orde = 0;
                fubuki = fubuki+packpagesler;
            }
            if(i == packpages-1){
                fubuki = packpages;
                for(w = (fubuki-1)/2 ; w >= 0; w--) heapifyMinimo(Wes,fubuki,w,aux);
                for(w = fubuki-1; w >= 0; w--) {
                  aux[0] = Wes[0];
                   Wes[0] = Wes[w];
                   Wes[w] = aux[0];
                   heapifyMinimo(Wes,w,0,aux);
                }
                int flag_imprimido = 0;
                int entrou = 0;
                for (ate = 0; ate < fubuki ; ate++){
                    if(Wes[ate].num_pack == atual){
                        entrou = 1;
                       if(flag_imprimido == 0){
                            fprintf(output,"[%d] ",imprimido);
                            flag_imprimido = 1;
                            imprimido++;
                       }
                    for(j=0;j<Wes[ate].tampack;j++)  fprintf(output,"%s ",Wes[ate].bytes_pack[j]);
                    atual++;
                    }else{
                        if(entrou == 1)fprintf(output,"\n");
                        entrou = 0;
                    }
                }
                fprintf(output,"\n");
            }
        }
    }
    fclose(input);
    fclose(output);
    return 0;
    }
