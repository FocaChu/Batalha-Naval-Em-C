#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Declaração das funções
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int posicaoValida(int linha, int coluna);

int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicio, int coluna_inicio, int orientacao);

int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao, const char* tipo);

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    // Inicializa o tabuleiro com zeros (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios (definidas no código)
    int navio_horizontal_linha = 2;
    int navio_horizontal_coluna = 3;
    
    int navio_vertical_linha = 5;
    int navio_vertical_coluna = 7;

    int navio_diagonal_esquerda_linha = 6;
    int navio_diagonal_esquerda_coluna = 3;

    int navio_diagonal_direita_linha = 2;
    int navio_diagonal_direita_coluna = 7;

    // Posicionar navio horizontal
    if (!posicionarNavio(tabuleiro, navio_horizontal_linha, navio_horizontal_coluna, 0, "horizontal")) {
        return 1; // Encerra o programa com erro
    }

    if (!posicionarNavio(tabuleiro, navio_diagonal_esquerda_linha, navio_diagonal_esquerda_coluna, 1, "diagonal esquerda")) {
        return 1; // Encerra o programa com erro
    }    

    if (!posicionarNavio(tabuleiro, navio_diagonal_direita_linha, navio_diagonal_direita_coluna, 2, "diagonal direita")) {
        return 1; // Encerra o programa com erro
    }

    // Posicionar navio vertical
    if (!posicionarNavio(tabuleiro, navio_vertical_linha, navio_vertical_coluna, 3, "vertical")) {
        return 1; // Encerra o programa com erro
    }

    // Exibir o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Inicializa o tabuleiro com zeros (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se uma posição está dentro dos limites do tabuleiro
int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && 
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Verifica se há sobreposição para um navio na posição especificada
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicio, int coluna_inicio, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha, coluna;
        
        // Calcula a posição atual baseado na orientação
        if (orientacao == 0) { // Horizontal
            linha = linha_inicio;
            coluna = coluna_inicio + i;
        } else { // Vertical
            linha = linha_inicio + i;
            coluna = coluna_inicio;
        }
        
        // Verifica se a posição está dentro do tabuleiro
        if (!posicaoValida(linha, coluna)) {
            printf("ERRO: Navio fora dos limites do tabuleiro na posição (%d, %d)!\n", linha, coluna);
            return 0; // Inválido
        }
        
        // Verifica se já tem um navio nesta posição
        if (tabuleiro[linha][coluna] == 3) {
            printf("ERRO: Sobreposição de navios na posição (%d, %d)!\n", linha, coluna);
            return 0; // Inválido
        }
    }
    return 1; // Válido
}

// Posiciona um navio no tabuleiro após validar
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao, const char* tipo) {
    printf("Posicionando navio %s...\n", tipo);
    
    if (verificarSobreposicao(tabuleiro, linha, coluna, orientacao)) {
        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (orientacao == 0) { // Horizontal
                tabuleiro[linha][coluna + i] = 3;
            } 
            else if (orientacao == 1) { // horizontal esquerda
                tabuleiro[linha + i][coluna - i] = 3;
            } 
            else if (orientacao == 2) { // horizontal direita
                tabuleiro[linha + i][coluna + i] = 3;
            } else { // Vertical
                tabuleiro[linha + i][coluna] = 3;
            }
        }
        printf("Navio %s posicionado com sucesso!\n", tipo);
        return 1; // Sucesso
    } else {
        printf("Não foi possível posicionar o navio %s.\n", tipo);
        return 0; // Falha
    }
}

// Exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro do Batalha Naval (%dx%d):\n", TAMANHO_TABULEIRO, TAMANHO_TABULEIRO);
    
    // Cabeçalho com números das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d  ", j);
    }
    printf("\n");
    
    // Linha separadora
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO * 3 - 2; j++) {
        printf("-");
    }
    printf("\n");
    
    // Conteúdo do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d|", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d  ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    // Legenda
    printf("\nLegenda:\n");
    printf("0 - Água\n");
    printf("3 - Navio\n");
}