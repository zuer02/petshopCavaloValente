#include <stdio.h>
#include <stdlib.h>
#include "Interface.h"
#include "Cliente.h"
#include "Animal.h"
#include "Produto.h"
#include "Servico.h"
#include "Empregado.h"
#include "Fornecedor.h"

int main()
{
    AbrirTudo();
    int Escolha;
    char OpcoesPrincipal[][36] = {"Cadastros", "Listar", "Pesquisar", "Servicos", "Sair"};
    do{
    CAVALO();
    Escolha = MenuHorizontal(OpcoesPrincipal, 5);
    switch(Escolha) {
        case 0:
            InterfaceCadastro();
            break;

        case 1:
            InterfaceListar();
            break;

        case 2:
            InterfacePesquisar();
            break;
        case 3:
            InterfaceServico();
            break;
    }

    }while(Escolha != 4);
    FecharTudo();
    CAVALOADEUS();
    return 0;
}

