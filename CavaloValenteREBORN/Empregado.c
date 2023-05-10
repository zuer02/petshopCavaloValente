#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Empregado.h"
#include "Interface.h"

FILE *fpEmpregado;
void AbrirEmpregado(){
    fpEmpregado = fopen("Empregados.txt", "rb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
    if(fpEmpregado == NULL){
        fpEmpregado = fopen("Empregados.txt", "wb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
        if(fpEmpregado == NULL){
            printf("Nao abri Empregados.txt!");
            exit(1);
        }
    }
}
void FecharEmpregado(){
    fclose(fpEmpregado);
}

Empregado Empregados[10];
int QtdeEmpregado=0;

void InserirEmpregado(Empregado E){
    fseek(fpEmpregado, 0, SEEK_END);
    fwrite(&E, sizeof(Empregado), 1, fpEmpregado);
    fflush(fpEmpregado);
}


void ImprimirEmpregado(Empregado E){
    Borda(53, 9, 63, 16, 1, 0);
    gotoxy(54, 10); printf ("Cadastro do funcionario:");
    gotoxy(54, 12); printf ("Codigo: %d", E.codigoE);
    gotoxy(54, 14); printf ("Nome: %s", E.NomeEmpregado);
    gotoxy(54, 15); printf ("CPF: %s", E.CPF);
    gotoxy(54, 16); printf ("Data de Nascimento: %s", E.DatadeNasc);
    gotoxy(54, 18); printf ("Funcao: %s", E.Funcao);
    gotoxy(54, 19); printf ("Formacao: %s", E.Formacao);
    gotoxy(54, 20); printf ("Salario: %f", E.Salario);
    gotoxy(54, 22); printf ("Telefone: %s", E.TelefoneE);
    gotoxy(54, 23); printf ("Email: %s", E.EmailE);
}

Empregado DigitarEmpregado(Empregado E){
    int Tecla, Opcao = 0;
    char Texto1[5], Texto2[8];
    do{
        if(Opcao == 0){
            sprintf(Texto1, "%d", E.codigoE);
            Tecla = EntradaDados(31, 8, 4, Texto1);
            E.codigoE = atoi(Texto1);}
        else if(Opcao == 1)
            Tecla = EntradaDados(30, 10, 50, E.NomeEmpregado);
        else if(Opcao == 2)
            Tecla = EntradaDados(29, 12, 14, E.CPF);
        else if(Opcao == 3)
            Tecla = EntradaDados(62, 12, 10, E.DatadeNasc);
        else if(Opcao == 4)
            Tecla = EntradaDados(32, 14, 20, E.Funcao);
        else if(Opcao == 5)
            Tecla = EntradaDados(34, 16, 35, E.Formacao);
        else if(Opcao == 6)
            Tecla = EntradaDados(34, 18, 20, E.TelefoneE);
        else if(Opcao == 7)
            Tecla = EntradaDados(31, 20, 50, E.EmailE);
        else if(Opcao == 8){
            sprintf(Texto2, "%f", E.Salario);
            Tecla = EntradaDados(35, 22, 10, Texto2);
            E.Salario = atof(Texto2);}
        if(Tecla == TEC_CIMA) Opcao--;
        else if(Opcao == 8 && Tecla == TEC_ENTER) break;
        if(Tecla == TEC_BAIXO || Tecla == TEC_ENTER) Opcao++;
        if(Opcao < 0) Opcao = 8;
        if(Opcao > 8) Opcao = 0;
   }while(Tecla != TEC_ESC);
    return E;
}

void TelaEmpregado(){
    Borda(20, 7, 66, 20, 1, 0);
    gtpf(21, 8, "  Codigo: ");
    gtpf(21, 10, "  Nome: ");
    gtpf(21, 12, "  CPF: ");
    gtpf(41, 12, "  Data de Nascimento: ");
    gtpf(21, 14, "  Funcao: ");
    gtpf(21, 16, "  Formacao: ");
    gtpf(21, 18, "  Telefone: ");
    gtpf(21, 20, "  Email: ");
    gtpf(21, 22, "  Salario: R$");
    gtpf(22, 24, "Inserir");
    gtpf(22, 25, "Voltar");
    gotoxy(40, 26); printf("%d Empregados ao total.", QtdeEmpregado);
}

void MostrarEmpregado(Empregado E){
    textcoloreback(BLACK, YELLOW);
    gotoxy(31, 8); printf("%*s", 4, " ");
    gotoxy(31, 8); printf("%d", E.codigoE);
    gotoxy(30, 10); printf("%*s", 50, " ");
    gotoxy(30, 10); printf("%s", E.NomeEmpregado);
    gotoxy(29, 12); printf("%*s", 14, " ");
    gotoxy(29, 12); printf("%s", E.CPF);
    gotoxy(62, 12); printf("%*s", 10, " ");
    gotoxy(62, 12); printf("%s", E.DatadeNasc);
    gotoxy(32, 14); printf("%*s", 20, " ");
    gotoxy(32, 14); printf("%s", E.Funcao);
    gotoxy(34, 16); printf("%*s", 35, " ");
    gotoxy(34, 16); printf("%s", E.Formacao);
    gotoxy(34, 18); printf("%*s", 20, " ");
    gotoxy(34, 18); printf("%s", E.TelefoneE);
    gotoxy(31, 20); printf("%*s", 50, " ");
    gotoxy(31, 20); printf("%s", E.EmailE);
    gotoxy(35, 22); printf("%*s", 10, " ");
    gotoxy(35, 22); printf("%f", E.Salario);
    textcoloreback(YELLOW, BLACK);
}

void InterfaceCadastroEmpregado(){
    int op;
    gtpf(8, 15, "Novo");
    gtpf(8, 16, "Alterar");
    gtpf(8, 17, "Excluir");
    gtpf(8, 18, "Voltar");
    do{
    op = selecaoV(8, 15, 4, 1);
    switch(op){
        case 0:
            NovoEmpregado();
            break;
        case 1:
            InterfaceAlterarEmpregado();
            break;
        case 2:
            InterfaceExluirEmpregado();
            break;
    }
}while(op != 3);
}

void NovoEmpregado(){
    int op;
    Empregado E;
    do{
        TelaEmpregado();
        E.codigoE = 0;
        strcpy(E.NomeEmpregado, "");
        strcpy(E.CPF, "");
        strcpy(E.DatadeNasc, "");
        strcpy(E.Funcao, "");
        strcpy(E.Formacao, "");
        strcpy(E.TelefoneE, "");
        strcpy(E.EmailE, "");
        E.Salario = 0;
        MostrarEmpregado(E);
        E = DigitarEmpregado(E);
        op = selecaoV(22, 24, 2, 1);
        switch(op){
            case 0:
                InserirEmpregado(E);
                QtdeEmpregado++;
                }
    }while(op != 1);
}

void AlterarEmpregado(Empregado ENovo){
    Empregado E;
    fseek(fpEmpregado, 0, SEEK_SET);  // Posicionar no início
    while(fread(&E, sizeof(Empregado), 1, fpEmpregado)){
        if(E.codigoE == ENovo.codigoE){
            fseek(fpEmpregado, -sizeof(Empregado), SEEK_CUR);
            fwrite(&ENovo, sizeof(Empregado), 1, fpEmpregado);
            fflush(fpEmpregado);
        }
    }
}

void InterfaceAlterarEmpregado(){
    Empregado E;
    int Tecla, op;
    char Texto[5];
    do{
    gtpf(40, 8, "Codigo do Empregado:");
    Texto[0] = 0;
    Tecla = EntradaDados(61, 8, 4, Texto);
    E.codigoE = atoi(Texto);

    E = PesquisarEmpregado(E.codigoE);
    E.codigoE = atoi(Texto);
    TelaEmpregado();
    MostrarEmpregado(E);

    E = DigitarEmpregado(E);

    op = selecaoV(22, 24, 2, 1);
    switch(op){
        case 0:
            AlterarEmpregado(E);
            break;
            }
    }while(TEC_ESC != TEC_ESC || op != 1);

}

void InterfaceExluirEmpregado(){
    Empregado E;
    int Tecla;
    char Texto[5];
    Texto[0] = 0;
    do{
    E.codigoE = 0;
    strcpy(E.NomeEmpregado, "");
    strcpy(E.CPF, "");
    strcpy(E.DatadeNasc, "");
    strcpy(E.Funcao, "");
    strcpy(E.Formacao, "");
    strcpy(E.TelefoneE, "");
    strcpy(E.EmailE, "");
    E.Salario = 0;
    TelaEmpregado();
    MostrarEmpregado(E);
    gtpf(40, 8, "Codigo do Empregado:");
    Texto[0] = 0;
    Tecla = EntradaDados(61, 8, 4, Texto);
    E.codigoE = atoi(Texto);
    E = PesquisarEmpregado(E.codigoE);
    E.codigoE = E.codigoE * (-1);
    MostrarEmpregado(E);

    QtdeEmpregado--;
    gtpf(40, 23, "Empregado demitido. Codigo com numero negativo.");
    }while(TEC_ESC != TEC_ESC);
}

void ListarEmpregados(){
    int i=0, y;
    Empregado E;
    Borda(2, 13, 115, 13, 0, 0);
    gtpf(48, 14, "Data de");
    gtpf(3, 15, "Cod  Nome                      CPF           Nascimento   Funcao        Salario  Telefone        Email");
    fseek(fpEmpregado, 0, SEEK_SET);  // Posicionar no início
    while(fread(&E, sizeof(Empregado), 1, fpEmpregado)){
        y = (16 + i) + 1;
        gotoxy(3, (y)); printf("%d", E.codigoE);
        gotoxy(8, (y)); printf("%s", E.NomeEmpregado);
        gotoxy(34, (y)); printf("%s", E.CPF);
        gotoxy(48, (y)); printf("%s", E.DatadeNasc);
        gotoxy(61, (y)); printf("%s", E.Funcao);
        gotoxy(75, (y)); printf("%.2lf", E.Salario);
        gotoxy(84, (y)); printf("%s", E.TelefoneE);
        gotoxy(100, (y)); printf("%s", E.EmailE);
        i++;
    }
    gotoxy(4, 14); printf(" %d Funcionarios cadastrados!", i);
}

Empregado PesquisarEmpregado(int codigo){
    int i;
    Empregado E;
    fseek(fpEmpregado, 0, SEEK_SET);  // Posicionar no início
    while(fread(&E, sizeof(Empregado), 1, fpEmpregado)){
        if(E.codigoE == codigo){
            return E;
    }
    }
    E.codigoE = 0;
    strcpy(E.NomeEmpregado, "");
    strcpy(E.CPF, "");
    strcpy(E.DatadeNasc, "");
    strcpy(E.Funcao, "");
    strcpy(E.Formacao, "");
    strcpy(E.TelefoneE, "");
    strcpy(E.EmailE, "");
    E.Salario = 0;
    return E;
}

void InterfacePesquisarEmpregado(){
    Empregado E;
    char Texto[21];
    int codigo, Tecla;
    gtpf(8, 16, "Digite o codigo do empregado: ");
    Texto[0] = 0;
    Tecla = EntradaDados(38, 16, 4, Texto);
    codigo = atoi(Texto);
    E = PesquisarEmpregado(codigo);
    ImprimirEmpregado(E);
    if(E.codigoE == 0) gtpf(54, 24, "Empregado demitido ou nao cadastrado.");
}
