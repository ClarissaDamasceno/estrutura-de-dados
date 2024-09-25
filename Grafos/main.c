#include <stdio.h>
#include <stdlib.h>

#define tam 100

typedef struct no {
    int vertice;
    struct no *prox;
} No;

typedef struct grafo {
    int vertices;
    No **adj;
    int *visitado;
} Grafo;

typedef struct {
    int inicio;
    int fim;
    int items[tam];
} Fila;

Fila criarFila() {
    Fila fila;
    fila.inicio = -1;
    fila.fim = -1;
    return fila;
}

int vazia(Fila *fila) {
  return fila->fim == -1;
}

void enfileirar(Fila *fila, int valor) {
    if (fila->fim == tam - 1) {
        printf("Fila cheia");
    } else {
        if (fila->inicio == -1) {
            fila->inicio = 0;
        }
        fila->fim++;
        fila->items[fila->fim] = valor;
    }
}

int desenfileirar(Fila *fila) {
    if (vazia(fila)) {
        printf("Fila vazia\n");
        return -1;
    }
    int item = fila->items[fila->inicio];
    fila->inicio++;
    if (fila->inicio > fila->fim) {
        fila->inicio = fila->fim = -1;
    }
    return item;
}

No* criarNo(int vertice) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = vertice;
    novoNo->prox = NULL;
    return novoNo;
}

Grafo* criarGrafo(int vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->vertices = vertices;
    grafo->adj = (No**)malloc(vertices * sizeof(No*));
    grafo->visitado = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        grafo->adj[i] = NULL;
        grafo->visitado[i] = 0;
    }
    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino) {
    No* novoNo = criarNo(destino);
    novoNo->prox = grafo->adj[origem];
    grafo->adj[origem] = novoNo;
}

void preencherGrafo(Grafo* grafo, int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] != 0) {
                adicionarAresta(grafo, i, j);
            }
        }
    }
}

int** criarMatriz(int n) {
    int **matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matriz[i][j] = 0; 
        }
    }
    return matriz;
}

void preencherMatriz(int **matriz, FILE *file, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &matriz[i][j]);
        }
    }
}

int** criarMatrizAdj(int **matriz, int n) {
    int **matrizAdj = criarMatriz(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrizAdj[i][j] = (matriz[i][j] != 0) ? 1 : 0;
        }
    }
    return matrizAdj;
}

void liberarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void imprimirMatriz(int **matriz, int n) {
    printf("\nMatriz %dx%d:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimirMatrizAdj(int **matrizAdj, int n) {
    printf("\nMatriz Adjacência:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrizAdj[i][j]);
        }
        printf("\n");
    }
}

void imprimirGrafo(Grafo* grafo) {
    printf("\nGrafo:\n");
    for (int v = 0; v < grafo->vertices; v++) {
        No* temp = grafo->adj[v];
        printf("Vértice %d:", v + 1);
        while (temp) {
            printf(" -> %d", temp->vertice + 1);
            temp = temp->prox;
        }
        printf("\n");
    }
}

void BFS(Grafo *grafo, int inicio, int destino) {
    for (int i = 0; i < grafo->vertices; i++) {
        grafo->visitado[i] = 0;
    }

    Fila fila = criarFila();
    grafo->visitado[inicio] = 1;
    enfileirar(&fila, inicio);

    int *predecessor = (int*)malloc(grafo->vertices * sizeof(int));
    for (int i = 0; i < grafo->vertices; i++) {
        predecessor[i] = -1;
    }

    while (!vazia(&fila)) {
        int u = desenfileirar(&fila);
        if (u == destino) {
            printf("\nBFS: Caminho encontrado entre %d e %d: ", inicio+1, destino+1);
            int pilha[tam], topo = -1;
            int temp = destino;
            while (temp != -1) {
                pilha[++topo] = temp;
                temp = predecessor[temp];
            }
            while (topo >= 0) {
                printf("%d ", pilha[topo--] + 1);
            }
            printf("\n");
            free(predecessor);
            return;
        }
        No* temp = grafo->adj[u];
        while (temp) {
            if (!grafo->visitado[temp->vertice]) {
                grafo->visitado[temp->vertice] = 1;
                enfileirar(&fila, temp->vertice);
                predecessor[temp->vertice] = u;
            }
            temp = temp->prox;
        }
    }
    printf("\nBFS: Caminho entre %d e %d não encontrado\n", inicio+1, destino+1);
    free(predecessor);
}

void DFS(Grafo *grafo, int inicio, int destino){
    for (int i = 0; i < grafo->vertices; i++) {
        grafo->visitado[i] = 0;
    }

    int pilha[tam], topo = -1;
    grafo->visitado[inicio] = 1;
    pilha[++topo] = inicio;

    int predecessor[tam];
    for (int i = 0; i < grafo->vertices; i++) {
        predecessor[i] = -1;
    }

    while (topo != -1) {
        int u = pilha[topo--];
        if (u == destino) {
            printf("DFS: Caminho encontrado entre %d e %d: ", inicio+1, destino+1);
            int temp = destino;
            while (temp != -1) {
                printf("%d ", temp + 1);
                temp = predecessor[temp];
            }
            printf("\n");
            return;
        }
        No *temp = grafo->adj[u];
        while (temp) {
            if (!grafo->visitado[temp->vertice]) {
                grafo->visitado[temp->vertice] = 1;
                pilha[++topo] = temp->vertice;
                predecessor[temp->vertice] = u;
            }
            temp = temp->prox;
        }
    }
    printf("DFS: Caminho entre %d e %d não encontrado\n", inicio+1, destino+1);
}

int main() {
    int n;
    FILE *file = fopen("pcv10.txt", "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return 1;
    }

    fscanf(file, "%d", &n);

    int **matriz = criarMatriz(n);
    preencherMatriz(matriz, file, n);
    int **matrizAdj = criarMatrizAdj(matriz, n);
    Grafo* grafo = criarGrafo(n);
    preencherGrafo(grafo, matriz, n);

    imprimirMatriz(matriz, n);
    imprimirMatrizAdj(matrizAdj, n);
    imprimirGrafo(grafo);

    BFS(grafo, 3, 9);
    DFS(grafo, 3, 9);

    liberarMatriz(matriz, n);
    liberarMatriz(matrizAdj, n);
    fclose(file);

    return 0;
}