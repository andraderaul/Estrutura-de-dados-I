#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tSinonimo {
    char sin[31];
    struct tSinonimo *prox;
} tSinonimo;

typedef struct tListaSin {
    tSinonimo *ini;
    tSinonimo *ult;
} tListaSin;

typedef struct tKey {
    char palavra[31];
    tListaSin* lista;
} tKey;

typedef struct tPalavra {
    char palavra[31];
    tListaSin* lista;
    unsigned int height;
    struct tPalavra* right;
    struct tPalavra* left;
} tPalavra;

tPalavra* inserirPalavra (tKey* key,tPalavra* root);
tPalavra* balanceamento (tPalavra* root);
void lerSin (FILE* input, tListaSin* lista);
void lerPalavra(FILE* input, tKey* key);
void limpar(tKey* key);
tListaSin* criarLista(void);
tKey* criarKey(void);
tPalavra* criarPalavra(tKey* key);
int maiorQue(char key[31], char ref[31]);
int igualA(char* key, char* ref);
int altura (tPalavra* root);
void ajustarAltura(tPalavra* root);
int fatorBalanceamento (tPalavra* root);
tPalavra* rotacaoEsq(tPalavra* root);
tPalavra* rotacaoDir(tPalavra* root);
tPalavra* rotacaoDirEsq(tPalavra* root);
tPalavra* rotacaoEsqDir(tPalavra* root);
void procurarPalavra (FILE* output, tPalavra* root, char busca[31]);
void imprimirListaSin(FILE* output, tListaSin* lista);
tPalavra* freeArvore(tPalavra* root);
void freeNode(tPalavra* root);
void freeLista(tListaSin* lista);

int main (int argc, char* argv[])
{
    //************************//
    // ABERTURA DO ARQUIVO
    //************************//
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    if (input == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    //************************//
    // FORMAÇÃO DO DICIONÁRIO
    //************************//
    
    tPalavra* root = NULL;
    tKey *key = criarKey();
    
    unsigned int nPalavras = 0;
    fscanf(input, "%u", &nPalavras);
    
    for (int i = 0; i < nPalavras; i++)
    {
        lerPalavra(input, key);
        root = inserirPalavra(key, root);
        limpar(key);
    }
    
    //************************//
    // LER BUSCAS
    //************************//
    
    unsigned int nBuscas;
    fscanf(input, "%u", &nBuscas);
    char busca[31];
    
    for (int i = 0; i < nBuscas; i++)
    {
        fscanf(input, "%s", busca);
        procurarPalavra(output, root, busca);
    }
    
    //************************//
    // DESALOCAR MEMÓRIA
    //************************//
    
    free(key);
    key = NULL;
    //root = freeArvore(root);
    fclose(input);
    fclose(output);
    return 0;
}

tPalavra* inserirPalavra (tKey* key,tPalavra* root)
{
    if (root == NULL)
        root = criarPalavra(key);
    
    else
    {
        if (maiorQue(key->palavra, root->palavra))
            root->right = inserirPalavra(key, root->right);
        else
            root->left = inserirPalavra(key, root->left);
    }
    
    ajustarAltura(root);
    root = balanceamento(root);
    return root;
}

tPalavra* balanceamento (tPalavra* root)
{
    if (fatorBalanceamento(root) == 2)
    {
        if (fatorBalanceamento(root->right) == -1)
            root = rotacaoDirEsq(root);
        else
            root = rotacaoEsq(root);
    }
    
    else if (fatorBalanceamento(root) == -2)
    {
        if (fatorBalanceamento(root->left) == 1)
            root = rotacaoEsqDir(root);
        else
            root = rotacaoDir(root);
    }
    return root;
}

void lerSin (FILE* input, tListaSin* lista)
{
    tSinonimo* novo = (tSinonimo*)malloc(sizeof(tSinonimo));
    if (novo == NULL)
        exit(1);
    
    if (lista -> ini == NULL)
        lista -> ini = novo;
    else
        lista -> ult -> prox = novo;
    
    lista -> ult = novo;
    fscanf(input, "%s", novo -> sin);
    novo -> prox = NULL;
}

void lerPalavra(FILE* input, tKey* key)
{
    unsigned int nSin = 0;
    fscanf(input, "%s %i", key->palavra, &nSin);
    key->lista = criarLista();
    for (int i = 0; i < nSin; i++)
        lerSin(input, key->lista);
}

tListaSin* criarLista(void)
{
    tListaSin* lista = (tListaSin*)malloc(sizeof(tListaSin));
    if (lista == NULL)
        return NULL;
    
    lista -> ini = NULL;
    lista -> ult = NULL;
    return lista;
}

tKey* criarKey(void)
{
    tKey *key = (tKey*)malloc(sizeof(tKey));
    if (key == NULL)
        return NULL;
    
    return key;
}

void limpar(tKey* key)
{
    key -> lista = NULL;
    key->palavra[0] = '\0';
}

tPalavra* criarPalavra(tKey* key)
{
    tPalavra* novo = (tPalavra*)malloc(sizeof(tPalavra));
    
    strcpy(novo->palavra, key->palavra);
    novo->height = 1;
    novo->left = NULL;
    novo->right = NULL;
    novo->lista = key->lista;
    
    return novo;
}

int maiorQue(char key[31], char ref[31])
{
    if (strcmp(key, ref) > 0)
        return 1;
    else
        return 0;
}

int altura (tPalavra* root)
{
    if (root == NULL)
        return 0;
    else
        return root->height;
}

void ajustarAltura(tPalavra* root)
{
    unsigned int hr = altura(root->right);
    unsigned int hl = altura(root->left);
    
    root -> height = (hr > hl ? hr : hl) + 1;
}

int fatorBalanceamento (tPalavra* root)
{
    unsigned int hr = altura(root->right);
    unsigned int hl = altura(root->left);
    
    return hr-hl;
}

tPalavra* rotacaoEsq(tPalavra* root)
{
    tPalavra* eixo = root->right;
    root->right = eixo->left;
    eixo->left = root;
    root = eixo;
    
    ajustarAltura(root->left);
    ajustarAltura(root);
    return root;
}

tPalavra* rotacaoDir(tPalavra* root)
{
    tPalavra* eixo = root->left;
    root->left = eixo->right;
    eixo->right = root;
    root = eixo;
    
    ajustarAltura(root->right);
    ajustarAltura(root);
    return root;
}

tPalavra* rotacaoDirEsq(tPalavra* root)
{
    root->right = rotacaoDir(root->right);
    root = rotacaoEsq(root);
    return root;
}

tPalavra* rotacaoEsqDir(tPalavra* root)
{
    root->left = rotacaoEsq(root->left);
    root = rotacaoDir(root);
    return root;
}

int igualA(char* key, char* ref)
{
    if (strcmp(key, ref) == 0)
        return 1;
    else
        return 0;
}

void imprimirListaSin(FILE* output, tListaSin* lista)
{
    tSinonimo* atual = lista->ini;
    
    fprintf(output, "[");
    while (atual != NULL)
    {
        fprintf(output, "%s", atual->sin);
        if (atual->prox != NULL)
            fprintf(output, ", ");
        atual = atual->prox;
    }
    fprintf(output, "]\n");
    atual = NULL;
}

void procurarPalavra (FILE* output, tPalavra* root, char busca[31])
{
    if (root != NULL)
    {
        fprintf(output, "%s", root->palavra);
        
        if (igualA(busca, root->palavra))
        {
            fprintf(output, ":\n");
            imprimirListaSin(output, root->lista);
            return;
        }
        fprintf(output, "->");
        
        if (maiorQue(busca, root->palavra))
            procurarPalavra(output, root->right, busca);
        else
            procurarPalavra(output, root->left, busca);
    }
    else
        fprintf(output, "?:\n[-]\n");
}

void freeLista(tListaSin* lista)
{
    tSinonimo* atual = lista->ini;
    while (lista->ini != NULL)
    {
        lista->ini = lista->ini->prox;
        free(atual);
        atual = lista->ini;
    }
    
    lista->ult = NULL;
}

void freeNode(tPalavra* root)
{
    freeLista(root->lista);
    free(root->lista);
    root->lista = NULL;
}

tPalavra* freeArvore(tPalavra* root)
{
    if (root == NULL)
        return root;
    
    root->left = freeArvore(root->left);
    root->right = freeArvore(root->right);
    
    freeNode(root);
    free(root);
    root = NULL;
    return root;
}