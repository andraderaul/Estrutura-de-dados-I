#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Users_Rede_Wesley
{
    char nome[50];
    struct Users_Rede_Wesley *anterior;
    struct Users_Rede_Wesley *proximo;
    struct Users_Rede_Wesley *amigoesquerda;
    struct Users_Rede_Wesley *amigodireita;

}Users_Rede_Wesley;

typedef struct Rede_Wesley
{
    Users_Rede_Wesley *cabeca;
    Users_Rede_Wesley *cauda;
}Rede_Wesley;

Rede_Wesley *iniciarRede_Wesley()
{
    Rede_Wesley *Lista_Wesley = (Rede_Wesley*) malloc (sizeof(Rede_Wesley));
    Lista_Wesley->cabeca = NULL;
    Lista_Wesley->cauda = NULL;
    return Lista_Wesley;
}

void ADD(char* Nome, Rede_Wesley *Lista_Wesley,FILE* output)
{
    if (Lista_Wesley->cabeca == NULL)
    {
        Users_Rede_Wesley *user = (Users_Rede_Wesley*) malloc (sizeof(Users_Rede_Wesley));
        strcpy(user->nome,Nome);
            Lista_Wesley->cabeca = user;
            Lista_Wesley->cauda = user;
            user->anterior = user;
            user->proximo = user;

            fprintf(output,"[%s] ADD-OK\n",Nome);
    }else{
        Users_Rede_Wesley *user = Lista_Wesley->cabeca, *add_new;
        int Existe = 0;
        while (user->proximo != Lista_Wesley->cabeca)
        {
            if(strcmp(user->nome,Nome) == 0){
                    user = user->proximo;
                    Existe = 1;
                }else{
                    user = user->proximo;
                }
        }
        if(strcmp(user->nome,Nome) == 0){
                    Existe = 1;
        }
        if (Existe == 1){
               fprintf(output,"[%s] ADD-ERROR\n",Nome);
        }else{
            add_new = (Users_Rede_Wesley*) malloc (sizeof(Users_Rede_Wesley));
            strcpy(add_new->nome,Nome);
            user->proximo = add_new;
            add_new->anterior = user;
            add_new->proximo = Lista_Wesley->cabeca;
            Lista_Wesley->cauda = add_new;
            fprintf(output,"[%s] ADD-OK\n",Nome);

        }

    }

}

void REMOVE(char* Nome, Rede_Wesley *Lista_Wesley,FILE* output)
{
    if (Lista_Wesley->cabeca == NULL){
        fprintf(output,"[%s] REMOVE-ERROR\n",Nome);
    }else{
        Users_Rede_Wesley *user = Lista_Wesley->cabeca;
        int Existe = 0;
        while (user->proximo != Lista_Wesley->cabeca)
        {
            if (user == Lista_Wesley->cabeca)
            {
                if(strcmp(user->nome,Nome) == 0)
                {
                    fprintf(output,"[%s] REMOVE-OK\n",Lista_Wesley->cabeca->nome);
                    Lista_Wesley->cabeca = user->proximo;
                    Lista_Wesley->cauda->proximo = Lista_Wesley->cabeca;
                    user = Lista_Wesley->cabeca;
                    Existe = 1;

                }
            }
            else
            {
                if(strcmp(user->nome,Nome) == 0)
                {
                    fprintf(output,"[%s] REMOVE-OK\n",user->nome);
                    Lista_Wesley->cabeca->amigodireita = user->amigodireita;
                    user->anterior->proximo = user->proximo;
                    user->proximo->anterior = user->anterior;
                    user = user->anterior;
                    Existe = 1;

                }
            }
            user = user->proximo;
        }
        if(strcmp(user->nome,Nome) == 0)
        {
            fprintf(output,"[%s] REMOVE-OK\n",user->nome);
            Lista_Wesley->cauda = user->anterior;
            Lista_Wesley->cauda->proximo = Lista_Wesley->cabeca;
            Lista_Wesley->cabeca->anterior = Lista_Wesley->cauda;


            Existe = 1;

        }
        else if (Existe == 0){
            fprintf(output,"[%s] REMOVE-ERROR\n",Nome);

        }
    }

}

void SHOW(char* Nome, Rede_Wesley *Lista_Wesley,FILE* output)
{
    if (Lista_Wesley->cabeca == NULL){
        fprintf(output,"[%s] SHOW-ERROR\n",Nome);
    }else{
        Users_Rede_Wesley *user = Lista_Wesley->cabeca;
        int Existe = 0;
        while (user->proximo != Lista_Wesley->cabeca)
        {
            if (user == Lista_Wesley->cabeca)
            {
                if(strcmp(user->nome,Nome) == 0)
                {
                    fprintf(output,"[%s]<-[%s]->[%s]\n",user->anterior, user->nome, user->proximo);
                    Existe = 1;
                }
            }
            else
            {
                if(strcmp(user->nome,Nome) == 0)
                {
                    fprintf(output,"[%s]<-[%s]->[%s]\n",user->anterior, user->nome, user->proximo);
                    Existe = 1;
                }
            }
            user = user->proximo;
        }
        if(strcmp(user->nome,Nome) == 0)
        {
            fprintf(output,"[%s]<-[%s]->[%s]\n",user->anterior, user->nome,user->proximo);
            Existe = 1;
        }else if (Existe == 0){
            fprintf(output,"[%s] SHOW-ERROR\n",Nome);
        }
    }

}
int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	if (input == NULL){
		printf("Arquivo de entrada nao existe");
	}else{
        Rede_Wesley *Lista_Wesley = iniciarRede_Wesley();
		while( ! feof(input) ) {
            char acao [7];
            char nome [50] = {0};
            char add [] = "ADD";
        	char show [] = "SHOW";
        	char remove [] = "REMOVE";
            int i;
            for(i=0;i<7;i++){
                fscanf(input, "%c", &acao[i]);
                if(acao[i] == ' '){
                    acao[i] = '\0';
                    break;
                }
            }
            for(i=0; i<50;i++){
                    fscanf(input, "%c", &nome[i]);
                    if ( nome [i] == '\n'){
                        nome [i] = '\0';
                        break;
                    }
            }
            if(strlen(acao) > 2 && strlen(nome) > 0){
                if(strcmp(acao,add) == 0){
            ADD(nome,Lista_Wesley,output);
            memset(nome, 0, sizeof(nome));
            }

             if(strcmp(acao,show) == 0){
                SHOW(nome,Lista_Wesley,output);
                memset(nome, 0, sizeof(nome));
            }
              if(strcmp(acao,remove) == 0){
                REMOVE(nome,Lista_Wesley,output);
                memset(nome, 0, sizeof(nome));
		    }
            }

        }
		}
	fclose(input);
	fclose(output);
    return 0;
}
