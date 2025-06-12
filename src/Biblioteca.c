#include "Biblioteca.h"

// Variáveis globais
FILE *fpin;
int **imagemR, **imagemG, **imagemB, ncol, nlin, quantizacao;
char nome_entrada[100];
char nome_base[100];

// Função para ler o cabeçalho do arquivo PPM
void ler_cabecalho(void) {
    char controle[4];
    fscanf(fpin, "%s\n", controle);
    fscanf(fpin, "%d %d\n", &ncol, &nlin);
    fscanf(fpin, "%d\n", &quantizacao);
}

// Função para ler a imagem do arquivo PPM
void ler_imagem(void) {
    imagemR = criar_matriz(ncol, nlin);
    imagemG = criar_matriz(ncol, nlin);
    imagemB = criar_matriz(ncol, nlin);

    for (int lin = 0; lin < nlin; lin++) {
        for (int col = 0; col < ncol; col++) {
            fscanf(fpin, "%d", &imagemR[lin][col]);
            fscanf(fpin, "%d", &imagemG[lin][col]);
            fscanf(fpin, "%d", &imagemB[lin][col]);
        }
    }
}

// Função para remover a extensão do nome do arquivo
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

// Função para carregar a imagem do arquivo PPM
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

// Função para salvar imagem no formato PPM ASCII
void salvar_ppm(const char *nome_arquivo, int **R, int **G, int **B, int largura, int altura) {
    FILE *fp = fopen(nome_arquivo, "w");
    if (!fp) {
        printf("Erro ao salvar imagem %s\n", nome_arquivo);
        return;
    }

    fprintf(fp, "P3\n%d %d\n%d\n", largura, altura, quantizacao);
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            fprintf(fp, "%d %d %d ", R[i][j], G[i][j], B[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Imagem salva: %s\n", nome_arquivo);
}

// Função pra adicionar nome do arquivo
void nome_arquivo(char *buffer, const char *sufixo) {
    int i = 0;

    char *path = "img/";
    while (*path != '\0') {
        buffer[i++] = *path++;
    }

    int j = 0;
    while (nome_base[j] != '\0') {
        buffer[i++] = nome_base[j++];
    }

    while (*sufixo != '\0') {
        buffer[i++] = *sufixo++;
    }

    char *ext = ".ppm";
    while (*ext != '\0') {
        buffer[i++] = *ext++;
    }
    buffer[i] = '\0';
}

// Função para liberar memória de uma imagem
void liberar_imagem(int **imagem, int altura) {
    for (int i = 0; i < altura; i++) {
        free(imagem[i]);
    }
    free(imagem);
}

// Função para liberar toda a memória alocada para a imagem original
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

// Função pra criar matriz
int **criar_matriz(int largura, int altura) {
    int **ret = malloc(altura * sizeof(int *));
    if (!ret) {
        printf("Erro ao alocar memória para a imagem.");
        exit(1);
    }

    for (int i = 0; i < altura; i++) {
        ret[i] = malloc(largura * sizeof(int));
        if (!ret[i]) {
            printf("Erro ao alocar memória para a imagem.");
            exit(1);
        }
    }

    return ret;
}