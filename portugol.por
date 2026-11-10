programa
{
    // Componente Curricular: Algoritmos e Pensamento Computacional (APC)
    // Atividade 2 Pratica - Sistema de Caixa Eletronico (ATM)
    // GRUPO 01
    // Integrantes (nome - RGM):
    //  Arthur de Jesus Salviano Oliveira - 47764988
    //  Emily Mayara Matos Moreira - 47323523
    //  Gabrielly Witai Pereira - 47396750
    //  Gustavo Rodrigues - 49237055
    //  Jaaziel Fernandes - 47889918
    //  João Gabriel Alves de Lima Neves - 48154300
    //
    // Pseudocodigo no padrao Portugol WebStudio. Descreve a mesma logica do
    // programa em C (GRUPO_01_codigo.c), passo a passo.
    //
    // SEQUENCIA LOGICA:
    //   1. Mostrar o saldo e as regras do saque
    //   2. Ler o valor do saque
    //   3. Verificar se o valor e maior que zero
    //   4. Verificar se o valor e menor ou igual ao saldo
    //   5. Calcular as notas de 100, 50, 20, 10, 5, 2 e 1 (divisao inteira e modulo)
    //   6. Atualizar o saldo e os totais da sessao
    //   7. Exibir somente as notas com quantidade maior que zero
    //   8. Perguntar se deseja fazer outro saque (aceita somente S ou N)
    //   9. Exibir o resumo da sessao (saques, total sacado, notas, saldo final)
    //
    // SOBRE O "MULTIPLO DE": existindo a nota de R$ 1, todo valor inteiro e
    // multiplo de 1, entao o calculo encadeado sempre termina com resto zero.
    // Por isso nao ha uma verificacao separada de multiplo (ela nunca falharia).
    //
    // VARIAVEIS (Passo 2):
    //   saldo         inteiro   saldo disponivel na conta (em reais)
    //   valor         inteiro   valor que o usuario deseja sacar
    //   restante      inteiro   parte do valor que ainda falta distribuir
    //   n100..n1      inteiro   quantidade de cada nota do saque atual
    //   t100..t1      inteiro   quantidade de cada nota entregue na sessao
    //   qtd_saques    inteiro   saques realizados com sucesso
    //   total_sacado  inteiro   soma dos valores sacados
    //   resposta      caracter  resposta S/N para repetir o saque
    //   continuar     logico    controla a repeticao do programa
    //   respondeu     logico    controla a validacao da resposta S/N
    //
    // NOTA SOBRE A ENTRADA: o leia(valor) do Portugol ja recusa texto quando a
    // variavel e inteira. No C essa protecao e feita com fgets + strtol, e a
    // mensagem "Entrada invalida" aparece na tela. A logica dos dois e igual.

    funcao inicio()
    {
        // Declaracao de variaveis
        inteiro saldo = 1000
        inteiro valor
        inteiro restante
        inteiro n100, n50, n20, n10, n5, n2, n1
        inteiro t100 = 0, t50 = 0, t20 = 0, t10 = 0, t5 = 0, t2 = 0, t1 = 0
        inteiro qtd_saques = 0
        inteiro total_sacado = 0
        caracter resposta
        logico continuar = verdadeiro
        logico respondeu

        // Tela inicial
        escreva("+----------------------------------------------+\n")
        escreva("|            CAIXA ELETRONICO (ATM)            |\n")
        escreva("+----------------------------------------------+\n")
        escreva("| Saldo disponivel: R$ ", saldo, "\n")
        escreva("| Notas: R$ 100, 50, 20, 10, 5, 2 e 1\n")
        escreva("| Saque de qualquer valor inteiro positivo\n")
        escreva("+----------------------------------------------+\n")

        enquanto (continuar)
        {
            // 1. Leitura do valor do saque
            escreva("\n  Digite o valor do saque: R$ ")
            leia(valor)

            // 2. Validacoes: maior que zero e saldo suficiente
            se (valor <= 0)
            {
                escreva("\nERRO: valor invalido. O saque deve ser maior que R$ 0.\n")
            }
            senao se (valor > saldo)
            {
                escreva("\nERRO: saldo insuficiente. Saque: R$ ", valor, " | Saldo: R$ ", saldo, "\n")
            }
            senao
            {
                // 3. Calculo encadeado com divisao inteira (/) e modulo (%)
                restante = valor

                n100 = restante / 100
                restante = restante % 100
                n50 = restante / 50
                restante = restante % 50
                n20 = restante / 20
                restante = restante % 20
                n10 = restante / 10
                restante = restante % 10
                n5 = restante / 5
                restante = restante % 5
                n2 = restante / 2
                restante = restante % 2
                n1 = restante / 1
                restante = restante % 1

                // 4. Atualizacao do saldo e dos totais da sessao
                saldo = saldo - valor
                qtd_saques = qtd_saques + 1
                total_sacado = total_sacado + valor
                t100 = t100 + n100
                t50 = t50 + n50
                t20 = t20 + n20
                t10 = t10 + n10
                t5 = t5 + n5
                t2 = t2 + n2
                t1 = t1 + n1

                // 5. Exibicao apenas das notas com quantidade maior que zero
                escreva("\n+----------------------------------------------+\n")
                escreva("|               SAQUE REALIZADO                |\n")
                escreva("+----------------------------------------------+\n")
                escreva("| Valor sacado: R$ ", valor, "\n")
                escreva("| Notas entregues:\n")
                se (n100 > 0)
                {
                    escreva("|   ", n100, " nota(s) de R$ 100\n")
                }
                se (n50 > 0)
                {
                    escreva("|   ", n50, " nota(s) de R$ 50\n")
                }
                se (n20 > 0)
                {
                    escreva("|   ", n20, " nota(s) de R$ 20\n")
                }
                se (n10 > 0)
                {
                    escreva("|   ", n10, " nota(s) de R$ 10\n")
                }
                se (n5 > 0)
                {
                    escreva("|   ", n5, " nota(s) de R$ 5\n")
                }
                se (n2 > 0)
                {
                    escreva("|   ", n2, " nota(s) de R$ 2\n")
                }
                se (n1 > 0)
                {
                    escreva("|   ", n1, " nota(s) de R$ 1\n")
                }
                escreva("| Novo saldo: R$ ", saldo, "\n")
                escreva("+----------------------------------------------+\n")
            }

            // 6. Repeticao: encerra se o saldo acabou ou se o usuario responder N
            se (saldo == 0)
            {
                escreva("\n  Saldo zerado. Nao ha mais valores para sacar.\n")
                continuar = falso
            }
            senao
            {
                respondeu = falso
                enquanto (nao respondeu)
                {
                    escreva("\n  Deseja realizar outro saque? (S/N): ")
                    leia(resposta)
                    se (resposta == 'S' ou resposta == 's')
                    {
                        respondeu = verdadeiro
                    }
                    senao se (resposta == 'N' ou resposta == 'n')
                    {
                        respondeu = verdadeiro
                        continuar = falso
                    }
                    senao
                    {
                        escreva("  Opcao invalida. Digite S para sim ou N para nao.\n")
                    }
                }
            }
        }

        // Encerramento com resumo da sessao
        escreva("\n+----------------------------------------------+\n")
        escreva("|            OBRIGADO POR USAR O ATM           |\n")
        escreva("+----------------------------------------------+\n")
        escreva("| Saques realizados: ", qtd_saques, "\n")
        escreva("| Total sacado: R$ ", total_sacado, "\n")
        se (qtd_saques > 0)
        {
            escreva("| Notas entregues na sessao:\n")
            se (t100 > 0)
            {
                escreva("|   ", t100, " nota(s) de R$ 100\n")
            }
            se (t50 > 0)
            {
                escreva("|   ", t50, " nota(s) de R$ 50\n")
            }
            se (t20 > 0)
            {
                escreva("|   ", t20, " nota(s) de R$ 20\n")
            }
            se (t10 > 0)
            {
                escreva("|   ", t10, " nota(s) de R$ 10\n")
            }
            se (t5 > 0)
            {
                escreva("|   ", t5, " nota(s) de R$ 5\n")
            }
            se (t2 > 0)
            {
                escreva("|   ", t2, " nota(s) de R$ 2\n")
            }
            se (t1 > 0)
            {
                escreva("|   ", t1, " nota(s) de R$ 1\n")
            }
        }
        escreva("| Saldo final: R$ ", saldo, "\n")
        escreva("+----------------------------------------------+\n")
    }
}
