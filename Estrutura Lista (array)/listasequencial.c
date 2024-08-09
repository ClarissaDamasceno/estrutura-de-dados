#include <stdio.h>
#include <stdbool.h>

#define tamMax 5

typedef struct {
  int dados[tamMax];
  int tamAtual;
} Lista;

void inicia(Lista *lista){
  lista->tamAtual = 0;
}

bool cheia(Lista *lista){
  if(lista->tamAtual == tamMax){
    return true;
  }else{
    return false;
  }
}

bool vazia(Lista *lista){
  if(lista->tamAtual == 0){
    return true;
  }else{
    return false;
  }
}

int tamanho(Lista *lista){
  return lista->tamAtual;
}

bool inserir(Lista *lista, int pos, int valor){
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

int remover(Lista *lista, int pos){
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

int posicao (Lista *lista, int dado){
  for (int i = 0; i < lista->tamAtual; i++){
    if (lista->dados[i] == dado){
      return (i + 1);
    }
  }
  return -1;
}

int elemento(Lista *lista, int pos){
  int dado;
  if ((pos > lista->tamAtual) || (pos <= 0)){
    return -1;
  }
  dado = lista->dados[pos-1];
  return dado;
}

int main(){
  Lista lista;
  int op, valor, pos;
  inicia(&lista);

  FILE *arquivo = fopen("teste.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo.\n");
    return 1;
  }

  while(fscanf(arquivo, "%d", &op) != EOF){
    switch (op) {
      case 1:
        if(fscanf(arquivo, "%d %d", &pos, &valor) == 2){
          if(inserir(&lista, pos, valor)){
            printf("Elemento %d inserido na posição %d com sucesso.\n", valor, pos);
          }else{
            printf("Erro: Posição %d inválida para inserção.\n", pos);
          }
        }
        break;
      case 2:
        if(fscanf(arquivo, "%d", &pos) == 1){
          int removido = remover(&lista, pos);
          if(removido != -1){
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
        if(fscanf(arquivo, "%d", &pos) == 1){
          int elem = elemento(&lista, pos);
          if(elem != -1){
            printf("Elemento na posição %d: %d\n", pos, elem);
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
        break;
      case 6:
        fclose(arquivo);
        return 0;
    }
  }
  return 0;
}
