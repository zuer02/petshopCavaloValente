#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

struct cliente{
    int Codigo;
    char Nome[51];
    char CPF[15];
    char DataNasc[11];
    char Telefone[21];
    char Email[51];
    char CEP[10];
};
typedef struct cliente Cliente;

Cliente DigitarCliente();

void ImprimirCliente(Cliente C);

void InserirCliente(Cliente C);

void TelaCliente();

void MostrarCliente(Cliente C);

void InterfaceCadastroCliente();

void ListarClientes();

Cliente PesquisarCliente(int Codigo);

void InterfacePesquisarCliente();

void AlterarCliente(Cliente CNovo);

void ExcluirCliente(Cliente C);

void NovoCliente();

void InterfaceAlterarCliente();

void InterfaceExluirCliente();

void AbrirCliente();

void FecharCliente();

#endif // CLIENTE_H_INCLUDED
