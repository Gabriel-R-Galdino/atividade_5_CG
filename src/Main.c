#include "Biblioteca.h"

int main() {
    // Carregar a imagem
    if (!carregar_imagem()) return 1;

    ler_cabecalho();
    ler_imagem();
    fclose(fpin);

    // Definir as novas dimensões para ampliação e redução
    
    int novaLarguraAmpl = ncol * 2; // dobrando a largura
    int novaAlturaAmpl = nlin * 2; // dobrando a altura
    int novaLarguraReduc = ncol / 2;  // reduzir pela metade a largura
    int novaAlturaReduc = nlin / 2;   // reduzir pela metade a altura

    // Variáveis para receber as imagens processadas
    int **reduzidaR, **reduzidaG, **reduzidaB, **ampliadaR, **ampliadaG, **ampliadaB;

    char nomeAmplVizinho[150];
    char nomeReducVizinho[150];

    // 1. Ampliação com vizinho mais próximo
    ampliacao_vizinho_mais_proximo(novaLarguraAmpl, novaAlturaAmpl, &ampliadaR, &ampliadaG, &ampliadaB);
    snprintf(nomeAmplVizinho, sizeof(nomeAmplVizinho), "img/%s_ampliada_vizinho.ppm", nome_base);
    salvar_ppm(nomeAmplVizinho, ampliadaR, ampliadaG, ampliadaB, novaLarguraAmpl, novaAlturaAmpl);

    liberar_imagem(ampliadaR, novaAlturaAmpl);
    liberar_imagem(ampliadaG, novaAlturaAmpl);
    liberar_imagem(ampliadaB, novaAlturaAmpl);
    
    // 3. Redução por vizinho mais próximo
    reducao_vizinho(novaLarguraReduc, novaAlturaReduc, &reduzidaR, &reduzidaG, &reduzidaB);
    snprintf(nomeReducVizinho, sizeof(nomeReducVizinho), "img/%s_reduzida_vizinho.ppm", nome_base);
    salvar_ppm(nomeReducVizinho, reduzidaR, reduzidaG, reduzidaB, novaLarguraReduc, novaAlturaReduc);
    
    // 4. Redução com interpolação biquadrática (9 vizinhos)
    reducao_biquadratica(novaLarguraReduc, novaAlturaReduc, &reduzidaR, &reduzidaG, &reduzidaB);
    snprintf(nomeReducVizinho, sizeof(nomeReducVizinho), "img/%s_reduzida_biquadratica.ppm", nome_base);
    salvar_ppm(nomeReducVizinho, reduzidaR, reduzidaG, reduzidaB, novaLarguraReduc, novaAlturaReduc);

    liberar_imagem(reduzidaR, novaAlturaReduc);
    liberar_imagem(reduzidaG, novaAlturaReduc);
    liberar_imagem(reduzidaB, novaAlturaReduc);

    // Liberar a imagem original
    liberar_memoria();

    printf("Imagens geradas com sucesso!\n");

    return 0;
}
