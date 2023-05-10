#ifndef EMPREGADO_H_INCLUDED
#define EMPREGADO_H_INCLUDED

struct empregado{
    int codigoE;
    char NomeEmpregado[51];
    char CPF[15];
    char DatadeNasc[11];
    char Funcao[21];
    char Formacao[36];
    char TelefoneE[21];
    char EmailE[51];
    float Salario;
};
typedef struct empregado Empregado;

Empregado DigitarEmpregado();

void ImprimirEmpregado(Empregado E);

void InserirEmpregado(Empregado E);

void TelaEmpregado();

void MostrarEmpregado(Empregado E);

void InterfaceCadastroEmpregado();

void ListarEmpregados();

Empregado PesquisarEmpregado(int codigo);

void InterfacePesquisarEmpregado();

void InterfaceRelatorioEmpregado();

void NovoEmpregado();

void AlterarEmpregado(Empregado ENovo);

void InterfaceAlterarEmpregado();

void InterfaceExluirEmpregado();

void AbrirEmpregado();

void FecharEmpregado();

#endif // EMPREGADO_H_INCLUDED
