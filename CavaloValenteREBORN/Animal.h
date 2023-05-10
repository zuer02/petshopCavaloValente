#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED

struct CadastroAnimal{
    char ReinoAnimal[31];
    char Raca[21];
    char NomeAnimal[36];
    int IdadeAnimal;
};
typedef struct CadastroAnimal Animal;

Animal DigitarAnimal();

void ImprimirAnimal(Animal A);

void TelaAnimal();

void MostrarAnimal(Animal A);

void InterfaceCadastroAnimal();

Animal PesquisarAnimal(char Nome[36]);

void InserirAnimal(Animal A);

void ListarAnimal();

void InterfacePesquisarAnimal();

void NovoAnimal();

void InterfaceAlterarAnimal();

void InterfaceExluirAnimal();

void AlterarAnimal(Animal ANovo);

void AbrirAnimal();

void FecharAnimal();

#endif // ANIMAL_H_INCLUDED
