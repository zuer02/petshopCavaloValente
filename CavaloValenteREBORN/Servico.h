#ifndef SERVICO_H_INCLUDED
#define SERVICO_H_INCLUDED

struct servico{
    char Cliente[51];
    char Animal[21];
    char Tipo[21];
    char Data[11];
    float Preco;
};
typedef struct servico Servico;

void InterfaceServicos();

Servico DigitarServico(Servico S);

void ImprimirServico(Servico S);

void TelaServico();

void MostrarServico(Servico S);

void InterfaceServico();

void InserirServico(Servico S);

void AgendarServico();

void ListarServico();

void AbrirServico();

void FecharServico();

#endif // SERVICO_H_INCLUDED
