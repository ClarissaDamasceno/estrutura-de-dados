### Este código implementa uma lista encadeada de inteiros, utilizando alocação dinâmica de memória, com as seguintes operações:

- Criação da lista vazia;
- Verificar se a lista está vazia;
- Obter o tamanho da lista;
- Obter/modificar o valor do elemento de uma determinada posição na lista;
- Inserir um elemento em uma determinada posição;
- Retirar um elemento de uma determinada posição.
- Imprimir os elementos de toda a lista. 

### Menu de opções:
- 1 - inserir na lista
 - 2 - remover da lista
 - 3 - exibir tamanho
 - 4 - buscar elemento
 - 5 - exibir lista
 - 6 - sair

### Arquivo de teste:

```c
1       //inserir
1 10    //posição 1, elemento 10
1       //inserir
2 20    //posição 2, elemento 20
1       //inserir
3 30    //posição 3, elemento 30
1       //inserir
4 40    //posição 4, elemento 40
5       //exibir lista
2 2     //remover, posição 2
5       //exibir lista
3       //exibir tamanho da lista
4 3     //buscar elemento, posição 3
6       //sair
```

### Saída esperada:
```c
Elemento 10 inserido na posição 1 com sucesso.
Elemento 20 inserido na posição 2 com sucesso.
Elemento 30 inserido na posição 3 com sucesso.
Elemento 40 inserido na posição 4 com sucesso.
Elementos da lista: 
Posição 1: [10]
Posição 2: [20]
Posição 3: [30]
Posição 4: [40]
Elemento '20' removido da posição '2' com sucesso.
Elementos da lista: 
Posição 1: [10]
Posição 2: [30]
Posição 3: [40]
Tamanho da lista: 3
Elemento na posição 3: 40
```
