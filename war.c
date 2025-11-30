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
#include <stdlib.h> 
#include <string.h> 
#include <time.h>   

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
// DADOS GLOBAIS (Vetor de Missões)
// ===================================
const char* missoes_estrategicas[] = {
    "Conquistar no mínimo 3 territórios com o nome 'Alpha'.",
    "Ter pelo menos 15 tropas no mapa.",
    "Eliminar todas as tropas da cor 'Vermelho'.",
    "Conquistar o primeiro e o último território cadastrado (Indices 0 e N-1).",
    "Ter todos os seus territórios com mais de 3 tropas."
};
const int TOTAL_MISSOES = 5;

// ===================================
// FUNÇÕES DE SERVIÇO (Modularização)
// ===================================

/**
 * @brief Atribui uma missão aleatória para o jogador.
 * * @param destino Ponteiro para onde a string da missão será copiada (alocada dinamicamente).
 * @param missoes Vetor de strings com as missões disponíveis.
 * @param totalMissoes O número total de missões no vetor.
 */
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indice_sorteado = rand() % totalMissoes;
    
    // Uso de ponteiros e strcpy para copiar a missão sorteada.
    // Garante que a missão sorteada (string literal) seja copiada para a memória dinâmica (destino).
    strcpy(destino, missoes[indice_sorteado]);
}

/**
 * @brief Exibe a missão atual do jogador.
 * Passagem por valor (char*) para exibição (apenas leitura).
 * * @param missao String contendo a missão do jogador.
 */
void exibirMissao(char* missao) {
    printf("\n===========================================\n");
    printf(" SUA MISSÃO ATUAL\n");
    printf("===========================================\n");
    printf("Missão: %s\n", missao);
    printf("===========================================\n");
}

/**
 * @brief Função de verificação (lógica simples inicial).
 * Esta função deve ser expandida para checar todas as 5 missões. 
 * A lógica atual verifica se a Missão 1 (índice 0) ou Missão 2 (índice 1) foi cumprida.
 * * @param missao String com a descrição da missão.
 * @param mapa Ponteiro para o array de territórios.
 * @param tamanho Número total de territórios.
 * @return int 1 se a missão foi cumprida, 0 caso contrário.
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // A cor do jogador é assumida como a cor do primeiro território (índice 0) para esta lógica simples.
    char cor_jogador[10];
    if (tamanho > 0) {
        strcpy(cor_jogador, mapa[0].cor);
    } else {
        return 0;
    }
    
    // 1. Lógica para a missão: "Ter pelo menos 15 tropas no mapa." (Índice 1)
    if (strstr(missao, "15 tropas") != NULL) {
        int tropas_total = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, cor_jogador) == 0) {
                tropas_total += mapa[i].tropas;
            }
        }
        return (tropas_total >= 15);
    }
    
    // 2. Lógica para a missão: "Eliminar todas as tropas da cor 'Vermelho'." (Índice 2)
    if (strstr(missao, "Eliminar todas as tropas da cor 'Vermelho'") != NULL) {
        int inimigo_vermelho_restante = 0;
        for (int i = 0; i < tamanho; i++) {
            // Conta quantas tropas de "Vermelho" ainda existem.
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                inimigo_vermelho_restante += mapa[i].tropas;
            }
        }
        return (inimigo_vermelho_restante == 0);
    }

    // 3. Lógica para a missão: "Conquistar o primeiro e o último território cadastrado..." (Índice 3)
    if (strstr(missao, "primeiro e o último território") != NULL) {
        if (tamanho >= 2) {
            // Verifica se o primeiro (índice 0) e o último (índice tamanho - 1) pertencem ao jogador.
            return (strcmp(mapa[0].cor, cor_jogador) == 0 && strcmp(mapa[tamanho - 1].cor, cor_jogador) == 0);
        }
    }
    
    // Se a missão não foi implementada/reconhecida ou não foi cumprida.
    return 0;
}


/**
 * @brief Simula um ataque entre dois territórios.
 * (Mantido do passo anterior)
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int ataque_dado = (rand() % 6) + 1;
    int defesa_dado = (rand() % 6) + 1;

    printf("\n BATALHA entre %s e %s \n", atacante->nome, defensor->nome);

    if (ataque_dado > defesa_dado) {
        printf("  DADOS: ATAQUE(%d) > DEFESA(%d). Vitória do atacante!\n", ataque_dado, defesa_dado);
        
        // Transferência de cor e tropas (Requisito)
        strcpy(defensor->cor, atacante->cor);
        int tropas_transferidas = atacante->tropas / 2;
        
        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;

        printf("  %s conquistou %s. %d tropas transferidas.\n", atacante->nome, defensor->nome, tropas_transferidas);

    } else {
        // DEFESA VENCEDORA (ou empate)
        printf("  DADOS: ATAQUE(%d) <= DEFESA(%d). Defesa bem-sucedida!\n", ataque_dado, defesa_dado);
        
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("  %s perdeu 1 tropa no ataque (Restantes: %d).\n", atacante->nome, atacante->tropas);
        } else {
            printf("  %s tinha tropas insuficientes para a perda.\n", atacante->nome);
        }
    }
}

/**
 * @brief Cadastra os territórios (Mantido do passo anterior).
 */
Territorio* cadastrarTerritorios(int* tamanho) {
    Territorio* mapa = NULL;
    int num_territorios;

    printf("===================================================\n");
    printf(" CONFIGURAÇÃO INICIAL DO MAPA\n");
    printf("===================================================\n");
    
    printf("Digite o número total de territórios no mapa: ");
    if (scanf("%d", &num_territorios) != 1 || num_territorios <= 0) {
        printf("Erro: Número inválido. Encerrando.\n");
        exit(1);
    }
    
    // Alocação dinâmica de memória com calloc
    mapa = (Territorio*)calloc(num_territorios, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro: Falha na alocação de memória. Encerrando.\n");
        exit(1);
    }

    *tamanho = num_territorios;

    for (int i = 0; i < num_territorios; i++) {
        printf("\n--- Cadastro do Território %d de %d ---\n", i + 1, num_territorios);
        
        printf("Digite o NOME do território: ");
        scanf(" %29s", (mapa + i)->nome); 

        printf("Digite a COR do exército (ex: Azul, Vermelho): ");
        scanf(" %9s", (mapa + i)->cor); 

        printf("Digite a QUANTIDADE de tropas: ");
        if (scanf("%d", &(mapa + i)->tropas) != 1) {
             printf("Entrada inválida. Tente novamente.\n");
             i--; 
             continue;
        }
    }
    return mapa;
}

/**
 * @brief Exibe o mapa atual (Mantido do passo anterior).
 */
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n===================================================\n");
    printf(" MAPA ATUAL DOS TERRITÓRIOS (%d)\n", tamanho);
    printf("===================================================\n");
    
    for (int i = 0; i < tamanho; i++) {
        printf(" [%d] Nome: %s\n", i, (mapa + i)->nome);
        printf("     Cor:    %s\n", (mapa + i)->cor);
        printf("     Tropas: %d\n", (mapa + i)->tropas);
        printf("---------------------------------------------------\n");
    }
}

/**
 * @brief Libera toda a memória alocada dinamicamente.
 * * @param mapa Ponteiro para o bloco de memória dos territórios.
 * @param missao Ponteiro para o bloco de memória da missão.
 */
void liberarMemoria(Territorio* mapa, char* missao) {
    // Libera a memória do vetor de territórios
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória do mapa liberada.\n");
    }
    // Libera a memória da missão do jogador
    if (missao != NULL) {
        free(missao);
        printf("Memória da missão liberada.\n");
    }
}

// ===================================
// FUNÇÃO PRINCIPAL
// ===================================
int main() {
    srand(time(NULL));

    Territorio* mapa_territorios = NULL;
    int num_territorios = 0;
    
    // Alocação dinâmica para armazenar a missão do jogador (Requisito)
    // O maior tamanho de string no vetor de missões é ~80 caracteres. Usamos 100 para segurança.
    char* missao_jogador = (char*)malloc(100 * sizeof(char)); 
    if (missao_jogador == NULL) {
        printf("Erro: Falha na alocação da missão.\n");
        return 1;
    }
    
    char continuar_ataque;

    // 1. CADASTRO INICIAL E ALOCAÇÃO
    mapa_territorios = cadastrarTerritorios(&num_territorios);
    
    // 2. ATRIBUIÇÃO E EXIBIÇÃO DA MISSÃO
    // Passa o ponteiro 'missao_jogador' por referência para a atribuição.
    atribuirMissao(missao_jogador, missoes_estrategicas, TOTAL_MISSOES);
    
    // Exibição da missão (apenas no início)
    exibirMissao(missao_jogador);

    // 3. LAÇO PRINCIPAL DE JOGO
    do {
        int indice_atacante, indice_defensor;
        
        exibirMapa(mapa_territorios, num_territorios);
        
        // Verificação condicional da missão (Verificação silenciosa)
        if (verificarMissao(missao_jogador, mapa_territorios, num_territorios)) {
            printf("\n\n PARABÉNS! VOCÊ CUMPRIU SUA MISSÃO! \n");
            printf("Sua missão era: %s\n", missao_jogador);
            break; // Sai do loop principal, declarando o vencedor.
        }

        printf("\n--- CONFIGURAR ATAQUE (Digite um índice entre 0 e %d) ---\n", num_territorios - 1);
        printf("Território ATACANTE: ");
        if (scanf("%d", &indice_atacante) != 1 || indice_atacante < 0 || indice_atacante >= num_territorios) {
            printf(" Índice inválido.\n");
            while (getchar() != '\n'); continue; 
        }

        if ((mapa_territorios + indice_atacante)->tropas <= 1) {
            printf(" Tropas insuficientes para atacar.\n");
            continue;
        }

        printf("Território DEFENSOR: ");
        if (scanf("%d", &indice_defensor) != 1 || indice_defensor < 0 || indice_defensor >= num_territorios) {
            printf(" Índice inválido.\n");
            while (getchar() != '\n'); continue;
        }

        // Validação: Atacar inimigo
        if (strcmp((mapa_territorios + indice_atacante)->cor, (mapa_territorios + indice_defensor)->cor) == 0) {
            printf(" Você não pode atacar um território da sua própria cor!\n");
            continue;
        }

        // EXECUÇÃO DO ATAQUE
        atacar(mapa_territorios + indice_atacante, mapa_territorios + indice_defensor);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar_ataque); 

    } while (continuar_ataque == 's' || continuar_ataque == 'S');

    // 4. LIBERAÇÃO DE MEMÓRIA (Requisito)
    liberarMemoria(mapa_territorios, missao_jogador);

    printf("\nPrograma encerrado.\n");
    
    return 0;
}