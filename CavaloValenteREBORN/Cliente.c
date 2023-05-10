#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "Interface.h"

FILE *fpCliente;
void AbrirCliente(){
    fpCliente = fopen("Clientes.txt", "rb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
    if(fpCliente == NULL){
        fpCliente = fopen("Clientes.txt", "wb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
        if(fpCliente == NULL){
            printf("Nao abri Clientes.txt!\n");
            exit(1);
        }
    }
}
void FecharCliente(){
    fclose(fpCliente);
}

Cliente Clientes[10];
int QtdeClientes = 0;

void InserirCliente(Cliente C){
    fseek(fpCliente, 0, SEEK_END);
    fwrite(&C, sizeof(Cliente), 1, fpCliente);
    fflush(fpCliente);
}

void AlterarCliente(Cliente CNovo){
    Cliente C;
    fseek(fpCliente, 0, SEEK_SET);  // Posicionar no início
    while(fread(&C, sizeof(Cliente), 1, fpCliente)){
        if(C.Codigo == CNovo.Codigo){
            fseek(fpCliente, -sizeof(Cliente), SEEK_CUR);
            fwrite(&CNovo, sizeof(Cliente), 1, fpCliente);
            fflush(fpCliente);
        }
    }
}

Cliente DigitarCliente(Cliente C){
    int Tecla, Opcao = 0;
    char Texto[5];
    do{
        if(Opcao == 0){
            sprintf(Texto, "%d", C.Codigo);
            Tecla = EntradaDados(31, 10, 4, Texto);
            C.Codigo = atoi(Texto);}
        else if(Opcao == 1)
            Tecla = EntradaDados(29, 12, 50, C.Nome);
        else if(Opcao == 2)
            Tecla = EntradaDados(28, 14, 14, C.CPF);
        else if(Opcao == 3)
            Tecla = EntradaDados(43, 16, 10, C.DataNasc);
        else if(Opcao == 4)
            Tecla = EntradaDados(33, 18, 20, C.Telefone);
        else if(Opcao == 5)
            Tecla = EntradaDados(30, 20, 50, C.Email);
        else if(Opcao == 6)
            Tecla = EntradaDados(28, 22, 9, C.CEP);
        if(Tecla == TEC_CIMA) Opcao--;
        else if(Opcao == 6 && Tecla == TEC_ENTER) break;
        if(Tecla == TEC_BAIXO || Tecla == TEC_ENTER) Opcao++;
        if(Opcao < 0) Opcao = 6;
        if(Opcao > 6) Opcao = 0;
   }while(Tecla != TEC_ESC);
    return C;
}

void ImprimirCliente(Cliente C){
    Borda(53, 9, 61, 16, 1, 0);
    gotoxy(54, 10); printf ("Codigo: %d\n", C.Codigo);
    gotoxy(54, 12); printf ("Nome: %s\n", C.Nome);
    gotoxy(54, 14); printf ("CPF: %s\n", C.CPF);
    gotoxy(54, 16); printf ("Data de Nascimento: %s\n", C.DataNasc);
    gotoxy(54, 18); printf ("Telefone: %s\n", C.Telefone);
    gotoxy(54, 20); printf ("Email: %s\n", C.Email);
    gotoxy(54, 22); printf ("CEP: %s\n", C.CEP);
}

void TelaCliente(){
    Borda(20, 7, 66, 20, 1, 0);
    gtpf(21, 10, "  Codigo: ");
    gtpf(21, 12, "  Nome: ");
    gtpf(21, 14, "  CPF: ");
    gtpf(21, 16, "  Data de nascimento: ");
    gtpf(21, 18, "  Telefone: ");
    gtpf(21, 20, "  Email: ");
    gtpf(21, 22, "  CEP: ");
    gtpf(22, 24, "  Inserir ");
    gtpf(22, 25, "  Voltar ");
}

void MostrarCliente(Cliente C){
    textcoloreback(BLACK, YELLOW);
    gotoxy(31, 10); printf("%*s", 4, " ");
    gotoxy(31, 10); printf("%d", C.Codigo);
    gotoxy(29, 12); printf("%*s", 50, " ");
    gotoxy(29, 12); printf("%s", C.Nome);
    gotoxy(28, 14); printf("%*s", 14, " ");
    gotoxy(28, 14); printf("%s", C.CPF);
    gotoxy(43, 16); printf("%*s", 10, " ");
    gotoxy(43, 16); printf("%s", C.DataNasc);
    gotoxy(33, 18); printf("%*s", 20, " ");
    gotoxy(33, 18); printf("%s", C.Telefone);
    gotoxy(30, 20); printf("%*s", 50, " ");
    gotoxy(30, 20); printf("%s", C.Email);
    gotoxy(28, 22); printf("%*s", 9, " ");
    gotoxy(28, 22); printf("%s", C.CEP);
    textcoloreback(YELLOW, BLACK);
}

void InterfaceCadastroCliente(){
    int op;
    gtpf(8, 15, "Novo");
    gtpf(8, 16, "Alterar");
    gtpf(8, 17, "Excluir");
    gtpf(8, 18, "Voltar");
    do{
    op = selecaoV(8, 15, 4, 1);
    switch(op){
        case 0:
            NovoCliente();
            break;
        case 1:
            InterfaceAlterarCliente();
            break;
        case 2:
            InterfaceExluirCliente();
            break;
    }
}while(op !=3);
}

void NovoCliente(){
    int op;
    Cliente C;
    do{
        TelaCliente();
        C.Codigo = 0;
        strcpy(C.Nome, "");
        strcpy(C.CPF, "");
        strcpy(C.DataNasc, "");
        strcpy(C.Email, "");
        strcpy(C.CEP, "");
        strcpy(C.Telefone, "");
        MostrarCliente(C);
        C = DigitarCliente(C);
        op = selecaoV(22, 24, 2, 1);
        switch(op){
            case 0:
                InserirCliente(C);
                QtdeClientes++;
                }
    }while(op != 1);
}

void InterfaceAlterarCliente(){
    Cliente C;
    int Tecla, op;
    char Texto[5];
    do{
    gtpf(21, 8, "Codigo do cliente:");
    Texto[0] = 0;
    Tecla = EntradaDados(39, 8, 4, Texto);
    C.Codigo = atoi(Texto);

    C = PesquisarCliente(C.Codigo);
    C.Codigo = atoi(Texto);
    TelaCliente();
    MostrarCliente(C);

    C = DigitarCliente(C);

    op = selecaoV(22, 24, 2, 1);
    switch(op){
        case 0:
            AlterarCliente(C);
            gotoxy(40, 24); printf("Cliente Salvo. %d Clientes ao total.", QtdeClientes);
    }
    }while(TEC_ESC != TEC_ESC || op != 1);
}

void InterfaceExluirCliente(){
    Cliente C;
    int Tecla;
    char Texto[5];
    Texto[0] = 0;
    do{
    C.Codigo = 0;
    strcpy(C.Nome, "");
    strcpy(C.CPF, "");
    strcpy(C.DataNasc, "");
    strcpy(C.Email, "");
    strcpy(C.CEP, "");
    strcpy(C.Telefone, "");
    TelaCliente();
    MostrarCliente(C);
    gtpf(21, 8, "Codigo do cliente:");
    Texto[0] = 0;
    Tecla = EntradaDados(39, 8, 4, Texto);
    C.Codigo = atoi(Texto);
    C = PesquisarCliente(C.Codigo);
    C.Codigo = atoi(Texto);
    C.Codigo = C.Codigo * (-1);
    MostrarCliente(C);

    QtdeClientes--;
    gtpf(40, 23, "Cliente excluido. Codigo com numero negativo.");
    }while(TEC_ESC != TEC_ESC);
}

void ListarClientes(){
    int i=0, y;
    Cliente C;
    Borda(2, 13, 115, 13, 0, 0);
    gtpf(58, 14, "Data de");
    gtpf(7, 15, "Codigo   Nome                       CPF            Nascimento  Telefone        Email                  CEP\n");
    fseek(fpCliente, 0, SEEK_SET);  // Posicionar no início
    while(fread(&C, sizeof(Cliente), 1, fpCliente)){
        y = (15 + i) + 1;
        gotoxy(7, (y)); printf("%d", C.Codigo);
        gotoxy(16, (y)); printf("%s", C.Nome);
        gotoxy(43, (y)); printf("%s", C.CPF);
        gotoxy(58, (y)); printf("%s", C.DataNasc);
        gotoxy(70, (y)); printf("%s", C.Telefone);
        gotoxy(86, (y)); printf("%s", C.Email);
        gotoxy(109, (y)); printf("%s", C.CEP);
        i++;
    }
    gotoxy(7, 14); printf(" %d Clientes cadastrados!\n", i);
}

Cliente PesquisarCliente(int Codigo){
    Cliente C;
    fseek(fpCliente, 0, SEEK_SET);  // Posicionar no início
    while(fread(&C, sizeof(Cliente), 1, fpCliente)){
        if(C.Codigo == Codigo){
            return C;
        }
    }
    C.Codigo = 0;
    strcpy(C.Nome, "");
    strcpy(C.CPF, "");
    strcpy(C.DataNasc, "");
    strcpy(C.Telefone, "");
    strcpy(C.Email, "");
    strcpy(C.CEP, "");
    return C;
}

void InterfacePesquisarCliente(){
    Cliente C;
    char Texto[21];
    int codigoC, Tecla;
    gtpf(8, 16, "Digite o codigo do cliente: ");
    Texto[0] = 0;
    Tecla = EntradaDados(36, 16, 4, Texto);
    codigoC = atoi(Texto);
    C = PesquisarCliente(codigoC);
    ImprimirCliente(C);
    if(C.Codigo == 0) gtpf(54, 23, "Cliente inexistente ou inativo.");
}

