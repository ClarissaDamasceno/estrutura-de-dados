#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = vetor[inicio];
        int esquerda = inicio;
        int direita = fim;

        while (esquerda <= direita) {
            while (vetor[esquerda] < pivo) {
                esquerda++;
            }
            while (vetor[direita] > pivo) {
                direita--;
            }
            if (esquerda <= direita) {
                int temp = vetor[esquerda];
                vetor[esquerda] = vetor[direita];
                vetor[direita] = temp;
                esquerda++;
                direita--;
            }
        }

        QuickSort(vetor, inicio, direita);
        QuickSort(vetor, esquerda, fim);
    }
}

void vetorOrdenado(int *vetor, int tamanho) {
    FILE *arquivo = fopen("ordenado_quicksort.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", vetor[i]);
    }

    fclose(arquivo);
}

int main()
{
    //Arquivos de Teste
    char* arquivos_teste[] = {"num.1000.1.in", "num.1000.2.in", "num.1000.3.in", "num.1000.4.in",
		    "num.10000.1.in", "num.10000.2.in", "num.10000.3.in", "num.10000.4.in",
		    "num.100000.1.in", "num.100000.2.in", "num.100000.3.in", "num.100000.4.in"};

    //Escolhe um arquivo de Teste
    int arquivo_selecionado = 1;

    //Abre o arquivo para leitura
    FILE *arquivo = fopen(arquivos_teste[arquivo_selecionado-1], "r");
    if (arquivo == NULL) {
		perror("Erro ao abrir o arquivo para leitura");
		return -1;
	}

	//Conta quantas linhas/numeros tem o arquivo
	int tamanho = 1;
	char c;
	while ((c = fgetc(arquivo)) != EOF) {
        if (c == '\n') {
            tamanho++;
        }
    }

	rewind(arquivo);

    //Aloca um vetor com o tamanho adequado
    int *vetor = (int*)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return -1;
    }

	//Preenche o vetor com os numeros do arquivo de Teste
	int i = 0;
	while (fscanf(arquivo, "%d", &vetor[i]) != EOF) {
	    i++;
	}

	fclose(arquivo);

	clock_t inicio = clock();

	//QuickSort
	QuickSort(vetor, 0, tamanho-1);

	clock_t fim = clock();
	double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

	printf("\n Tempo de Execução do Quick Sort: %f segundos\n", tempo);

	//Grava vetor ordenado
	vetorOrdenado(vetor, tamanho);

    	free(vetor);

    return 0;
}
