    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    FILE * output;
    int flag=0;

    typedef struct cliente{
        char org[200];
        char nome[100];
        int idade;
        int hora;
        int min;
        int seg;
    }cliente; // clientes

    typedef struct org{
        char nameorg[200]; // nome
        int qatend;
        int qcli;
        struct cliente * cl;

    }org; // vetor de orgãos

    void muda(org *hx,int io, int pai, int mf){
        cliente aux;

        //salva em aux
        aux = hx[io].cl[pai];

        // troca o pai pelo filho

        hx[io].cl[pai]=hx[io].cl[mf];

        //posicao de maior filho recebe aux
        hx[io].cl[mf]=aux;

}

    void heapfy_max(org * hx , unsigned int io, unsigned int iu){

        int pai=iu;
        int fe=(2*iu)+1; // esquerda
        int fd=(2*iu)+2; // direita

      /*printf("%s\n",hx[io].cl[pai].nome);
        printf("%s\n",hx[io].cl[fe].nome);
        printf("%s\n",hx[io].cl[fd].nome);*/

    // se a idade do pai for maior ou igual a 60

    if(hx[io].cl[pai].idade>=60){

    // se o pai for maior de 60 só precisa avaliar se seus filhos são, caso não sejam, n muda nada

      // avalia o filho da esquerda

      if(fe<hx[io].qcli &&  hx[io].cl[fe].idade>=60){
            if(hx[io].cl[fe].hora == hx[io].cl[pai].hora){ // avalia se a hora é igual
                if(hx[io].cl[fe].min == hx[io].cl[pai].min){// avalia se o min é igual
                        if(hx[io].cl[fe].seg < hx[io].cl[pai].seg){ // avalia se os segundos do filho da esquerda são menores que o pai
                            pai = fe ; // atualiza o pai
                        }
                }else{ // else min
                if(hx[io].cl[fe].min < hx[io].cl[pai].min) pai = fe; // avalia se os minutos do filho da esquerda são menores que o pai // atualiza o pai
                } // fim else min
            }else{ // else hora
              if(hx[io].cl[fe].hora < hx[io].cl[pai].hora) pai = fe;// avalia se as horas do filho da esquerda são menores que o pai // atualiza o pai
            } //fim else hora
        }

         // avalia o filho da direita

        if(fd<hx[io].qcli &&  hx[io].cl[fd].idade>=60){
            if(hx[io].cl[fd].hora == hx[io].cl[pai].hora){ // avalia se a hora é igual
                if(hx[io].cl[fd].min == hx[io].cl[pai].min){// avalia se o min é igual
                        if(hx[io].cl[fd].seg < hx[io].cl[pai].seg){ // avalia se os segundos do filho da esquerda são menores que o pai
                            pai = fd ; // atualiza o pai
                        }
                }else{ // else min
                    if(hx[io].cl[fd].min < hx[io].cl[pai].min) pai = fd; // avalia se os minutos do filho da esquerda são menores que o pai // atualiza o pai
                    } // fim else min
            }else{ // else hora
              if(hx[io].cl[fd].hora < hx[io].cl[pai].hora) pai = fd;// avalia se as horas do filho da esquerda são menores que o pai // atualiza o pai
            } //fim else hora
        }
    }else{ // fim idade maior


    // se a idade do pai for menor que 60

    if(hx[io].cl[pai].idade<60){

    // se a idade do pai for menor que 60, primeiro avaliamos se a idade filho é maior ou igual a 60 ,se for já troca, caso n, avalia

    // filho da esquerda

    if(fe<hx[io].qcli){
         if(hx[io].cl[fe].idade>=60){ // se a idade for maior ja troca pq o pai é menor
            pai = fe;
            flag=1;
         }else{
            if(hx[io].cl[fe].hora == hx[io].cl[pai].hora){ // avalia se a hora é igual
                if(hx[io].cl[fe].min == hx[io].cl[pai].min){// avalia se o min é igual
                        if(hx[io].cl[fe].seg < hx[io].cl[pai].seg){ // avalia se os segundos do filho da esquerda são menores que o pai
                            pai = fe ; // atualiza o pai
                        }
                }else{ // else min
                if(hx[io].cl[fe].min < hx[io].cl[pai].min) pai = fe; // avalia se os minutos do filho da esquerda são menores que o pai // atualiza o pai
                } // fim else min
            }else{ // else hora
              if(hx[io].cl[fe].hora < hx[io].cl[pai].hora) pai = fe;// avalia se as horas do filho da esquerda são menores que o pai // atualiza o pai
            } //fim else hora
         }
    }

    //filho da direita

    if(fd < hx[io].qcli){
        if(flag == 1){
            if(hx[io].cl[fd].idade>=60){
            if(hx[io].cl[fd].hora == hx[io].cl[pai].hora){ // avalia se a hora é igual
                if(hx[io].cl[fd].min == hx[io].cl[pai].min){// avalia se o min é igual
                        if(hx[io].cl[fd].seg < hx[io].cl[pai].seg){ // avalia se os segundos do filho da esquerda são menores que o pai
                            pai = fd ; // atualiza o pai
                        }
                }else{ // else min
                    if(hx[io].cl[fd].min < hx[io].cl[pai].min) pai = fd; // avalia se os minutos do filho da esquerda são menores que o pai // atualiza o pai
                    } // fim else min
            }else{ // else hora
              if(hx[io].cl[fd].hora < hx[io].cl[pai].hora) pai = fd;// avalia se as horas do filho da esquerda são menores que o pai // atualiza o pai
            } //fim else hora
        }
        flag =0;
        }else{
        if(hx[io].cl[fd].idade>=60){ // se a idade for maior ja troca pq o pai é menor
            pai = fd;
         }else{
            if(hx[io].cl[fd].hora == hx[io].cl[pai].hora){ // avalia se a hora é igual
                if(hx[io].cl[fd].min == hx[io].cl[pai].min){// avalia se o min é igual
                        if(hx[io].cl[fd].seg < hx[io].cl[pai].seg){ // avalia se os segundos do filho da esquerda são menores que o pai
                            pai = fd ; // atualiza o pai
                        }
                }else{ // else min
                    if(hx[io].cl[fd].min < hx[io].cl[pai].min) pai = fd; // avalia se os minutos do filho da esquerda são menores que o pai // atualiza o pai
                    } // fim else min
            }else{ // else hora
              if(hx[io].cl[fd].hora < hx[io].cl[pai].hora) pai = fd;// avalia se as horas do filho da esquerda são menores que o pai // atualiza o pai
            } //fim else hora

         }

    }

    }

    } // fim idade menor

    } // fim else

  // printf("%d \n",pai);

if(pai!=iu){
muda(hx,io,iu,pai);
heapfy_max(hx,io,pai);
}
}


    int removeimprime(org* hm,int i, int j){
        if(hm[i].qcli!=0){
            if(j==0){
                fprintf(output,"[%s] %s",hm[i].nameorg,hm[i].cl[0].nome);
            }else{
               fprintf(output,", %s",hm[i].cl[0].nome);
            }




        hm[i].cl[0]=hm[i].cl[hm[i].qcli-1]; // substituiu pelo ultimo
        hm[i].qcli--; // decrementa tamanho
        //ir=0;
        heapfy_max(hm,i,0);
        }
    return hm[i].qcli;
    }


    int main(int argc, char* argv[]){
    int i=0,j=0;    // usado no while
    int qtdorg;   // quantidadde de  orgãos
    int qtdcli; // quantidade de clientes
    int cont=0;// contador
    int iu,ct=0;
    int soma=1;

    // Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);


    org *orgao; // cria um ponteiro do tipo orgão
    cliente *clientes; // ponteiro do tipo cliente

    FILE * input = fopen(argv[1],"r");
    output = fopen(argv[2],"w");

    fscanf(input,"%d",&qtdorg); // quantidade de orgãos

    orgao = (org *) malloc ( sizeof (org )*(qtdorg)); // cria um vetor de orgãos

    while(i<qtdorg){ // criar os orgãos

        fscanf(input,"%s %d",orgao[i].nameorg,&orgao[i].qatend);

   i++;
   }

    fscanf(input,"%d ",&qtdcli); // quantidade de clientes

    clientes = (cliente *) malloc ( sizeof (cliente )*(qtdcli)); // cria um vetor de clientes

   i=0;

   while(i<qtdcli){ // salvar todos os clientes

    fscanf(input," %[^:]*c",clientes[i].org); // nome do orgão

   fscanf(input,":%[^-]*c",clientes[i].nome); // nome do cliente

   fscanf(input,"-%d-%d:%d:%d",&clientes[i].idade,&clientes[i].hora,&clientes[i].min,&clientes[i].seg);
   i++;
   }


    for(i=0;i<qtdorg; i++){  // contar quantos maluco de cada tipo de orgão tem
        for(j=0;j<qtdcli ; j++){
            if(strcmp(orgao[i].nameorg,clientes[j].org)==0){

              cont++;
            }
        }
    orgao[i].qcli=cont;
    orgao[i].cl = (cliente *) malloc ( sizeof (cliente )*(cont)); // cria um vetor de clientes
    cont=0;
}

    for(i=0;i<qtdorg; i++){  // copiar cada pessoa para o vetor de seu orgão
        for(j=0;j<qtdcli ; j++){
            if(strcmp(orgao[i].nameorg,clientes[j].org)==0){
                orgao[i].cl[cont]=clientes[j];
              cont++;
            }
        }
    cont=0;
}

    for(i=0 ; i<qtdorg ; i++){
        iu=((orgao[i].qcli-1)-1)/2;
        while(iu>=0){
            heapfy_max(orgao,i,iu);
            iu--;
        }

    }

    while(soma>0){

    for(i=0;i<qtdorg; i++){  // contar quantos maluco de cada tipo de orgão tem

            if(orgao[i].qcli != 0){

                for(j=0;j<orgao[i].qatend ; j++){
                 removeimprime(orgao,i,j);
                }
                 fprintf(output,"\n");

            }
        }
            soma=0;
            ct=0;
            while(ct<qtdorg){
            soma= soma + orgao[ct].qcli ;
            ct++;
            }


    }

    fclose(input);
	fclose(output);
    return 0;
    }
