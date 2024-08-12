### Este código implementa uma fila sequencial circular em C com as seguintes operações:
- Inserir no fim da fila
- Remover do início da fila
- Consultar o início da fila
- Indicar se a fila está vazia
- Indicar se a fila está cheia

### Menu de opções:
 - 1 - inserir na fila
 - 2 - remover da fila
 - 3 - exibir tamanho
 - 4 - exibir 1º elemento
 - 5 - exibir fila
 - 6 - sair

### Arquivo de teste:
```c
1 10    //inserir
1 20    //inserir
1 30    //inserir
1 40    //inserir
1 50    //inserir
5       //exibir fila
2       //remover
2       //remover
4       //exibir 1º elemento
3       //exibir tamanho
5       //exibir fila
1 60    //inserir
1 70    //inserir
5       //exibir fila
6       //sair
```

### Comportamento do vetor:

Inserção:
| 10    | 20    | 30    | 40   | 50   | 
|---    |---    |---    |---   |---   | 
|    0  | 1     | 2     | 3    | 4    |
|inicio | &nbsp;| &nbsp;|&nbsp;|fim   | 

Remoção:
| &nbsp;| &nbsp;| 30    | 40   | 50   |
|---    |---    |---    |---   |---   |
| 0     | 1     |    2  | 3    | 4    |
|&nbsp; | &nbsp;|inicio |&nbsp;|fim   |

Inserção:
| 60    | 70    | 30    | 40   | 50   |
|---    |---    |---    |---   |---   |
| 0     | 1     | 2     | 3    | 4    |
|&nbsp; | fim   |inicio |&nbsp;|&nbsp;|

### Saída esperada:
```c
Elemento 10 inserido com sucesso.
Elemento 20 inserido com sucesso.
Elemento 30 inserido com sucesso.
Elemento 40 inserido com sucesso.
Elemento 50 inserido com sucesso.
Fila: 10 20 30 40 50 
Elemento '10' removido com sucesso.
Elemento '20' removido com sucesso.
Primeiro elemento: 30
Tamanho da fila: 3
Fila: 30 40 50 
Elemento 60 inserido com sucesso.
Elemento 70 inserido com sucesso.
Fila: 30 40 50 60 70
```
