#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estrutura para registrar um bem
struct Bem
{
    string nome;
    string categoria;
    string dataAquisicao;
    float peso;
    string endereco; // Apenas para imóveis

    // Construtor
    Bem(string nome, string categoria, string dataAquisicao, float peso, string endereco)
    {
        this->nome = nome;
        this->categoria = categoria;
        this->dataAquisicao = dataAquisicao;
        this->peso = peso;
        this->endereco = endereco;
    }

public:
    Bem() {}

public:
    friend istream &operator>>(istream &in, Bem &bem)
    {
        // Leia os dados do bem da stream "in"
        // ...
        return in;
    }
};

// Função para exibir os detalhes de um bem
void exibirBem(Bem bem)
{
    cout << "Nome: " << bem.nome << endl;
    cout << "Categoria: " << bem.categoria << endl;
    cout << "Data de Aquisição: " << bem.dataAquisicao << endl;
    cout << "Peso: " << bem.peso << " kg" << endl;
    if (!bem.endereco.empty())
    {
        cout << "Endereço: " << bem.endereco << endl;
    }
    cout << endl;
}

// Função para ler os dados de um bem do teclado
Bem lerBem()
{
    string nome, categoria, dataAquisicao, endereco;
    float peso;

    cout << "Digite o nome do bem: ";
    cin >> nome;

    cout << "Digite a categoria do bem: ";
    cin >> categoria;

    cout << "Digite a data de aquisição do bem (dd/mm/aaaa): ";
    cin >> dataAquisicao;

    cout << "Digite o peso do bem (kg): ";
    cin >> peso;

    cout << "Digite o endereço do bem (se for imóvel): ";
    cin >> endereco;

    return Bem(nome, categoria, dataAquisicao, peso, endereco);
}

// Função para gravar um bem em um arquivo
void gravarBem(Bem bem, ofstream &arquivo)
{
    arquivo << bem.nome << endl;
    arquivo << bem.categoria << endl;
    arquivo << bem.dataAquisicao << endl;
    arquivo << bem.peso << endl;
    arquivo << bem.endereco << endl;
}

// Função para ler um bem de um arquivo
Bem lerBem(ifstream &arquivo)
{
    string nome, categoria, dataAquisicao, endereco;
    float peso;

    getline(arquivo, nome);
    getline(arquivo, categoria);
    getline(arquivo, dataAquisicao);
    arquivo >> peso;
    arquivo.ignore();
    getline(arquivo, endereco);

    return Bem(nome, categoria, dataAquisicao, peso, endereco);
}

// Função para exibir todos os bens cadastrados
void exibirTodosBens(const char *nomeArquivo)
{
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    Bem bem;
    while (arquivo >> bem)
    {
        exibirBem(bem);
    }

    arquivo.close();
}

// Função para buscar um bem por nome
void buscarBemPorNome(const char *nomeArquivo)
{
    string nomePesquisa;
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    cout << "Digite o nome do bem que deseja buscar: ";
    cin >> nomePesquisa;

    Bem bem;
    bool encontrado = false;
    while (arquivo >> bem)
    {
        if (bem.nome == nomePesquisa)
        {
            exibirBem(bem);
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "Bem não encontrado!" << endl;
    }

    arquivo.close();
}

// Função para adicionar um novo bem
void adicionarBem(const char *nomeArquivo)
{
    ofstream arquivo(nomeArquivo, ios::app);

    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    Bem novoBem = lerBem();
    gravarBem(novoBem, arquivo);

    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    novoBem = lerBem();
    gravarBem(novoBem, arquivo); // Gravando o novo bem no arquivo
    cout << "Bem adicionado com sucesso!" << endl;

    arquivo.close();
}

int main()
{
    const char *nomeArquivo = "bens.txt"; // Nome do arquivo de armazenamento

    int opcao;

    do
    {
        cout << "\nMenu de Gestão de Bens da Universidade Zambeze" << endl;
        cout << "1. Exibir todos os bens" << endl;
        cout << "2. Buscar bem por nome" << endl;
        cout << "3. Adicionar novo bem" << endl;
        cout << "0. Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            exibirTodosBens(nomeArquivo);
            break;
        case 2:
            buscarBemPorNome(nomeArquivo);
            break;
        case 3:
            adicionarBem(nomeArquivo);
            break;
        case 0:
            cout << "Saindo do programa..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);

    return 0;
}
