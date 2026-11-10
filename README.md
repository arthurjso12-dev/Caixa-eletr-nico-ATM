🏧 Sistema de Caixa Eletrônico (ATM)

Programa em C que simula um caixa eletrônico: o usuário informa o valor de um saque e o sistema valida o pedido, calcula a menor quantidade de cédulas necessárias e atualiza o saldo da conta.

Projeto desenvolvido para o componente curricular Algoritmos e Pensamento Computacional (APC) — Atividade 2 Prática.

✨ Funcionalidades
Solicita o valor do saque e valida a entrada (somente inteiros).
Verifica se o valor é maior que zero.
Verifica se o valor é menor ou igual ao saldo disponível.
Calcula a distribuição de cédulas de R$ 100, 50, 20, 10, 5, 2 e 1 usando divisão inteira (/) e módulo (%) encadeados.
Exibe apenas as cédulas com quantidade maior que zero.
Mostra mensagens de erro apropriadas dentro de caixas na tela.
Permite vários saques seguidos (pergunta S/N ao final de cada um).
Exibe um resumo da sessão: saques realizados, total sacado, cédulas entregues e saldo final.
Encerra automaticamente quando o saldo chega a zero.

Sobre "múltiplo de": como existe a cédula de R$ 1, todo valor inteiro positivo pode ser entregue por completo. Por isso não há erro de "valor não múltiplo".

🚀 Como executar
Requisitos
Compilador gcc (ou qualquer compilador C99)
Compilar
bash
gcc -Wall -Wextra -pedantic -std=c99 -o atm GRUPO_01_codigo.c
Executar
bash
./atm        # Linux / macOS
atm.exe      # Windows

O saldo inicial é de R$ 1000, definido pela constante SALDO_INICIAL.

🖥️ Exemplo de execução

Saque de R$ 95:

+----------------------------------------------+
|            CAIXA ELETRONICO (ATM)            |
+----------------------------------------------+
| Saldo disponivel: R$ 1000                    |
| Notas: R$ 100, 50, 20, 10, 5, 2 e 1          |
| Saque de qualquer valor inteiro positivo     |
+----------------------------------------------+

  Digite o valor do saque: R$ 95

+----------------------------------------------+
|               SAQUE REALIZADO                |
+----------------------------------------------+
| Valor sacado: R$ 95                          |
| Notas entregues:                             |
|   1 nota(s) de R$ 50                         |
|   2 nota(s) de R$ 20                         |
|   1 nota(s) de R$ 5                          |
| Novo saldo: R$ 905                           |
+----------------------------------------------+

  Deseja realizar outro saque? (S/N):

Saque acima do saldo (R$ 1005):

+----------------------------------------------+
|                     ERRO                     |
+----------------------------------------------+
| Saldo insuficiente.                          |
| Saque: R$ 1005 | Saldo: R$ 1000              |
+----------------------------------------------+
🧮 Como o cálculo funciona

O valor é distribuído da maior para a menor cédula. A divisão inteira diz quantas cédulas cabem; o módulo guarda o que sobrou para a próxima.

Exemplo com R$ 95:

Cédula	Divisão	Resto
100	95 / 100 = 0	95
50	95 / 50 = 1	45
20	45 / 20 = 2	5
10	5 / 10 = 0	5
5	5 / 5 = 1	0
2	0	0
1	0	0

Resultado: 1×50 + 2×20 + 1×5 = R$ 95.

📁 Estrutura do projeto
.
├── GRUPO_01_codigo.c      # Programa em C
├── GRUPO_01_portugol.por  # Pseudocódigo (Portugol WebStudio)
├── Documentacao_Testes.pdf # Documentação de testes
└── README.md
Organização do código C
Função	Responsabilidade
borda, titulo, linha	Desenham as caixas da interface
exibir_cabecalho	Tela inicial com saldo e regras
exibir_erro	Caixa de erro com causa e dica
exibir_notas	Lista só as cédulas com quantidade > 0
ler_inteiro	Leitura segura com fgets + strtol
perguntar_continuar	Valida a resposta S/N
calcular_notas	Regra de negócio com / e % encadeados
main	Fluxo principal e resumo da sessão
🛡️ Robustez da entrada

A leitura com fgets + strtol evita travamentos e aceitações indevidas. O programa trata corretamente:

Entrada	Resultado
abc, 12abc, 12.5, linha vazia	Erro: entrada inválida
0, -10	Erro: valor deve ser maior que R$ 0
99999999999999999999	Erro: valor muito grande
 100  (com espaços)	Aceito normalmente
Ctrl+D (fim da entrada)	Encerra sem travar
Resposta x ou sim em S/N	Rejeitada; a pergunta se repete
✅ Testes

Foram executados 20 cenários reais em pseudo-terminal (Ubuntu 24.04, gcc 13.3), todos aprovados:

T1–T4: testes exigidos pela proposta (R$ 50, 95, 123 e 1005);
T5–T10: testes complementares (exemplo de R$ 285, zero, negativo, texto, saque total e vários saques);
T11–T20: testes de robustez da entrada e casos limite.

Além disso:

Verificação exaustiva dos 1000 valores de R$ 1 a R$ 1000: resto zero, soma correta e menor número possível de cédulas — 0 falhas.
Compilação com -Wall -Wextra -pedantic: 0 avisos, 0 erros.
Mesmos testes com -fsanitize=address,undefined: nenhum erro reportado.

Os detalhes completos estão na documentação de testes (PDF).

📝 Pseudocódigo (Portugol)

O arquivo GRUPO_01_portugol.por descreve a mesma lógica em Portugol, em 9 passos:

Mostrar o saldo e as regras
Ler o valor do saque
Verificar se é maior que zero
Verificar se é menor ou igual ao saldo
Calcular as cédulas (divisão inteira e módulo)
Atualizar o saldo e os totais da sessão
Exibir somente cédulas com quantidade > 0
Perguntar se deseja outro saque (S/N)
Exibir o resumo da sessão

No Portugol, leia(inteiro) já recusa texto; no C essa proteção é feita manualmente com fgets + strtol.

👥 Integrantes — Grupo 01
Nome	RGM
Arthur de Jesus Salviano Oliveira	47764988
Emily Mayara Matos Moreira	47323523
Gabrielly Witai Pereira	47396750
Gustavo Rodrigues	49237055
Jaaziel Fernandes	47889918
João Gabriel Alves de Lima Neves	48154300
📄 Licença

Projeto acadêmico desenvolvido para fins educacionais.
