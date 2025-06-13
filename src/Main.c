#include "Biblioteca.h"

int main(void) {
    // Carregar a imagem
    if (!carregar_imagem()) return 1;

    ler_cabecalho();
    ler_imagem();
    fclose(fpin);

    printf("Imagem lida!\n");
    printf("Dimensões atuais: %dx%d\n", ncol, nlin);

    int novaLarguraAmpl, novaAlturaAmpl;
    int novaLarguraReduc, novaAlturaReduc;
    float fatX, fatY;

    printf("Digite os fatores de ampliação (x e y): ");
    while (1) {
        scanf("%f %f", &fatX, &fatY);
        if (fatX <= 1.0f || fatY <= 1.0f) {
            printf("Tanto a altura quanto a largura devem ser maiores que o valor atual!\n");
            return 1;
        } else {
            novaLarguraAmpl = fatX * ncol;
            novaAlturaAmpl = fatY * nlin;
            break;
        }
    }

    printf("Digite os fatores de redução (x e y): ");
    while (1) {
        scanf("%f %f", &fatX, &fatY);
        if (fatX >= 1.0f || fatY >= 1.0f) {
            printf("Tanto a altura quanto a largura devem ser menores que o valor atual!\n");
            return 1;
        } else {
            novaLarguraReduc = fatX * ncol;
            novaAlturaReduc = fatY * nlin;
            break;
        }
    }

    printf("Gerando imagens...\n");

    // Variáveis para receber as imagens processadas
    int **reduzidaR, **reduzidaG, **reduzidaB, **ampliadaR, **ampliadaG, **ampliadaB;

    char nomeAmplVizinho[150];
    char nomeReducVizinho[150];

    // 1. Ampliação com vizinho mais próximo
    vizinho_proximo(novaLarguraAmpl, novaAlturaAmpl, &ampliadaR, &ampliadaG, &ampliadaB, 1);
    nome_arquivo(nomeAmplVizinho, "_ampliada_vizinho");
    salvar_ppm(nomeAmplVizinho, ampliadaR, ampliadaG, ampliadaB, novaLarguraAmpl, novaAlturaAmpl);

    liberar_imagem(ampliadaR, novaAlturaAmpl);
    liberar_imagem(ampliadaG, novaAlturaAmpl);
    liberar_imagem(ampliadaB, novaAlturaAmpl);

    // 2. Ampliação com interpolação linear (4 vizinhos)
    interpolacao_bilinear(novaLarguraAmpl, novaAlturaAmpl, &ampliadaR, &ampliadaG, &ampliadaB, 1);
    nome_arquivo(nomeAmplVizinho, "_ampliada_bilinear");
    salvar_ppm(nomeAmplVizinho, ampliadaR, ampliadaG, ampliadaB, novaLarguraAmpl, novaAlturaAmpl);

    // 3. Redução por vizinho mais próximo
    vizinho_proximo(novaLarguraReduc, novaAlturaReduc, &reduzidaR, &reduzidaG, &reduzidaB, 0);
    nome_arquivo(nomeReducVizinho, "_reduzida_vizinho");
    salvar_ppm(nomeReducVizinho, reduzidaR, reduzidaG, reduzidaB, novaLarguraReduc, novaAlturaReduc);

    liberar_imagem(reduzidaR, novaAlturaReduc);
    liberar_imagem(reduzidaG, novaAlturaReduc);
    liberar_imagem(reduzidaB, novaAlturaReduc);

    // 4. Redução com interpolação biquadrática (9 vizinhos)
    reducao_biquadratica(novaLarguraReduc, novaAlturaReduc, &reduzidaR, &reduzidaG, &reduzidaB);
    nome_arquivo(nomeReducVizinho, "_reduzida_biquadratica");
    salvar_ppm(nomeReducVizinho, reduzidaR, reduzidaG, reduzidaB, novaLarguraReduc, novaAlturaReduc);

    liberar_imagem(reduzidaR, novaAlturaReduc);
    liberar_imagem(reduzidaG, novaAlturaReduc);
    liberar_imagem(reduzidaB, novaAlturaReduc);

    // Liberar a imagem original
    liberar_memoria();

    printf("Imagens geradas com sucesso!\n");

    return 0;
}

