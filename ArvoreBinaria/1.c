#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node {
    char nome[51];
    char perm[3];
    unsigned long nbytes;
    int i;
    struct node *left;
    struct node *right;
};

struct node* lerEntrada(FILE* input, struct node* key);
struct node* buscar(struct node* root, char key[51]);
struct node* inserir(struct node* root, struct node* key);
void inOrder (FILE* output, struct node* root);
void preOrder (FILE* output, struct node* root);
void postOrder (FILE* output, struct node* root);
void imprimir (FILE* output, struct node* root);

int main(int argc, char* argv[]) {
    
    /** *********************** **/
    // ABRIR ARQUIVO
    /** *********************** **/
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    assert (input != NULL);
    
    /** *********************** **/
    // CRIAR ESTRUTURA DE ÁRVORE
    /** *********************** **/
    
    struct node *root = NULL;
    
    /** *********************** **/
    // LEITURA DA ENTRADA
    /** *********************** **/
    
    struct node* key = (struct node*)calloc(1, sizeof(struct node));
    int nEntradas; fscanf(input, "%i", &nEntradas);
    for (int i = 0; i < nEntradas; i++)
    {
        key = lerEntrada(input, key);
        key -> i = i;
        root = inserir(root, key);
    }
    
    /** *********************** **/
    // IMPRESSÃO DA ÁRVORE
    /** *********************** **/
    
    fprintf(output, "EPD:\n");
    inOrder(output, root);
    fprintf(output, "PED:\n");
    preOrder(output, root);
    fprintf(output, "EDP:\n");
    postOrder(output, root);
    
    return 0;
}

struct node* inserir(struct node* root, struct node* key)
{
    if (root == NULL)
    {
        root = (struct node*)malloc(sizeof(struct node));
        *root = *key;
    }
    else
    {
        struct node* node = buscar(root, key -> nome);
        
        //Se o arquivo já existir
        if (strcmp(node -> nome, key -> nome) == 0)
        {
            //Se o arquivo permitir reescrita
            if (strcmp(node -> perm, "rw") == 0)
            {
                strcpy(node -> perm, key -> perm);
                node -> nbytes = key -> nbytes;
                node -> i = key -> i;
            }
        }
        else //Caso o arquivo não exista
        {
            //Compare o pai - o node novo entra na esquerda ou direita?
            if (strcmp(node -> nome, key -> nome) > 0)
            {
                node -> left = (struct node*)malloc(sizeof(struct node));
                node = node -> left;
                *node = *key;
            }
            
            else
            {
                node -> right = (struct node*)malloc(sizeof(struct node));
                node = node -> right;
                *node = *key;
            }
        }
    }
    
    return root;
}

struct node* buscar(struct node* root, char key[51])
{
    struct node* node = root;
    
    while (strcmp(node -> nome, key) != 0) //Se o node atual é um arquivo repetido, saia do loop e retorne-o.
    {
        //GREATER THAN
        if (strcmp(node -> nome, key) > 0)
        {
            //Se o arquivo procurado deveria está à esquerda, mas a posição está vazia, retorne o pai.
            if (node -> left == NULL)
                return node;
            //Se não estiver vazia, continue percorrendo a árvore.
            else
                node = node -> left;
        }
        //LESS THAN
        else
        {
            //Se o arquivo procurado deveria está à direita, mas a posição está vazia, retorne o pai.
            if (node -> right == NULL)
                return node;
            //Se não estiver vazia, continue percorrendo a árvore.
            else
                node = node -> right;
        }
    }
    return node;
}

void inOrder (FILE* output, struct node* root)
{
    //EPD
    if (root == NULL) return;
    
    inOrder(output, root -> left);
    imprimir(output, root);
    inOrder(output, root -> right);
}

void preOrder (FILE* output, struct node* root)
{
    //PED
    if (root == NULL) return;

    imprimir(output, root);
    preOrder(output, root -> left);
    preOrder(output, root -> right);
}

void postOrder (FILE* output, struct node* root)
{
    //EDP
    if (root == NULL) return;
    
    postOrder(output, root -> left);
    postOrder(output, root -> right);
    imprimir(output, root);
}

struct node* lerEntrada(FILE* input, struct node* key)
{
    fscanf(input, "%s %s %li", key -> nome, key -> perm, &(key -> nbytes));
    return key;
}

void imprimir (FILE* output, struct node* root) 
{    
    fprintf(output, "%i %s %s ", root -> i, root -> nome, root -> perm);
    if (root -> nbytes > 1 || root -> nbytes == 0)
        fprintf(output, "%lu bytes\n", root -> nbytes);
    else
        fprintf(output, "%lu byte\n", root -> nbytes);
}