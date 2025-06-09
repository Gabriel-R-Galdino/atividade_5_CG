#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>

// Variáveis globais
extern FILE *fpin;
extern int **imagemR, **imagemG, **imagemB, ncol, nlin, quantizacao;
extern char nome_entrada[100];
extern char nome_base[100];

// Funções
void ler_cabecalho(void);
void ler_imagem(void);
void remover_extensao(char *nome);
int carregar_imagem(void);
void liberar_memoria(void);
void salvar_ppm(const char *nome_arquivo, int **R, int **G, int **B, int largura, int altura);
int clamp(int val, int min, int max);
int media9(int **matriz, int x, int y, int largura, int altura);
void ampliacao_vizinho_mais_proximo(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB);
void reducao_biquadratica(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB);
void liberar_imagem(int **imagem, int altura);


#endif
