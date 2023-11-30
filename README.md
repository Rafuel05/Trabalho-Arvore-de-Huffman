# Trabalho-Arvore-de-Huffman-
 
 Trabalho acadêmico desenvolvido como parte da disciplina de Estrutura de Dados II, do curso de Engenharia da Computação - 4º semestre, no IFMT - Campus Cuiabá.

 Profº João Paulo Preti

 Membros: Leticia Arruda de Freitas e Rafael Melchior de Oliveira

 # Documentação:

 - [Makefile](https://github.com/Rafuel05/Trabalho-Arvore-de-Huffman-/blob/main/Makefile)

 Para rodar o codigo digite no terminal 'make tree'

 - [main.c](https://github.com/Rafuel05/Trabalho-Arvore-de-Huffman-/blob/main/main.c)

 - [huffman.h](https://github.com/Rafuel05/Trabalho-Arvore-de-Huffman-/blob/main/huffmanTree.h)

 - [huffman.c](https://github.com/Rafuel05/Trabalho-Arvore-de-Huffman-/blob/main/huffmanTree.c)

## Sobre o projeto 

Este projeto tem como objetivo realizar a montagem de uma arvore de Huffman e após a montagem realizar algumas aplicações.

Para isso o projeto esta dividido nas seguintes etapas: 

- Ler o texto e gerar a tabela de frequência de caracteres:

  ```c
  inicializa_tabela_com_zero(tabela_frequencia);
  preenche_tab_frequencia(arquivo, tabela_frequencia);
  ```

- Gerar uma lista com os caracteres encontrados no texto:

  ```c
  criar_lista(&lista);
  preencher_lista(tabela_frequencia, &lista); 
  ```

- Montar a Árvore de Huffman:

  ```c
  arvore = montar_arvore(&lista); 
  ```

- Gerar a tabela de códigos (dicionário):

  ```c
  colunas = altura_arvore(arvore) + 1;
  tabela_codigos = aloca_matriz_codigo(TAM, colunas);
  gerar_tabela_codigos(arvore, tabela_codigos, "", colunas);
  imprime_tabela_codigos(tabela_codigos);
  ```

### Aplicações:

- Comprimrir o texto de acordo com o dicionário gerado anteriormente, substituindo cada caracter pelo "novo" código binario:

  ```c
  comprimir_arquivo("teste.txt", "arquivo_comprimido.bin", tabela_codigos);
  ```

- Decodificar o arquivo comprimido ".bin" de acordo com a tabela ascii, ou seja comparar o binario gerado com o binario da tabela ascii, assim gerando um novo texto compactado:

  ```c
  processarArquivoBinario("arquivo_comprimido.bin", "arquivo_comprimido_1.txt");
  ``` 

#### Fim!

  

  
  
  
