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

 #include <stdio.h>
#include <stdlib.h> // Para malloc, calloc e free
#include <string.h> // Para strcpy
#include <time.h>   // Para srand e time

// ===================================
// DEFINIÇÃO DA ESTRUTURA
// ===================================

/**
 * @brief Estrutura de dados composta Territorio.
 * Contém o nome, a cor do exército e a quantidade de tropas.
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ===================================
// FUNÇÕES DE SERVIÇO (Modularização)
// ===================================

/**
 * @brief Simula um ataque entre dois territórios.
 * Utiliza ponteiros para acessar e modificar os dados do atacante e defensor.
 * * @param atacante Ponteiro para o Territorio atacante.
 * @param defensor Ponteiro para o Territorio defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Requisito técnico: Usar rand() para simular um dado de 1 a 6.
    int ataque_dado = (rand() % 6) + 1;
    int defesa_dado = (rand() % 6) + 1;

    printf("\n SIMULAÇÃO DE BATALHA \n");
    printf("  %s (Tropas: %d) rola o dado de ATAQUE: %d\n", atacante->nome, atacante->tropas, ataque_dado);
    printf("  %s (Tropas: %d) rola o dado de DEFESA: %d\n", defensor->nome, defensor->tropas, defesa_dado);

    if (ataque_dado > defesa_dado) {
        // ATAQUE VENCEDOR
        // Atualização de campos: O defensor muda de dono (cor do exército).
        printf("\nVitória! %s conquistou %s!\n", atacante->nome, defensor->nome);
        
        // Transferência de cor: Utiliza strcpy com ponteiros.
        strcpy(defensor->cor, atacante->cor);
        
        // Transferência de tropas: Metade das tropas do atacante se movem para o defensor.
        int tropas_transferidas = atacante->tropas / 2;
        
        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;

        printf("  Dono do território defensor alterado para a cor %s.\n", defensor->cor);
        printf("  %d tropas transferidas de %s para %s.\n", tropas_transferidas, atacante->nome, defensor->nome);

    } else {
        // DEFESA VENCEDORA (ou empate)
        printf("\nDerrota! %s manteve o controle do território.\n", defensor->nome);
        
        // Se perder (ou empatar), o atacante perde uma tropa.
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("  %s perdeu 1 tropa no ataque (Restantes: %d).\n", atacante->nome, atacante->tropas);
        } else {
            // Evita que o número de tropas fique negativo ou zero, impedindo novos ataques.
            printf("  %s tem tropas insuficientes para a perda.\n", atacante->nome);
        }
    }
}

/**
 * @brief Função para cadastrar todos os territórios.
 * Solicita o tamanho, aloca memória e preenche os dados.
 * * @param tamanho Ponteiro para a variável que armazenará o número total de territórios.
 * @return Territorio* Retorna o ponteiro para o bloco de memória alocado.
 */
Territorio* cadastrarTerritorios(int* tamanho) {
    Territorio* mapa = NULL;
    int num_territorios;

    printf("===================================================\n");
    printf(" CONFIGURAÇÃO INICIAL DO MAPA\n");
    printf("===================================================\n");
    
    // Alocação de memória: Pede ao usuário o número total de territórios.
    printf("Digite o número total de territórios no mapa: ");
    if (scanf("%d", &num_territorios) != 1 || num_territorios <= 0) {
        printf("Erro: Número inválido de territórios. Encerrando.\n");
        exit(1);
    }
    
    // Alocação dinâmica de memória: Usando calloc para inicializar com zero.
    mapa = (Territorio*)calloc(num_territorios, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro: Falha na alocação de memória. Encerrando.\n");
        exit(1);
    }

    *tamanho = num_territorios;
    printf("\nMemória alocada com sucesso para %d territórios.\n", num_territorios);

    // Entrada dos dados: Laço para preencher as informações.
    for (int i = 0; i < num_territorios; i++) {
        printf("\n--- Cadastro do Território %d de %d ---\n", i + 1, num_territorios);
        
        // Uso de ponteiros para acessar o elemento (mapa + i) e seu campo.
        printf("Digite o NOME do território: ");
        scanf(" %29s", (mapa + i)->nome); 

        printf("Digite a COR do exército (ex: Azul, Vermelho): ");
        scanf(" %9s", (mapa + i)->cor); 

        printf("Digite a QUANTIDADE de tropas (mínimo 2 para atacar): ");
        if (scanf("%d", &(mapa + i)->tropas) != 1) {
             printf("Entrada inválida. Tente novamente.\n");
             i--; // Repete a iteração
             continue;
        }
    }
    return mapa;
}

/**
 * @brief Exibe as informações de todos os territórios alocados dinamicamente.
 * * @param mapa Ponteiro para o array de Territorios.
 * @param tamanho Número de elementos no array.
 */
void exibirTerritorios(Territorio* mapa, int tamanho) {
    printf("\n===================================================\n");
    printf(" MAPA ATUAL DOS TERRITÓRIOS (%d)\n", tamanho);
    printf("===================================================\n");
    
    for (int i = 0; i < tamanho; i++) {
        // Uso de ponteiros: (mapa + i) aponta para o i-ésimo elemento.
        printf(" [%d] Nome: %s\n", i, (mapa + i)->nome);
        printf("     Cor:    %s\n", (mapa + i)->cor);
        printf("     Tropas: %d\n", (mapa + i)->tropas);
        printf("---------------------------------------------------\n");
    }
}

/**
 * @brief Libera a memória alocada dinamicamente.
 * * @param mapa Ponteiro para o bloco de memória a ser liberado.
 */
void liberarMemoria(Territorio* mapa) {
    // Gerenciamento de memória: free() deve ser chamado para liberar a memória alocada.
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória do mapa liberada com sucesso.\n");
    }
}

// ===================================
// FUNÇÃO PRINCIPAL
// ===================================
int main() {
    // Requisito técnico: Inicializa o gerador de números aleatórios.
    srand(time(NULL));

    Territorio* mapa_territorios = NULL;
    int num_territorios = 0;
    char continuar_ataque;

    // 1. CADASTRO INICIAL E ALOCAÇÃO
    mapa_territorios = cadastrarTerritorios(&num_territorios);

    // 2. LAÇO PRINCIPAL DE ATAQUE
    do {
        int indice_atacante, indice_defensor;
        
        // Exibição dos dados atualizados antes de cada ataque (Requisito)
        exibirTerritorios(mapa_territorios, num_territorios);
        
        printf("\n--- CONFIGURAR ATAQUE ---\n");
        printf("Escolha o índice do território ATACANTE (0 a %d): ", num_territorios - 1);
        if (scanf("%d", &indice_atacante) != 1 || indice_atacante < 0 || indice_atacante >= num_territorios) {
            printf(" Índice de atacante inválido. Tente novamente.\n");
            // Limpa o buffer de entrada.
            while (getchar() != '\n'); 
            continue; 
        }

        // Validação: Atacante deve ter mais de uma tropa para atacar.
        if ((mapa_territorios + indice_atacante)->tropas <= 1) {
            printf(" O território %s tem tropas insuficientes para atacar. Mínimo de 2 tropas.\n", (mapa_territorios + indice_atacante)->nome);
            continue;
        }

        printf("Escolha o índice do território DEFENSOR (0 a %d): ", num_territorios - 1);
        if (scanf("%d", &indice_defensor) != 1 || indice_defensor < 0 || indice_defensor >= num_territorios) {
            printf(" Índice de defensor inválido. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        // Validação: Jogador não deve atacar território da própria cor.
        // Utiliza strcmp para comparar as strings de cor (campos acessados por ponteiros).
        if (strcmp((mapa_territorios + indice_atacante)->cor, (mapa_territorios + indice_defensor)->cor) == 0) {
            printf(" Você não pode atacar um território da sua própria cor (%s)!\n", (mapa_territorios + indice_atacante)->cor);
            continue;
        }

        // 3. EXECUÇÃO DO ATAQUE
        // Passa os ponteiros dos territórios selecionados para a função atacar.
        // &mapa_territorios[indice] ou (mapa_territorios + indice) são ponteiros válidos.
        atacar(mapa_territorios + indice_atacante, mapa_territorios + indice_defensor);

        // 4. PERGUNTA SE DESEJA CONTINUAR
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar_ataque); // Espaço antes de %c para ignorar o newline.

    } while (continuar_ataque == 's' || continuar_ataque == 'S');

    // 5. LIBERAÇÃO DE MEMÓRIA (Requisito)
    liberarMemoria(mapa_territorios);

    printf("\nPrograma encerrado.\n");
    
    return 0;
}