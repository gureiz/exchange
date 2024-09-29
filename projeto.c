#include "projeto.h"
#include <stdio.h>



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

//base das funcoes
void salvarDados(Usuario usuarios[], int numUsuarios);
void carregarDados(Usuario usuarios[], int *numUsuarios);
int login(Usuario usuarios[], int numUsuarios, char *cpf, char *senha);
int cadastrarUsuario(Usuario usuarios[], int *numUsuarios);
void menuPrincipal(Usuario *usuario){
    printf("Menu\n");
    return 0;
}
void consultarSaldo(Usuario *usuario);
void consultarExtrato(Usuario *usuario);
void depositarReais(Usuario *usuario);
void sacarReais(Usuario *usuario);
void comprarCripto(Usuario *usuario);
void venderCripto(Usuario *usuario);
void atualizarCotas();
void registrarOperacao(Usuario *usuario, const char *operacao);

