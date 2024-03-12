#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Estrutura base para todos os bens
struct Bem
{
    std::string nome;
    std::string categoria;
    std::string dataAquisicao;

    virtual ~Bem() {} // Destrutor da classe
};

// Estrutura para moveis
struct Mover : public Bem
{
    double peso;
};

// Estrutura para imóveis
struct Imovel : public Bem
{
    std::string endereco;
};

// Função para adicionar um bem à lista
void adicionarBem(std::vector<Bem *> &lista, Bem *bem)
{
    lista.push_back(bem);
}

// Função para listar todos os bens
void listarBens(const std::vector<Bem *> &lista)
{
    for (const auto &bem : lista)
    {
        std::cout << "Nome: " << bem->nome << ", Categoria: " << bem->categoria << ", Data de Aquisição: " << bem->dataAquisicao << std::endl;
        if (dynamic_cast<Mover *>(bem))
        {
            std::cout << "Peso: " << static_cast<Mover *>(bem)->peso << std::endl;
        }
        else if (dynamic_cast<Imovel *>(bem))
        {
            std::cout << "Endereço: " << static_cast<Imovel *>(bem)->endereco << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }
}

// Função para salvar os dados em um arquivo
void salvarDados(const std::vector<Bem *> &lista)
{
    std::ofstream arquivo("bens.txt");
    if (arquivo.is_open())
    {
        for (const auto &bem : lista)
        {
            arquivo << "Nome: " << bem->nome << ", Categoria: " << bem->categoria << ", Data de Aquisição: " << bem->dataAquisicao << std::endl;
            if (dynamic_cast<Mover *>(bem))
            {
                arquivo << "Peso: " << static_cast<Mover *>(bem)->peso << std::endl;
            }
            else if (dynamic_cast<Imovel *>(bem))
            {
                arquivo << "Endereço: " << static_cast<Imovel *>(bem)->endereco << std::endl;
            }
            arquivo << "------------------------" << std::endl;
        }
        arquivo.close();
    }
    else
    {
        std::cout << "Não foi possível abrir o arquivo para escrita." << std::endl;
    }
}

int main()
{
    std::vector<Bem *> listaBens;

    // Exemplo de adição de um mover
    Mover *mover = new Mover;
    mover->nome = "Mesa";
    mover->categoria = "Móveis";
    mover->dataAquisicao = "01/01/2022";
    mover->peso = 15.0;
    adicionarBem(listaBens, mover);

    // Exemplo de adição de um imóvel
    Imovel *imovel = new Imovel;
    imovel->nome = "Edifício Principal";
    imovel->categoria = "Imóveis";
    imovel->dataAquisicao = "01/01/2000";
    imovel->endereco = "Rua Principal, 123";
    adicionarBem(listaBens, imovel);

    // Listar todos os bens
    listarBens(listaBens);

    // Salvar os dados em um arquivo
    salvarDados(listaBens);

    // Liberar memória alocada
    for (auto &bem : listaBens)
    {
        delete bem;
    }

    return 0;
}