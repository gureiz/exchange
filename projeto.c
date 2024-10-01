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

  //registrar na funcao de registrar operacao
  char operacao[100];
  snprintf(operacao, 100, "Deposito de R$ %.2f", valor);
  registrarOperacao(usuario, operacao);
}

//sacar
void sacarReais(Usuario *usuario) {
  float valor;
  char senha[20];
  printf("Digite o valor do saque: R$ ");
  scanf("%f", &valor);

  printf("Confirme sua senha: ");
  scanf("%s", senha);

  if (strcmp(senha, usuario->senha) == 0) {
    if (usuario->carteira.reais >= valor) {
      usuario->carteira.reais -= valor;
      printf("Saque realizado com sucesso!\n");

      //registrar
      char operacao[100];
      snprintf(operacao, 100, "Saque de R$ %.2f", valor);
      registrarOperacao(usuario, operacao);
    } else {
      printf("Saldo insuficiente!\n");
    }
  } else {
    printf("Senha incorreta!\n");
  }
}

//comprar criptomoedas
void comprarCripto(Usuario *usuario) {
  int opcao;
  float valor, taxa;
  char confirmacao;
  char senha[20];

  printf("\nEscolha a criptomoeda para comprar:\n");
  printf("1. Bitcoin\n2. Ethereum\n3. Ripple\n");
  scanf("%d", &opcao);

  printf("Digite o valor da compra: R$ ");
  scanf("%f", &valor);

  //pede para o usuario colocar a senha
  printf("Digite sua senha: ");
  scanf("%s", senha);

  //verifica a se a senha do usuario condiz com a do cadastro
  if (strcmp(senha, usuario->senha) != 0) {
    printf("Senha incorreta!\n");
    return;
  }

  switch (opcao) {
  case 1: 
    taxa = valor * 0.02;
    if (usuario->carteira.reais >= (valor + taxa)) {
      printf("Comprar %.6f BTC por R$ %.2f (taxa: R$ %.2f)? (S/N) ",
             valor / cotacaoBitcoin, valor, taxa);
      scanf(" %c", &confirmacao);
      if (confirmacao == 'S' || confirmacao == 's') {
        usuario->carteira.reais -= (valor + taxa);
        usuario->carteira.bitcoin += valor / cotacaoBitcoin;
        printf("Compra realizada com sucesso!\n");

        //salvar o bitcoin
        char operacao[100];
        snprintf(operacao, 100, "Compra de %.6f BTC por R$ %.2f",
                 valor / cotacaoBitcoin, valor);
        registrarOperacao(usuario, operacao);
      }
    } else {
      printf("Saldo insuficiente!\n");
    }
    break;
  case 2: 
    taxa = valor * 0.01;
    if (usuario->carteira.reais >= (valor + taxa)) {
      printf("Comprar %.6f ETH por R$ %.2f (taxa: R$ %.2f)? (S/N) ",
             valor / cotacaoEthereum, valor, taxa);
      scanf(" %c", &confirmacao);
      if (confirmacao == 'S' || confirmacao == 's') {
        usuario->carteira.reais -= (valor + taxa);
        usuario->carteira.ethereum += valor / cotacaoEthereum;
        printf("Compra realizada com sucesso!\n");

        // salvar o ethereum
        char operacao[100];
        snprintf(operacao, 100, "Compra de %.6f ETH por R$ %.2f",
                 valor / cotacaoEthereum, valor);
        registrarOperacao(usuario, operacao);
      }
    } else {
      printf("Saldo insuficiente!\n");
    }
    break;
  case 3:
    taxa = valor * 0.01;
    if (usuario->carteira.reais >= (valor + taxa)) {
      printf("Comprar %.6f XRP por R$ %.2f (taxa: R$ %.2f)? (S/N) ",
             valor / cotacaoRipple, valor, taxa);
      scanf(" %c", &confirmacao);
      if (confirmacao == 'S' || confirmacao == 's') {
        usuario->carteira.reais -= (valor + taxa);
        usuario->carteira.ripple += valor / cotacaoRipple;
        printf("Compra realizada com sucesso!\n");

        //salvar o ripple
        char operacao[100];
        snprintf(operacao, 100, "Compra de %.6f XRP por R$ %.2f",
                 valor / cotacaoRipple, valor);
        registrarOperacao(usuario, operacao);
      }
    } else {
      printf("Saldo insuficiente!\n");
    }
    break;
  default:
    printf("Opcao invalida!\n");
  }
}

//vender criptomoedas
void venderCripto(Usuario *usuario) {
  int opcao;
  float valor, taxa;
  char confirmacao;

  printf("\nEscolha a criptomoeda para vender:\n");
  printf("1. Bitcoin\n2. Ethereum\n3. Ripple\n");
  scanf("%d", &opcao);

  switch (opcao) {
  case 1:
    printf("Digite a quantidade de BTC: ");
    scanf("%f", &valor);
    taxa = valor * cotacaoBitcoin * 0.03;
    if (usuario->carteira.bitcoin >= valor) {
      printf("Vender %.6f BTC por R$ %.2f (taxa: R$ %.2f)? (S/N) ", valor,
             valor * cotacaoBitcoin, taxa);
      scanf(" %c", &confirmacao);
      if (confirmacao == 'S' || confirmacao == 's') {
        usuario->carteira.bitcoin -= valor;
        usuario->carteira.reais += (valor * cotacaoBitcoin) - taxa;
        printf("Venda realizada com sucesso!\n");

        //salvar no historico (bitcoin)
        char operacao[100];
        snprintf(operacao, 100, "Venda de %.6f BTC por R$ %.2f", valor,
                 valor * cotacaoBitcoin);
        registrarOperacao(usuario, operacao);
      }
    } else {
      printf("Quantidade de Bitcoin insuficiente!\n");
    }
    break;
  case 2:
    printf("Digite a quantidade de ETH: ");
    scanf("%f", &valor);
    taxa = valor * cotacaoEthereum * 0.02;
    if (usuario->carteira.ethereum >= valor) {
      printf("Vender %.6f ETH por R$ %.2f (taxa: R$ %.2f)? (S/N) ", valor,
             valor * cotacaoEthereum, taxa);
      scanf(" %c", &confirmacao);
      if (confirmacao == 'S' || confirmacao == 's') {
        usuario->carteira.ethereum -= valor;
        usuario->carteira.reais += (valor * cotacaoEthereum) - taxa;
        printf("Venda realizada com sucesso!\n");

        //salvar no historico (ethereum)
        char operacao[100];
        snprintf(operacao, 100, "Venda de %.6f ETH por R$ %.2f", valor,
                 valor * cotacaoEthereum);
        registrarOperacao(usuario, operacao);
      }
    } else {
      printf("Quantidade de Ethereum insuficiente!\n");
    }
    break;
  case 3: 
    printf("Digite a quantidade de XRP: ");
    scanf("%f", &valor);
    taxa = valor * cotacaoRipple * 0.01;
    if (usuario->carteira.ripple >= valor) {
      printf("Vender %.6f XRP por R$ %.2f (taxa: R$ %.2f)? (S/N) ", valor,
             valor * cotacaoRipple, taxa);
      scanf(" %c", &confirmacao);
      if (confirmacao == 'S' || confirmacao == 's') {
        usuario->carteira.ripple -= valor;
        usuario->carteira.reais += (valor * cotacaoRipple) - taxa;
        printf("Venda realizada com sucesso!\n");

        //salvar no histotico
        char operacao[100];
        snprintf(operacao, 100, "Venda de %.6f XRP por R$ %.2f", valor,
                 valor * cotacaoRipple);
        registrarOperacao(usuario, operacao);
      }
    } else {
      printf("Quantidade de Ripple insuficiente!\n");
    }
    break;
  default:
    printf("Opcao invalida!\n");
  }
}

//atualizar cotações cripto
void atualizarCotas() {
  srand(time(NULL));
  cotacaoBitcoin += cotacaoBitcoin * ((rand() % 11 - 5) / 100.0);
  cotacaoEthereum += cotacaoEthereum * ((rand() % 11 - 5) / 100.0);
  cotacaoRipple += cotacaoRipple * ((rand() % 11 - 5) / 100.0);
  printf("Cotações atualizadas!\n");
}