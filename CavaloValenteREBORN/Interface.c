#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Interface.h"
#include "Cliente.h"
#include "Animal.h"
#include "Produto.h"
#include "Servico.h"
#include "Empregado.h"
#include "Fornecedor.h"

void textcoloreback (int letras, int fundo){
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letras + (fundo << 4));
}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Borda(int x, int y, int largura, int altura, int tipo, int sombra){
    // EsqSup DirSup EsqInf DirInf LHoriz LVertical
    char C[][6] = {"\xda\xbf\xc0\xd9\xc4\xb3" ,
                    "\xc9\xbb\xc8\xbc\xcd\xba"};
    int i, j;
    gotoxy(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][1]);
    for(j = 0; j < altura; j++){
        gotoxy(x, y+j+1); printf("%c", C[tipo][5]);
        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][5]);
        if(sombra) printf("\xb2");
    }
    gotoxy(x, y+altura); printf("%c", C[tipo][2]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][3]);
    if(sombra){
        gotoxy(x+1, y+altura+1);
        for(i = 0; i < largura+2; i++) printf("\xb2");
    }
}

void gtpf(int x, int y, char td[100]){
    gotoxy(x, y);
    printf("%s", td);
}

int MenuHorizontal(char Opcoes[][36], int nOpcoes){
    int i, OpcaoAtual = 0, Tecla;
    gotoxy(23, 6);
    textcoloreback(YELLOW, BLACK);
    printf("%80s", " ");
    gotoxy(23, 6);
    for(i = 0; i < nOpcoes; i++){
        gotoxy(i*13 + 31, 6);printf("%-10s ", Opcoes[i]);
    }
    while(1){
        textcoloreback(BLACK, YELLOW);
        gotoxy((OpcaoAtual * 13 + 31), 6);
        printf("%s", Opcoes[OpcaoAtual]);


        Tecla = getTecla();


        textcoloreback(YELLOW, BLACK);
        gotoxy((OpcaoAtual * 13 + 31), 6);
        printf("%-10s", Opcoes[OpcaoAtual]);


        if(Tecla == TEC_DIR) OpcaoAtual++;
        if(Tecla == TEC_ESQ) OpcaoAtual--;
        if(Tecla == TEC_ENTER) break;
        if(Tecla == TEC_ESC){
            OpcaoAtual = -1;
            break;
        }


        if(OpcaoAtual < 0) OpcaoAtual = nOpcoes - 1;
        if(OpcaoAtual >= nOpcoes) OpcaoAtual = 0;
    }


    textcoloreback(YELLOW, BLACK);


    return OpcaoAtual;
}

int getTecla(){
    int ch;
    ch = getch();
    if(ch == 224){
        ch = getch() + 1000;
    }
    return ch;
}

void CAVALO(){
    Borda(0, 0, 118, 27, 1, 0);
    gtpf(2,1, "   _____,,;;;`;           P E T S H O P");
    gtpf(2,2, ",~(  )  , )~~\\|  ");
    gtpf(2,3, "' / / --`--,      ");
    gtpf(2,4, " /  \\    | '      ");
    gtpf(43, 1, "  ____           \\      /");
    gtpf(43, 2, " /                \\    /");
    gtpf(43, 3, " |                 \\  /");
    gtpf(43, 4, " \\____ A V A L O    \\/  A L E N T E");
    gtpf(102, 1, " ;';;;,,_____");
    gtpf(102, 2, " |/~~( ,  (  )~;");
    gtpf(102, 3, "    .--'-- \\ \\ `");
    gtpf(102, 4, "    ` |    /  \\  ");

}

int EntradaDados(int x, int y, int Tamanho, char Texto[]){
    int Tecla, Pos;
    gotoxy(x, y);
    textcoloreback(BLACK, YELLOW);
    printf("%*s", Tamanho, " ");
    gotoxy(x, y);
    printf("%s", Texto);
    Pos = strlen(Texto);
    do{

        gotoxy(Pos + x, y);
        Tecla = getTecla();
        if(Tecla == TEC_ENTER) break;
        if(Tecla == TEC_ESQ) Pos--;
        if(Tecla == TEC_DIR) Pos++;
        if(Tecla == TEC_CIMA) break;
        if(Tecla == TEC_BAIXO) break;
        if(Tecla == TEC_ESC) break;
        if(Tecla == TEC_BACKSPACE && Pos > 0){
            printf("\x08 \x08");
            Pos--;
        }
        if(Tecla >= ' ' && Tecla < 127){
            if(Pos < Tamanho){
                if(Texto[Pos] == 0) Texto[Pos+1] = 0;
                Texto[Pos++] = Tecla;
                printf("%c", Tecla);
            }
        }
        if(Pos < 0) Pos = 0;
        if(Pos > Tamanho) Pos = Tamanho;
        if(Pos > 0 && Texto[Pos-1] == 0) Pos--;
    } while(1);
    textcoloreback(YELLOW, BLACK);
    return Tecla;
}

int selecaoV (int x, int y, int quant, int salto){
    x-=1;
    int tecla=0, opcaoA = y, ultPos = y+((quant-1)*salto), pos = 0; //salvei a ultima posição pra eu poder dar o loop

    for (int i=y; i<y+((quant)*salto); i+=salto)
        gtpf(x,i," "); //limpando opção antiga

    gotoxy(x, y); printf("\xaf");

    while(1)
    {

        tecla = getTecla();

        if (tecla == TEC_ENTER)
            break;

        gtpf(x, opcaoA, " ");

        if (tecla == TEC_CIMA){
            opcaoA -= salto;
            pos--;
            if (pos<1) pos = quant;
        }
        if (tecla == TEC_BAIXO){
            opcaoA += salto;
            pos++;
            if (pos>quant) pos = 1;
        }
        if (opcaoA < y)
        {
            opcaoA = ultPos;
            pos=quant;
        }
        if (opcaoA > ultPos)
        {
            opcaoA = y;
            pos=0;
        }

        gotoxy(x, opcaoA); printf("\xaf");
    }
    return pos;
}

void InterfaceCadastro(){
    int op;
    do{
    gtpf(5, 8, "Clientes");
    gtpf(5, 9, "Animal");
    gtpf(5, 10, "Produto");
    gtpf(5, 11, "Fornecedor");
    gtpf(5, 12, "Empregado");
    gtpf(5, 13, "Voltar");
    op = selecaoV(5, 8, 6, 1);
    switch(op){
        case 0:
            InterfaceCadastroCliente();
            break;
        case 1:
            InterfaceCadastroAnimal();
            break;
        case 2:
            InterfaceCadastroProduto();
            break;
        case 3:
            InterfaceCadastroFornecedor();
            break;
        case 4:
            InterfaceCadastroEmpregado();
            break;
    }
    }while(op != 5);
}

void InterfacePesquisar(){
    Cliente C;
    Animal A;
    Empregado E;
    Produto P;
    int op;
    do{
    gtpf(8, 10, "Clientes");
    gtpf(8, 11, "Animal");
    gtpf(8, 12, "Produto");
    gtpf(8, 13, "Fornecedor");
    gtpf(8, 14, "Empregado");
    gtpf(8, 15, "Voltar");
    op = selecaoV(8, 10, 6, 1);
    switch(op){
    case 0:
        InterfacePesquisarCliente();
        break;
    case 1:
        InterfacePesquisarAnimal();
        break;
    case 2:
        InterfacePesquisarProduto();
        break;
    case 3:
        InterfacePesquisarFornecedor();
        break;
    case 4:
        InterfacePesquisarEmpregado();
        break;
    }
    }while(op != 5);
}

void InterfaceListar(){
    int op;
    do{
    gtpf(8, 7, "Clientes");
    gtpf(8, 8, "Animal");
    gtpf(8, 9, "Produto");
    gtpf(8, 10, "Fornecedor");
    gtpf(8, 11, "Empregado");
    gtpf(8, 12, "Voltar");
    op = selecaoV(8, 7, 6, 1);
    switch(op){
    case 0:
        ListarClientes();
        break;
    case 1:
        ListarAnimal();
        break;
    case 2:
        ListarProdutos();
        break;
    case 3:
        ListarFornecedor();
        break;
    case 4:
        ListarEmpregados();
        break;
    }
    }while(op != 5);
}

void AbrirTudo(){
    AbrirCliente();
    AbrirAnimal();
    AbrirEmpregado();
    AbrirFornecedor();
    AbrirProduto();
    AbrirServico();
}

void FecharTudo(){
    FecharCliente();
    FecharAnimal();
    FecharEmpregado();
    FecharFornecedor();
    FecharProduto();
    FecharServico();
}

void CAVALOADEUS(){
    gotoxy(25,9); printf ("       ____                      |\\    /|     ");
    gotoxy(25,10); printf ("      /                       ___| \\,,/_/     ");
    gotoxy(25,11); printf ("     /   \\      /          ---__/ \\/   \\     ");
    gotoxy(25,12); printf ("     |    \\    /          __--/     (D)  \\    ");
    gotoxy(25,13); printf ("      \\____\\  /            _ -/    (_    \\   ");
    gotoxy(25,14); printf ("            \\/           // /       \\_ / -\\  ");
    gotoxy(25,15); printf ("   __-------_____--___--/            /\\_O o) ");
    gotoxy(25,16); printf ("  /                                 /  \\__/  ");
    gotoxy(25,17); printf ("||          )                    \\_/\\          ");
    gotoxy(25,18); printf ("||         /              _      /  |         ");
    gotoxy(25,19); printf ("| |      /--______      ___\\    /\\  :         ");
    gotoxy(25,20); printf ("| /   __/    _/   ------    |  |   \\ \\        ");
    gotoxy(25,21); printf (" |   /  |   /                | |     \\ )      ");
    gotoxy(25,22); printf (" |  |   \\  |                 | )     | |      ");
    gotoxy(25,23); printf (" \\  |    | |                 | |    | |       ");
    gotoxy(25,24); printf ("  | |    < |                 | |   |_/        ");
    gotoxy(25,25); printf ("  < |    /__\\                <  \\             ");
    gotoxy(25,26); printf ("  /__\\                       /___\\            ");
    gotoxy(70,17); printf("                C A V A L O");
    gtpf(68, 20, "Agradeço o professor Heveraldo e os demais colegas");
    gtpf(68, 21, "pela ajuda e orientacao.");
    gtpf(68, 23, "Josue Junior, 11 de Junho de 2021");
    gtpf(27, 27, " ");

}
