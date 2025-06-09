#include "Biblioteca.h"

int main() {
    // Carregar a imagem
    if (!carregar_imagem()) return 1;

    ler_cabecalho();
    ler_imagem();
    fclose(fpin);

    // Definir as novas dimensões para ampliação e redução
    
    int novaLarguraReduc = ncol / 2;  // reduzir pela metade a largura
    int novaAlturaReduc = nlin / 2;   // reduzir pela metade a altura

    // Variáveis para receber as imagens processadas
    int **ampliadaR, **ampliadaG, **ampliadaB;
    int **reduzidaR, **reduzidaG, **reduzidaB;

    char nomeReducVizinho[150];
    
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
