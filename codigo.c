/*
 * Componente Curricular: Algoritmos e Pensamento Computacional (APC)
 * Atividade 2 Pratica: Sistema de Caixa Eletronico (ATM)
 *
 * GRUPO 01
 * Integrantes (nome - RGM):
 *  Arthur de Jesus Salviano Oliveira - 47764988
 *  Emily Mayara Matos Moreira - 47323523
 *  Gabrielly Witai Pereira - 47396750
 *  Gustavo Rodrigues - 49237055
 *  Jaaziel Fernandes - 47889918
 *  João Gabriel Alves de Lima Neves - 48154300
 *
 * O programa solicita o valor de um saque e:
 *   1) verifica se o valor e maior que zero;
 *   2) verifica se o valor e menor ou igual ao saldo disponivel;
 *   3) calcula a distribuicao de notas/moedas de 100, 50, 20, 10, 5, 2 e 1
 *      usando divisao inteira (/) e modulo (%) de forma encadeada;
 *   4) exibe apenas as notas com quantidade maior que zero;
 *   5) caso contrario, exibe uma mensagem de erro apropriada;
 *   6) ao final, exibe um resumo da sessao (saques, total e notas).
 *
 * Sobre o "multiplo de": como existe a cedula de R$ 1, qualquer valor inteiro
 * e multiplo de 1 e pode ser entregue por completo. Por isso nao ha erro de
 * "valor nao multiplo": valores inteiros positivos sempre fecham sem resto.
 * Entradas com virgula/ponto (ex.: 12.5) sao rejeitadas como invalidas.
 *
 * Variaveis principais (Passo 2):
 *   saldo    (int) - saldo disponivel na conta, em reais
 *   valor    (int) - valor que o usuario deseja sacar
 *   restante (int) - parte do valor que ainda falta distribuir em notas
 *   n100, n50, n20, n10, n5, n2, n1 (int) - quantidade de cada nota
 *                                   (agrupadas na struct Notas)
 *   qtd_saques, total_sacado (int) - estatisticas da sessao
 *
 * Observacao: as mensagens de tela nao usam acentos para que o texto
 * apareca corretamente em qualquer terminal (Windows, Linux ou macOS).
 *
 * Compilacao: gcc -Wall -Wextra -pedantic -std=c99 -o atm GRUPO_01_codigo.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

/* ---------- Constantes do sistema ---------- */
#define SALDO_INICIAL 1000   /* saldo da conta no inicio do programa      */
#define LARGURA 46           /* largura interna das caixas da interface   */

/* Resultados possiveis da leitura de um numero inteiro */
enum { LEITURA_OK, LEITURA_INVALIDA, LEITURA_FORA_DA_FAIXA, LEITURA_EOF };

/* Quantidade de cada nota (Passo 2: contadores de notas) */
typedef struct {
    int n100, n50, n20, n10, n5, n2, n1;
} Notas;

/* ================================================================
 *  INTERFACE: funcoes que desenham as caixas na tela
 * ================================================================ */

/* Desenha uma linha de borda: +----------------+ */
static void borda(void) {
    int i;
    putchar('+');
    for (i = 0; i < LARGURA; i++) {
        putchar('-');
    }
    printf("+\n");
}

/* Escreve um texto centralizado dentro da caixa */
static void titulo(const char *texto) {
    int tamanho = (int)strlen(texto);
    int esquerda = (LARGURA - tamanho) / 2;
    int direita = LARGURA - tamanho - esquerda;
    printf("|%*s%s%*s|\n", esquerda, "", texto, direita, "");
}

/* Escreve uma linha de texto formatada (estilo printf) dentro da caixa */
static void linha(const char *formato, ...) {
    char texto[128];
    va_list args;

    va_start(args, formato);
    vsnprintf(texto, sizeof(texto), formato, args);
    va_end(args);

    printf("| %-*s |\n", LARGURA - 2, texto);
}

/* Tela inicial com o saldo e as regras de saque */
static void exibir_cabecalho(int saldo) {
    borda();
    titulo("CAIXA ELETRONICO (ATM)");
    borda();
    linha("Saldo disponivel: R$ %d", saldo);
    linha("Notas: R$ 100, 50, 20, 10, 5, 2 e 1");
    linha("Saque de qualquer valor inteiro positivo");
    borda();
}

/* Caixa de erro com duas linhas de explicacao */
static void exibir_erro(const char *causa, const char *dica) {
    printf("\n");
    borda();
    titulo("ERRO");
    borda();
    linha("%s", causa);
    linha("%s", dica);
    borda();
}

/* Exibe somente as notas com quantidade maior que zero */
static void exibir_notas(const Notas *n) {
    if (n->n100 > 0) linha("  %d nota(s) de R$ 100", n->n100);
    if (n->n50  > 0) linha("  %d nota(s) de R$ 50",  n->n50);
    if (n->n20  > 0) linha("  %d nota(s) de R$ 20",  n->n20);
    if (n->n10  > 0) linha("  %d nota(s) de R$ 10",  n->n10);
    if (n->n5   > 0) linha("  %d nota(s) de R$ 5",   n->n5);
    if (n->n2   > 0) linha("  %d nota(s) de R$ 2",   n->n2);
    if (n->n1   > 0) linha("  %d nota(s) de R$ 1",   n->n1);
}

/* ================================================================
 *  ENTRADA DE DADOS
 * ================================================================ */

/*
 * Le uma linha do teclado e converte para inteiro.
 * Usar fgets + strtol evita que textos como "12abc" ou "abc"
 * travem o programa ou sejam aceitos como numeros validos.
 */
static int ler_inteiro(int *destino) {
    char entrada[64];
    char *fim;
    long numero;
    int c;

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return LEITURA_EOF;
    }

    /* Linha maior que o buffer: descarta o restante e rejeita */
    if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
        while ((c = getchar()) != '\n' && c != EOF) { }
        return LEITURA_INVALIDA;
    }

    errno = 0;
    numero = strtol(entrada, &fim, 10);

    if (fim == entrada) {                 /* nenhum digito encontrado */
        return LEITURA_INVALIDA;
    }
    while (isspace((unsigned char)*fim)) { /* ignora espacos finais   */
        fim++;
    }
    if (*fim != '\0') {                   /* sobrou texto (ex.: 12abc) */
        return LEITURA_INVALIDA;
    }
    if (errno == ERANGE || numero > INT_MAX || numero < INT_MIN) {
        return LEITURA_FORA_DA_FAIXA;
    }

    *destino = (int)numero;
    return LEITURA_OK;
}

/*
 * Pergunta se o usuario quer fazer outro saque.
 * Aceita apenas S/s ou N/n (uma resposta como "sim" ou "x" e rejeitada).
 * Retorna 1 (sim) ou 0 (nao). Fim da entrada (EOF) conta como "nao".
 */
static int perguntar_continuar(void) {
    char resposta[32];
    char *p;
    char letra;

    for (;;) {
        printf("\n  Deseja realizar outro saque? (S/N): ");
        if (fgets(resposta, sizeof(resposta), stdin) == NULL) {
            return 0;
        }
        p = resposta;
        while (isspace((unsigned char)*p)) {
            p++;
        }
        letra = *p;
        p++;
        while (isspace((unsigned char)*p)) {   /* so pode sobrar espaco */
            p++;
        }
        if (*p == '\0' && (letra == 's' || letra == 'S')) {
            return 1;
        }
        if (*p == '\0' && (letra == 'n' || letra == 'N')) {
            return 0;
        }
        printf("  Opcao invalida. Digite S para sim ou N para nao.\n");
    }
}

/* ================================================================
 *  REGRA DE NEGOCIO: calculo das notas
 * ================================================================ */

/*
 * Divisao inteira (/) informa quantas notas cabem no valor;
 * o modulo (%) guarda o que sobrou para a proxima nota.
 * Como existe a nota de R$ 1, o resto final sempre sera zero.
 * Retorna o resto final (0 = valor distribuido por completo).
 */
static int calcular_notas(int valor, Notas *n) {
    int restante = valor;

    n->n100 = restante / 100;  restante = restante % 100;
    n->n50  = restante / 50;   restante = restante % 50;
    n->n20  = restante / 20;   restante = restante % 20;
    n->n10  = restante / 10;   restante = restante % 10;
    n->n5   = restante / 5;    restante = restante % 5;
    n->n2   = restante / 2;    restante = restante % 2;
    n->n1   = restante / 1;    restante = restante % 1;

    return restante;
}

/* ================================================================
 *  PROGRAMA PRINCIPAL
 * ================================================================ */
int main(void) {
    int saldo = SALDO_INICIAL;  /* saldo disponivel (em reais)        */
    int valor = 0;              /* valor que o usuario quer sacar     */
    int status;                 /* resultado da leitura do teclado    */
    char detalhe[64];           /* texto auxiliar das mensagens       */
    Notas notas;                /* notas do saque atual               */
    Notas total = {0, 0, 0, 0, 0, 0, 0}; /* notas entregues na sessao */
    int qtd_saques = 0;         /* saques realizados com sucesso      */
    int total_sacado = 0;       /* soma dos valores sacados           */

    exibir_cabecalho(saldo);

    for (;;) {
        /* ---------- 1. Solicita o valor do saque ---------- */
        printf("\n  Digite o valor do saque: R$ ");
        status = ler_inteiro(&valor);

        if (status == LEITURA_EOF) {          /* entrada encerrada */
            printf("\n");
            break;
        }

        /* ---------- 2. Validacoes (na ordem do pseudocodigo) ---------- */
        if (status == LEITURA_INVALIDA) {
            exibir_erro("Entrada invalida.",
                        "Digite apenas numeros inteiros.");
        } else if (status == LEITURA_FORA_DA_FAIXA) {
            exibir_erro("Valor muito grande.",
                        "Digite um valor dentro do limite do saldo.");
        } else if (valor <= 0) {
            exibir_erro("Valor invalido.",
                        "O saque deve ser maior que R$ 0.");
        } else if (valor > saldo) {
            snprintf(detalhe, sizeof(detalhe),
                     "Saque: R$ %d | Saldo: R$ %d", valor, saldo);
            exibir_erro("Saldo insuficiente.", detalhe);
        } else {
            /* ---------- 3. Calcula as notas ---------- */
            if (calcular_notas(valor, &notas) != 0) {
                /* Nunca deve ocorrer: com a nota de R$ 1 nao sobra resto */
                exibir_erro("Falha interna no calculo.",
                            "Saque cancelado. Saldo mantido.");
            } else {
                /* ---------- 4. Atualiza saldo e exibe o resultado ---------- */
                saldo = saldo - valor;
                qtd_saques++;
                total_sacado += valor;
                total.n100 += notas.n100;
                total.n50  += notas.n50;
                total.n20  += notas.n20;
                total.n10  += notas.n10;
                total.n5   += notas.n5;
                total.n2   += notas.n2;
                total.n1   += notas.n1;

                printf("\n");
                borda();
                titulo("SAQUE REALIZADO");
                borda();
                linha("Valor sacado: R$ %d", valor);
                linha("Notas entregues:");
                exibir_notas(&notas);
                linha("Novo saldo: R$ %d", saldo);
                borda();
            }
        }

        /* Sem saldo, nao ha mais o que sacar */
        if (saldo == 0) {
            printf("\n  Saldo zerado. Nao ha mais valores para sacar.\n");
            break;
        }

        if (!perguntar_continuar()) {
            break;
        }
    }

    /* ---------- Encerramento com resumo da sessao ---------- */
    printf("\n");
    borda();
    titulo("OBRIGADO POR USAR O ATM");
    borda();
    linha("Saques realizados: %d", qtd_saques);
    linha("Total sacado: R$ %d", total_sacado);
    if (qtd_saques > 0) {
        linha("Notas entregues na sessao:");
        exibir_notas(&total);
    }
    linha("Saldo final: R$ %d", saldo);
    borda();

    return 0;
}
