#include <iostream>
#include <string>
#include <iomanip> // Para formatar o saldo com 2 casas decimais (Ex: R$ 100.00)

using namespace std;

int main() {
    // ===== Variaveis obrigatorias (Etapa 1) =====
    int numeroConta = 0;
    string nomeCliente = "";
    string cpf = "";
    int tipoConta = 0;        // 1 = Corrente; 2 = Poupanca
    double saldo = 0.0;
    bool contaAtiva = false;

    bool contaCadastrada = false;  // controla se ja existe uma conta
    int opcao;

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
            cin.clear();              // limpa o estado de erro
            cin.ignore(1000, '\n');   // descarta o que foi digitado
            opcao = 0;                // opcao invalida
        }

        switch (opcao) {
            case 1:
                // ----- CADASTRAR -----
                cout << "\n--- CADASTRAR NOVA CONTA ---\n";

                // Pedir numeroConta e repetir enquanto for <= 0
                do {
                    cout << "Digite o numero da conta (numero positivo): ";
                    cin >> numeroConta;
                    if (numeroConta <= 0) {
                        cout << "Erro: O numero da conta deve ser maior que zero!\n";
                    }
                } while (numeroConta <= 0);

                // Limpa o buffer do cin para permitir a leitura de strings com espaço
                cin.ignore();

                // Pedir nomeCliente e cpf
                cout << "Digite o nome completo do cliente: ";
                getline(cin, nomeCliente);

                cout << "Digite o CPF do cliente: ";
                getline(cin, cpf);

                // Pedir tipoConta e repetir enquanto nao for 1 ou 2
                do {
                    cout << "Digite o tipo da conta (1 = Corrente | 2 = Poupanca): ";
                    cin >> tipoConta;
                    if (tipoConta != 1 && tipoConta != 2) {
                        cout << "Erro: Opcao invalida! Digite 1 para Corrente ou 2 para Poupanca.\n";
                    }
                } while (tipoConta != 1 && tipoConta != 2);

                // Pedir saldo inicial e repetir enquanto for < 0
                do {
                    cout << "Digite o saldo inicial (R$): ";
                    cin >> saldo;
                    if (saldo < 0) {
                        cout << "Erro: O saldo inicial nao pode ser negativo!\n";
                    }
                } while (saldo < 0);

                // Ativar e registrar cadastro
                contaAtiva = true;
                contaCadastrada = true;

                cout << "\n>> Conta cadastrada com sucesso! <<\n";
                break;

            case 2:
                // ----- CONSULTAR -----
                cout << "\n--- CONSULTAR CONTA ---\n";

                // Se !contaCadastrada, avisar e sair do case
                if (!contaCadastrada) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema ainda.\n";
                    break;
                }

                // Mostrar todos os dados
                cout << "Numero da Conta: " << numeroConta << "\n";
                cout << "Cliente: " << nomeCliente << "\n";
                cout << "CPF: " << cpf << "\n";
                cout << "Tipo de Conta: " << (tipoConta == 1 ? "Corrente" : "Poupanca") << "\n";
                cout << "Saldo: R$ " << saldo << "\n";
                cout << "Status: " << (contaAtiva ? "Ativa" : "Inativa") << "\n";
                break;

            case 3:
                // ----- VERIFICAR SALDO -----
                cout << "\n--- VERIFICAR SALDO ---\n";

                // Verificar se existe conta E se contaAtiva == true
                if (!contaCadastrada) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema.\n";
                } else if (!contaAtiva) {
                    cout << "Atencao: A conta esta inativa. Nao e possivel verificar o saldo.\n";
                } else {
                    cout << "Saldo atual da conta (" << numeroConta << "): R$ " << saldo << "\n";
                }
                break;

            case 4:
                // ----- ALTERAR TIPO -----
                cout << "\n--- ALTERAR TIPO DA CONTA ---\n";

                // Verificar se existe conta E se esta ativa
                if (!contaCadastrada) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema.\n";
                } else if (!contaAtiva) {
                    cout << "Atencao: A conta esta inativa. Nao e possivel alterar o tipo.\n";
                } else {
                    cout << "Tipo atual: " << (tipoConta == 1 ? "Corrente" : "Poupanca") << "\n";

                    int novoTipo = 0;
                    do {
                        cout << "Digite o novo tipo (1 = Corrente | 2 = Poupanca): ";
                        cin >> novoTipo;
                        if (novoTipo != 1 && novoTipo != 2) {
                            cout << "Erro: Opcao invalida! Digite 1 para Corrente ou 2 para Poupanca.\n";
                        }
                    } while (novoTipo != 1 && novoTipo != 2);

                    tipoConta = novoTipo;
                    cout << ">> Tipo de conta alterado com sucesso! <<\n";
                }
                break;

            case 5:
                // ----- ATIVAR/DESATIVAR -----
                cout << "\n--- ATIVAR / DESATIVAR CONTA ---\n";

                // Verificar se existe conta
                if (!contaCadastrada) {
                    cout << "Atencao: Nenhuma conta cadastrada no sistema.\n";
                } else {
                    // Inverter o valor do bool
                    contaAtiva = !contaAtiva;

                    // Mostrar mensagem informando o novo estado
                    if (contaAtiva) {
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
