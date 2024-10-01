#include "projeto.h"

// a função de login
int login(Usuario usuarios[], int numUsuarios, char *cpf, char *senha) {
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      return i;
    }
  }
  return -1;
}

// funcao cadastro de novo usuario
int cadastrarUsuario(Usuario usuarios[], int *numUsuarios) {
  if (*numUsuarios >= MAX_USUARIOS) {
    printf("Limite máximo de usuários atingido!\n");
    return 0;
  }

  printf("Digite o CPF (11 dígitos): ");
  scanf("%s", usuarios[*numUsuarios].cpf);
  printf("Digite a senha: ");
  scanf("%s", usuarios[*numUsuarios].senha);

  // iniciar a carteira do usuário
  usuarios[*numUsuarios].carteira.reais = 0.0;
  usuarios[*numUsuarios].carteira.bitcoin = 0.0;
  usuarios[*numUsuarios].carteira.ethereum = 0.0;
  usuarios[*numUsuarios].carteira.ripple = 0.0;
  usuarios[*numUsuarios].numTransacoes = 0;

  (*numUsuarios)++;
  return 1;
}

// funcao de salvar os dados em arquivo tipo binario
void salvarDados(Usuario usuarios[], int numUsuarios) {
  FILE *arquivo = fopen("usuarios.dat", "wb");
  if (arquivo == NULL) {
    printf("Erro ao salvar dados!\n");
    return;
  }
  fwrite(&numUsuarios, sizeof(int), 1, arquivo);
  fwrite(usuarios, sizeof(Usuario), numUsuarios, arquivo);
  fclose(arquivo);
}

// funcao de carregar os dados em arquivo tipo binario
void carregarDados(Usuario usuarios[], int *numUsuarios) {
  FILE *arquivo = fopen("usuarios.dat", "rb");
  if (arquivo == NULL) {
    printf("Nenhum dado existente encontrado.\n");
    return;
  }
  fread(numUsuarios, sizeof(int), 1, arquivo);
  fread(usuarios, sizeof(Usuario), *numUsuarios, arquivo);
  fclose(arquivo);
}

//funcao para exibir o menu apos o usuario realizar o login
void menuPrincipal(Usuario *usuario) {
  int opcao;

  do {
    printf("\n--- Menu Principal ---\n");
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar reais\n");
    printf("4. Sacar reais\n");
    printf("5. Comprar criptomoedas\n");
    printf("6. Vender criptomoedas\n");
    printf("7. Atualizar cotações\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      consultarSaldo(usuario);
      break;
    case 2:
      consultarExtrato(usuario);
      break;
    case 3:
      depositarReais(usuario);
      break;
    case 4:
      sacarReais(usuario);
      break;
    case 5:
      comprarCripto(usuario);
      break;
    case 6:
      venderCripto(usuario);
      break;
    case 7:
      atualizarCotas();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida!\n");
    }
  } while (opcao != 0);
}

//saldo
void consultarSaldo(Usuario *usuario) {
  printf("\n--- Saldo ---\n");
  printf("Reais: %.2f\n", usuario->carteira.reais);
  printf("Bitcoin: %.6f (R$ %.2f)\n", usuario->carteira.bitcoin,
         usuario->carteira.bitcoin * cotacaoBitcoin);
  printf("Ethereum: %.6f (R$ %.2f)\n", usuario->carteira.ethereum,
         usuario->carteira.ethereum * cotacaoEthereum);
  printf("Ripple: %.6f (R$ %.2f)\n", usuario->carteira.ripple,
         usuario->carteira.ripple * cotacaoRipple);
}

//consultar extrato
void consultarExtrato(Usuario *usuario) {
  printf("\n--- Extrato ---\n");
  if (usuario->numTransacoes == 0) {
    printf("Nenhuma transacao realizada.\n");
  } else {
    for (int i = 0; i < usuario->numTransacoes; i++) {
      printf("%s\n", usuario->historico[i]);
    }
  }
}

//operações realizadas 
void registrarOperacao(Usuario *usuario, const char *operacao) {
  if (usuario->numTransacoes < MAX_TRANSACOES) {
    snprintf(usuario->historico[usuario->numTransacoes], 100, "%s", operacao);
    usuario->numTransacoes++;
  } else {
    printf("Limite de transacoes atingido!\n");
  }
}

//depositar
void depositarReais(Usuario *usuario) {
  float valor;
  printf("Digite o valor do deposito: R$ ");
  scanf("%f", &valor);
  usuario->carteira.reais += valor;
  printf("Deposito realizado com sucesso!\n");

  // Registrar no histórico
  char operacao[100];
  snprintf(operacao, 100, "Deposito de R$ %.2f", valor);
  registrarOperacao(usuario, operacao);
}
