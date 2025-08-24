/*
 * Desafio Cartas de Cidades - Nível Aventureiro (C puro)
 * Feito por Gustavo Teixeira Louro
 * 
 * Novidades em relação ao Novato:
 *  - Menu interativo com switch para escolher o atributo de comparação
 *  - Comparação ANINHADA: decisão baseada em múltiplos atributos (tie-breakers)
 *  - Cadastro de cartas via terminal (igual ao Novato)
 *  - Saídas organizadas e claras
 *
 * Regras de comparação:
 * - População: maior vence
 * - Área: maior vence
 * - PIB: maior vence
 * - Pontos turísticos: maior vence
 * - Densidade populacional: menor vence (população/área)
 * - Comparação aninhada (ordem de prioridade):
  */

#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    char estado[3];
    char codigo[16];
    char cidade[50];
    long long populacao;
    double area;
    double pib;
    int pontosTuristicos;
} Carta;

enum Criterio {
    POPULACAO = 1,
    AREA      = 2,
    PIB       = 3,
    PONTOS    = 4,
    DENSIDADE = 5,
    ANINHADA  = 6
};

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}

static void ler_string(const char *label, char *buf, size_t maxlen) {
    printf("%s", label);
    if (fgets(buf, (int)maxlen, stdin) == NULL) { buf[0] = '\0'; return; }
    size_t n = strlen(buf);
    if (n && buf[n-1] == '\n') buf[n-1] = '\0';
}

static void ler_carta(Carta *c, int idx) {
    printf("\n=== Cadastro da Carta %d ===\n", idx);
    ler_string("Estado (UF, ex: SP): ", c->estado, sizeof(c->estado));
    ler_string("Código da carta: ", c->codigo, sizeof(c->codigo));
    ler_string("Nome da cidade: ", c->cidade, sizeof(c->cidade));

    printf("População (habitantes): ");
    while (scanf("%lld", &c->populacao) != 1 || c->populacao < 0) {
        printf("Valor inválido. Tente novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("Área (km^2): ");
    while (scanf("%lf", &c->area) != 1 || c->area <= 0.0) {
        printf("Valor inválido (>0). Tente novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("PIB: ");
    while (scanf("%lf", &c->pib) != 1 || c->pib < 0.0) {
        printf("Valor inválido. Tente novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("Pontos turísticos: ");
    while (scanf("%d", &c->pontosTuristicos) != 1 || c->pontosTuristicos < 0) {
        printf("Valor inválido. Tente novamente: ");
        limpar_buffer();
    }
    limpar_buffer();
}

static double densidade(const Carta *c) {
    return (c->area > 0.0) ? ( (double)c->populacao / c->area ) : INFINITY;
}

static void exibir_carta(const Carta *c, const char *titulo) {
    printf("\n--- %s ---\n", titulo);
    printf("Estado: %s\n", c->estado);
    printf("Código: %s\n", c->codigo);
    printf("Cidade: %s\n", c->cidade);
    printf("População: %lld\n", c->populacao);
    printf("Área: %.3f km^2\n", c->area);
    printf("PIB: %.3f\n", c->pib);
    printf("Pontos Turísticos: %d\n", c->pontosTuristicos);
    double d = densidade(c);
    if (isfinite(d)) printf("Densidade: %.3f hab/km^2\n", d);
    else printf("Densidade: indefinida (área inválida)\n");
}

static void menu(void) {
    printf("\n===== MENU DE COMPARAÇÃO =====\n");
    printf("1) População (maior vence)\n");
    printf("2) Área (maior vence)\n");
    printf("3) PIB (maior vence)\n");
    printf("4) Pontos turísticos (maior vence)\n");
    printf("5) Densidade populacional (menor vence)\n");
    printf("6) Comparação aninhada (múltiplos atributos)\n");
    printf("Selecione uma opção: ");
}

static int comparar_simples(int opcao, const Carta *a, const Carta *b) {
    switch (opcao) {
        case POPULACAO: return (a->populacao > b->populacao) - (a->populacao < b->populacao);
        case AREA:      return (a->area      > b->area)      - (a->area      < b->area);
        case PIB:       return (a->pib       > b->pib)       - (a->pib       < b->pib);
        case PONTOS:    return (a->pontosTuristicos > b->pontosTuristicos) - (a->pontosTuristicos < b->pontosTuristicos);
        case DENSIDADE: {
            double da = densidade(a), db = densidade(b);
            if (da == db) return 0;
            return (da < db) ? +1 : -1; // MENOR vence → invertido
        }
        default: return 0;
    }
}

/* Comparação aninhada:
 * 1º: População (maior vence)
 * 2º: Área (maior vence)
 * 3º: PIB (maior vence)
 * 4º: Densidade (MENOR vence)
 * 5º: Pontos turísticos (maior vence)
 */
static int comparar_aninhado(const Carta *a, const Carta *b) {
    int r;
    if ((r = comparar_simples(POPULACAO, a, b)) != 0) return r;
    if ((r = comparar_simples(AREA,      a, b)) != 0) return r;
    if ((r = comparar_simples(PIB,       a, b)) != 0) return r;
    if ((r = comparar_simples(DENSIDADE, a, b)) != 0) return r;
    if ((r = comparar_simples(PONTOS,    a, b)) != 0) return r;
    return 0;
}

static const char* nome_opcao(int opcao) {
    switch (opcao) {
        case POPULACAO: return "População (maior vence)";
        case AREA:      return "Área (maior vence)";
        case PIB:       return "PIB (maior vence)";
        case PONTOS:    return "Pontos Turísticos (maior vence)";
        case DENSIDADE: return "Densidade Populacional (menor vence)";
        case ANINHADA:  return "Comparação Aninhada (múltiplos atributos)";
        default:        return "Desconhecido";
    }
}

int main(void) {
    Carta a = {0}, b = {0};
    ler_carta(&a, 1);
    ler_carta(&b, 2);

    exibir_carta(&a, "Carta 1");
    exibir_carta(&b, "Carta 2");

    int opcao = 0;
    menu();
    while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 6) {
        printf("Opção inválida. Tente novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("\n>>> Critério escolhido: %s\n", nome_opcao(opcao));

    int resultado = 0;
    if (opcao == ANINHADA) {
        resultado = comparar_aninhado(&a, &b);
    } else {
        resultado = comparar_simples(opcao, &a, &b);
    }

    if (resultado == 0) {
        printf("\nResultado: EMPATE segundo o critério selecionado.\n");
    } else if (resultado > 0) {
        printf("\nResultado: Carta 1 VENCEU segundo o critério selecionado.\n");
    } else {
        printf("\nResultado: Carta 2 VENCEU segundo o critério selecionado.\n");
    }

    return 0;
}
