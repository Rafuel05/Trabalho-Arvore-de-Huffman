#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>
#include "huffmanTree.h"

char binarioParaAscii(char *binario) {
    int valor = 0;
    for (int i = 7; i >= 0; i--) {
        valor |= (binario[7 - i] - '0') << i;
    }
    return (char)valor;
}

void processarArquivoBinario(const char *entrada, const char *saida) {
    FILE *arquivoEntrada = fopen(entrada, "rb");
    FILE *arquivoSaida = fopen(saida, "w");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        perror("Erro ao abrir os arquivos");
        return;
    }

    char conjuntoBits[9];  // 8 bits + caractere nulo
    size_t lidos;

    while ((lidos = fread(conjuntoBits, 1, 8, arquivoEntrada)) > 0) {
        conjuntoBits[lidos] = '\0';

        // Convertendo os bits para um caractere ASCII
        char caractere = binarioParaAscii(conjuntoBits);

        // Escrevendo o caractere no arquivo de saída
        fprintf(arquivoSaida, "%c", caractere);
    }

    fclose(arquivoEntrada);
    fclose(arquivoSaida);
}

// Função para inicializar a tabela de frequência com zero
void inicializa_tabela_com_zero(unsigned int tab[]) {
    int i;
    for (i = 0; i < TAM; i++)
        tab[i] = 0;
}

// Função para preencher a tabela de frequência a partir de um arquivo
void preenche_tab_frequencia(FILE *arquivo, unsigned int tab[]) {
    int c;
    while ((c = fgetc(arquivo)) != EOF) {
        tab[c]++;
    }
}

// Função para criar a lista encadeada ordenada
void criar_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->tam = 0;
}

// Função para inserir um nó ordenadamente na lista
void inserir_ordenado(Lista *lista, No *no) {
    No *aux;
    if (lista->inicio == NULL) {
        lista->inicio = no;
    } else if (no->frequencia < lista->inicio->frequencia) {
        no->proximo = lista->inicio;
        lista->inicio = no;
    } else {
        aux = lista->inicio;
        while (aux->proximo && aux->proximo->frequencia <= no->frequencia)
            aux = aux->proximo;
        no->proximo = aux->proximo;
        aux->proximo = no;
    }
    lista->tam++;
}

// Função para preencher a lista a partir da tabela de frequência
void preencher_lista(unsigned int tab[], Lista *lista) {
    int i;
    No *novo;
    for (i = 0; i < TAM; i++) {
        if (tab[i] > 0) {
            novo = malloc(sizeof(No));
            if (novo) {
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo);
            } else {
                printf("\terro ao alocar memoria em preencher_lista\n");
                break;
            }
        }
    }
}

// Função para imprimir a lista ordenada
void imprimir_lista(Lista *lista) {
    No *aux = lista->inicio;

    printf("\nFrequência de Caracteres:\n");
    while (aux) {
        if (isprint(aux->caracter)) {
            printf("Caractere: %c | Contador: %d\n", aux->caracter, aux->frequencia);
        } else {
            printf("Caractere: \\x%02X | Contador: %d\n", aux->caracter, aux->frequencia);
        }
        aux = aux->proximo;
    }
}

// Função para remover o nó do início da lista
No *remove_no_inicio(Lista *lista) {
    No *aux = NULL;
    if (lista->inicio != NULL) {
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }
    return aux;
}

// Função para montar a árvore de Huffman
No *montar_arvore(Lista *lista) {
    No *primeiro, *segundo, *novo;
    while (lista->tam > 1) {
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if (novo) {
            novo->caracter = '+';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);
        } else {
            printf("\n\tErro ao alocar memoria em montar_arvore\n");
            break;
        }
    }
    return lista->inicio;
}

// Função para imprimir a árvore de Huffman
void imprimir_arvore(No *raiz, int tam) {
    if (raiz->esq == NULL && raiz->dir == NULL)
        printf("Caracter: %c | Contador: %d\n", raiz->caracter, raiz->frequencia);
    else {
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}

// Função para calcular a altura da árvore
int altura_arvore(No *raiz) {
    int esq, dir;
    if (raiz == NULL)
        return -1;
    else {
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if (esq > dir)
            return esq;
        else
            return dir;
    }
}

// Função para alocar a matriz de códigos binários
CodigoBinario **aloca_matriz_codigo(int linhas, int colunas) {
    CodigoBinario **matriz;
    int i;

    matriz = malloc(sizeof(CodigoBinario *) * linhas);

    for (i = 0; i < linhas; i++) {
        matriz[i] = malloc(sizeof(CodigoBinario));
        matriz[i]->caractere = '\0';
        matriz[i]->codigo = NULL;
    }

    return matriz;
}

// Função para gerar a tabela de códigos binários a partir da árvore
void gerar_tabela_codigos(No *raiz, CodigoBinario **tabela, char *caminho, int colunas) {
    char esquerda[colunas], direita[colunas];

    if (raiz->esq == NULL && raiz->dir == NULL) {
        tabela[raiz->caracter]->caractere = raiz->caracter;
        tabela[raiz->caracter]->codigo = strdup(caminho);
    } else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_tabela_codigos(raiz->esq, tabela, esquerda, colunas);
        gerar_tabela_codigos(raiz->dir, tabela, direita, colunas);
    }
}

// Função para imprimir a tabela de códigos binários
void imprime_tabela_codigos(CodigoBinario **tabela) {
    int i;

    printf("\nTabela de Códigos Binários:\n");
    for (i = 0; i < TAM; i++) {
        if (tabela[i]->codigo != NULL) {
            printf("Caractere: %c | Código Binário: %s\n", tabela[i]->caractere, tabela[i]->codigo);
        }
    }
}

void escrever_tabela_no_arquivo(FILE *arquivo_comprimido, CodigoBinario **tabela) {
    int i;
    for (i = 0; i < TAM; i++) {
        if (tabela[i]->codigo != NULL) {
            fprintf(arquivo_comprimido, "%c%s\n", tabela[i]->caractere, tabela[i]->codigo);
        }
    }
}

// Função para escrever os dados comprimidos no arquivo
void escrever_dados_comprimidos(FILE *arquivo_comprimido, FILE *arquivo_original, CodigoBinario **tabela) {
    int c;
    char buffer[9] = {'\0'};
    int pos = 0;

    while ((c = fgetc(arquivo_original)) != EOF) {
        char *codigo = tabela[c]->codigo;
        int i = 0;
        while (codigo[i] != '\0') {
            buffer[pos++] = codigo[i++];
            if (pos == 8) {
                fprintf(arquivo_comprimido, "%ld", strtol(buffer, NULL, 2));
                pos = 0;
            }
        }
    }

    // Escrever o restante do buffer, se houver
    if (pos > 0) {
        fprintf(arquivo_comprimido, "%ld", strtol(buffer, NULL, 2));
    }
}


// Função para ler a tabela de códigos binários do arquivo comprimido
void ler_tabela_do_arquivo(FILE *arquivo_comprimido, CodigoBinario **tabela) {
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo_comprimido) != NULL) {
        char caractere;
        char *codigo = strtok(linha, "\n");
        sscanf(codigo, "%c%s", &caractere, codigo);
        tabela[caractere]->codigo = strdup(codigo);
    }
}

// Função para descomprimir os dados e escrever no arquivo original
void descomprimir_dados(FILE *arquivo_comprimido, FILE *arquivo_descomprimido, No *arvore) {
    int bit;
    No *atual = arvore;

    while ((bit = fgetc(arquivo_comprimido)) != EOF) {
        if (bit == '0') {
            atual = atual->esq;
        } else if (bit == '1') {
            atual = atual->dir;
        }

        if (atual->esq == NULL && atual->dir == NULL) {
            fprintf(arquivo_descomprimido, "%c", atual->caracter);
            atual = arvore;
        }
    }
}


void comprimir_arquivo(char *nome_arquivo_original, char *nome_arquivo_comprimido, CodigoBinario **tabela) {
    FILE *arquivo_original, *arquivo_comprimido;
    int bit, c;

    arquivo_original = fopen(nome_arquivo_original, "r");
    arquivo_comprimido = fopen(nome_arquivo_comprimido, "wb"); // Usando modo binário

    if (arquivo_original == NULL || arquivo_comprimido == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos.\n");
        exit(EXIT_FAILURE);
    }

    while ((c = fgetc(arquivo_original)) != EOF) {
        // Escrever código binário correspondente ao caractere no arquivo comprimido
        fprintf(arquivo_comprimido, "%s", tabela[c]->codigo);
    }

    fclose(arquivo_original);
    fclose(arquivo_comprimido);
}

void descomprimir_arquivo(char *nome_arquivo_comprimido, char *nome_arquivo_descomprimido, No *arvore, CodigoBinario **tabela) {
    FILE *arquivo_comprimido, *arquivo_descomprimido;
    int bit;
    No *atual = arvore;

    arquivo_comprimido = fopen(nome_arquivo_comprimido, "rb"); // Usando modo binário
    arquivo_descomprimido = fopen(nome_arquivo_descomprimido, "w");

    if (arquivo_comprimido == NULL || arquivo_descomprimido == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos.\n");
        exit(EXIT_FAILURE);
    }

    while ((bit = fgetc(arquivo_comprimido)) != EOF) {
        if (bit == '0') {
            atual = atual->esq;
        } else if (bit == '1') {
            atual = atual->dir;
        }

        if (atual->esq == NULL && atual->dir == NULL) {
            fprintf(arquivo_descomprimido, "%c", atual->caracter);
            atual = arvore; // Reinicia a busca a partir da raiz
        }
    }

    fclose(arquivo_comprimido);
    fclose(arquivo_descomprimido);
}
