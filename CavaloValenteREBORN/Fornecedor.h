#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

struct fornecedor{
    char RazaoSocial[21];
    char CNPJ[15];
    char TelefoneFornecedor[20];
    char EmailFornecedor[41];
    char ProdutoFornecido[36];
};
typedef struct fornecedor Fornecedor;

Fornecedor DigitarFornecedor();

void ImprimirFornecedor(Fornecedor F);

void TelaFornecedor();

void MostrarFornecedor(Fornecedor F);

void InterfaceCadastroFornecedor();

Fornecedor PesquisarFornecedor(char razao[21]);

void InterfacePesquisarFornecedor();

void InserirFornecedor(Fornecedor F);

void ListarFornecedor();

void NovoFornecedor();

void AlterarFornecedor(Fornecedor FNovo);

void InterfaceAlterarFornecedor();

void InterfaceExluirFornecedor();

void AbrirFornecedor();

void FecharFornecedor();

#endif // FORNECEDOR_H_INCLUDED
