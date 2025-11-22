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
#include <string.h>

//
/**
 * @brief Definição da struct territótio.
 ** Estrutura de dados composta para armazenar informações de um território.
 *- Nome: Armazena o nome do território (máximo de 29 caracteres +'\O').
 *Cor: Armazena a cor do exército que domina o território (máximo de 9 carácteres + '\O').
 * Tropas: Armazena a quantidade de tropas presentes no território.
 */

 typedef struct  {
    char nome [30];
    char cor [10];
    int tropas;
 } Territorio;

 int main() {

    Territorio territorios[5];
    int i; //Variável de controle para os laços  (loops)
    //--- CADASTRO DOS TERRITÓRIOS---
    printf("===================================\n");

    printf("SISTEMA DE CADASTRO DE TERRITÓRIOS\n");

    printf("===================================\n");

    printf("Por favor, preencha as informações para 5 territórios.\n\n");

    for (i = 0; i < 5; i ++) {

        printf("---Cadastro do território %d de 5 ---\n", i + 1);

        // Entrada: Nome do território
        printf("Digite o nome do território (máx. 29 caracteres:):");

        if (scanf(" %29s", territorios[i].nome) !=1) {
            
            printf("Erro na leitura do nome. Encerrando.\n");

            return 1;
        }

        // Entrada - cor do exército

        printf("Digite a cor do exército (máx. 9 caracteres:)");

        if (scanf(" %9s", territorios[i].cor) !=1) {
            printf("Erro na leitura da cor. Encerrando.\n");

            return 1;
        }

        // Entrada - Quantidade de tropas

        printf("Digite a quantidade de tropas (número inteiro):");

        if (scanf("%d", &territorios[i].tropas) !=1) {
            printf("Erro na leitura da quantidade de tropas. Certifique-se de digitar um número inteiro.\n");

            while (getchar() !='\n');
            i--;
            
        }

        printf("\n");
    }

    // --- Exibição dos dados ---

    printf("\n =============================\n");

    printf("Dados dos territórios cadastrados (5/5)\n");

    printf("================================\n");

    for (i = 0; i < 5; i++) {
        printf("Território %d\n", i+1);

        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("------------------------\n");
    }

    printf("\n Programa finalizado com sucesso!\n");

    return 0;

 }
 