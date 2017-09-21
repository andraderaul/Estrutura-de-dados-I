#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* output;

typedef struct aposta{
 char cod[30];
 unsigned int acertos;
}aposta;

void muda(aposta *hx, int pai, int mf){
        aposta aux;
        //salva em aux
        aux.acertos=hx[pai].acertos;
        strcpy(aux.cod,hx[pai].cod);
        // troca o pai pelo filho
        strcpy(hx[pai].cod,hx[mf].cod);
        hx[pai].acertos=hx[mf].acertos;
        //posicao de maior filho recebe aux
        strcpy(hx[mf].cod,aux.cod);
        hx[mf].acertos=aux.acertos;

}

void heapfy_max(aposta * hx , unsigned int iu , int t){
    int pai=iu;
    int fe=(2*iu)+1; // esquerda
    int fd=(2*iu)+2; // direita

    if(fe<t){
        if(hx[fe].acertos>hx[pai].acertos){
         pai=fe;
        }
    }
    if(fd<t){
        if(hx[fd].acertos>hx[pai].acertos){
         pai=fd;
        }
    }
if(pai!=iu){
muda(hx,iu,pai);
heapfy_max(hx,pai,t);
}
}

int removeimprime(aposta* heapmax,int ac ,int t){
    int cont=0;
    int ir;
    while(ac==heapmax[0].acertos){
    fprintf(output,"%s\n",heapmax[0].cod);

   if(heapmax[0].acertos==ac){
     cont++;
    heapmax[0]=heapmax[t-1]; // substituiu pelo ultimo
    t=t-1; // decrementa tamanho
    ir=0;
    heapfy_max(heapmax,ir,t);
   }
}

return cont;
}

void heapfy_min(aposta * hm , unsigned int iu , int t){
    int pai=iu;
    int fe=(2*iu)+1; // esquerda
    int fd=(2*iu)+2; // direita

    if(fe<t){
        if(hm[fe].acertos<hm[pai].acertos){
         pai=fe;
        }
    }
    if(fd<t){
        if(hm[fd].acertos<hm[pai].acertos){
         pai=fd;
        }
    }
if(pai!=iu){
muda(hm,iu,pai);
heapfy_min(hm,pai,t);
}
}

int removeimprime2(aposta* heapmin,int ac ,int t){
    int cont=0;
    int ir;
     while(ac==heapmin[0].acertos){
    fprintf(output,"%s\n",heapmin[0].cod);
   if(heapmin[0].acertos==ac){
     cont++;
    heapmin[0]=heapmin[t-1]; // substituiu pelo ultimo
    t=t-1; // decrementa tamanho
    ir=0;
    heapfy_min(heapmin,ir,t);
   }
}
return cont;
}

  int main(int argc, char* argv[]){

	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);

int a,qtga;
int iu; //indice ultimo
int apt[15],result[10];
int premio,qtdap;
char cod[30];
int i,j,cont=0,ind=0;
FILE * input=fopen(argv[1],"r");
output=fopen(argv[2],"w");

fscanf(input,"%d",&premio);
fscanf(input,"%d",&qtdap);
int pma=premio/2;
aposta *heapmax;
heapmax =(aposta *) malloc ( sizeof (aposta )*(qtdap*2));
aposta *heapmin;
heapmin =(aposta *) malloc ( sizeof (aposta )*(qtdap*2));


fscanf(input,"%d %d %d %d %d %d %d %d %d %d ",&result[0],&result[1],&result[2],&result[3],&result[4],&result[5],&result[6],&result[7],&result[8],&result[9]);

   while((fscanf(input," %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",cod,&apt[0],&apt[1],&apt[2],&apt[3],&apt[4],&apt[5],&apt[6],&apt[7],&apt[8],&apt[9],&apt[10],&apt[11],&apt[12],&apt[13],&apt[14]))!=EOF){

    //COMPARA
        for(i=0;i<15;i++){
            for(j=0;j<10;j++){
                if(apt[i]==result[j]){
                    cont++;
                }
            }
        }
        //PASSA PRO STRUCT
        //MAX
        strcpy(heapmax[ind].cod,cod);
        heapmax[ind].acertos=cont;
        //MIN
        strcpy(heapmin[ind].cod,cod);
        heapmin[ind].acertos=cont;

        cont=0;//CONTADOR ZERADO
        ind++; // INCREMENTA
   }

   //MAX
    iu =((qtdap-1)/2);
    while(iu>=0){
    heapfy_max(heapmax,iu,qtdap);
    iu--;
    }

        a=heapmax[0].acertos;
        if(a>1){
            fprintf(output,"Faixa: %d acertos\n",a);
        }else{
            fprintf(output,"Faixa: %d acerto\n",a);
        }
        qtga=removeimprime(heapmax,a,qtdap);
        if(qtga>1){
        fprintf(output,"%d ganhadores de R$%d\n",qtga,pma/qtga);
        }else{
        fprintf(output,"%d ganhador de R$%d\n",qtga,pma/qtga);
        }
     fprintf(output,"\n");

     //MIN
    iu =((qtdap-1)/2);
    while(iu>=0){
    heapfy_min(heapmin,iu,qtdap);
    iu--;
    }

    a=heapmin[0].acertos;
    if(a>1){
     fprintf(output,"Faixa: %d acertos\n",a);
    }else{
    fprintf(output,"Faixa: %d acerto\n",a);
    }

       qtga=removeimprime2(heapmin,a,qtdap);
       if(qtga>1){
        fprintf(output,"%d ganhadores de R$%d",qtga,pma/qtga);
        }else{
        fprintf(output,"%d ganhador de R$%d",qtga,pma/qtga);
        }


fclose(input);
fclose(output);

 return 0;
 }

