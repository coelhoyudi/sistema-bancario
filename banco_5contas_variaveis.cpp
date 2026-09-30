#include <iostream>
#include <string>
#include <iomanip> // Para formatar o saldo com 2 casas decimais (Ex: R$ 100.00)

using namespace std;

const int MAX_CONTAS = 5; // Quantidade maxima de contas

// Procura uma conta pelo numero. Retorna a posicao no array ou -1 se nao achar.
int buscarConta(int numero, int numeroConta[], int total) {
    for (int i = 0; i < total; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

int main() {
    // ===== Variaveis obrigatorias, agora como arrays (ate 5 contas) =====
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int idade[MAX_CONTAS];            // variavel extra: idade do titular
    string telefone[MAX_CONTAS];      // variavel extra: telefone do titular
    int tipoConta[MAX_CONTAS];        // 1 = Corrente; 2 = Poupanca
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    int totalContas = 0;  // quantas contas ja foram cadastradas
    int opcao;
    int numeroBusca;      // numero digitado para procurar uma conta
    int pos;              // posicao da conta encontrada no array

    // Configura a exibicao de numeros decimais para 2 casas decimais
    cout << fixed << setprecision(2);

    do {
        // ===== Menu =====
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        // Se o usuario digitar uma letra, limpa o erro do cin e cai no "default"
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcao = 0;
        }

        switch (opcao) {
            case 1: {
                // ----- CADASTRAR -----
                cout << "\n--- CADASTRAR NOVA CONTA ---\n";

                // Verifica se ainda cabe uma conta
                if (totalContas >= MAX_CONTAS) {
                    cout << "Erro: Limite de " << MAX_CONTAS << " contas atingido!\n";
                    break;
                }

                int novoNumero;
                do {
                    cout << "Digite o numero da conta (numero positivo): ";
                    cin >> novoNumero;
                    if (novoNumero <= 0) {
                        cout << "Erro: O numero da conta deve ser maior que zero!\n";
                    }
                } while (novoNumero <= 0);

                // Nao permite duas contas com o mesmo numero
                if (buscarConta(novoNumero, numeroConta, totalContas) != -1) {
                    cout << "Erro: Ja existe uma conta com esse numero!\n";
                    break;
                }

                // A nova conta ocupa a proxima posicao livre (totalContas)
                numeroConta[totalContas] = novoNumero;

                cin.ignore();

                cout << "Digite o nome completo do cliente: ";
                getline(cin, nomeCliente[totalContas]);

                cout << "Digite o CPF do cliente: ";
                getline(cin, cpf[totalContas]);

                // Pedir idade e repetir enquanto for menor que 18
                do {
                    cout << "Digite a idade do cliente (minimo 18 anos): ";
                    cin >> idade[totalContas];
                    if (idade[totalContas] < 18) {
                        cout << "Erro: O titular deve ter 18 anos ou mais!\n";
                    }
                } while (idade[totalContas] < 18);

                // Limpa o buffer antes de ler o telefone com getline
                cin.ignore();

                cout << "Digite o telefone do cliente: ";
                getline(cin, telefone[totalContas]);

                do {
                    cout << "Digite o tipo da conta (1 = Corrente | 2 = Poupanca): ";
                    cin >> tipoConta[totalContas];
                    if (tipoConta[totalContas] != 1 && tipoConta[totalContas] != 2) {
                        cout << "Erro: Opcao invalida! Digite 1 para Corrente ou 2 para Poupanca.\n";
                    }
                } while (tipoConta[totalContas] != 1 && tipoConta[totalContas] != 2);

                do {
                    cout << "Digite o saldo inicial (R$): ";
                    cin >> saldo[totalContas];
                    if (saldo[totalContas] < 0) {
                        cout << "Erro: O saldo inicial nao pode ser negativo!\n";
                    }
                } while (saldo[totalContas] < 0);

                contaAtiva[totalContas] = true;
                totalContas++; // agora temos mais uma conta cadastrada

                cout << "\n>> Conta cadastrada com sucesso! (" << totalContas
                     << "/" << MAX_CONTAS << ") <<\n";
                break;
            }

            case 2:
                // ----- CONSULTAR -----
                cout << "\n--- CONSULTAR CONTA ---\n";

                if (totalContas == 0) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema ainda.\n";
                    break;
                }

                cout << "Digite o numero da conta: ";
                cin >> numeroBusca;
                pos = buscarConta(numeroBusca, numeroConta, totalContas);

                if (pos == -1) {
                    cout << "Erro: Conta nao encontrada!\n";
                } else {
                    cout << "Numero da Conta: " << numeroConta[pos] << "\n";
                    cout << "Cliente: " << nomeCliente[pos] << "\n";
                    cout << "CPF: " << cpf[pos] << "\n";
                    cout << "Idade: " << idade[pos] << " anos\n";
                    cout << "Telefone: " << telefone[pos] << "\n";
                    cout << "Tipo de Conta: " << (tipoConta[pos] == 1 ? "Corrente" : "Poupanca") << "\n";
                    cout << "Saldo: R$ " << saldo[pos] << "\n";
                    cout << "Status: " << (contaAtiva[pos] ? "Ativa" : "Inativa") << "\n";
                }
                break;

            case 3:
                // ----- VERIFICAR SALDO -----
                cout << "\n--- VERIFICAR SALDO ---\n";

                if (totalContas == 0) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema.\n";
                    break;
                }

                cout << "Digite o numero da conta: ";
                cin >> numeroBusca;
                pos = buscarConta(numeroBusca, numeroConta, totalContas);

                if (pos == -1) {
                    cout << "Erro: Conta nao encontrada!\n";
                } else if (!contaAtiva[pos]) {
                    cout << "Atencao: A conta esta inativa. Nao e possivel verificar o saldo.\n";
                } else {
                    cout << "Saldo atual da conta (" << numeroConta[pos] << "): R$ " << saldo[pos] << "\n";
                }
                break;

            case 4: {
                // ----- ALTERAR TIPO -----
                cout << "\n--- ALTERAR TIPO DA CONTA ---\n";

                if (totalContas == 0) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema.\n";
                    break;
                }

                cout << "Digite o numero da conta: ";
                cin >> numeroBusca;
                pos = buscarConta(numeroBusca, numeroConta, totalContas);

                if (pos == -1) {
                    cout << "Erro: Conta nao encontrada!\n";
                } else if (!contaAtiva[pos]) {
                    cout << "Atencao: A conta esta inativa. Nao e possivel alterar o tipo.\n";
                } else {
                    cout << "Tipo atual: " << (tipoConta[pos] == 1 ? "Corrente" : "Poupanca") << "\n";

                    int novoTipo = 0;
                    do {
                        cout << "Digite o novo tipo (1 = Corrente | 2 = Poupanca): ";
                        cin >> novoTipo;
                        if (novoTipo != 1 && novoTipo != 2) {
                            cout << "Erro: Opcao invalida! Digite 1 para Corrente ou 2 para Poupanca.\n";
                        }
                    } while (novoTipo != 1 && novoTipo != 2);

                    tipoConta[pos] = novoTipo;
                    cout << ">> Tipo de conta alterado com sucesso! <<\n";
                }
                break;
            }

            case 5:
                // ----- ATIVAR/DESATIVAR -----
                cout << "\n--- ATIVAR / DESATIVAR CONTA ---\n";

                if (totalContas == 0) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema.\n";
                    break;
                }

                cout << "Digite o numero da conta: ";
                cin >> numeroBusca;
                pos = buscarConta(numeroBusca, numeroConta, totalContas);

                if (pos == -1) {
                    cout << "Erro: Conta nao encontrada!\n";
                } else {
                    contaAtiva[pos] = !contaAtiva[pos]; // inverte o valor

                    if (contaAtiva[pos]) {
                        cout << ">> A conta foi ATIVADA com sucesso. <<\n";
                    } else {
                        cout << ">> A conta foi DESATIVADA com sucesso. <<\n";
                    }
                }
                break;

            case 6:
                cout << "\nEncerrando o sistema. Ate logo!\n";
                break;

            default:
                cout << "\nOpcao invalida! Tente novamente.\n";
        }

    } while (opcao != 6);

    return 0;
}
