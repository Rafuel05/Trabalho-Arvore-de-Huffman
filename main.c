#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>
#include "huffmanTree.h"

void main () {
    FILE *arquivo;
    char nome_arquivo[] = "teste.txt";
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
    }
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas;
    CodigoBinario **tabela_codigos;
    setlocale(LC_ALL, "portuguese");
//----------------------------------------------------------------Função Parte 1: Tabela de Frequência
    inicializa_tabela_com_zero(tabela_frequencia);
    preenche_tab_frequencia(arquivo, tabela_frequencia);
    fclose(arquivo);

//----------------------------------------------------------------Parte 2: Lista Encadeada Ordenada
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
//----------------------------------------------------------------ParteParte 3: Montar a Árvore de Huffman
    arvore = montar_arvore(&lista);
    printf("\nÁrvore de Huffman:\n");
//----------------------------------------------------------------Parte 4:Montar o Dicionário
    colunas = altura_arvore(arvore) + 1;
    tabela_codigos = aloca_matriz_codigo(TAM, colunas);
    gerar_tabela_codigos(arvore, tabela_codigos, "", colunas);
    imprime_tabela_codigos(tabela_codigos);
    // Comprimir
    printf("\nComprimindo...\n");
    comprimir_arquivo("teste.txt", "arquivo_comprimido.bin", tabela_codigos);
    printf("Arquivo comprimido com sucesso.\n");
    //substitui de acordo com a tabela ascii
    processarArquivoBinario("arquivo_comprimido.bin", "arquivo_comprimido_1.txt");


}
