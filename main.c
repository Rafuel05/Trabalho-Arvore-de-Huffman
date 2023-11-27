#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>
#include "huffmanTree.h"

void menu () {
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

    // Parte 1: Tabela de Frequência
    inicializa_tabela_com_zero(tabela_frequencia);
    preenche_tab_frequencia(arquivo, tabela_frequencia);
    fclose(arquivo);

    // Parte 2: Lista Encadeada Ordenada
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);

    // Parte 3: Montar a Árvore de Huffman
    arvore = montar_arvore(&lista);

    int choice;
    printf("==============\n");
    printf("MENU DE USUARIO");
    printf("\n==============\n");
    printf("1-Gerar dicionario de caracter\n");
    printf("2-Comprimir arquivo\n");
    printf("3-Descomprimir arquivo\n");
    printf("4-EXIT\n");
    printf("Digite o codigo referente a escolha:");
    scanf("%d",&choice);

    switch (choice)
    {
        case 1:
    colunas = altura_arvore(arvore) + 1;
    tabela_codigos = aloca_matriz_codigo(TAM, colunas);
    gerar_tabela_codigos(arvore, tabela_codigos, "", colunas);
    imprime_tabela_codigos(tabela_codigos);
    menu ();
    break;
        case 2:
    printf("\nComprimindo...\n");
    comprimir_arquivo("teste.txt", "arquivo_comprimido.bin", tabela_codigos);
    printf("Arquivo comprimido com sucesso.\n");
    menu ();
    break;
        case 3:
    printf("\nDescomprimindo...\n");
    descomprimir_arquivo("arquivo_comprimido.bin", "arquivo_descomprimido.txt", arvore, tabela_codigos);
    printf("Arquivo descomprimido com sucesso.\n");
    menu ();
    break;
        case 4:
        printf("tchau!!!!\n");
        break;
    default:
    menu ();
    }
}

void main () {
    menu ();
}
