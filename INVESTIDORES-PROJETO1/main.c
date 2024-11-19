#include "projeto.h"

int main() {
    Usuario usuarios[MAX_USUARIOS];
    int numUsuarios = 0;
    char cpf[12], senha[20];
    int opcao;

    carregarDados(usuarios, &numUsuarios);

    do {
        printf("\n--- Sistema de Login ---\n");
        printf("1. Fazer Login\n");
        printf("2. Cadastrar Novo Usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: // Login de usuário existente
            while (1) {
                printf("Digite seu CPF: ");
                scanf("%s", cpf);
                printf("Digite sua senha: ");
                scanf("%s", senha);

                int usuarioIndex = login(usuarios, numUsuarios, cpf, senha);
                if (usuarioIndex != -1) {
                    printf("Login bem-sucedido!\n");
                    menuPrincipal(&usuarios[usuarioIndex]);
                    salvarDados(usuarios, numUsuarios);
                    break;
                } else {
                    printf("CPF ou senha incorretos.\n");
                    printf("Deseja tentar novamente (1) ou voltar ao menu principal (2)? ");
                    int escolha;
                    scanf("%d", &escolha);

                    if (escolha == 2) {
                        break;
                    }
                }
            }
            break;

        case 2: // Cadastro de novo usuário
            if (cadastrarUsuario(usuarios, &numUsuarios)) {
                printf("Cadastro realizado com sucesso!\n");
                salvarDados(usuarios, numUsuarios);
            } else {
                printf("Erro no cadastro. Número máximo de usuários atingido.\n");
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
