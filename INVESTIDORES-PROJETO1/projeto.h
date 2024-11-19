#ifndef PROJETO_H
#define PROJETO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100

typedef struct {
    float reais;
    float bitcoin;
    float ethereum;
    float ripple;
} Carteira;

typedef struct {
    char cpf[12];
    char senha[20];
    Carteira carteira;
    int numTransacoes;
    char historico[MAX_TRANSACOES][100];
} Usuario;

typedef enum { BITCOIN, ETHEREUM, RIPPLE } Cripto;

extern float cotacaoBitcoin;
extern float cotacaoEthereum;
extern float cotacaoRipple;

//declaração das funções que estarão em projeto.c
void salvarDados(Usuario usuarios[], int numUsuarios);
void carregarDados(Usuario usuarios[], int *numUsuarios);
int login(Usuario usuarios[], int numUsuarios, char *cpf, char *senha);
int cadastrarUsuario(Usuario usuarios[], int *numUsuarios);
void menuPrincipal(Usuario *usuario);
void consultarSaldo(Usuario *usuario);
void consultarExtrato(Usuario *usuario);
void depositarReais(Usuario *usuario);
void sacarReais(Usuario *usuario);
void comprarCripto(Usuario *usuario);
void venderCripto(Usuario *usuario);
void atualizarCotas();
void registrarOperacao(Usuario *usuario, const char *operacao);

#endif
