// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TER 05
#define MAX_COR 10

// --- Estrutura de Dados ---
// Define a estrutura(STRUCT) para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio{
    char nome[MAX_COR];
    char cor[MAX_COR];
    int tropas;
};

// Nova estrutura(STRUCT) para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes para tamanhos máximos
#define MAX_NOME 30
#define MAX_COR 10

// --- Estrutura de Dados ---
// Define o modelo de um território com nome, cor (exército) e quantidade de tropas
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// Declaração das funções utilizadas no código
Territorio* cadastrarTerritorios(int total);
void mostrarMapa(Territorio* mapa, int total);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// --- Função Principal ---
int main() {
    int totalTerritorios = 5; // Número fixo de territórios
    srand(time(NULL));        // Inicializa a semente aleatória (dados diferentes a cada execução)

    printf("============== Desafio War! ==============\n\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n\n");

    // Aloca dinamicamente memória e cadastra os territórios
    Territorio* mapa = cadastrarTerritorios(totalTerritorios);

    printf("\nCadastro inicial concluído com sucesso!!!\n");

    int opcaoAtacante = -1;
    int opcaoDefensor = -1;

    // Loop de ataque, até o jogador digitar 0
    do {
        // Mostra o estado atual dos territórios
        printf("\n==================================\n");
        printf("MAPA DO MUNDO ATUAL - ESTADO ATUAL\n");
        printf("==================================\n");
        mostrarMapa(mapa, totalTerritorios);

        // Escolha do território atacante
        printf("\nFase de ATAQUE\n");
        printf("Escolha o território ATACANTE (1 a 5, ou 0 para sair): ");
        scanf("%d", &opcaoAtacante);
        getchar(); // limpa buffer do teclado

        if (opcaoAtacante == 0) {
            break; // Encerra o loop se for 0
        }

        // Verifica se o índice é válido
        if (opcaoAtacante < 1 || opcaoAtacante > totalTerritorios) {
            printf("Território inválido!\n");
            continue;
        }

        // Escolha do território defensor
        printf("Escolha o território DEFENSOR (1 a 5): ");
        scanf("%d", &opcaoDefensor);
        getchar();

        // Verifica se o índice é válido
        if (opcaoDefensor < 1 || opcaoDefensor > totalTerritorios) {
            printf("Território inválido!\n");
            continue;
        }

        // Obtém ponteiros para os territórios escolhidos
        Territorio* atacante = &mapa[opcaoAtacante - 1];
        Territorio* defensor = &mapa[opcaoDefensor - 1];

        // Verifica se estão na mesma cor (não pode atacar aliados)
        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Erro: Não é possível atacar um território do mesmo exército!\n");
            continue;
        }

        // Verifica se o atacante tem tropas
        if (atacante->tropas < 1) {
            printf("Erro: Território atacante não possui tropas suficientes!\n");
            continue;
        }

        // Executa o ataque
        atacar(atacante, defensor);

    } while (1); // Repete até o jogador sair

    liberarMemoria(mapa); // Libera memória alocada dinamicamente

    printf("\nFim da simulação. Obrigado por jogar!\n");

    return 0;
}

// --- Funções ---

// Cadastra os territórios com entrada do usuário
Territorio* cadastrarTerritorios(int total) {
    // Aloca memória para o vetor de territórios
    Territorio* vetor = (Territorio*) malloc(total * sizeof(Territorio));
    if (vetor == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1); // Encerra se falhar
    }

    // Loop para cadastrar cada território
    for (int i = 0; i < total; i++) {
        printf("--- Cadastrando Território %d ---\n", i + 1);

        printf("Nome do Território: ");
        fgets(vetor[i].nome, MAX_NOME, stdin);
        vetor[i].nome[strcspn(vetor[i].nome, "\n")] = '\0'; // Remove o '\n'

        printf("Cor do Exército: ");
        fgets(vetor[i].cor, MAX_COR, stdin);
        vetor[i].cor[strcspn(vetor[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &vetor[i].tropas);
        getchar(); // limpa o \n do buffer
    }

    return vetor; // Retorna ponteiro para o vetor criado
}

// Mostra o estado atual de todos os territórios
void mostrarMapa(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nIniciando batalha entre %s (cor %s) e %s (cor %s)...\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Gera valores aleatórios (dados de 1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Atacante venceu
    if (dadoAtacante > dadoDefensor) {
        printf("Vitória do atacante!\n");

        // Transfere a cor para o defensor
        strcpy(defensor->cor, atacante->cor);

        // Calcula metade das tropas para transferir
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas == 0) tropasTransferidas = 1; // mínimo 1

        // Atualiza tropas de ambos
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        printf("O território %s agora pertence ao exército %s.\n", defensor->nome, defensor->cor);
    } else {
        // Defensor venceu
        printf("Defesa bem-sucedida!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("%s perdeu uma tropa e agora tem %d tropas.\n", atacante->nome, atacante->tropas);
    }
}

// Libera a memória alocada para o vetor de territórios
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
