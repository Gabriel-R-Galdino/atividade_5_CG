#include "Biblioteca.h"

// 1. Ampliação pelo vizinho mais próximo e 3. Redução pelo vizinho mais próximo
void vizinho_proximo(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB, int flag) {
    float escalaX = (float)ncol / novaLargura;
    float escalaY = (float)nlin / novaAltura;

    // Se flag = 1, ampliação; se flag = 0, redução
    float arredonda_corretamente = flag ? 0.0f : 0.5f;

    *outR = criar_matriz(novaLargura, novaAltura);
    *outG = criar_matriz(novaLargura, novaAltura);
    *outB = criar_matriz(novaLargura, novaAltura);

    for (int i = 0; i < novaAltura; i++) {
        for (int j = 0; j < novaLargura; j++) {
            int x = (int)(j * escalaX + arredonda_corretamente);
            int y = (int)(i * escalaY + arredonda_corretamente);
            (*outR)[i][j] = imagemR[y][x];
            (*outG)[i][j] = imagemG[y][x];
            (*outB)[i][j] = imagemB[y][x];
        }
    }
}

// 2. Ampliação com interpolação bilinear (4 vizinhos)
void interpolacao_bilinear(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB, int flag) {
    // Se flag = 1 = ampliação, se flag = 0 = redução
    float escalaX = (float)ncol / novaLargura;
    float escalaY = (float)nlin / novaAltura;

    // Se flag = 1, ampliação; se flag = 0, redução
    float arredonda_corretamente = flag ? 0.0f : 0.5f;

    *outR = criar_matriz(novaLargura, novaAltura);
    *outG = criar_matriz(novaLargura, novaAltura);
    *outB = criar_matriz(novaLargura, novaAltura);

    for (int i = 0; i < novaAltura; i++) {
        for (int j = 0; j < novaLargura; j++) {
            int x = (int)(j * escalaX + arredonda_corretamente);
            int y = (int)(i * escalaY + arredonda_corretamente);

            (*outR)[i][j] = media4(imagemR, x, y, ncol, nlin);
            (*outG)[i][j] = media4(imagemG, x, y, ncol, nlin);
            (*outB)[i][j] = media4(imagemB, x, y, ncol, nlin);
        }
    }
}

// 4. Redução com interpolação biquadrática (9 vizinhos)
void reducao_biquadratica(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB) {
    float escalaX = (float)ncol / novaLargura;
    float escalaY = (float)nlin / novaAltura;

    *outR = criar_matriz(novaLargura, novaAltura);
    *outG = criar_matriz(novaLargura, novaAltura);
    *outB = criar_matriz(novaLargura, novaAltura);

    for (int i = 0; i < novaAltura; i++) {
        for (int j = 0; j < novaLargura; j++) {
            int x = (int)(j * escalaX);
            int y = (int)(i * escalaY);

            (*outR)[i][j] = media9(imagemR, x, y, ncol, nlin);
            (*outG)[i][j] = media9(imagemG, x, y, ncol, nlin);
            (*outB)[i][j] = media9(imagemB, x, y, ncol, nlin);
        }
    }
}
