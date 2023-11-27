#include <stdio.h>
#include <stdlib.h>
#define TAM 256

typedef struct no {
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;
} No;

typedef struct {
    No *inicio;
    int tam;
} Lista;

typedef struct {
    char caractere;
    char *codigo;
} CodigoBinario;


void inicializa_tabela_com_zero(unsigned int tab[]);
void preenche_tab_frequencia(FILE *arquivo, unsigned int tab[]);
void criar_lista(Lista *lista);
void inserir_ordenado(Lista *lista, No *no);
void preencher_lista(unsigned int tab[], Lista *lista);
void imprimir_lista(Lista *lista);
No *remove_no_inicio(Lista *lista);
No *montar_arvore(Lista *lista);
void imprimir_arvore(No *raiz, int tam);
int altura_arvore(No *raiz);
CodigoBinario **aloca_matriz_codigo(int linhas, int colunas);
void gerar_tabela_codigos(No *raiz, CodigoBinario **tabela, char *caminho, int colunas);
void imprime_tabela_codigos(CodigoBinario **tabela);
void escrever_tabela_no_arquivo(FILE *arquivo_comprimido, CodigoBinario **tabela);
void escrever_dados_comprimidos(FILE *arquivo_comprimido, FILE *arquivo_original, CodigoBinario **tabela);
void ler_tabela_do_arquivo(FILE *arquivo_comprimido, CodigoBinario **tabela);
void descomprimir_dados(FILE *arquivo_comprimido, FILE *arquivo_descomprimido, No *arvore);
void comprimir_arquivo(char *nome_arquivo_original, char *nome_arquivo_comprimido, CodigoBinario **tabela);
void descomprimir_arquivo(char *nome_arquivo_comprimido, char *nome_arquivo_descomprimido, No *arvore, CodigoBinario **tabela);
char binarioParaAscii(char *binario);
void processarArquivoBinario(const char *entrada, const char *saida);