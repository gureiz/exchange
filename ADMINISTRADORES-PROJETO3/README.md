# Projeto 3- Exchange de criptomoedas para administradores

## Objetivo do Projeto

O objetivo deste projeto é criar um sistema de gerenciamento de investidores e criptomoedas, onde um administrador pode realizar diversas ações relacionadas ao cadastro, exclusão e consulta de investidores e criptomoedas. O programa permite ainda a consulta de saldos e extratos dos investidores, além da atualização das cotações das criptomoedas.

## Forma de Compilação e Execução

### Compilação

1.	Certifique-se de que você possui o compilador `gcc` instalado no seu sistema. Caso não tenha, você pode instalá-lo;
2.	Navegue até o diretório onde o código-fonte está localizado. Em seguida, compile o código com o comando:  “gcc -o administrador.c”;
3.	Isso criará um executável chamado “administrador”.

### Execução
Para executar o programa, digite o seguinte comando:  “./administrador”

## Forma de Uso do Programa

### Login de Administrador

O programa solicitará o **CPF** e a **senha** do administrador. Somente se os dados forem corretos, o menu principal será exibido. Caso contrário, o administrador será solicitado a tentar novamente.

Para acessar, basta digitar o CPF : "123456789-10" e a seguinte senha: "123456"

### Menu Principal

Após um login bem-sucedido, o menu principal será exibido com as seguintes opções:

1. **Cadastrar novo investidor**  
   O administrador deve fornecer o **nome**, **CPF** e **senha** do investidor. O investidor será cadastrado com um saldo inicial de 0 em reais e nas criptomoedas disponíveis.

2. **Excluir investidor**  
   O administrador deve informar o **CPF** do investidor a ser excluído. O programa exibirá os dados do investidor e pedirá a confirmação para a exclusão. Se confirmado, o investidor será removido do sistema.

3. **Cadastrar criptomoeda**  
   O administrador deve fornecer o **nome** da criptomoeda, sua **cotação inicial**, **taxa de compra** e **taxa de venda**. A criptomoeda será cadastrada no sistema.

4. **Excluir criptomoeda**  
   O administrador deve fornecer o **nome** da criptomoeda a ser excluída. O programa exibirá os dados da moeda e pedirá a confirmação para a exclusão. Se confirmado, a criptomoeda será removida do sistema.

5. **Consultar saldo de investidor**  
   O administrador deve fornecer o **CPF** do investidor. O programa exibirá o saldo de reais e as criptomoedas associadas a esse investidor.

6. **Consultar extrato de investidor**  
   O administrador deve fornecer o **CPF** do investidor. O programa exibirá o extrato de transações realizadas pelo investidor.

7. **Atualizar cotação de criptomoedas**  
   O administrador pode atualizar as cotações das criptomoedas cadastradas. O sistema vai atualizar a cotação de cada criptomoeda com uma variação aleatória dentro de um intervalo de -5% a +5% de sua cotação atual.

## Funcionalidades Detalhadas

- **Efetuar login**:  O administrador deve fornecer um CPF e uma senha. Caso o login seja bem-sucedido, o menu principal é exibido. Caso contrário, o administrador será solicitado a tentar novamente.
  
- **Cadastro de investidor**:  O administrador fornece o nome, CPF e senha de um investidor, e o sistema cria o investidor com saldo inicial de 0,00 em reais e em criptomoedas.

- **Exclusão de investidor**:  O administrador fornece o CPF do investidor e, caso o CPF seja encontrado, o sistema exibe os dados do investidor e solicita confirmação para exclusão.

- **Cadastro de criptomoeda**:  O administrador fornece o nome, a cotação inicial, a taxa de compra e a taxa de venda de uma criptomoeda, que é então registrada no sistema.

- **Exclusão de criptomoeda**:  O administrador fornece o nome da criptomoeda a ser excluída. Se a criptomoeda for encontrada, o sistema exibe seus dados e solicita confirmação para exclusão.

- **Consulta de saldo de investidor**:  O administrador fornece o CPF de um investidor e o sistema retorna o saldo em reais e nas criptomoedas:  Bitcoin, Ethereum e Ripple.

- **Consulta de extrato de investidor**:  O administrador fornece o CPF de um investidor e o sistema exibe todas as transações realizadas por esse investidor.

- **Atualização de cotações de criptomoedas**:  O administrador pode atualizar as cotações de Bitcoin, Ethereum e Ripple, que sofrem uma variação aleatória dentro de um intervalo de -5% a +5%.

## Arquivos

- **investidores.txt**: Arquivo onde os dados dos investidores são salvos, incluindo informações pessoais, saldos e histórico de transações.
- **criptomoedas.txt**: Arquivo onde os dados das criptomoedas são salvos, incluindo nome, cotação e taxas de compra e venda.

Os arquivos são carregados automaticamente ao iniciar o programa e atualizados sempre que ocorrerem alterações nos dados.

## Conclusão

Esse projeto permite ao administrador gerenciar investidores e criptomoedas com funcionalidades como cadastro, exclusão, consulta de saldos e extratos, e atualização de cotações de criptomoedas.

## Link do REPLIT

https://replit.com/@reisgu267/adm?v=1

## Participantes

Lucas Gasparetto Pimentel 22.124.025.2
Gustavo Reis Teixeira 22.124.055-9

