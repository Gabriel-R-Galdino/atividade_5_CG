#include "Biblioteca.h"

int main() {
    if (!carregar_imagem()) return 1;

    ler_cabecalho();
    ler_imagem();
    fclose(fpin);

    

    liberar_memoria();

    printf("Imagens geradas com sucesso!\n");

    return 0;
}
