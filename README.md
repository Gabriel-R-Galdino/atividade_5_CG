# 🖼️ Atividade 5 – Computação Gráfica

Projeto da disciplina de **Computação Gráfica** – Atividade 5.

Este projeto tem como objetivo desenvolver um programa em **C puro** que realiza reamostragem de imagens no formato `.ppm` (modo ASCII - P3), aplicando diferentes algoritmos de **interpolação para ampliação e redução** da imagem original.

## Objetivo

O programa deve ler uma imagem `.ppm` a partir do diretório `img/` e gerar **quatro versões processadas** utilizando os seguintes métodos:

1. **Ampliação por Vizinho Mais Próximo (interpolação de 1-vizinhança)**

   - Método rápido e simples, copia o valor do pixel mais próximo.
   - Gera bordas mais definidas porém serrilhadas.

2. **Ampliação por Média Aritmética Simples (interpolação de 4-vizinhança)**

   - Cada pixel ampliado é calculado pela média dos quatro vizinhos.
   - Suaviza bordas e reduz aliasing.

3. **Redução por Vizinho Mais Próximo**

   - Escolhe o pixel correspondente mais próximo da imagem original.
   - Rápido, mas pode gerar perda de detalhes e aliasing.

4. **Redução com Interpolação Biquadrática (9-vizinhança)**
   - Usa o pixel central e seus 8 vizinhos com pesos ponderados.
   - Mantém mais detalhes e suaviza transições.

---

## 📁 Estrutura de Pastas

```
.
├── build/              # Pasta que Armazena o Executável
│   └── Main            # Executável
├── img/                # Imagens de entrada e saída
│   └── arco-iris.ppm   # Imagem usada como teste
├── src/                # Códigos-fonte (.c)
│   ├── Main.c
│   └── Biblioteca.c
├── include/            # Arquivo de cabeçalho (.h)
│   └── Biblioteca.h
├── Makefile
└── README.md
```

---

## ▶️ Como Compilar e Executar

### ✅ Requisitos

- GCC instalado (em Linux, WSL ou MinGW/Git Bash no Windows)
- Make (caso esteja usando Windows, utilize MSYS2 ou WSL para ter o `make`)

### 🧪 Passo a passo

1. **Abra o terminal**:

   - No Linux: use seu terminal padrão.
   - No Windows: use **MSYS2 MinGW 64-bit** ou **Git Bash**.

2. **Navegue até a pasta do projeto**:

   ```bash
   cd caminho/para/seu/projeto
   ```

3. **Compile o projeto com `make`**:

   ```bash
   make
   ```

4. **Execute com `make run`**:

   ```bash
   make run
   ```

5. **Informe o caminho da imagem** quando solicitado:

   ```bash
   Digite o nome da imagem .ppm: arco-iris.ppm
   ```

6. **Verifique a pasta `img/`** para os arquivos de saída:
   - `nome_ampliada_vizinho.ppm` → ampliação usando vizinho mais próximo (1-vizinhança)
   - `nome_ampliada_media.ppm` → ampliação usando média aritmética (4-vizinhança)
   - `nome_reduzida_vizinho.ppm` → redução usando vizinho mais próximo
   - `nome_reduzida_biquadratica.ppm` → redução com interpolação biquadrática (9-vizinhança)

---

## 📝 Observações

- A imagem `.ppm` deve estar dentro da pasta `img/` caso queira adicionar novas imagens.
- As imagens de saída também serão salvas dentro da pasta `img/`.
- Ao executar o programa, informe o caminho relativo como: `Nome_Da_Imagem.ppm`

---

## 🎓 Informações Acadêmicas

Desenvolvido para a disciplina **CET080 – Computação Gráfica**, ministrada pela  
**Prof.ª Dra. Vânia Cordeiro da Silva**  
Universidade Estadual de Santa Cruz (UESC)

---

## 👨‍💻 Autores

- Gabriel Rosa Galdino
- Yohanan Santana

---

## 📄 Licença

Este projeto é apenas para fins educacionais e acadêmicos.
