#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variáveis globais
extern FILE *fpin;
extern int **imagemR, **imagemG, **imagemB, ncol, nlin, quantizacao;
extern char nome_entrada[100];
extern char nome_base[100];

// Funções de leitura e escrita de imagem e arquivos
void ler_cabecalho(void);
void ler_imagem(void);
void remover_extensao(char *nome);
int carregar_imagem(void);
void nome_arquivo(char *buffer, const char *sufixo);
void salvar_ppm(const char *nome_arquivo, int **R, int **G, int **B, int largura, int altura);

// Funções gerais
int **criar_matriz(int largura, int altura);
void liberar_memoria(void);
void liberar_imagem(int **imagem, int altura);

// Funções matemáticas
int clamp(int val, int min, int max);
int media9(int **matriz, int x, int y, int largura, int altura);
int media4(int **matriz, int x, int y, int largura, int altura);

// Funções de amplicação & redução
void vizinho_proximo(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB, int flag);
void interpolacao_bilinear(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB, int flag);
void reducao_biquadratica(int novaLargura, int novaAltura, int ***outR, int ***outG, int ***outB);

#endif
