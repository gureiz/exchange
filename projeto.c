#include "projeto.h"

// Função de login
int login(Usuario usuarios[], int numUsuarios, char *cpf, char *senha) {
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      return i;
    }
  }
  return -1;
}

