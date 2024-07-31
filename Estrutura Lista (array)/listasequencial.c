#include <stdio.h>
#include <stdbool.h>

#define tamMax 5

typedef struct {
  int dados[tamMax];
  int tamAtual;
} ListaSeq;

void inicia(ListaSeq *lista){
  lista->tamAtual = 0;
}

bool cheia(ListaSeq *lista){
  if(lista->tamAtual == tamMax){
    return true;
  }else{
    return false;
  }
}

bool vazia(ListaSeq *lista){
  if(lista->tamAtual == 0){
    return true;
  }else{
    return false;
  }
}

int tamanho(ListaSeq *lista){
  return lista->tamAtual;
}

bool inserir(ListaSeq *lista, int pos, int valor){
  if (cheia(lista) || pos <= 0 || pos > lista->tamAtual + 1) {
      return false;
  }
  for (int i = lista->tamAtual; i >= pos; i--) {
    lista->dados[i] = lista->dados[i - 1];
  }
    lista->dados[pos - 1] = valor;
    lista->tamAtual++;
    return true;
}

int remover(ListaSeq *lista, int pos){
  if (pos <= 0 || pos > lista->tamAtual) {
      return -1;
  }
  int valor = lista->dados[pos - 1];
  for (int i = pos - 1; i < lista->tamAtual - 1; i++){
    lista->dados[i] = lista->dados[i + 1];
  }
  lista->tamAtual--;
  return valor;
}

int posicao (ListaSeq *lista, int dado){
  for (int i = 0; i < lista->tamAtual; i++){
    if (lista->dados[i] == dado){
      return (i + 1);
    }
  }
  return -1;
}

int elemento(ListaSeq *lista, int pos){
  int dado;
  if ((pos > lista->tamAtual) || (pos <= 0)){
    return -1;
  }
  dado = lista->dados[pos-1];
  return dado;
}

int main(){
  ListaSeq lista;
  int op, valor, pos;
  inicia(&lista);

  while(op != 6){
    printf("\nMENU\n1 - inserir na lista\n2 - remover da lista\n3 - exibir tamanho\n4 - buscar elemento\n5 - exibir lista\n6 - sair\n");
    scanf("%d", &op);
      
    switch (op) {
      case 1:
        if(cheia(&lista)){
          printf("Lista cheia!\n");
        }else{
          printf("Digite o valor a ser inserido: ");
          scanf("%d", &valor);
          printf("Digite a posição a ser inserida: ");
          scanf("%d", &pos);
          if(inserir(&lista, pos, valor)){
            printf("Elemento %d inserido na posição %d com sucesso.\n", valor, pos);
          }else{
            printf("Erro: Posição %d inválida para inserção.\n", pos);
          }
        }
        break;
      case 2:
        if(vazia(&lista)){
          printf("Lista vazia.\n");
        }else{
          printf("Digite a posição a ser removida: ");
          scanf("%d", &pos);
          int removido = remover(&lista, pos);
          if(removido!=-1){
            printf("Elemento '%d' removido da posição '%d' com sucesso.\n", removido, pos);
          }else{
            printf("Erro: Posição fora dos limites da lista.\n");
          }
        }
        break;
      case 3:
        printf("Tamanho da lista: %d\n", tamanho(&lista));
        break;
      case 4:
        if(vazia(&lista)){
          printf("Lista vazia.\n");
        }else{
          printf("Digite a posição do elemento a ser buscado: ");
          scanf("%d", &pos);
          if(elemento(&lista, pos)!=-1){
            printf("Elemento na posição %d: %d\n", pos, elemento(&lista, pos));
          }else{
            printf("Erro: Posição fora dos limites da lista.\n");
          }
        }
        break;
      case 5:
        if(vazia(&lista)){
          printf("Lista vazia.\n");
        }else{
          if(cheia(&lista)){
            printf("Lista cheia.\n");
          }
          printf("Elementos da lista: \n");
          for(int i = 0; i<lista.tamAtual; i++){
            printf("Posição %d: [%d]\n", i+1, elemento(&lista, i+1));
          }
        }
      case 6:
        break;
    }
  }
  return 0;
}