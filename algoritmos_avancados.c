#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct para representar uma sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Protótipos das funções
Sala* criarSala(const char* nome);
void conectarSalas(Sala* pai, Sala* esquerda, Sala* direita);
void explorarMansao(Sala* inicio);
void liberarArvore(Sala* raiz);
void limparBuffer();

int main() {
    printf("=== DETECTIVE QUEST - MAPA DA MANSÃO ===\n");
    printf("Enigma Studios - Sistema de Exploracao\n\n");
    
    // Criar todas as salas da mansão
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* escritorio = criarSala("Escritorio");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jardim = criarSala("Jardim");
    Sala* quarto = criarSala("Quarto Principal");
    Sala* banheiro = criarSala("Banheiro");
    Sala* sotao = criarSala("Sotao");
    Sala* porao = criarSala("Porao");
    
    // Montar a estrutura da árvore binária
    // Hall de Entrada: esquerda = Biblioteca, direita = Sala de Estar
    conectarSalas(hallEntrada, biblioteca, salaEstar);
    
    // Biblioteca: esquerda = Escritório, direita = Cozinha
    conectarSalas(biblioteca, escritorio, cozinha);
    
    // Sala de Estar: esquerda = Jardim, direita = Quarto Principal
    conectarSalas(salaEstar, jardim, quarto);
    
    // Escritório: esquerda = Sótão, direita = NULL (folha)
    conectarSalas(escritorio, sotao, NULL);
    
    // Cozinha: esquerda = NULL, direita = Porão
    conectarSalas(cozinha, NULL, porao);
    
    // Jardim: esquerda = NULL, direita = NULL (folha)
    // Quarto Principal: esquerda = Banheiro, direita = NULL
    conectarSalas(quarto, banheiro, NULL);
    
    // Iniciar exploração a partir do Hall de Entrada
    explorarMansao(hallEntrada);
    
    // Liberar memória alocada para a árvore
    liberarArvore(hallEntrada);
    
    printf("\nSaindo do Detective Quest...\n");
    return 0;
}

// Função para criar uma nova sala dinamicamente
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Função para conectar salas (definir filhos esquerdo e direito)
void conectarSalas(Sala* pai, Sala* esquerda, Sala* direita) {
    if (pai != NULL) {
        pai->esquerda = esquerda;
        pai->direita = direita;
    }
}

// Função principal de exploração da mansão
void explorarMansao(Sala* inicio) {
    Sala* salaAtual = inicio;
    char opcao;
    
    printf("Exploracao iniciada no: %s\n\n", salaAtual->nome);
    
    do {
        printf("Voce esta no: %s\n", salaAtual->nome);
        
        // Verificar caminhos disponíveis
        int temEsquerda = (salaAtual->esquerda != NULL);
        int temDireita = (salaAtual->direita != NULL);
        
        if (!temEsquerda && !temDireita) {
            printf("Fim do caminho! Esta sala nao tem saidas.\n");
            break;
        }
        
        printf("Caminhos disponiveis:\n");
        if (temEsquerda) {
            printf("  [e] Esquerda -> %s\n", salaAtual->esquerda->nome);
        }
        if (temDireita) {
            printf("  [d] Direita -> %s\n", salaAtual->direita->nome);
        }
        printf("  [s] Sair da exploracao\n");
        
        printf("Para onde deseja ir? ");
        scanf(" %c", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 'e':
            case 'E':
                if (temEsquerda) {
                    salaAtual = salaAtual->esquerda;
                    printf("\nMovendo para a esquerda...\n");
                } else {
                    printf("Nao ha caminho a esquerda!\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (temDireita) {
                    salaAtual = salaAtual->direita;
                    printf("\nMovendo para a direita...\n");
                } else {
                    printf("Nao ha caminho a direita!\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("Encerrando exploracao...\n");
                break;
                
            default:
                printf("Opcao invalida! Use 'e', 'd' ou 's'.\n");
        }
        
        printf("\n");
        
    } while(opcao != 's' && opcao != 'S');
}

// Função para liberar a memória da árvore (pós-ordem)
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Liberar subárvores primeiro
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    
    // Liberar o nó atual
    free(raiz);
}

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
