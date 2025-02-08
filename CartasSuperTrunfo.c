#include <stdio.h>
#include <string.h>

#define MAX_PAISES 10  // Máximo de países que podem ser cadastrados

// Estrutura para armazenar os dados das cidades
typedef struct {
    char codigo[4];
    char nome[20];
    int populacao;
    float area;
    double pib;
    int pontos_turisticos;
    float densidade;
    double pib_per_capita;
    double super_poder;
} Cidade;

double calcular_super_poder(Cidade c) {
    double densidade_ajustada = (c.densidade > 0) ? (1 / (c.densidade + 1)) * 100 : 100; 
    return c.populacao + c.area + (c.pib / 1000000000) + c.pontos_turisticos + densidade_ajustada + c.pib_per_capita;
}

// Estrutura para armazenar os estados
typedef struct {
    char letra;
    Cidade cidades[4];
} Estado;

// Estrutura para armazenar o país e seus estados
typedef struct {
    char nome[30];
    Estado estados[8];
} Pais;

void exibir_dados_cidade(Cidade cidade) {
    printf("\nCidade %s\n", cidade.codigo);
    printf("Nome: %s\n", cidade.nome);
    printf("População: %d habitantes\n", cidade.populacao);
    printf("Área: %.2f km²\n", cidade.area);
    printf("PIB: R$ %.2lf\n", cidade.pib);
    printf("Densidade Populacional: %.2f habitantes/km²\n", cidade.densidade);
    printf("PIB per Capita: R$ %.2f por habitante\n", cidade.pib_per_capita);
    printf("Pontos turísticos: %d\n", cidade.pontos_turisticos);
    printf("Super Poder: %.2f\n", cidade.super_poder);
}

// Função para buscar uma cidade em qualquer país cadastrado
Cidade* buscar_cidade(Pais paises[], int num_paises, char codigo[]) {
    for (int p = 0; p < num_paises; p++) { // Percorre os países cadastrados
        for (int i = 0; i < 8; i++) { // Percorre os estados
            for (int j = 0; j < 4; j++) { // Percorre as cidades
                if (strcmp(paises[p].estados[i].cidades[j].codigo, codigo) == 0) {
                    return &paises[p].estados[i].cidades[j];
                }
            }
        }
    }
    return NULL;
}

// Função para comparar duas cidades
void comparar_cartas(Cidade c1, Cidade c2) {
    printf("\nComparação entre %s e %s\n", c1.nome, c2.nome);
    
    printf("\nPopulação: %d vs %d - %s vence!\n", c1.populacao, c2.populacao, (c1.populacao > c2.populacao) ? c1.nome : c2.nome);
    printf("\nÁrea: %.2f km² vs %.2f km² - %s vence!\n", c1.area, c2.area, (c1.area > c2.area) ? c1.nome : c2.nome);
    printf("\nPIB: R$ %.2lf vs R$ %.2lf - %s vence!\n", c1.pib, c2.pib, (c1.pib > c2.pib) ? c1.nome : c2.nome);
    printf("\nPontos Turísticos: %d vs %d - %s vence!\n", c1.pontos_turisticos, c2.pontos_turisticos, (c1.pontos_turisticos > c2.pontos_turisticos) ? c1.nome : c2.nome);
    printf("\nPIB per Capita: R$ %.2f vs R$ %.2f - %s vence!\n", c1.pib_per_capita, c2.pib_per_capita, (c1.pib_per_capita > c2.pib_per_capita) ? c1.nome : c2.nome);
    printf("\nDensidade Populacional: %.2f hab/km² vs %.2f hab/km² - %s vence!\n", c1.densidade, c2.densidade, (c1.densidade < c2.densidade) ? c1.nome : c2.nome);
    printf("\nSuper Poder: %.2f vs %.2f - %s vence!\n", c1.super_poder, c2.super_poder, (c1.super_poder > c2.super_poder) ? c1.nome : c2.nome);
}

int main() {
    Pais paises[MAX_PAISES]; // Array para armazenar países
    int num_paises = 0;
    char continuar;

    do {
        if (num_paises >= MAX_PAISES) {
            printf("\nLimite máximo de países cadastrados atingido!\n");
            break;
        }

        Pais *pais = &paises[num_paises];

        // Cadastro do país
        printf("\nDigite o nome do país: ");
        scanf(" %[^\n]", pais->nome);

        // Loop para cadastrar os 8 estados (A-H)
        for (int i = 0; i < 8; i++) {
            pais->estados[i].letra = 'A' + i;
            printf("\n--- Cadastro do Estado %c ---\n", pais->estados[i].letra);

            // Loop para cadastrar 4 cidades dentro de cada estado
            for (int j = 0; j < 4; j++) {
                sprintf(pais->estados[i].cidades[j].codigo, "%c0%d", pais->estados[i].letra, j + 1);
                printf("\nCadastro da cidade %s (Estado %c)\n", pais->estados[i].cidades[j].codigo, pais->estados[i].letra);

                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", pais->estados[i].cidades[j].nome);
                printf("Digite a população: ");
                scanf("%d", &pais->estados[i].cidades[j].populacao);
                printf("Digite a área (em km²): ");
                scanf("%f", &pais->estados[i].cidades[j].area);
                printf("Digite o PIB (em reais): ");
                scanf("%lf", &pais->estados[i].cidades[j].pib);

                // Cálculo e exibição imediata
                pais->estados[i].cidades[j].densidade = pais->estados[i].cidades[j].populacao / pais->estados[i].cidades[j].area;
                pais->estados[i].cidades[j].pib_per_capita = pais->estados[i].cidades[j].pib / pais->estados[i].cidades[j].populacao;

                printf("Densidade Populacional calculada: %.2f habitantes/km²\n", pais->estados[i].cidades[j].densidade);
                printf("PIB per Capita calculado: R$ %.2f\n", pais->estados[i].cidades[j].pib_per_capita);

                printf("Digite o número de pontos turísticos: ");
                scanf("%d", &pais->estados[i].cidades[j].pontos_turisticos);

                pais->estados[i].cidades[j].super_poder = calcular_super_poder(pais->estados[i].cidades[j]);

                exibir_dados_cidade(pais->estados[i].cidades[j]); 
            }
        }

        num_paises++;

        printf("\nDeseja cadastrar outro país? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's'); // Finaliza cadastro de países

    // **INÍCIO DA FASE DE COMPARAÇÃO**
    char opcao_comparacao;
    do {
        printf("\nIniciando sistema de comparação de cartas...\n");

        // Entrada dos códigos das cidades para comparação
        char codigo1[4], codigo2[4];
        Cidade *cidade1, *cidade2;

        do {
            printf("\nDigite o código da primeira cidade para comparação: ");
            scanf("%s", codigo1);
            cidade1 = buscar_cidade(paises, num_paises, codigo1);

            if (cidade1 == NULL) {
            printf("Código não encontrado! Tente novamente.\n");
            }

        } while (cidade1 == NULL);

        do {
            printf("Digite o código da segunda cidade para comparação: ");
            scanf("%s", codigo2);
            cidade2 = buscar_cidade(paises, num_paises, codigo2);

            if (cidade2 == NULL) {
                printf("Código não encontrado! Tente novamente.\n");
            }

        } while (cidade2 == NULL);

        // Chama a função para comparar as cidades escolhidas
        comparar_cartas(*cidade1, *cidade2);

        // Pergunta ao usuário se deseja continuar comparando
        printf("\nDeseja fazer outra comparação? (S/N): ");
        scanf(" %c", &opcao_comparacao);

    } while (opcao_comparacao == 'S' || opcao_comparacao == 's'); // Continua até o usuário digitar "N"

    printf("\nSistema encerrado. Obrigado por usar o Super Trunfo de Cidades!\n");

    return 0;
}
