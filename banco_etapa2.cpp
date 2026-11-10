#include <iostream>
#include <string>
#include <iomanip> // fixed e setprecision (saldo com 2 casas decimais)

using namespace std;

// ===== Dados das contas (ate 100 contas) =====
const int MAX_CONTAS = 100;
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];      // 1 = Corrente; 2 = Poupanca
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int quantidadeContas = 0;

// ===== Historico de movimentacoes (ate 500) =====
const int MAX_MOVIMENTACOES = 500;
int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];   // 'D' = Deposito; 'S' = Saque
double valorMovimentacao[MAX_MOVIMENTACOES];
int quantidadeMovimentacoes = 0;

// Procura a conta pelo numero. Retorna a posicao no array ou -1 se nao achar.
int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

// Guarda uma movimentacao no historico
void registrarMovimentacao(int conta, char tipo, double valor) {
    contaMovimentacao[quantidadeMovimentacoes] = conta;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;
    quantidadeMovimentacoes++;
}

void cadastrarConta() {
    cout << "\n--- CADASTRAR CONTA ---\n";
    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Erro: limite de contas atingido!\n";
        return;
    }

    int numero;
    do {
        cout << "Numero da conta: ";
        cin >> numero;
        if (numero <= 0) cout << "Erro: o numero deve ser maior que zero!\n";
    } while (numero <= 0);

    if (buscarConta(numero) != -1) {
        cout << "Erro: ja existe uma conta com esse numero!\n";
        return;
    }

    int i = quantidadeContas;       // proxima posicao livre
    numeroConta[i] = numero;

    cin.ignore();                   // descarta o Enter para o getline funcionar
    cout << "Nome do cliente: ";
    getline(cin, nomeCliente[i]);
    cout << "CPF: ";
    getline(cin, cpf[i]);

    do {
        cout << "Tipo (1 = Corrente | 2 = Poupanca): ";
        cin >> tipoConta[i];
        if (tipoConta[i] != 1 && tipoConta[i] != 2) cout << "Erro: digite 1 ou 2!\n";
    } while (tipoConta[i] != 1 && tipoConta[i] != 2);

    do {
        cout << "Saldo inicial: R$ ";
        cin >> saldo[i];
        if (saldo[i] < 0) cout << "Erro: o saldo nao pode ser negativo!\n";
    } while (saldo[i] < 0);

    contaAtiva[i] = true;
    quantidadeContas++;
    cout << ">> Conta cadastrada com sucesso! <<\n";
}

void listarContas() {
    cout << "\n--- CONTAS CADASTRADAS ---\n";
    if (quantidadeContas == 0) cout << "Nenhuma conta cadastrada.\n";
    for (int i = 0; i < quantidadeContas; i++) {
        cout << "Conta " << numeroConta[i] << " | " << nomeCliente[i]
             << " | " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca")
             << " | R$ " << saldo[i]
             << " | " << (contaAtiva[i] ? "Ativa" : "Inativa") << "\n";
    }
}

void consultarConta() {
    cout << "\n--- CONSULTAR CONTA ---\nNumero da conta: ";
    int numero;
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Erro: conta nao encontrada!\n";
        return;
    }
    cout << "Conta: " << numeroConta[i] << "\nCliente: " << nomeCliente[i]
         << "\nCPF: " << cpf[i]
         << "\nTipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca")
         << "\nSaldo: R$ " << saldo[i]
         << "\nStatus: " << (contaAtiva[i] ? "Ativa" : "Inativa") << "\n";
}

void depositar() {
    cout << "\n--- DEPOSITAR ---\nNumero da conta: ";
    int numero;
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) { cout << "Erro: conta nao encontrada!\n"; return; }
    if (!contaAtiva[i]) { cout << "Erro: conta inativa!\n"; return; }
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) { cout << "Erro: historico cheio!\n"; return; }

    double valor;
    cout << "Valor do deposito: R$ ";
    cin >> valor;
    if (valor <= 0) { cout << "Erro: o valor deve ser maior que zero!\n"; return; }

    saldo[i] = saldo[i] + valor;
    registrarMovimentacao(numeroConta[i], 'D', valor);
    cout << ">> Deposito realizado! Novo saldo: R$ " << saldo[i] << " <<\n";
}

void sacar() {
    cout << "\n--- SACAR ---\nNumero da conta: ";
    int numero;
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) { cout << "Erro: conta nao encontrada!\n"; return; }
    if (!contaAtiva[i]) { cout << "Erro: conta inativa!\n"; return; }
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) { cout << "Erro: historico cheio!\n"; return; }

    double valor;
    cout << "Saldo disponivel: R$ " << saldo[i] << "\nValor do saque: R$ ";
    cin >> valor;
    if (valor <= 0) { cout << "Erro: o valor deve ser maior que zero!\n"; return; }
    if (valor > saldo[i]) { cout << "Erro: saldo insuficiente!\n"; return; }

    saldo[i] = saldo[i] - valor;
    registrarMovimentacao(numeroConta[i], 'S', valor);
    cout << ">> Saque realizado! Novo saldo: R$ " << saldo[i] << " <<\n";
}

void transferir() {
    int origem, destino;
    double valor;
    cout << "\n--- TRANSFERIR ---\nConta de ORIGEM: ";
    cin >> origem;
    cout << "Conta de DESTINO: ";
    cin >> destino;

    int io = buscarConta(origem);     // posicao da origem
    int id = buscarConta(destino);    // posicao do destino
    if (io == -1 || id == -1) { cout << "Erro: conta nao encontrada!\n"; return; }
    if (io == id) { cout << "Erro: as contas devem ser diferentes!\n"; return; }
    if (!contaAtiva[io] || !contaAtiva[id]) { cout << "Erro: as duas contas precisam estar ativas!\n"; return; }
    // A transferencia gera DOIS registros, entao precisa haver espaco para os dois
    if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) { cout << "Erro: historico cheio!\n"; return; }

    cout << "Saldo da origem: R$ " << saldo[io] << "\nValor da transferencia: R$ ";
    cin >> valor;
    if (valor <= 0) { cout << "Erro: o valor deve ser maior que zero!\n"; return; }
    if (valor > saldo[io]) { cout << "Erro: saldo insuficiente!\n"; return; }

    saldo[io] = saldo[io] - valor;
    saldo[id] = saldo[id] + valor;
    registrarMovimentacao(origem, 'S', valor);    // saida da origem
    registrarMovimentacao(destino, 'D', valor);   // entrada no destino
    cout << ">> Transferencia realizada com sucesso! <<\n";
}

void exibirExtrato() {
    cout << "\n--- EXTRATO ---\nNumero da conta: ";
    int numero;
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Erro: conta nao encontrada!\n";
        return;
    }
    cout << "Extrato da conta " << numero << " - " << nomeCliente[i] << "\n";
    // Percorre o historico e mostra so as movimentacoes desta conta
    for (int m = 0; m < quantidadeMovimentacoes; m++) {
        if (contaMovimentacao[m] == numero) {
            if (tipoMovimentacao[m] == 'D') cout << "Deposito: R$ " << valorMovimentacao[m] << endl;
            else cout << "Saque: R$ " << valorMovimentacao[m] << endl;
        }
    }
    cout << "Saldo atual: R$ " << saldo[i] << "\n";
}

void alternarConta() {
    cout << "\n--- ATIVAR/DESATIVAR CONTA ---\nNumero da conta: ";
    int numero;
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Erro: conta nao encontrada!\n";
        return;
    }
    contaAtiva[i] = !contaAtiva[i];   // inverte o bool
    cout << (contaAtiva[i] ? ">> Conta ATIVADA. <<\n" : ">> Conta DESATIVADA. <<\n");
}

int main() {
    int opcao;
    cout << fixed << setprecision(2);

    do {
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n2 - Listar contas\n3 - Consultar conta\n";
        cout << "4 - Depositar\n5 - Sacar\n6 - Transferir\n7 - Extrato\n";
        cout << "8 - Ativar/Desativar conta\n9 - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {             // se digitou letra, limpa o erro e cai no default
            cin.clear();
            cin.ignore(1000, '\n');
            opcao = 0;
        }

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: listarContas(); break;
            case 3: consultarConta(); break;
            case 4: depositar(); break;
            case 5: sacar(); break;
            case 6: transferir(); break;
            case 7: exibirExtrato(); break;
            case 8: alternarConta(); break;
            case 9: cout << "\nEncerrando o sistema. Ate logo!\n"; break;
            default: cout << "\nOpcao invalida! Tente novamente.\n";
        }
    } while (opcao != 9);

    return 0;
}
