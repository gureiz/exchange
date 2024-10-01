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