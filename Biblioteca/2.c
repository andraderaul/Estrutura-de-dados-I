#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Biblioteca_Wesley{
    long long int ISBN;
    char titulo [100];
    char autor [50];
}Biblioteca_Wesley;
int intvit = 0;
int bivit = 0;
int totalbin = 0 ;
int totalint = 0 ;
// Busca binária iterativa
int busca_interpolada(Biblioteca_Wesley * livro,int tamanho,long long int num_ISBN) {
    unsigned int prime = 0, ulti = tamanho - 1; int contin=0;
    unsigned int posicao = (prime +(livro[ulti].ISBN - livro[prime].ISBN)%(ulti - prime + 1));
    while(ulti >= prime && livro[posicao].ISBN != num_ISBN) {
        if(livro[posicao].ISBN  > num_ISBN){
            ulti = posicao - 1;
            contin++;
        }else{
            prime = posicao + 1;
            contin++;
        }
        if (ulti >= prime){
            posicao = (prime +(livro[ulti].ISBN - livro[prime].ISBN)%(ulti - prime + 1));
        }
    }
    if (livro[posicao].ISBN == num_ISBN){
        contin++;
        totalint+=  contin; //total de passos dado
        return contin;
    }else{
        totalint+=  contin; //total de passos dado
        return contin;
    }
}
void busca_binaria(Biblioteca_Wesley * livro,int tamanho,long long int num_ISBN,FILE * output,int contin) {
    unsigned int prime = 0, ulti = tamanho - 1; int cont=0;
    unsigned int posicao = (ulti + prime) / 2;
    while(ulti >= prime && livro[posicao].ISBN != num_ISBN) {
        if(livro[posicao].ISBN  > num_ISBN){
            ulti = posicao - 1;
            cont++;
        }else{
            prime = posicao + 1;
            cont++;
        }
        posicao = (ulti + prime) / 2;
    }

    if(livro[posicao].ISBN  == num_ISBN){
        cont++;
        if(cont >= contin){//Da vitoria para interpolada se ganhar ou empatar
            intvit++;
        }else{//vitoria binaria
            bivit++;
        }
        totalbin+=  cont; //total de passos dado
        fprintf(output,"[%lld] BINARY: %d, INTERPOLATION: %d\nAuthor:%s\nTitle: %s\n",num_ISBN,cont,contin,livro[posicao].autor,livro[posicao].titulo);
    }else{
        cont++;
        if(cont >= contin){//Da vitoria para interpolada se ganhar ou empatar
            intvit++;
        }else{//vitoria binaria
            bivit++;
        }
        totalbin+=  cont; //total de passos dado
        fprintf(output,"[%lld] BINARY: %d, INTERPOLATION: %d\nISBN NOT FOUND\n",num_ISBN,cont,contin);
    }

}

int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	if (input == NULL){
		printf("Arquivo de entrada nao existe");
	}else{
	    int j;
        int livros;
        fscanf(input,"%d\n", &livros);
        Biblioteca_Wesley *Livros;
        Livros = (Biblioteca_Wesley *) malloc (livros * sizeof(Biblioteca_Wesley));
        int cont = livros;
        int consultas;
        int i = 0;
        for(i=0;i<cont;i++){
            fscanf(input,"%lld", &Livros[i].ISBN);
            for(j=0;j<50;j++){
                fscanf(input,"%c", &Livros[i].autor[j]);
                if(Livros[i].autor[j] == '|'){
                    Livros[i].autor[j] = '\0';
                    break;
                }
            }//Termina For autor
            for(j=0;j<100;j++){
                fscanf(input,"%c", &Livros[i].titulo[j]);
                if(Livros[i].titulo[j] == '\n'){
                    Livros[i].titulo[j] = '\0';
                    break;
                }
            }
        }//Termina For Geral
        fscanf(input,"%d\n", &consultas);
        long long int buscar;
        for(i=0;i<consultas;i++){
            fscanf(input,"%lld", &buscar);
            int conta = busca_interpolada(Livros,livros,buscar);
            busca_binaria(Livros,livros,buscar,output,conta);
        }
        int binp = totalbin/consultas;
        int intp = totalint/consultas;
        fprintf(output,"\nSEARCH RESULTS\nBINARY: %d @ ~%d STEPS\nINTERPOLATION: %d @ ~%d STEPS\n",bivit,binp,intvit,intp);
	}
	fclose(input);
	fclose(output);
return 0;
}
