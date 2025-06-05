#include "Biblioteca.h"

// Variáveis globais
FILE *fpin;
int **imagemR, **imagemG, **imagemB, ncol, nlin, quantizacao;
char nome_entrada[100];
char nome_base[100];

void ler_cabecalho(void) {
    char controle[4];
    fscanf(fpin, "%s\n", controle);
    fscanf(fpin, "%d %d\n", &ncol, &nlin);
    fscanf(fpin, "%d\n", &quantizacao);
}

void ler_imagem(void) {
    imagemR = (int **)malloc(nlin * sizeof(int *));
    imagemG = (int **)malloc(nlin * sizeof(int *));
    imagemB = (int **)malloc(nlin * sizeof(int *));

    for (int i = 0; i < nlin; i++) {
        imagemR[i] = (int *)malloc(ncol * sizeof(int));
        imagemG[i] = (int *)malloc(ncol * sizeof(int));
        imagemB[i] = (int *)malloc(ncol * sizeof(int));
    }

    for (int lin = 0; lin < nlin; lin++) {
        for (int col = 0; col < ncol; col++) {
            fscanf(fpin, "%d", &imagemR[lin][col]);
            fscanf(fpin, "%d", &imagemG[lin][col]);
            fscanf(fpin, "%d", &imagemB[lin][col]);
        }
    }
}

void remover_extensao(char *nome) {
    int i;
    for (i = 0; nome[i] != '\0'; i++);
    while (i >= 0 && nome[i] != '.') {
        i--;
    }
    if (i >= 0) {
        nome[i] = '\0';
    }
}

int carregar_imagem(void) {
    printf("Digite o nome da imagem .ppm: ");
    scanf("%s", nome_entrada);

    char caminho_completo[150];
    snprintf(caminho_completo, sizeof(caminho_completo), "img/%s", nome_entrada);

    fpin = fopen(caminho_completo, "r");
    if (!fpin) {
        printf("Erro ao abrir imagem.\n");
        return 0;
    }

    int i = 0;
    while (nome_entrada[i] != '\0') {
        nome_base[i] = nome_entrada[i];
        i++;
    }
    nome_base[i] = '\0';

    remover_extensao(nome_base);
    return 1;
}



void liberar_memoria(void) {
    for (int i = 0; i < nlin; i++) {
        free(imagemR[i]);
        free(imagemG[i]);
        free(imagemB[i]);
    }
    free(imagemR);
    free(imagemG);
    free(imagemB);
}
