#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Estrutura para registrar um bem
struct Bem
{
    string nome;
    string categoria;
    string dataAquisicao;
    float peso;
    string endereco; // Obrigatório para bens imóveis
};

// Tipo de dado para armazenar um vetor de bens
typedef vector<Bem> VetorBens;

/*
Função para dividir uma string com base em um delimitador

Este código define uma função chamada split que recebe uma cadeia
de caracteres 's' e um carácter 'delimiter' como entradas e devolve
um vetor de cadeias de caracteres. A função divide a cadeia de entrada
 em várias subcadeias com base no carácter delimitador e armazena-as no vetor.
*/
vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

/*
    Função para adicionar um novo bem
    Esta função 'adicionarBem' é utilizada para adicionar um novo
    item a um vetor de objectos 'Bem'. Pede ao utilizador que introduza
    os detalhes do novo item, como o nome, a categoria, a data de aquisição
    e o peso. Se a categoria for "imovel", também pede o endereço.
    A função cria então um novo objeto 'Bem' com os detalhes introduzidos e
    adiciona-o ao vetor.
*/
void adicionarBem(VetorBens &bens)
{
    Bem novoBem;

    // Leitura dos dados do bem
    cout << "Nome do bem: ";
    cin.ignore(); // Ignora o caractere de nova linha pendente
    getline(cin, novoBem.nome);

    cout << "Categoria (movel/imovel): ";
    cin >> novoBem.categoria;

    cout << "Data de aquisição (dd/mm/aaaa): ";
    cin >> novoBem.dataAquisicao;

    cout << "Peso (kg): ";
    cin >> novoBem.peso;

    // Verificação da categoria e leitura do endereço (se necessário)
    if (novoBem.categoria == "imovel")
    {
        cout << "Endereço (obrigatório para imóveis): ";
        cin.ignore(); // Ignora o caractere de nova linha pendente
        getline(cin, novoBem.endereco);
    }
    else
    {
        novoBem.endereco = ""; // Define o endereço como vazio para bens móveis
    }

    // Adição do novo bem ao vetor
    bens.push_back(novoBem);
}

/*
    Função para listar todos os bens
    Esta função, 'listarBens', é utilizada para apresentar os detalhes
    de cada item num vetor de objectos 'Bem'.
*/
void listarBens(const VetorBens &bens)
{
    for (const Bem &bem : bens)
    {
        cout << "Nome: " << bem.nome << endl;
        cout << "Categoria: " << bem.categoria << endl;
        cout << "Data de aquisição: " << bem.dataAquisicao << endl;
        cout << "Peso: " << bem.peso << " kg" << endl;

        if (bem.categoria == "imovel")
        {
            cout << "Endereço: " << bem.endereco << endl;
        }

        cout << endl;
    }
}

/*

Função para buscar um bem por nome

Esta função 'buscarBemPorNome' procura um objeto 'Bem'
num vetor de objectos 'Bem' com base no parâmetro 'nome' fornecido.
*/
Bem *buscarBemPorNome(VetorBens &bens, string nome)
{
    for (Bem &bem : bens)
    {
        if (bem.nome == nome)
        {
            return &bem;
        }
    }

    return nullptr;
}

/*
    Função para remover um bem por nome
    Esta função remove um objeto 'Bem' de um vetor de objectos 'Bem'
    com base no parâmetro 'nome' (name) fornecido.
*/
void removerBemPorNome(VetorBens &bens, string nome)
{
    // Busca o bem pelo nome
    auto it = std::remove_if(bens.begin(), bens.end(), [nome](const Bem &bem)
                             { return bem.nome == nome; });

    // Se o bem for encontrado, remove-o do vetor
    if (it != bens.end())
    {
        bens.erase(it, bens.end());
    }
    else
    {
        cout << "Bem não encontrado!" << endl;
    }
}

/*
    Função para ler os dados dos bens de um arquivo
    Esta função lê dados de um ficheiro e preenche um vetor de objectos com os dados lidos.

    1 - Abra o ficheiro com o nome "bens.txt" para leitura.
    2 - Se o ficheiro for aberto com sucesso:
        - Ler cada linha do ficheiro.
        - Dividir cada linha em campos utilizando uma vírgula como delimitador.
        - Crie um novo objeto e atribua os campos aos seus atributos.
        - Se a categoria do objeto for "imovel", atribua o quinto campo ao seu atributo de endereço.
        - Adicione o novo objeto ao vetor.
    3 - Feche o ficheiro.
    4 - Se o ficheiro não puder ser aberto, emite uma mensagem de erro.
*/
void lerDadosDoArquivo(VetorBens &bens)
{
    ifstream arquivo("bens.txt");

    if (arquivo.is_open())
    {
        string linha;

        // Leitura de cada linha do arquivo
        while (getline(arquivo, linha))
        {
            // Separação dos campos da linha
            vector<string> campos = split(linha, ',');

            // Criação de um novo bem com os dados da linha
            Bem novoBem;
            novoBem.nome = campos[0];
            novoBem.categoria = campos[1];
            novoBem.dataAquisicao = campos[2];
            novoBem.peso = stof(campos[3]);

            // Verificação da categoria e leitura do endereço (se necessário)
            if (novoBem.categoria == "imovel")
            {
                novoBem.endereco = campos[4];
            }

            // Adição do novo bem ao vetor
            bens.push_back(novoBem);
        }

        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}

/*
    Função para gravar os dados dos bens em um arquivo
    Esta função é responsável por escrever os dados armazenados
    no vetor bens para um ficheiro chamado "bens.txt". Os dados
    são escritos num formato específico, com cada linha a
    representar um único item no vetor.
*/
void gravarDadosNoArquivo(const VetorBens &bens)
{
    ofstream arquivo("bens.txt");

    if (arquivo.is_open())
    {
        for (const Bem &bem : bens)
        {
            // Gravação dos dados do bem no arquivo
            arquivo << bem.nome << ","
                    << bem.categoria << ","
                    << bem.dataAquisicao << ","
                    << bem.peso << ",";

            if (bem.categoria == "imovel")
            {
                arquivo << bem.endereco;
            }

            arquivo << endl;
        }

        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}

/*
    Este código representa um programa baseado
    em menus para gerir uma coleção de bens.
    Permite ao utilizador adicionar, listar,
    pesquisar e remover activos da coleção. Os activos
    são armazenados num vetor e os dados são lidos e
    escritos num ficheiro.
*/
int main()
{
    VetorBens bens; // Vetor para armazenar os bens

    // Leitura inicial dos dados do arquivo
    lerDadosDoArquivo(bens);

    int opcao;

    do
    {
        // Exibição do menu
        cout << endl;
        cout << "Menu de Gerenciamento de Bens da UniZambeze" << endl;
        cout << "1. Adicionar Bem" << endl;
        cout << "2. Listar Bens" << endl;
        cout << "3. Buscar Bem por Nome" << endl;
        cout << "4. Remover Bem por Nome" << endl;
        cout << "5. Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            adicionarBem(bens);
            break;
        case 2:
            listarBens(bens);
            break;
        case 3:
        {
            string nomeBusca;
            cout << "Digite o nome do bem a ser buscado: ";
            cin >> nomeBusca;

            Bem *bemEncontrado = buscarBemPorNome(bens, nomeBusca);

            if (bemEncontrado != nullptr)
            {
                cout << endl;
                cout << "Bem encontrado:" << endl;
                cout << "Nome: " << bemEncontrado->nome << endl;
                cout << "Categoria: " << bemEncontrado->categoria << endl;
                cout << "Data de aquisição: " << bemEncontrado->dataAquisicao << endl;
                cout << "Peso: " << bemEncontrado->peso << " kg" << endl;

                if (bemEncontrado->categoria == "imovel")
                {
                    cout << "Endereço: " << bemEncontrado->endereco << endl;
                }
            }
            else
            {
                cout << "Bem não encontrado!" << endl;
            }
            break;
        }
        case 4:
        {
            string nomeRemocao;
            cout << "Digite o nome do bem a ser removido: ";
            cin >> nomeRemocao;

            removerBemPorNome(bens, nomeRemocao);
            break;
        }
        case 5:
            cout << "Saindo do programa..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while (opcao != 5);

    // Gravação dos dados finais no arquivo
    gravarDadosNoArquivo(bens);

    return 0;
}
