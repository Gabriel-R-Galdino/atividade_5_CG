#include "Biblioteca.h"

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

// Calcula a média dos 4 vizinhos de matriz[y][x], levando em conta os limites
// da matriz.
int media4(int **matriz, int x, int y, int largura, int altura) {
    int soma = 0;
    soma += (x > 0) ? matriz[y][x - 1] : matriz[y][x];
    soma += (x < largura - 1) ? matriz[y][x + 1] : matriz[y][x];
    soma += (y > 0) ? matriz[y - 1][x] : matriz[y][x];
    soma += (y < altura - 1) ? matriz[y + 1][x] : matriz[y][x];

    return soma / 4;
}
