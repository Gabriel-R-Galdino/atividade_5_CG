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

#endif
