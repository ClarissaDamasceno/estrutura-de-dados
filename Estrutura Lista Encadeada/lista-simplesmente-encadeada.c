#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no{
  int dado;
  struct no *prox;
}No;

typedef struct lista{
  No* cabeca;
  int tamanho;
}Lista;

void inicia(Lista *lista){
  lista->cabeca = NULL;
  lista->tamanho = 0;
}

bool vazia(Lista *lista){
  if (lista->tamanho == 0){
    return true;
  }else{
    return false;
  }
}

int tamanho(Lista *lista){
  return lista->tamanho;
}

bool inserirInicioLista(Lista *lista, int valor) {
  No* novoNo = (No*)malloc(sizeof(No));
  if (novoNo == NULL) {
      return false;
  }
  novoNo->dado = valor;
  novoNo->prox = lista->cabeca;
  lista->cabeca = novoNo;
  lista->tamanho++;
  return true;
}

bool inserirMeioLista(Lista *lista, int pos, int valor){
  int cont = 1;
  No* novoNo = (No*)malloc(sizeof(No));
  if (novoNo == NULL) {
      return false;
  }
  novoNo->dado = valor;
  No* aux = lista->cabeca;
  while ((cont < pos-1) && (aux != NULL)){
    aux = aux->prox;
    cont++;
  }
  if (aux == NULL) {
    return false;
  }
  novoNo->prox = aux->prox;
  aux->prox = novoNo;
  lista->tamanho++;
  return true;
}

bool inserirFimLista(Lista *lista, int valor){
  No* novoNo = (No*)malloc(sizeof(No));
  if (novoNo == NULL) {
      return false;
  }
  novoNo->dado = valor;
  No* aux = lista->cabeca;
  while(aux->prox != NULL){
    aux = aux->prox;
  }
  novoNo->prox = NULL;
  aux->prox = novoNo;
  lista->tamanho++;
  return true;
}

bool inserir(Lista *lista, int pos, int valor) {
  if ((vazia(lista)) && (pos != 1)) {
    return false;
  }
  if (pos == 1){
    return inserirInicioLista(lista, valor);
  }else if (pos == lista->tamanho+1){
    return inserirFimLista(lista, valor);
  }
  else{
    return inserirMeioLista(lista, pos, valor);
  }
}

int removeInicioLista(Lista *lista){
  No* p = lista->cabeca;
  int valor = p->dado;
  lista->cabeca = p->prox;
  lista->tamanho--;
  return valor;
}

int removeNaLista(Lista *lista, int pos){
  No* atual = NULL; 
  No* antecessor = NULL;
  int valor = -1;
  int cont = 1;
  atual = lista->cabeca;
  while((cont < pos) && (atual != NULL)){
    antecessor = atual;
    atual = atual->prox;
    cont++;
  }
  if (atual == NULL){
    return -1;
  }
  valor = atual->dado;
  antecessor->prox = atual->prox;
  lista->tamanho--;
  return valor;
}

int remover(Lista *lista, int pos) {
  if (vazia(lista)){ 
    return -1;
  }
  if (pos == 1){
    return removeInicioLista(lista);
  }
  else{
    return removeNaLista(lista, pos);
  }
}

int posicao (Lista *lista, int valor) {
  int cont = 1;
  No* aux;
  if (vazia(lista)){
    return 0;
  }
  aux = lista->cabeca;
  while (aux != NULL) {
    if (aux->dado == valor){
      return cont;
    }
    aux = aux->prox;
    cont++;
  }
  return -1;
}

int elemento (Lista *lista, int pos) {
  No* aux = lista->cabeca;
  int cont = 1;
  if (vazia(lista)){
    return -1;
  }
  if ((pos < 1) || (pos > lista->tamanho)){
    return -1;
  }
  while (cont < pos){
    aux = aux->prox;
    cont++;
  }
  return aux->dado;
}

int main(void) {
  Lista lista;
  int op, valor, pos;
  inicia(&lista);

  while(op != 6){
    printf("\nMENU\n1 - inserir na lista\n2 - remover da lista\n3 - exibir tamanho\n4 - buscar elemento\n5 - exibir lista\n6 - sair\n");
    scanf("%d", &op);
    switch (op) {
      case 1:
        printf("Digite o valor a ser inserido: ");
        scanf("%d", &valor);
        printf("Digite a posição a ser inserida: ");
        scanf("%d", &pos);
        if(inserir(&lista, pos, valor)){
          printf("\nElemento %d inserido na posição %d com sucesso.\n", valor, pos);
        }else{
          printf("\nErro: Posição %d inválida para inserção.\n", pos);
        }
        break;
      case 2:
        printf("Digite a posição a ser removida: ");
        scanf("%d", &pos);
        int removido = remover(&lista, pos);
        if(removido!=-1){
          printf("\nElemento '%d' removido da posição '%d' com sucesso.\n", removido, pos);
        }else{
          printf("\nErro: Não foi possível remover elemento.\n");
        }
        break;
      case 3:
        printf("\nTamanho da lista: %d\n", tamanho(&lista));
        break;
      case 4:
        if(vazia(&lista)){
          printf("\nLista vazia.\n");
        }else{
          printf("Digite a posição do elemento a ser buscado: ");
          scanf("%d", &pos);
          if(elemento(&lista, pos)!=-1){
            printf("\nElemento na posição %d: %d\n", pos, elemento(&lista, pos));
          }else{
            printf("\nErro: Posição fora dos limites da lista.\n");
          }
        }
        break;
      case 5:
        if(vazia(&lista)){
          printf("\nLista vazia.\n");
        }else{
          printf("Elementos da lista: \n");
          for(int i = 0; i<lista.tamanho; i++){
            printf("Posição %d: [%d]\n", i+1, elemento(&lista, i+1));
          }
        }
        break;
      case 6:
        break;
    }
  }
  return 0;
}