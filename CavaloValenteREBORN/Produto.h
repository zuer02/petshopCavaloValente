#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

struct produto{
    int CodigoP;
    char NomeProduto[36];
    char Tipo[21];
    char Marca[21];
    float Preco;
    char DataValidade[11];
    char Quantidade[21];
};
typedef struct produto Produto;

Produto DigitarProduto();

void ImprimirProduto(Produto P);

void InserirProduto(Produto P);

void TelaProduto();

void MostrarProduto(Produto P);

void InterfaceCadastroProduto();

void ListarProdutos();

Produto PesquisarProduto(int codigo);

void InterfacePesquisarProduto();

void NovoProduto();

void AlterarProduto(Produto PNovo);

void InterfaceAlterarProduto();

void InterfaceExluirProduto();

void AbrirProduto();

void FecharProduto();

#endif // PRODUTO_H_INCLUDED
