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