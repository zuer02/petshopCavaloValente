#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Fornecedor.h"
#include "Interface.h"

FILE *fpFornecedor;
void AbrirFornecedor(){
    fpFornecedor = fopen("Fornecedores.txt", "rb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
    if(fpFornecedor == NULL){
        fpFornecedor = fopen("Fornecedores.txt", "wb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
        if(fpFornecedor == NULL){
            printf("Nao abri Fornecedores.txt!\n");
            exit(1);
        }
    }
}
void FecharFornecedor(){
    fclose(fpFornecedor);
}

Fornecedor Fornecedores[10];
int QtdeFornecedor = 0;

Fornecedor DigitarFornecedor(Fornecedor F){
    int Tecla, Opcao = 0;
    do{
        if(Opcao == 0)
            Tecla = EntradaDados(37, 10, 20, F.RazaoSocial);
        else if(Opcao == 1)
            Tecla = EntradaDados(58, 12, 14, F.CNPJ);
        else if(Opcao == 2)
            Tecla = EntradaDados(33, 14, 19, F.TelefoneFornecedor);
        else if(Opcao == 3)
            Tecla = EntradaDados(30, 16, 40, F.EmailFornecedor);
        else if(Opcao == 4)
            Tecla = EntradaDados(42, 18, 35, F.ProdutoFornecido);
        if(Tecla == TEC_CIMA) Opcao--;
        else if(Opcao == 4 && Tecla == TEC_ENTER) break;
        if(Tecla == TEC_BAIXO || Tecla == TEC_ENTER) Opcao++;
        if(Opcao < 0) Opcao = 4;
        if(Opcao > 4) Opcao = 0;
   }while(Tecla != TEC_ESC);
    return F;
};

void ImprimirFornecedor(Fornecedor F) {
    Borda(53, 9, 63, 16, 1, 0);
    gotoxy(54, 10); printf ("Cadastro do fornecedor:");
    gotoxy(54, 12); printf ("Fornecedor: %s", F.RazaoSocial);
    gotoxy(54, 14); printf ("CNPJ: %s", F.CNPJ);
    gotoxy(54, 16); printf ("Telefone: %s", F.TelefoneFornecedor);
    gotoxy(54, 18); printf ("Email: %s", F.EmailFornecedor);
    gotoxy(54, 20); printf("Produto fornecido: %s", F.ProdutoFornecido);
}

void InserirFornecedor(Fornecedor F){
    fseek(fpFornecedor, 0, SEEK_END);
    fwrite(&F, sizeof(Fornecedor), 1, fpFornecedor);
    fflush(fpFornecedor);
}

void TelaFornecedor(){
    Borda(20, 7, 66, 20, 1, 0);
    gtpf(21, 10, "  Razao Social: ");
    gtpf(21, 12, "  CNPJ(ou CPF se for pessoa fisica): ");
    gtpf(21, 14, "  Telefone: ");
    gtpf(21, 16, "  Email: ");
    gtpf(21, 18, "  Produto fornecido: ");
    gtpf(22, 20, "Inserir");
    gtpf(22, 21, "Voltar");
}

void MostrarFornecedor(Fornecedor F){
    textcoloreback(BLACK, YELLOW);
    gotoxy(37, 10); printf("%*s", 20, " ");
    gotoxy(37, 10); printf("%s", F.RazaoSocial);
    gotoxy(58, 12); printf("%*s", 14, " ");
    gotoxy(58, 12); printf("%s", F.CNPJ);
    gotoxy(33, 14); printf("%*s", 19, " ");
    gotoxy(33, 14); printf("%s", F.TelefoneFornecedor);
    gotoxy(30, 16); printf("%*s", 40, " ");
    gotoxy(30, 16); printf("%s", F.EmailFornecedor);
    gotoxy(42, 18); printf("%*s", 35, " ");
    gotoxy(42, 18); printf("%s", F.ProdutoFornecido);
    textcoloreback(YELLOW, BLACK);
}

void InterfaceCadastroFornecedor(){
    int op;
    gtpf(8, 15, "Novo");
    gtpf(8, 16, "Alterar");
    gtpf(8, 17, "Excluir");
    gtpf(8, 18, "Voltar");
    do{
    op = selecaoV(8, 15, 4, 1);
    switch(op){
        case 0:
            NovoFornecedor();
            break;
        case 1:
            InterfaceAlterarFornecedor();
            break;
        case 2:
            InterfaceExluirFornecedor();
            break;
    }
}while(op !=3);
}

void NovoFornecedor(){
    int op;
    Fornecedor F;
    do{
        TelaFornecedor();
        strcpy(F.RazaoSocial, "");
        strcpy(F.CNPJ, "");
        strcpy(F.TelefoneFornecedor, "");
        strcpy(F.EmailFornecedor, "");
        strcpy(F.ProdutoFornecido, "");
        MostrarFornecedor(F);
        F = DigitarFornecedor(F);
        op = selecaoV(22, 20, 2, 1);
        switch(op){
            case 0:
                InserirFornecedor(F);
                QtdeFornecedor++;
                }
    }while(op != 1);
}

void AlterarFornecedor(Fornecedor FNovo){
    Fornecedor F;
    fseek(fpFornecedor, 0, SEEK_SET);  // Posicionar no início
    while(fread(&F, sizeof(Fornecedor), 1, fpFornecedor)){
        if((strcmp(F.RazaoSocial, FNovo.RazaoSocial))==0){
            fseek(fpFornecedor, -sizeof(Fornecedor), SEEK_CUR);
            fwrite(&FNovo, sizeof(Fornecedor), 1, fpFornecedor);
            fflush(fpFornecedor);
        }
    }
}

void InterfaceAlterarFornecedor(){
    Fornecedor F;
    int Tecla, op;
    do{
    TelaFornecedor();
    strcpy(F.RazaoSocial, "");
    strcpy(F.CNPJ, "");
    strcpy(F.TelefoneFornecedor, "");
    strcpy(F.EmailFornecedor, "");
    strcpy(F.ProdutoFornecido, "");
    MostrarFornecedor(F);
    gtpf(21, 8, "Razao Social do Fornecedor:");
    Tecla = EntradaDados(48, 8, 35, F.RazaoSocial);
    F = PesquisarFornecedor(F.RazaoSocial);
    MostrarFornecedor(F);
    F = DigitarFornecedor(F);

    op = selecaoV(22, 20, 2, 1);
    switch(op){
        case 0:
            AlterarFornecedor(F);
            break;
            }
            gotoxy(40, 24); printf("Fornecedor alterado.");
    }while(TEC_ESC != TEC_ESC || op != 1);

}

void InterfaceExluirFornecedor(){
    Fornecedor F;
    int Tecla;
    do{
    Fornecedor F;
    strcpy(F.RazaoSocial, "");
    strcpy(F.CNPJ, "");
    strcpy(F.TelefoneFornecedor, "");
    strcpy(F.EmailFornecedor, "");
    strcpy(F.ProdutoFornecido, "");
    TelaFornecedor();
    MostrarFornecedor(F);
    gtpf(21, 8, "Razao social do Fornecedor:");
    Tecla = EntradaDados(48, 8, 35, F.RazaoSocial);
    F = PesquisarFornecedor(F.RazaoSocial);
    strcat(F.RazaoSocial, " FORNECEDOR INATIVO");
    MostrarFornecedor(F);

    QtdeFornecedor--;
    gtpf(40, 23, "Fornecedor excluido do sistema.");
    }while(TEC_ESC != TEC_ESC);
}

void ListarFornecedor(){
    int i=0, y;
    Fornecedor F;
    Borda(2, 13, 115, 13, 0, 0);
    gtpf(7, 15, "Razao Social    CNPJ ou CPF    Telefone       Email                  Produto Fornecido");
    fseek(fpFornecedor, 0, SEEK_SET);  // Posicionar no início
    while(fread(&F, sizeof(Fornecedor), 1, fpFornecedor)){
        y = (16 + i) + 1;
        gotoxy(7, (y)); printf("%s", F.RazaoSocial);
        gotoxy(22, (y)); printf("%s", F.CNPJ);
        gotoxy(37, (y)); printf("%s", F.TelefoneFornecedor);
        gotoxy(52, (y)); printf("%s", F.EmailFornecedor);
        gotoxy(75, (y)); printf("%s", F.ProdutoFornecido);
        i++;
    }
    gotoxy(7, 14);printf(" %d Fornecedores cadastrados!", i);
}

Fornecedor PesquisarFornecedor(char razao[21]){
    int i;
    Fornecedor F;
    fseek(fpFornecedor, 0, SEEK_SET);  // Posicionar no início
    while(fread(&F, sizeof(Fornecedor), 1, fpFornecedor)){
        if((strcmp(F.RazaoSocial, razao)) == 0) return F;
    }
    strcpy(F.RazaoSocial, "");
    strcpy(F.CNPJ, "");
    strcpy(F.TelefoneFornecedor, "");
    strcpy(F.EmailFornecedor, "");
    strcpy(F.ProdutoFornecido, "");
    return F;
}

void InterfacePesquisarFornecedor(){
    Fornecedor F;
    int Tecla;
    gtpf(8, 16, "Digite a razao social:");
    Tecla = EntradaDados(30, 16, 19, F.RazaoSocial);
    F = PesquisarFornecedor(F.RazaoSocial);
    ImprimirFornecedor(F);
    if(strcmp(F.RazaoSocial, F.EmailFornecedor)==0) gtpf(54, 24, "Fornecedor inexistente ou nao cadastrado.");
}
