# 🖼️ Atividade 5 – Computação Gráfica

Projeto da disciplina de **Computação Gráfica** – Atividade 5.  
O objetivo é processar uma imagem no formato `.ppm` e gerar três versões:


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
   - `arco-iris_1.pgm` → cinza (média simples)
   - `arco-iris_2.pgm` → cinza (média ponderada)
   - `arco-iris_3.ppm` → negativo

---

## 📝 Observações

- A imagem `.ppm` deve estar dentro da pasta `img/` caso queira adicionar novas imagens.
- As imagens de saída também serão salvas dentro da pasta `img/`.
- Ao executar o programa, informe o caminho relativo como: `Nome_Da_Imagem.ppm`

---

## 👨‍💻 Autores 

Gabriel Rosa Galdino

