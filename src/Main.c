#include "Biblioteca.h"

int main() {
    // Carregar a imagem
    if (!carregar_imagem()) return 1;

    ler_cabecalho();
    ler_imagem();
    fclose(fpin);

    int novaLarguraAmpl = ncol * 2;
    int novaAlturaAmpl = nlin * 2;
    int novaLarguraReduc = ncol / 2;
    int novaAlturaReduc = nlin / 2;

    int **reduzidaR, **reduzidaG, **reduzidaB, **ampliadaR, **ampliadaG, **ampliadaB;
    char nomeAmplVizinho[150], nomeReducVizinho[150];
    clock_t inicio, fim;
    double tempo;

    // 1. Ampliação - Vizinho mais próximo
    inicio = clock();
    vizinho_proximo(novaLarguraAmpl, novaAlturaAmpl, &ampliadaR, &ampliadaG, &ampliadaB, 1);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo para ampliação (vizinho mais próximo): %.3f segundos\n\n\n", tempo);

    nome_arquivo(nomeAmplVizinho, "_ampliada_vizinho");
    salvar_ppm(nomeAmplVizinho, ampliadaR, ampliadaG, ampliadaB, novaLarguraAmpl, novaAlturaAmpl);
    liberar_imagem(ampliadaR, novaAlturaAmpl);
    liberar_imagem(ampliadaG, novaAlturaAmpl);
    liberar_imagem(ampliadaB, novaAlturaAmpl);

    // 2. Ampliação - Interpolação bilinear
    inicio = clock();
    interpolacao_bilinear(novaLarguraAmpl, novaAlturaAmpl, &ampliadaR, &ampliadaG, &ampliadaB, 1);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo para ampliação (interpolação bilinear): %.3f segundos\n\n\n", tempo);

    nome_arquivo(nomeAmplVizinho, "_ampliada_bilinear");
    salvar_ppm(nomeAmplVizinho, ampliadaR, ampliadaG, ampliadaB, novaLarguraAmpl, novaAlturaAmpl);
    liberar_imagem(ampliadaR, novaAlturaAmpl);
    liberar_imagem(ampliadaG, novaAlturaAmpl);
    liberar_imagem(ampliadaB, novaAlturaAmpl);

    // 3. Redução - Vizinho mais próximo
    inicio = clock();
    vizinho_proximo(novaLarguraReduc, novaAlturaReduc, &reduzidaR, &reduzidaG, &reduzidaB, 0);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo para redução (vizinho mais próximo): %.3f segundos\n\n\n", tempo);

    nome_arquivo(nomeReducVizinho, "_reduzida_vizinho");
    salvar_ppm(nomeReducVizinho, reduzidaR, reduzidaG, reduzidaB, novaLarguraReduc, novaAlturaReduc);
    liberar_imagem(reduzidaR, novaAlturaReduc);
    liberar_imagem(reduzidaG, novaAlturaReduc);
    liberar_imagem(reduzidaB, novaAlturaReduc);

    // 4. Redução - Interpolação biquadrática
    inicio = clock();
    reducao_biquadratica(novaLarguraReduc, novaAlturaReduc, &reduzidaR, &reduzidaG, &reduzidaB);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo para redução (interpolação biquadrática): %.3f segundos\n\n\n", tempo);

    nome_arquivo(nomeReducVizinho, "_reduzida_biquadratica");
    salvar_ppm(nomeReducVizinho, reduzidaR, reduzidaG, reduzidaB, novaLarguraReduc, novaAlturaReduc);
    liberar_imagem(reduzidaR, novaAlturaReduc);
    liberar_imagem(reduzidaG, novaAlturaReduc);
    liberar_imagem(reduzidaB, novaAlturaReduc);

    liberar_memoria();
    printf("Imagens geradas com sucesso!\n");

    return 0;
}
