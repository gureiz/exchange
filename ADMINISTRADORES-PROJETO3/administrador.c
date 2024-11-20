#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_USUARIOS 50
#define MAX_CRIPTOMOEDAS 50
#define ADMIN_CPF "123456789-10"
#define ADMIN_SENHA "123456"

float cotacaoBitcoin = 50000.0;
float cotacaoEthereum = 3000.0;
float cotacaoRipple = 1.0;

typedef struct {
    char nome[50];
    char cpf[12];
    char senha[20];
    float saldoReais;
    float saldoBitcoin;
    float saldoEthereum;
    float saldoRipple;
    char historico[100][100];
    int numTransacoes;
} Usuario;


typedef struct {
    char nome[20];
    float cotacaoAtual;
    float taxaCompra;
    float taxaVenda;
} Criptomoeda;

Usuario investidores[MAX_USUARIOS];
Criptomoeda criptomoedas[MAX_CRIPTOMOEDAS];
int numInvestidores = 0;
int numCriptomoedas = 0;

//salvar usuarios no arquivo.dat
void salvarInvestidores() {
    FILE *file = fopen("usuarios.dat", "wb");
    if (file != NULL) {
        for (int i = 0; i < numInvestidores; i++) {
            fprintf(file, "%s %s %s %.2f %.6f %.6f %.6f %d\n",
                    investidores[i].nome,
                    investidores[i].cpf,
                    investidores[i].senha,
                    investidores[i].saldoReais,
                    investidores[i].saldoBitcoin,
                    investidores[i].saldoEthereum,
                    investidores[i].saldoRipple,
                    investidores[i].numTransacoes);
        }
        fclose(file);
    }
}

//ler os dados que estao salvos
void carregarInvestidores() {
    FILE *file = fopen("usuarios.dat", "rb");
    if (file != NULL) {
        while (fscanf(file, "%s %s %s %f %f %f %f %d", 
                        investidores[numInvestidores].nome, 
                        investidores[numInvestidores].cpf,
                        investidores[numInvestidores].senha,
                        &investidores[numInvestidores].saldoReais,
                        &investidores[numInvestidores].saldoBitcoin,
                        &investidores[numInvestidores].saldoEthereum,
                        &investidores[numInvestidores].saldoRipple,
                        &investidores[numInvestidores].numTransacoes) != EOF) {
            numInvestidores++;
        }
        fclose(file);
    }
}

//salva os dados das criptos em um arquivo .txt
void salvarCriptomoedas() {
    FILE *file = fopen("criptomoedas.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numCriptomoedas; i++) {
            fprintf(file, "%s %.2f %.2f %.2f\n", 
                    criptomoedas[i].nome, 
                    criptomoedas[i].cotacaoAtual, 
                    criptomoedas[i].taxaCompra, 
                    criptomoedas[i].taxaVenda);
        }
        fclose(file);
    }
}

//carrega os dados do arquivo salvo
void carregarCriptomoedas() {
    FILE *file = fopen("criptomoedas.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %f %f %f", 
                        criptomoedas[numCriptomoedas].nome, 
                        &criptomoedas[numCriptomoedas].cotacaoAtual, 
                        &criptomoedas[numCriptomoedas].taxaCompra, 
                        &criptomoedas[numCriptomoedas].taxaVenda) != EOF) {
            numCriptomoedas++;
        }
        fclose(file);
    }
}

//login do administrador
int efetuarLogin() {
    char cpf[12], senha[20];
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(cpf, ADMIN_CPF) == 0 && strcmp(senha, ADMIN_SENHA) == 0) {
        printf("Bem-vindo, administrador.\n");
        return 1;
    }

    printf("CPF ou senha incorretos.\n");
    return 0;
}

//cadastrar um novo investidor
void cadastrarInvestidor() {
    if (numInvestidores >= MAX_USUARIOS) {
        printf("Limite máximo de investidores atingido!\n");
        return;
    }

    Usuario novo;
    printf("Digite o nome do investidor: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o CPF (11 dígitos): ");
    scanf("%s", novo.cpf);
    printf("Digite a senha: ");
    scanf("%s", novo.senha);

    novo.saldoReais = 0.0;
    novo.saldoBitcoin = 0.0;
    novo.saldoEthereum = 0.0;
    novo.saldoRipple = 0.0;
    novo.numTransacoes = 0;

    investidores[numInvestidores++] = novo;
    salvarInvestidores();  // Salva os investidores no arquivo após o cadastro
    printf("Investidor cadastrado com sucesso!\n");
}

//excluir um investidor
void excluirInvestidor() {
    char cpf[12];
    printf("Digite o CPF do investidor a ser excluído: ");
    scanf("%s", cpf);

    for (int i = 0; i < numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            printf("Investidor encontrado:\n");
            printf("Nome: %s, CPF: %s\n", investidores[i].nome, investidores[i].cpf);
            printf("Confirmar exclusão? (S/N): ");
            char confirmacao;
            scanf(" %c", &confirmacao);
            if (confirmacao == 'S' || confirmacao == 's') {
                for (int j = i; j < numInvestidores - 1; j++) {
                    investidores[j] = investidores[j + 1];
                }
                numInvestidores--;
                printf("Investidor excluído com sucesso!\n");
                return;
            } else {
                printf("Operação cancelada.\n");
                return;
            }
        }
    }
    printf("Investidor não encontrado.\n");
}

//cadastrar criptomoeda
void cadastrarCriptomoeda() {
    if (numCriptomoedas >= MAX_CRIPTOMOEDAS) {
        printf("Limite máximo atingido!\n");
        return;
    }

    Criptomoeda nova;
    printf("Digite o nome da criptomoeda: ");
    scanf("%s", nova.nome);
    printf("Digite a cotação inicial: ");
    scanf("%f", &nova.cotacaoAtual);
    printf("Digite a taxa de compra (em %%): ");
    scanf("%f", &nova.taxaCompra);
    printf("Digite a taxa de venda (em %%): ");
    scanf("%f", &nova.taxaVenda);

    criptomoedas[numCriptomoedas++] = nova;
    salvarCriptomoedas();  // Salva as criptomoedas no arquivo após o cadastro
    printf("Cadastrada com sucesso!\n");
}

//excluir uma criptomoeda
void excluirCriptomoeda() {
    char nome[20];
    printf("Digite o nome da criptomoeda a ser excluída: ");
    scanf("%s", nome);

    for (int i = 0; i < numCriptomoedas; i++) {
        if (strcmp(criptomoedas[i].nome, nome) == 0) {
            printf("Criptomoeda encontrada:\n");
            printf("Nome: %s, Cotação: %.2f\n", criptomoedas[i].nome, criptomoedas[i].cotacaoAtual);
            printf("Confirmar exclusão? (S/N): ");
            char confirmacao;
            scanf(" %c", &confirmacao);
            if (confirmacao == 'S' || confirmacao == 's') {
                for (int j = i; j < numCriptomoedas - 1; j++) {
                    criptomoedas[j] = criptomoedas[j + 1];
                }
                numCriptomoedas--;
                printf("Criptomoeda excluída com sucesso!\n");
                return;
            } else {
                printf("Operação cancelada.\n");
                return;
            }
        }
    }
    printf("Criptomoeda não encontrada.\n");
}

//consultar saldo de um investidor
void consultarSaldo() {
    char cpf[12];
    printf("Digite o CPF do investidor: ");
    scanf("%s", cpf);

    for (int i = 0; i < numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            printf("Saldo do investidor (CPF: %s):\n", cpf);
            printf("Reais: %.2f\n", investidores[i].saldoReais);
            printf("Bitcoin: %.6f\n", investidores[i].saldoBitcoin);
            printf("Ethereum: %.6f\n", investidores[i].saldoEthereum);
            printf("Ripple: %.6f\n", investidores[i].saldoRipple);
            return;
        }
    }
    printf("Investidor não encontrado.\n");
}

//consultar extrato de um investidor
void consultarExtrato() {
    char cpf[12];
    printf("Digite o CPF do investidor: ");
    scanf("%s", cpf);

    for (int i = 0; i < numInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            printf("Extrato do investidor (CPF: %s):\n", cpf);
            for (int j = 0; j < investidores[i].numTransacoes; j++) {
                printf("%d: %s\n", j + 1, investidores[i].historico[j]);
            }
            return;
        }
    }
    printf("Investidor não encontrado.\n");
}

//atualizar cotações de criptomoedas
void atualizarCotas() {
  srand(time(NULL));
  cotacaoBitcoin += cotacaoBitcoin * ((rand() % 11 - 5) / 100.0);
  cotacaoEthereum += cotacaoEthereum * ((rand() % 11 - 5) / 100.0);
  cotacaoRipple += cotacaoRipple * ((rand() % 11 - 5) / 100.0);
  printf("Cotações atualizadas!\n");
}

// Menu principal do administrador
void menuAdministrador() {
    int opcao;
    do {
        printf("\n--- Menu Administrador ---\n");
        printf("1. Cadastrar novo investidor\n");
        printf("2. Excluir investidor\n");
        printf("3. Cadastrar criptomoeda\n");
        printf("4. Excluir criptomoeda\n");
        printf("5. Consultar saldo de investidor\n");
        printf("6. Consultar extrato de investidor\n");
        printf("7. Atualizar cotações de criptomoedas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarInvestidor(); break;
            case 2: excluirInvestidor(); break;
            case 3: cadastrarCriptomoeda(); break;
            case 4: excluirCriptomoeda(); break;
            case 5: consultarSaldo(); break;
            case 6: consultarExtrato(); break;
            case 7: atualizarCotas(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}


// Função principal
int main() {
    carregarInvestidores();  // Carrega os investidores do arquivo
    carregarCriptomoedas();  // Carrega as criptomoedas do arquivo

    if (efetuarLogin()) {
        menuAdministrador();
    }

    return 0;
}
