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
    imagemR = (int **)malloc(nlin * sizeof(int *));
    imagemG = (int **)malloc(nlin * sizeof(int *));
    imagemB = (int **)malloc(nlin * sizeof(int *));

    if (!imagemR || !imagemG || !imagemB) {
        printf("Erro ao alocar memória para a imagem.\n");
        exit(1);
    }

    // Alocação de memória para cada linha da imagem
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

// Função auxiliar: clamp
int clamp(int val, int min, int max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

// Função auxiliar: média de 9 vizinhos
int media9(int **matriz, int x, int y, int largura, int altura) {
    int soma = 0;
    int contador = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int xi = clamp(x + j, 0, largura - 1);
            int yi = clamp(y + i, 0, altura - 1);
            soma += matriz[yi][xi];
            contador++;
        }
    }
    return soma / contador;
}

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

// Demais codigos devem ser adicionados aqui
// 1. Ampliação pelo vizinho mais próximo
void ampliacao_vizinho_mais_proximo(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB) {
    float escalaX = (float)ncol / novaLargura;
    float escalaY = (float)nlin / novaAltura;

    *outR = malloc(novaAltura * sizeof(int *));
    *outG = malloc(novaAltura * sizeof(int *));
    *outB = malloc(novaAltura * sizeof(int *));

    if (!(*outR) || !(*outG) || !(*outB)) {
        printf("Erro ao alocar memória para a imagem ampliada.\n");
        exit(1);
    }

    for (int i = 0; i < novaAltura; i++) {
        (*outR)[i] = malloc(novaLargura * sizeof(int));
        (*outG)[i] = malloc(novaLargura * sizeof(int));
        (*outB)[i] = malloc(novaLargura * sizeof(int));

        for (int j = 0; j < novaLargura; j++) {
            int x_original = (int)(j * escalaX);
            int y_original = (int)(i * escalaY);

            (*outR)[i][j] = imagemR[y_original][x_original];
            (*outG)[i][j] = imagemG[y_original][x_original];
            (*outB)[i][j] = imagemB[y_original][x_original];
        }
    }
}


// 3. Redução por Vizinho Mais Próximo
void reducao_vizinho(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB) {
    // Calcula a razão de escala
    float escalaX = (float)ncol / novaLargura;
    float escalaY = (float)nlin / novaAltura;

    if (escalaX < 1.0f || escalaY < 1.0f) {
        printf("Tanto a largura quanto a altura precisam ser menores que as originais\n");
        exit(1);
    }

    // Aloca memória para os canais R, G, B da nova imagem
    *outR = malloc(novaAltura * sizeof(int *));
    *outG = malloc(novaAltura * sizeof(int *));
    *outB = malloc(novaAltura * sizeof(int *));

    if (!(*outR) || !(*outG) || !(*outB)) {
        printf("Erro ao alocar memória para a imagem reduzida.\n");
        exit(1);
    }

    for (int i = 0; i < novaAltura; i++) {
        (*outR)[i] = malloc(novaLargura * sizeof(int));
        (*outG)[i] = malloc(novaLargura * sizeof(int));
        (*outB)[i] = malloc(novaLargura * sizeof(int));

        for (int j = 0; j < novaLargura; j++) {
            // Calcula a posição correspondente na imagem original (arredondando)
            int x = (int)(j * escalaX + 0.5f);  // +0.5 para arredondar corretamente
            int y = (int)(i * escalaY + 0.5f);

            // Copia o pixel mais próximo
            (*outR)[i][j] = imagemR[y][x];
            (*outG)[i][j] = imagemG[y][x];
            (*outB)[i][j] = imagemB[y][x];
        }
    }
}

// 4. Redução com interpolação biquadrática (9 vizinhos)
void reducao_biquadratica(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB) {
    float escalaX = (float)ncol / novaLargura;
    float escalaY = (float)nlin / novaAltura;

    *outR = malloc(novaAltura * sizeof(int *));
    *outG = malloc(novaAltura * sizeof(int *));
    *outB = malloc(novaAltura * sizeof(int *));

    if (!(*outR) || !(*outG) || !(*outB)) {
        printf("Erro ao alocar memória para a imagem reduzida.\n");
        exit(1);
    }

    for (int i = 0; i < novaAltura; i++) {
        (*outR)[i] = malloc(novaLargura * sizeof(int));
        (*outG)[i] = malloc(novaLargura * sizeof(int));
        (*outB)[i] = malloc(novaLargura * sizeof(int));
        for (int j = 0; j < novaLargura; j++) {
            int x = (int)(j * escalaX);
            int y = (int)(i * escalaY);
            (*outR)[i][j] = media9(imagemR, x, y, ncol, nlin);
            (*outG)[i][j] = media9(imagemG, x, y, ncol, nlin);
            (*outB)[i][j] = media9(imagemB, x, y, ncol, nlin);
        }
    }
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
