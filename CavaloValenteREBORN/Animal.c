#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Animal.h"
#include "Interface.h"

FILE *fpAnimal;
void AbrirAnimal(){
    fpAnimal = fopen("Animais.txt", "rb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
    if(fpAnimal == NULL){
        fpAnimal = fopen("Animais.txt", "wb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
        if(fpAnimal == NULL){
            printf("Nao abri Animais.txt!");
            exit(1);
        }
    }
}
void FecharAnimal(){
    fclose(fpAnimal);
}


Animal Animais[10];
int QtdeAnimal=0;

Animal DigitarAnimal(Animal A){
    char Texto[4];
    int Tecla, Opcao = 0;
    do{
        if(Opcao == 0)
            Tecla = EntradaDados(31, 10, 30, A.ReinoAnimal);
        else if(Opcao == 1)
            Tecla = EntradaDados(29, 12, 20, A.Raca);
        else if(Opcao == 2)
            Tecla = EntradaDados(39, 14, 35, A.NomeAnimal);
        else if(Opcao == 3){
            sprintf(Texto, "%d", A.IdadeAnimal);
            Tecla = EntradaDados(30, 16, 3, Texto);
            A.IdadeAnimal = atoi(Texto);}
        if(Tecla == TEC_CIMA) Opcao--;
        else if(Opcao == 3 && Tecla == TEC_ENTER) break;
        if(Tecla == TEC_BAIXO || Tecla == TEC_ENTER) Opcao++;
        if(Opcao < 0) Opcao = 3;
        if(Opcao > 3) Opcao = 0;
        if(Opcao == 6 && Tecla == TEC_ENTER) break;
   }while(Tecla != TEC_ESC);
   return A;
}

void TelaAnimal(){
    Borda(20, 7, 66, 20, 1, 0);
    gtpf(21, 10, "  Animal: ");
    gtpf(21, 12, "  Raca: ");
    gtpf(21, 14, "  Nome do animal: ");
    gtpf(21, 16, "  Idade: ");
    gtpf(22, 18, "  Inserir ");
    gtpf(22, 19, "  Voltar ");
}

void MostrarAnimal(Animal A){
    textcoloreback(BLACK, YELLOW);
    gotoxy(31, 10); printf("%*s", 30, " ");
    gotoxy(31, 10); printf("%s", A.ReinoAnimal);
    gotoxy(29, 12); printf("%*s", 20, " ");
    gotoxy(29, 12); printf("%s", A.Raca);
    gotoxy(39, 14); printf("%*s", 35, " ");
    gotoxy(39, 14); printf("%s", A.NomeAnimal);
    gotoxy(30, 16); printf("%*s", 4, " ");
    gotoxy(30, 16); printf("%d", A.IdadeAnimal);
    textcoloreback(YELLOW, BLACK);
}

void InterfaceCadastroAnimal(){
    int op;
    gtpf(8, 15, "Novo");
    gtpf(8, 16, "Alterar");
    gtpf(8, 17, "Excluir");
    gtpf(8, 18, "Voltar");
    do{
    op = selecaoV(8, 15, 4, 1);
    switch(op){
        case 0:
            NovoAnimal();
            break;
        case 1:
            InterfaceAlterarAnimal();
            break;
        case 2:
            InterfaceExluirAnimal();
            break;
    }
}while(op !=3);
}

void NovoAnimal(){
    int op;
    Animal A;
    do{
        TelaAnimal();
        strcpy(A.ReinoAnimal, "");
        strcpy(A.Raca, "");
        strcpy(A.NomeAnimal, "");
        A.IdadeAnimal = 0;
        MostrarAnimal(A);
        A = DigitarAnimal(A);
        op = selecaoV(22, 18, 2, 1);
        switch(op){
            case 0:
                InserirAnimal(A);
                QtdeAnimal++;
                }
    }while(op != 1);
}

void AlterarAnimal(Animal ANovo){
    Animal A;
    fseek(fpAnimal, 0, SEEK_SET);  // Posicionar no início
    while(fread(&A, sizeof(Animal), 1, fpAnimal)){
        if((strcmp(A.NomeAnimal, ANovo.NomeAnimal))==0){
            fseek(fpAnimal, -sizeof(Animal), SEEK_CUR);
            fwrite(&ANovo, sizeof(Animal), 1, fpAnimal);
            fflush(fpAnimal);
        }
    }
}

void InterfaceAlterarAnimal(){
    Animal A;
    int Tecla, op;
    do{
    TelaAnimal();
    strcpy(A.ReinoAnimal, "");
    strcpy(A.Raca, "");
    strcpy(A.NomeAnimal, "");
    A.IdadeAnimal = 0;
    MostrarAnimal(A);
    gtpf(21, 8, "Nome do animal:");
    Tecla = EntradaDados(39, 8, 35, A.NomeAnimal);
    A = PesquisarAnimal(A.NomeAnimal);
    MostrarAnimal(A);
    A = DigitarAnimal(A);

    op = selecaoV(22, 18, 2, 1);
    switch(op){
        case 0:
            AlterarAnimal(A);
            break;
            }
    }while(TEC_ESC != TEC_ESC || op != 1);

}

void InterfaceExluirAnimal(){
    Animal A;
    int Tecla;
    do{
    Animal A;
    strcpy(A.ReinoAnimal, "");
    strcpy(A.Raca, "");
    strcpy(A.NomeAnimal, "");
    A.IdadeAnimal = 0;
    TelaAnimal();
    MostrarAnimal(A);
    gtpf(21, 8, "Nome do animal:");
    Tecla = EntradaDados(39, 8, 35, A.NomeAnimal);
    A = PesquisarAnimal(A.NomeAnimal);
    strcat(A.NomeAnimal, " ANIMAL INATIVO");
    MostrarAnimal(A);

    QtdeAnimal--;
    gtpf(40, 23, "Animal excluido do sistema.");
    }while(TEC_ESC != TEC_ESC);
}

void ImprimirAnimal(Animal A) {
    Borda(53, 9, 61, 16, 1, 0);
    gotoxy(54, 10); printf ("Cadastro do animal: ");
    gotoxy(54, 12); printf ("Animal: %s", A.ReinoAnimal);
    gotoxy(54, 14); printf ("Raca: %s", A.Raca);
    gotoxy(54, 16); printf ("Nome: %s", A.NomeAnimal);
    gotoxy(54, 18); printf ("Idade: %d", A.IdadeAnimal);
}

void InserirAnimal(Animal A){
    fseek(fpAnimal, 0, SEEK_END);
    fwrite(&A, sizeof(Animal), 1, fpAnimal);
    fflush(fpAnimal);
}

void ListarAnimal(){
    int i=0, y;
    Animal A;
    Borda(2, 13, 115, 13, 0, 0);
    gtpf(7, 15, "Animal               Raca            Nome                      Idade\n");
    fseek(fpAnimal, 0, SEEK_SET);  // Posicionar no início
    while(fread(&A, sizeof(Animal), 1, fpAnimal)){
        y = (16 + i) + 1;
        gotoxy(7, (y)); printf("%s", A.ReinoAnimal);
        gotoxy(28, (y)); printf("%s", A.Raca);
        gotoxy(44, (y)); printf("%s", A.NomeAnimal);
        gotoxy(70, (y)); printf("%d", A.IdadeAnimal);
        i++;
    }
    gotoxy(7, 14); printf("%d Animais cadastrados!", i);
}

Animal PesquisarAnimal(char Nome[36]){
    Animal A;
    fseek(fpAnimal, 0, SEEK_SET);  // Posicionar no início
    while(fread(&A, sizeof(Animal), 1, fpAnimal)){
        if((strcmp(A.NomeAnimal, Nome)) == 0){
            return A;
    }
    }
    strcpy(A.ReinoAnimal, "");
    A.IdadeAnimal = 0;
    strcpy(A.NomeAnimal, "");
    strcpy(A.Raca, "");
    return A;
}


void InterfacePesquisarAnimal(){
    Animal A;
    int Tecla;
    char Nome[36];
    gtpf(8, 16, "Digite o nome do animal:");
    Tecla = EntradaDados(32, 16, 19, Nome);
    A = PesquisarAnimal(Nome);
    ImprimirAnimal(A);
    if(A.IdadeAnimal == 0) gtpf(54, 22, "Animal nao cadastrado ou inativo.");
}
