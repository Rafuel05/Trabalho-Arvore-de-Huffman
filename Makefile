help:	
	@echo "======================="	
	@echo "		AJUDA          "
	@echo "======================="
	@echo "help  | ajuda"
	@echo "ola   | executa mensagem de teste"
	@echo "clean | apaga codigos compilados"
tree: clean 
	@echo "======================="
	@echo  "Trabalho Arvore de Huffman "
	@echo "======================="
	@echo "Compilando o programa Arvore de Huffman"
	gcc main.c huffmanTree.h huffmanTree.c -o tree
	@echo "Tornando o programa Arvore de Huffman  executavel"
	chmod +x tree
	@echo "executando o programa Arvore de Huffman"
	./tree
	@echo "======================="
clean:
	@echo "======================="
	@echo "Removendo os progamas compilados"
	@echo "======================="
	rm -f Arvore
	@echo "======================="