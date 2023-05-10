#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Produto.h"
#include "Interface.h"

FILE *fpProduto;
void AbrirProduto(){
    fpProduto = fopen("Produtos.txt", "rb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
    if(fpProduto == NULL){
        fpProduto = fopen("Produtos.txt", "wb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
        if(fpProduto == NULL){
            printf("Nao abri Produtos.txt!");
            exit(1);
        }
    }
}
void FecharProduto(){
    fclose(fpProduto);
}

Produto Produtos[10];
int QtdeProduto = 0;


Produto DigitarProduto(Produto P){
    int Tecla, Opcao = 0;
    char Texto1[5], Texto2[10];
    do{
        if(Opcao == 0){
            if(P.CodigoP == 0) Texto1[0] = 0;
            else sprintf(Texto1, "%d", P.CodigoP);
            Tecla = EntradaDados(42, 10, 4, Texto1);
            P.CodigoP = atoi(Texto1);
            if(Tecla == TEC_ESC) break;
            P = PesquisarProduto(P.CodigoP);
            P.CodigoP = atoi(Texto1);
            MostrarProduto(P);
        }
        else if(Opcao == 1)
            Tecla = EntradaDados(41, 12, 35, P.NomeProduto);
        else if(Opcao == 2)
            Tecla = EntradaDados(29, 14, 20, P.Tipo);
        else if(Opcao == 3)
            Tecla = EntradaDados(30, 16, 20, P.Marca);
        else if(Opcao == 4){
            sprintf(Texto2, "%f", P.Preco);
            Tecla = EntradaDados(33, 18, 10, Texto2);
            P.Preco = atof(Texto2);}
        else if(Opcao == 5)
            Tecla = EntradaDados(41, 20, 10, P.DataValidade);
        else if(Opcao == 6)
            Tecla = EntradaDados(37, 22, 20, P.Quantidade);
        if(Tecla == TEC_CIMA) Opcao--;
        else if(Opcao == 6 && Tecla == TEC_ENTER) break;
        if(Tecla == TEC_BAIXO || Tecla == TEC_ENTER) Opcao++;
        if(Opcao < 0) Opcao = 6;
        if(Opcao > 6) Opcao = 0;
   }while(Tecla != TEC_ESC);
    return P;
}

void ImprimirProduto(Produto P) {
    Borda(53, 9, 61, 16, 1, 0);
    gotoxy(54, 10); printf ("Codigo: %d\n", P.CodigoP);
    gotoxy(54, 12); printf ("Produto: %s\n", P.NomeProduto);
    gotoxy(54, 14); printf ("Tipo: %s\n", P.Tipo);
    gotoxy(54, 16); printf ("Marca: %s\n", P.Marca);
    gotoxy(54, 18); printf ("Preco: %.2f\n", P.Preco);
    gotoxy(54, 20); printf("Data de validade: %s\n", P.DataValidade);
    gotoxy(54, 22); printf("Quantidade: %s\n", P.Quantidade);
}

void InserirProduto(Produto P){
    fseek(fpProduto, 0, SEEK_END);
    fwrite(&P, sizeof(Produto), 1, fpProduto);
    fflush(fpProduto);
    QtdeProduto++;
}

void TelaProduto(){
    Borda(20, 7, 66, 20, 1, 0);
    gtpf(21, 10, "  Codigo do produto: ");
    gtpf(21, 12, "  Nome do produto: ");
    gtpf(21, 14, "  Tipo: ");
    gtpf(21, 16, "  Marca: ");
    gtpf(21, 18, "  Preco: RS ");
    gtpf(21, 20, "  Data de validade: ");
    gtpf(21, 22, "  Quantidade: ");
    gtpf(22, 24, "Inserir");
    gtpf(22, 25, "Voltar");
}

void MostrarProduto(Produto P){
    textcoloreback(BLACK, YELLOW);
    gotoxy(42, 10); printf("%*s", 4, " ");
    gotoxy(42, 10); printf("%d", P.CodigoP);
    gotoxy(41, 12); printf("%*s", 35, " ");
    gotoxy(41, 12); printf("%s", P.NomeProduto);
    gotoxy(29, 14); printf("%*s", 20, " ");
    gotoxy(29, 14); printf("%s", P.Tipo);
    gotoxy(30, 16); printf("%*s", 20, " ");
    gotoxy(30, 16); printf("%s", P.Marca);
    gotoxy(33, 18); printf("%*s", 7, " ");
    gotoxy(33, 18); printf("%f", P.Preco);
    gotoxy(41, 20); printf("%*s", 10, " ");
    gotoxy(41, 20); printf("%s", P.DataValidade);
    gotoxy(37, 22); printf("%*s", 20, " ");
    gotoxy(37, 22); printf("%s", P.Quantidade);
    textcoloreback(YELLOW, BLACK);
}

void InterfaceCadastroProduto(){
    int op;
    gtpf(8, 15, "Novo");
    gtpf(8, 16, "Alterar");
    gtpf(8, 17, "Excluir");
    gtpf(8, 18, "Voltar");
    do{
    op = selecaoV(8, 15, 4, 1);
    switch(op){
        case 0:
            NovoProduto();
            break;
        case 1:
            InterfaceAlterarProduto();
            break;
        case 2:
            InterfaceExluirProduto();
            break;
    }
}while(op !=3);
}

void NovoProduto(){
    int op;
    Produto P;
    do{
        TelaProduto();
        P.CodigoP = 0;
        strcpy(P.NomeProduto, "");
        strcpy(P.Tipo, "");
        strcpy(P.Marca, "");
        P.Preco = 0;
        strcpy(P.Quantidade, "");
        strcpy(P.DataValidade, "");
        MostrarProduto(P);
        P = DigitarProduto(P);
        op = selecaoV(22, 24, 2, 1);
        switch(op){
            case 0:
                InserirProduto(P);
                QtdeProduto++;
                }
    }while(op != 1);
}

void AlterarProduto(Produto PNovo){
    Produto P;
    fseek(fpProduto, 0, SEEK_SET);  // Posicionar no início
    while(fread(&P, sizeof(Produto), 1, fpProduto)){
        if(P.CodigoP == PNovo.CodigoP){
            fseek(fpProduto, -sizeof(Produto), SEEK_CUR);
            fwrite(&PNovo, sizeof(Produto), 1, fpProduto);
            fflush(fpProduto);
        }
}
}

void InterfaceAlterarProduto(){
    Produto P;
    int Tecla, op;
    char Texto[5];
    do{
    TelaProduto();
    P.CodigoP = 0;
    strcpy(P.NomeProduto, "");
    strcpy(P.Tipo, "");
    strcpy(P.Marca, "");
    P.Preco = 0;
    strcpy(P.Quantidade, "");
    strcpy(P.DataValidade, "");
    MostrarProduto(P);
    gtpf(21, 8, "Codigo do Produto:");
    Texto[0] = 0;
    Tecla = EntradaDados(39, 8, 4, Texto);
    P.CodigoP = atoi(Texto);
    P = PesquisarProduto(P.CodigoP);
    MostrarProduto(P);
    P = DigitarProduto(P);

    op = selecaoV(22, 24, 2, 1);
    switch(op){
        case 0:
            AlterarProduto(P);
            break;
            }
    gotoxy(40, 24); printf("Produto alterado.");
    }while(TEC_ESC != TEC_ESC || op != 1);

}

void InterfaceExluirProduto(){
    Produto P;
    int Tecla;
    char Texto[5];
    do{
    Produto P;
    P.CodigoP = 0;
    strcpy(P.NomeProduto, "");
    strcpy(P.Tipo, "");
    strcpy(P.Marca, "");
    P.Preco = 0;
    strcpy(P.Quantidade, "");
    strcpy(P.DataValidade, "");
    TelaProduto();
    MostrarProduto(P);
    gtpf(21, 8, "Codigo do Produto:");
    Texto[0] = 0;
    Tecla = EntradaDados(39, 8, 4, Texto);
    P.CodigoP = atoi(Texto);
    P = PesquisarProduto(P.CodigoP);
    P.CodigoP = P.CodigoP * (-1);
    strcat(P.NomeProduto, " PRODUTO EXCLUIDO");
    MostrarProduto(P);

    QtdeProduto--;
    gtpf(40, 23, "Produto excluido do sistema.");
    }while(TEC_ESC != TEC_ESC);
}

void ListarProdutos(){
    int i=0, y;
    Produto P;
    Borda(2, 13, 115, 13, 0, 0);
    gtpf(7, 15, "Codigo  Produto            Tipo         Marca          Preco    Validade   Quantidade");
    fseek(fpProduto, 0, SEEK_SET);  // Posicionar no início
    while(fread(&P, sizeof(Produto), 1, fpProduto)){
        y = (16 + i) + 1;
        gotoxy(7, (y)); printf("%d", P.CodigoP);
        gotoxy(15, (y)); printf("%s", P.NomeProduto);
        gotoxy(34, (y)); printf("%s", P.Tipo);
        gotoxy(47, (y)); printf("%s", P.Marca);
        gotoxy(62, (y)); printf("%.2f", P.Preco);
        gotoxy(71, (y)); printf("%s", P.DataValidade);
        gotoxy(82, (y)); printf("%s", P.Quantidade);
        i++;
    }
    gotoxy(7, 14); printf(" %d Produtos cadastrados!", i);
}

Produto PesquisarProduto(int codigo){
    int i;
    Produto P;
    fseek(fpProduto, 0, SEEK_SET);  // Posicionar no início
    while(fread(&P, sizeof(Produto), 1, fpProduto)){
        if(P.CodigoP == codigo){
            return P;
        }
    }
    P.CodigoP = 0;
    strcpy(P.NomeProduto, "");
    strcpy(P.Tipo, "");
    strcpy(P.Marca, "");
    P.Preco = 0;
    strcpy(P.Quantidade, "");
    strcpy(P.DataValidade, "");
    return P;
}


void InterfacePesquisarProduto(){
    Produto P;
    char Texto[21];
    int codigo, Tecla;
    gtpf(8, 16, "Digite o codigo do produto: ");
    Texto[0] = 0;
    Tecla = EntradaDados(36, 16, 4, Texto);
    codigo = atoi(Texto);
    P = PesquisarProduto(codigo);
    ImprimirProduto(P);
    if(P.CodigoP == 0) gtpf(54, 24, "Produto inexistente ou nao cadastrado.");
}
