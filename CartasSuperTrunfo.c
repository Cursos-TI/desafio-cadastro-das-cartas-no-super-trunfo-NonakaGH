#include <stdio.h>
#include <string.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Autor: Rafael Nonaka

// Estrutura para armazenar os dados das cidades
typedef struct {
    char codigo[4];  // Código da cidade (Exemplo: A01, B02)
    char nome[20];   // Nome da cidade
    int populacao;   // População da cidade
    float area;      // Área da cidade em km²
    double pib;      // PIB da cidade (em reais, não mais em bilhões)
    int pontos_turisticos; // Número de pontos turísticos
    float densidade;  // Densidade Populacional (População / Área)
    double pib_per_capita; // PIB per Capita (PIB em reais / População)
} Cidade;

// Estrutura para armazenar os dados dos estados
typedef struct {
    char letra;      // Letra do estado (A até H)
    Cidade cidades[4]; // Cada estado tem 4 cidades
} Estado;

// Estrutura para armazenar o país e seus estados
typedef struct {
    char nome[30];  // Nome do país
    Estado estados[8]; // O país tem 8 estados
} Pais;

int main() {
    char continuar; // Variável para permitir cadastrar mais de um país

    do {
        Pais pais;
        
        // Cadastro do país
        printf("\nDigite o nome do país: ");
        scanf(" %[^\n]", pais.nome);

        // Loop para cadastrar os 8 estados (A-H)
        for (int i = 0; i < 8; i++) {
            pais.estados[i].letra = 'A' + i;
            printf("\n--- Cadastro do Estado %c ---\n", pais.estados[i].letra);

            // Loop para cadastrar 4 cidades dentro de cada estado
            for (int j = 0; j < 4; j++) {
                // Gerar código da cidade automaticamente (A01, A02...)
                sprintf(pais.estados[i].cidades[j].codigo, "%c0%d", pais.estados[i].letra, j + 1);

                printf("\nCadastro da cidade %s (Estado %c)\n", pais.estados[i].cidades[j].codigo, pais.estados[i].letra);

                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", pais.estados[i].cidades[j].nome);

                printf("Digite a população: ");
                scanf("%d", &pais.estados[i].cidades[j].populacao);
                
                printf("Digite a área (em km²): ");
                scanf(" %f", &pais.estados[i].cidades[j].area);

                printf("Digite o PIB (em reais): ");
                scanf(" %lf", &pais.estados[i].cidades[j].pib);

                // Cálculo densidade
                pais.estados[i].cidades[j].densidade = (pais.estados[i].cidades[j].area > 0) ? 
                    pais.estados[i].cidades[j].populacao / pais.estados[i].cidades[j].area : 0;
                // Cálculo PIB
                pais.estados[i].cidades[j].pib_per_capita = (pais.estados[i].cidades[j].populacao > 0) ? 
                    (pais.estados[i].cidades[j].pib * 1000000000) / pais.estados[i].cidades[j].populacao : 0;


                // 📌 Exibição dos cálculos antes de perguntar pelos pontos turísticos
                printf("Densidade Populacional: %.2f habitantes/km²\n", pais.estados[i].cidades[j].densidade);
                printf("PIB per Capita: R$ %.2lf por habitante\n", pais.estados[i].cidades[j].pib_per_capita);

                printf("Digite o número de pontos turísticos: ");
                scanf(" %d", &pais.estados[i].cidades[j].pontos_turisticos);
            }

            // Exibir os dados cadastrados do estado antes de prosseguir para o próximo
            printf("\n--- Cidades cadastradas no Estado %c ---\n", pais.estados[i].letra);
            for (int j = 0; j < 4; j++) {
                printf("\nCidade %s\n", pais.estados[i].cidades[j].codigo);
                printf("Nome: %s\n", pais.estados[i].cidades[j].nome);
                printf("População: %d habitantes\n", pais.estados[i].cidades[j].populacao);
                printf("Área: %.2f km²\n", pais.estados[i].cidades[j].area);
                printf("PIB: R$ %.2lf\n", pais.estados[i].cidades[j].pib);
                printf("Densidade Populacional: %.2f habitantes/km²\n", pais.estados[i].cidades[j].densidade);
                printf("PIB per Capita: R$ %.2lf por habitante\n", pais.estados[i].cidades[j].pib_per_capita);
                printf("Pontos turísticos: %d\n", pais.estados[i].cidades[j].pontos_turisticos);
            }
        }

        // Exibição final dos dados cadastrados
        printf("\n\n---- DADOS FINAIS CADASTRADOS ----\n");
        printf("País: %s\n", pais.nome);

        for (int i = 0; i < 8; i++) {
            printf("\nEstado: %c\n", pais.estados[i].letra);

            for (int j = 0; j < 4; j++) {
                printf("\nCidade %s\n", pais.estados[i].cidades[j].codigo);
                printf("Nome: %s\n", pais.estados[i].cidades[j].nome);
                printf("População: %d habitantes\n", pais.estados[i].cidades[j].populacao);
                printf("Área: %.2f km²\n", pais.estados[i].cidades[j].area);
                printf("PIB: R$ %.2lf\n", pais.estados[i].cidades[j].pib);
                printf("Densidade Populacional: %.2f habitantes/km²\n", pais.estados[i].cidades[j].densidade);
                printf("PIB per Capita: R$ %.2lf por habitante\n", pais.estados[i].cidades[j].pib_per_capita);
                printf("Pontos turísticos: %d\n", pais.estados[i].cidades[j].pontos_turisticos);
            }
        }

        // Pergunta ao usuário se deseja cadastrar outro país
        printf("\nDeseja cadastrar outro país? (S/N): ");
        scanf(" %c", &continuar);

        // Validação: enquanto a resposta não for 'S', 's', 'N' ou 'n', pede novamente
        while (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n') {
            printf("Opção inválida. Digite 'S' para cadastrar outro país ou 'N' para sair: ");
            scanf(" %c", &continuar);
        }

    } while (continuar == 'S' || continuar == 's'); // Repete se o usuário digitar 'S' ou 's', se digitar "N" finaliza

    printf("\nPrograma finalizado!\n");

    return 0;
}
