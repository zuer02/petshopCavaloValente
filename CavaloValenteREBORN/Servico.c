#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Servico.h"
#include "Interface.h"

FILE *fpServico;
void AbrirServico(){
    fpServico = fopen("Servicos.txt", "rb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
    if(fpServico == NULL){
        fpServico = fopen("Servicos.txt", "wb+"); //  w - um novo arquivo vazio  a - acrescentar ou novo
        if(fpServico == NULL){
            printf("Nao abri Servicos.txt!");
            exit(1);
        }
    }
}
void FecharServico(){
    fclose(fpServico);
}

Servico Servicos[10];
int QtdeServicos = 0;

void InterfaceServico(){
    gtpf(7, 7, "Agendar");
    gtpf(7, 8, "Listar");
    gtpf(7, 9, "Voltar");
    int op;
    do{
    op = selecaoV(7, 7, 3, 1);
    switch(op){
        case 0:
            AgendarServico();
            break;
        case 1:
            ListarServico();
            break;
    }
    }while(op!=2);
}

Servico DigitarServico(Servico S){
    int Tecla, Opcao;
    char Texto[7];
    do{
        if(Opcao == 0)
            Tecla = EntradaDados(30, 11, 50, S.Cliente);
        else if(Opcao == 1)
            Tecla = EntradaDados(29, 13, 20, S.Animal);
        else if(Opcao == 2)
            Tecla = EntradaDados(27, 15, 10, S.Data);
        else if(Opcao == 3)
            Tecla = EntradaDados(27, 17, 20, S.Tipo);
        else if(Opcao == 4){
            Texto[0] = 0;
            sprintf(Texto, "%.2lf", S.Preco);
            Tecla = EntradaDados(31, 19, 6, Texto);
            S.Preco = atof(Texto);}
        if(Tecla == TEC_CIMA) Opcao--;
        else if(Opcao == 4 && Tecla == TEC_ENTER) break;
        if(Tecla == TEC_BAIXO || Tecla == TEC_ENTER) Opcao++;
        if(Opcao < 0) Opcao = 4;
        if(Opcao > 4) Opcao = 0;
   }while(Tecla != TEC_ESC);
    return S;
}

void ImprimirServico(Servico S){
    Borda(20, 10, 66, 17, 1, 0);
    gotoxy(21, 11); printf ("Cliente: %s", S.Cliente);
    gotoxy(21, 13); printf ("Animal: %s", S.Animal);
    gotoxy(21, 15); printf ("Data: %s", S.Data);
    gotoxy(21, 17); printf ("Tipo: %s", S.Tipo);
    gotoxy(21, 19); printf ("Preco: %.2f", S.Preco);
    gotoxy(21, 21); printf(" %d Servicos ao total.", QtdeServicos);
}

void TelaServico(){
    Borda(20, 10, 66, 17, 1, 0);
    gtpf(21, 11, "Cliente: ");
    gtpf(21, 13, "Animal: ");
    gtpf(21, 15, "Data: ");
    gtpf(21, 17, "Tipo: ");
    gtpf(21, 19, "Preco: RS");
    gtpf(22, 21, "Inserir ");
    gtpf(22, 22, "Voltar ");
}

void MostrarServico(Servico S){
    textcoloreback(BLACK, YELLOW);
    gotoxy(30, 11); printf("%*s", 50, " ");
    gotoxy(30, 11); printf("%s", S.Cliente);
    gotoxy(29, 13); printf("%*s", 20, " ");
    gotoxy(29, 13); printf("%s", S.Animal);
    gotoxy(27, 15); printf("%*s", 10, " ");
    gotoxy(27, 15); printf("%s", S.Data);
    gotoxy(27, 17); printf("%*s", 20, " ");
    gotoxy(27, 17); printf("%s", S.Tipo);
    gotoxy(31, 19); printf("%*s", 6, " ");
    gotoxy(31, 19); printf("%.2f", S.Preco);
    textcoloreback(YELLOW, BLACK);
}

void AgendarServico(){
    int op;
    Servico S;
    do{
        TelaServico();
        strcpy(S.Cliente, "");
        strcpy(S.Animal, "");
        strcpy(S.Data, "");
        strcpy(S.Tipo, "");
        S.Preco = 0;
        MostrarServico(S);
        S = DigitarServico(S);
        op = selecaoV(22, 21, 2, 1);
        switch(op){
        case 0:
            InserirServico(S);
            gtpf(45, 22, "Servico inserido.");
            //break;
        }
    }while(op != 1);
}

void InserirServico(Servico S){
    fseek(fpServico, 0, SEEK_END);
    fwrite(&S, sizeof(Servico), 1, fpServico);
    fflush(fpServico);
}

void ListarServico(){
    int i=0, y;
    Servico S;
    Borda(3, 10, 114, 17, 0, 0);
    gotoxy(7, 11);printf("Cliente                Animal              Data       Tipo Servico                   Preco");
    fseek(fpServico, 0, SEEK_SET);  // Posicionar no início
    while(fread(&S, sizeof(Servico), 1, fpServico)){
        y = (11 + i) + 1;
        gotoxy(7, (y)); printf("%s", S.Cliente);
        gotoxy(30, (y)); printf("%s", S.Animal);
        gotoxy(50, (y)); printf("%s", S.Data);
        gotoxy(61, (y)); printf("%s", S.Tipo);
        gotoxy(92, (y)); printf("%.2lf", S.Preco);
        i++;
    }
    gotoxy(21, 10);printf(" %d Servicos cadastrados!", i);
}
