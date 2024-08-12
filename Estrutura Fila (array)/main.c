#include <stdio.h>
#include <stdbool.h>

#define tamMax 5

typedef struct {
  int dados[tamMax];
  int inicio;
  int fim;
  int tamAtual;
} Fila;

void inicia(Fila *fila) {
  fila->inicio = 0;
  fila->fim = 0;
  fila->tamAtual = 0;
}

bool cheia(Fila *fila) {
  if (fila->tamAtual == tamMax){
    return true;
  }else{
    return false;
  }
}

bool vazia(Fila *fila) {
  if (fila->tamAtual == 0){
    return true;
  }else{
    return false;
  }
}

int tamanho(Fila *fila) {
  return fila->tamAtual;
}

int primeiro(Fila *fila) {
  if (vazia(fila)){
    return -1;
  }
  return fila->dados[fila->inicio];
}

bool inserir(Fila *fila, int valor) {
  if (cheia(fila)){
    return false;
  }
  fila->dados[fila->fim] = valor;
  fila->fim = (fila->fim + 1) % tamMax;
  fila->tamAtual++;
  return true;
}

int remover(Fila *fila) {
  if (vazia(fila)){
    return -1;
  }
  int res = primeiro(fila);
  fila->inicio = (fila->inicio + 1) % tamMax;
  fila->tamAtual--;
  return res;
}

int main(void) {
  Fila fila;
  int op, valor, remov, inicio;
  inicia(&fila);

  FILE *arquivo = fopen("teste.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo.\n");
    return 1;
  }

  while(fscanf(arquivo, "%d", &op) != EOF){
    switch (op) {
      case 1:
        if(fscanf(arquivo, "%d", &valor) == 1){
          if(inserir(&fila, valor)){
            printf("Elemento %d inserido com sucesso.\n", valor);
          }else{
            printf("Erro: Não foi possível inserir elemento.\n");
          }
        }
        break;
      case 2:
          remov = remover(&fila);
          if(remov!=-1){
            printf("Elemento '%d' removido com sucesso.\n", remov);
          }else{
            printf("Erro: Não foi possível remover elemento.\n");
          }
        break;
      case 3:
        printf("Tamanho da fila: %d\n", tamanho(&fila));
        break;
      case 4:
        inicio = primeiro(&fila);
        if(inicio != -1){
          printf("Primeiro elemento: %d\n", inicio);
        }else{
          printf("Erro: Posição fora dos limites da lista.\n");
        }
        break;
      case 5:
        if(vazia(&fila)){
          printf("\nFila vazia.\n");
        }else{
          printf("Fila: ");
            for(int i = 0; i < fila.tamAtual; i++){
                int index = (fila.inicio + i) % tamMax;
                printf("%d ", fila.dados[index]);
            }
            printf("\n");
          }
        break;
      case 6:
        fclose(arquivo);
        return 0;
    }
  }
  return 0;
}