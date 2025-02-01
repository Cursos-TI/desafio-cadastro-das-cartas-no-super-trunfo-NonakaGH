#include <stdio.h>
#include <string.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Autor: Rafael Nonaka
// OBS: Eu precisei adicionar algumas funções não apresentadas até o momento, pois não daria certo pelo que foi proposto

// Estrutura para armazenar os dados das cidades
typedef struct {
    char codigo[4];  // Código da cidade (Exemplo: A01, B02)
    char nome[20];   // Nome da cidade
    int populacao;   // População da cidade
    float area;      // Área da cidade em km²
    double pib;      // PIB da cidade em bilhões
    int pontos_turisticos; // Número de pontos turísticos
} Cidade;

// Estrutura para armazenar os dados dos estados (OBS: Eu tive que adicionar essa estrutura, não tinha nas aulas iniciais)
typedef struct {
    char letra;      // Letra do estado (A até H - OBS: Usando apenas "char" por ser um único caractere)
    Cidade cidades[4]; // Cada estado tem 4 cidades
} Estado;

// Estrutura para armazenar o país e seus estados (OBS: Mais uma estrutura para adicionar informações)
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

        // Loop para cadastrar os 8 estados (A-H) (OBS: Não tem na aula, mas adicionei para dar certo a proposta do desafio)
        for (int i = 0; i < 8; i++) {
            pais.estados[i].letra = 'A' + i; // Define a letra do estado (A, B, C... H)
            printf("\n--- Cadastro do Estado %c ---\n", pais.estados[i].letra);

            // Loop para cadastrar 4 cidades dentro de cada estado (OBS: A parte do "armazenar em caixas")
            for (int j = 0; j < 4; j++) {
                // Gerar código da cidade automaticamente (A01, A02...)
                sprintf(pais.estados[i].cidades[j].codigo, "%c0%d", pais.estados[i].letra, j + 1);

                printf("\nCadastro da cidade %s (Estado %c)\n", pais.estados[i].cidades[j].codigo, pais.estados[i].letra);

                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", pais.estados[i].cidades[j].nome);

                printf("Digite a população: ");
                scanf("%d", &pais.estados[i].cidades[j].populacao);

                printf("Digite a área (em km²): ");
                scanf("%f", &pais.estados[i].cidades[j].area);

                printf("Digite o PIB (em bilhões): ");
                scanf("%lf", &pais.estados[i].cidades[j].pib);

                printf("Digite o número de pontos turísticos: ");
                scanf("%d", &pais.estados[i].cidades[j].pontos_turisticos);
            }

            // Exibir os dados cadastrados do estado antes de prosseguir para o próximo (As partes do "colocar e tirar das caixas")
            printf("\n--- Cidades cadastradas no Estado %c ---\n", pais.estados[i].letra);
            for (int j = 0; j < 4; j++) {
                Cidade cidade = pais.estados[i].cidades[j];

                printf("\nCidade %s\n", cidade.codigo);
                printf("Nome: %s\n", cidade.nome);
                printf("População: %d habitantes\n", cidade.populacao);
                printf("Área: %.2f km²\n", cidade.area);
                printf("PIB: %.2lf bilhões\n", cidade.pib);
                printf("Pontos turísticos: %d\n", cidade.pontos_turisticos);
            }
        }

        // Exibição final dos dados cadastrados
        printf("\n\n---- DADOS FINAIS CADASTRADOS ----\n");
        printf("País: %s\n", pais.nome);

        for (int i = 0; i < 8; i++) {
            printf("\nEstado: %c\n", pais.estados[i].letra);

            for (int j = 0; j < 4; j++) {
                Cidade cidade = pais.estados[i].cidades[j];

                printf("\nCidade %s\n", cidade.codigo);
                printf("Nome: %s\n", cidade.nome);
                printf("População: %d habitantes\n", cidade.populacao);
                printf("Área: %.2f km²\n", cidade.area);
                printf("PIB: %.2lf bilhões\n", cidade.pib);
                printf("Pontos turísticos: %d\n", cidade.pontos_turisticos);
            }
        }

        // Pergunta ao usuário se deseja cadastrar outro país
        printf("\nDeseja cadastrar outro país? (S/N): ");
        scanf(" %c", &continuar); // Espaço antes do %c evita erro de buffer

        // Validação: enquanto a resposta não for 'S', 's', 'N' ou 'n', pede novamente
        while (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n') {
            printf("Opção inválida. Digite 'S' para cadastrar outro país ou 'N' para sair: ");
            scanf(" %c", &continuar);
        }

    } while (continuar == 'S' || continuar == 's'); // Repete se o usuário digitar 'S' ou 's', se digitar "n" finaliza

    printf("\nPrograma finalizado!\n");
    // Aguardando para criar o restante do programa e concluir o desafio
    return 0;
}
