#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h> // Utilizado para usar teclas do teclado na seleção de opcões
#include "ListaEncad.h"

#define ANSI_COLOR_RED "\x1b[31m"     // Cor: Vermelho
#define ANSI_COLOR_GREEN "\x1b[32m"   // Cor: Verde
#define ANSI_COLOR_YELLOW "\x1b[33m"  // Cor: Amarelo
#define ANSI_COLOR_BLUE "\x1b[34m"    // Cor: Azul
#define ANSI_COLOR_MAGENTA "\x1b[35m" // Cor: Magenta
#define ANSI_COLOR_CYAN "\x1b[36m"    // Cor: Ciano
#define ANSI_COLOR_RESET "\x1b[0m"    // Cor: Padrão

void print_logo();
void imprimelento(char *p, int N);
void mostrar_conta_cliente(lista_clientes *l, cadastro it);
void mostrar_carrinho(lista_clientes *l, cadastro it);
void mostrar_comprados(lista_clientes *l, cadastro it);
void mostrar_produtos(lista_produtos *l);
void mostra_produtos_vendedor(vendedor v);
void mostrar_conta_vendedor(vendedor v);
void mostrar_relatorio(lista_produtos *l);

int main()
{
    int opcao, opcao2, opcao3, categoria, num, pos, qtd, ret, sair, i = 0, indice;
    char tecla, *pesquisa = (char *)malloc(30 * sizeof(char));
    char *senha = (char *)malloc(30 * sizeof(char));       // Usado para verificar a senha do it.senha
    lista_clientes *l = ler_clientes();                    // Lista dos Clientes
    lista_vendedores *l_vendedores = lerListaVendedores(); // Lista dos Vendedores
    cadastro it;
    no_clientes *c;
    vendedor v;
    produtos p;                                             // Necessario uma função que retorna um produto de uma lista de produtos;
    lista_produtos *retorno_lista = criar_lista_produtos(); // Lista temporaria de produtos para printar
    lista_produtos *retorno_lista2 = criar_lista_produtos();
    lista_produtos *relatorio = criar_lista_produtos();

    // Necessario para salvar os 5 produtos iniciais, se usarmos as op. de pesquisa de produtos perderemos esses 5 pordutos (utilizar outra lista)

    /*    -----      DECLARAÇÕES    ----   */

    do
    {
        system("cls");
        print_logo();
        printf(ANSI_COLOR_YELLOW);
        printf("\n      Bem-vindo a Powerful Machine - Sua Loja de Eletronicos de Excelencia\n");
        printf("\n                             -- O QUE DESEJA FAZER? --\n\n");
        printf(ANSI_COLOR_RESET);
        printf("                                1- Cadastrar/Login \n");
        printf("                                2- Sobre a Loja\n");
        printf("                                0- Sair\n\n");
        printf(ANSI_COLOR_YELLOW);
        printf("                               DIGITE SUA OPCAO:");
        printf(ANSI_COLOR_RESET);
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            /* CADASTRAR/LOGAR */
            do
            {
                system("cls");
                print_logo();
                printf(ANSI_COLOR_YELLOW);
                printf("\n                             -- O QUE DESEJA FAZER? --\n\n");
                printf(ANSI_COLOR_RESET);
                printf("                             1- Cadastrar como Cliente\n");
                printf("                             2- Cadastrar como Vendedor\n");
                printf("                             3- Login como Cliente\n");
                printf("                             4- Login como Vendedor\n");
                printf("                             0- Voltar\n\n");
                printf(ANSI_COLOR_YELLOW);
                printf("                             DIGITE SUA OPCAO:");
                printf(ANSI_COLOR_RESET);
                setbuf(stdin, NULL);
                scanf("%d", &opcao2);
                if (opcao2 == 1 || opcao2 == 3) // Login e Cadastro de Cliente
                {
                    num = 3;
                    do
                    {
                        system("cls");
                        print_logo();
                        printf("\n                                                                (Tentativas: ");
                        printf(ANSI_COLOR_CYAN);
                        printf("%d", num);
                        printf(ANSI_COLOR_RESET);
                        printf(")");
                        printf(ANSI_COLOR_YELLOW);
                        printf("\n\n                            --- Digite seus DADOS ---\n\n");
                        printf(ANSI_COLOR_RESET);
                        printf("                              Digite seu nome:");
                        setbuf(stdin, NULL);
                        printf(ANSI_COLOR_YELLOW);
                        fgets(it.nome, 30, stdin);
                        printf(ANSI_COLOR_RESET);
                        it.nome[strcspn(it.nome, "\n")] = '\0'; // Remove o \n da string
                        printf("                              Digite sua senha:");
                        setbuf(stdin, NULL);
                        printf(ANSI_COLOR_YELLOW);
                        fgets(it.senha, 10, stdin);
                        printf(ANSI_COLOR_RESET);
                        it.senha[strcspn(it.senha, "\n")] = '\0';
                        ret = verifica_cliente(l, it);
                        if (ret == 0 && opcao2 == 1)
                        {
                            printf(ANSI_COLOR_RED);
                            printf("\n                           NOME JA EXISTE, TENTE OUTRO!\n");
                            printf(ANSI_COLOR_RESET);
                            Sleep(1000);
                            num--;
                            if (num == 0)
                            {
                                break;
                            }
                        }
                        if (opcao2 == 3 && (ret == 2 || ret == 1 || ret == 3))
                        {
                            printf(ANSI_COLOR_RED);
                            printf("\n                       NOME DE USUARIO OU SENHA INCORRETOS!\n");
                            printf(ANSI_COLOR_RESET);
                            Sleep(1000);
                            num--;
                            if (num == 0)
                            {
                                break;
                            }
                        }
                    } while ((opcao2 == 1 && ret == 0) || (opcao2 == 3 && (ret == 2 || ret == 1 || ret == 3)));
                    if (num == 0)
                    {
                        opcao = 10;
                        opcao2 = 0;
                        opcao3 = 0;
                        break;
                    }
                    if (opcao2 == 1)
                    {
                        insere_novo_cliente(l, it);
                        printf(ANSI_COLOR_YELLOW);
                        printf("\n");
                        printf("                                   ");
                        imprimelento("SALVANDO...", 200);
                        printf(ANSI_COLOR_RESET);
                    }
                    if (opcao2 == 3)
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("\n");
                        printf("                                  ");
                        imprimelento("CARREGANDO...", 200);
                        printf(ANSI_COLOR_RESET);
                    }
                    do
                    {
                        system("cls");
                        print_logo();
                        printf("\n");
                        printf("                                BEM VINDO, ");
                        printf(ANSI_COLOR_YELLOW);
                        printf("%s!\n\n", it.nome);
                        printf(ANSI_COLOR_RESET);
                        c = buscar_cliente(l, it);
                        zerar_produtos(retorno_lista);
                        if (retorna_5_produtos(l_vendedores, l, it, retorno_lista) == 0)
                            mostrar_produtos(retorno_lista);
                        else
                        {
                            printf(ANSI_COLOR_YELLOW);
                            printf("             NAO FOI ENCONTRADO NENHUM PRODUTO NA LOJA, SINTO MUITO! :(\n");
                            printf(ANSI_COLOR_RESET);
                        }
                        printf(ANSI_COLOR_YELLOW);
                        printf("\n                            -- O QUE DESEJA FAZER? --\n\n");
                        printf(ANSI_COLOR_RESET);
                        printf("                           1- Procurar  por  um  Produto\n");
                        printf("                           2- Adicionar Produto ao Carrinho\n");
                        printf("                           3- Ver Carrinho  de  Compras\n");
                        printf("                           4- Ver Historico  de  Compras\n");
                        printf("                           5- Acessar  Opcoes  da  Conta\n");
                        printf("                           0- Voltar  para  o  MENU Inicial\n\n");
                        printf(ANSI_COLOR_YELLOW);
                        printf("                               DIGITE SUA OPCAO:");
                        printf(ANSI_COLOR_RESET);
                        setbuf(stdin, NULL);
                        scanf("%d", &opcao3);
                        switch (opcao3)
                        {
                        case 1: // procurar produto
                            system("cls");
                            print_logo();
                            printf(ANSI_COLOR_YELLOW);
                            printf("\n                            -- O QUE DESEJA FAZER? --\n\n");
                            printf(ANSI_COLOR_RESET);
                            printf("                             1- Procurar por NOME\n");
                            printf("                             2- Procurar por CATEGORIA\n");
                            printf("                             0- Voltar\n\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("                               DIGITE SUA OPCAO:");
                            printf(ANSI_COLOR_RESET);
                            setbuf(stdin, NULL);
                            scanf("%d", &opcao2);
                            switch (opcao2)
                            {
                            case 1: // por nome
                                system("cls");
                                print_logo();
                                printf("\n                            Digite o nome do Produto:");
                                printf(ANSI_COLOR_YELLOW);
                                setbuf(stdin, NULL);
                                fgets(pesquisa, 30, stdin);
                                pesquisa[strlen(pesquisa) - 1] = '\0';
                                printf("\n                            Pesquisando por %s", pesquisa);
                                i = 3;
                                while (i > 0)
                                {
                                    imprimelento("...", 500);
                                    printf("\b\b\b   \b\b\b");
                                    i--;
                                }
                                printf(ANSI_COLOR_RESET);
                                produtos_de_nome(l_vendedores, pesquisa, retorno_lista2);
                                sair = 0;
                                if (listaVazia_produtos(retorno_lista2) != 0)
                                {
                                    do
                                    {
                                        system("cls");
                                        print_logo();
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("\n                         Produtos encontrados para %s:\n\n", pesquisa);
                                        printf(ANSI_COLOR_RESET);
                                        mostrar_produtos(retorno_lista2);
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("\n\n          Pressione Enter para Adicionar Produtos ou Esc para Voltar...\n\n");
                                        printf(ANSI_COLOR_RESET);
                                        while (1)
                                        {

                                            if (_kbhit())
                                            {
                                                tecla = _getch();
                                                if (tecla == 13)
                                                { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                                    do
                                                    {
                                                        printf("                      Digite o qual Produto deseja Adicionar:");
                                                        printf(ANSI_COLOR_YELLOW);
                                                        setbuf(stdin, NULL);
                                                        scanf("%d", &num);
                                                        printf(ANSI_COLOR_RESET);
                                                        printf("\n");
                                                    } while (num > tamanho_lista_produtos(retorno_lista2) || num < 0);
                                                    do
                                                    {
                                                        printf("                               Digite a Quantidade:");
                                                        printf(ANSI_COLOR_YELLOW);
                                                        setbuf(stdin, NULL);
                                                        scanf("%d", &qtd);
                                                        printf(ANSI_COLOR_RESET);
                                                        printf("\n");
                                                    } while (qtd <= 0);
                                                    ret = compra_produto(l, l_vendedores, retorno_lista2, it, qtd, num, &p);
                                                    if (ret == 0)
                                                    {
                                                        insere_novo_carrinho(l, it, p);
                                                        printf(ANSI_COLOR_YELLOW);
                                                        printf("                             ");
                                                        imprimelento("Adicionando ao Carrinho...\n\n", 200);
                                                        printf(ANSI_COLOR_RESET);
                                                    }
                                                    else
                                                    {
                                                        printf(ANSI_COLOR_RED);
                                                        printf("                      NAO FOI POSSIVEL ADICIONAR AO CARRINHO\n\n");
                                                        printf(ANSI_COLOR_RESET);
                                                        system("pause");
                                                    }
                                                    break;
                                                }
                                                if (tecla == 27)
                                                { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                                                    sair = 1;
                                                    break;
                                                }
                                            }
                                        }
                                    } while (sair != 1);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_RED);
                                    printf("\n\n                        NENHUM PRODUTO FOI ENCONTRADO :(\n\n");
                                    printf(ANSI_COLOR_RESET);
                                    system("pause");
                                    break;
                                }
                                zerar_produtos(retorno_lista2);
                                break;
                            case 2: // por categoria
                                system("cls");
                                print_logo();
                                printf("\n");
                                printf(ANSI_COLOR_YELLOW);
                                printf("\n                          ---- Escolha um CATEGORIA ----\n\n");
                                printf(ANSI_COLOR_RESET);
                                printf("1-  Celulares e Telefones     2-  Acessorios para PC      3-  Componentes para PC\n");
                                printf("4-  Perifericos para PC       5-  Software                6-  Cabos e Hubs USB\n");
                                printf("7-  Monitores e Telas         8-  Pilhas e Carregadores   9-  Acessorios em Geral\n");
                                printf("10- Componentes Eletronicos  11-  Controles Remotos      12-  Outros\n\n");
                                printf(ANSI_COLOR_YELLOW);
                                printf("                                DIGITE SUA OPCAO:");
                                printf(ANSI_COLOR_RESET);
                                setbuf(stdin, NULL);
                                scanf("%d", &categoria);                               
                                // FUNÇÃO QUE RETORNA TODOS OS PRODUTOS DE CATEGORIA X
                                produtos_de_categoria(l_vendedores, categoria, retorno_lista2);
                                printf(ANSI_COLOR_YELLOW);
                                printf("\n                        Pesquisando pela Categoria %d", categoria);
                                i = 3;
                                while (i > 0)
                                {
                                    imprimelento("...", 200);
                                    printf("\b\b\b   \b\b\b");
                                    i--;
                                }
                                printf(ANSI_COLOR_RESET);
                                sair = 0;
                                if (listaVazia_produtos(retorno_lista2) != 0)
                                {
                                    do
                                    {
                                        system("cls");
                                        print_logo();
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("\n\n                     Produtos encontrados para Categoria %d:\n\n", categoria);
                                        printf(ANSI_COLOR_RESET);
                                        mostrar_produtos(retorno_lista2);
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("\n\n          Pressione Enter para Adicionar Produtos ou Esc para Voltar...\n\n");
                                        printf(ANSI_COLOR_RESET);
                                        while (1)
                                        {
                                            if (_kbhit())
                                            {
                                                tecla = _getch();
                                                if (tecla == 13)
                                                { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                                    do
                                                    {
                                                        printf("                      Digite o qual Produto deseja Adicionar:");
                                                        printf(ANSI_COLOR_YELLOW);
                                                        setbuf(stdin, NULL);
                                                        scanf("%d", &num);
                                                        printf(ANSI_COLOR_RESET);
                                                        printf("\n");
                                                    } while (num > tamanho_lista_produtos(retorno_lista2) || num < 0);
                                                    do
                                                    {
                                                        printf("                               Digite a Quantidade:");
                                                        printf(ANSI_COLOR_YELLOW);
                                                        setbuf(stdin, NULL);
                                                        scanf("%d", &qtd);
                                                        printf(ANSI_COLOR_RESET);
                                                        printf("\n");
                                                    } while (qtd <= 0);
                                                    ret = compra_produto(l, l_vendedores, retorno_lista2, it, qtd, num, &p);
                                                    if (ret == 0)
                                                    {
                                                        insere_novo_carrinho(l, it, p);
                                                        printf(ANSI_COLOR_YELLOW);
                                                        printf("                             ");
                                                        imprimelento("Adicionando ao Carrinho...\n\n", 200);
                                                        printf(ANSI_COLOR_RESET);
                                                    }
                                                    else
                                                    {
                                                        printf(ANSI_COLOR_RED);
                                                        printf("                      NAO FOI POSSIVEL ADICIONAR AO CARRINHO\n\n");
                                                        printf(ANSI_COLOR_RESET);
                                                        system("pause");
                                                    }
                                                    break;
                                                }
                                                if (tecla == 27)
                                                { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                                                    sair = 1;
                                                    break;
                                                }
                                            }
                                        }
                                    } while (sair != 1);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_RED);
                                    printf("\n\n                        NENHUM PRODUTO FOI ENCONTRADO :(\n\n");
                                    printf(ANSI_COLOR_RESET);
                                    system("pause");
                                    break;
                                }
                                zerar_produtos(retorno_lista2);
                                break;
                            default:
                                break;
                            }
                            break;
                        case 2: // Adicionar no carrinho
                            do
                            {
                                system("cls");
                                print_logo();
                                mostrar_produtos(retorno_lista); // Mostra a lista do 5 produtos iniciais
                                if (listaVazia_produtos(retorno_lista) != 0)
                                {
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("\n\n          Pressione Enter para Adicionar Produtos ou Esc para Voltar...\n");
                                    printf(ANSI_COLOR_RESET);
                                    while (1)
                                    {
                                        if (_kbhit())
                                        {
                                            tecla = _getch();
                                            if (tecla == 13)
                                            { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                                do
                                                {
                                                    printf("\n                      Digite o qual Produto deseja Adicionar:");
                                                    printf(ANSI_COLOR_YELLOW);
                                                    setbuf(stdin, NULL);
                                                    scanf("%d", &num);
                                                    printf(ANSI_COLOR_RESET);
                                                    printf("\n");
                                                } while (num > tamanho_lista_produtos(retorno_lista) - 1 || num < 0);
                                                do
                                                {
                                                    printf("                               Digite a Quantidade:");
                                                    printf(ANSI_COLOR_YELLOW);
                                                    setbuf(stdin, NULL);
                                                    scanf("%d", &qtd);
                                                    printf(ANSI_COLOR_RESET);
                                                    printf("\n");
                                                } while (qtd <= 0);
                                                ret = compra_produto(l, l_vendedores, retorno_lista, it, qtd, num, &p);
                                                if (ret == 0)
                                                {
                                                    insere_novo_carrinho(l, it, p);
                                                    printf(ANSI_COLOR_YELLOW);
                                                    printf("                             ");
                                                    imprimelento("Adicionando ao Carrinho...\n\n", 200);
                                                    printf(ANSI_COLOR_RESET);
                                                }
                                                else
                                                {
                                                    printf(ANSI_COLOR_RED);
                                                    printf("                      NAO FOI POSSIVEL ADICIONAR AO CARRINHO\n\n");
                                                    printf(ANSI_COLOR_RESET);
                                                    system("pause");
                                                }
                                                break;
                                            }
                                            if (tecla == 27)
                                            { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                                                sair = 1;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    printf(ANSI_COLOR_RED);
                                    printf("\n\n                        NENHUM PRODUTO FOI ENCONTRADO :(\n\n");
                                    printf(ANSI_COLOR_RESET);
                                    system("pause");
                                    break;
                                }
                            } while (sair != 1);
                            break;
                        case 3: // Ver carrinho
                            do
                            {
                                system("cls");
                                print_logo();
                                mostrar_carrinho(l, it);
                                c = buscar_cliente(l, it);
                                opcao2 = 10;
                                if (c->valor.total_carrinho != 0 && opcao2 != 0)
                                {
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("\n                             -- O QUE DESEJA FAZER? --\n\n");
                                    printf(ANSI_COLOR_RESET);
                                    printf("                               1- Confirmar Compra\n");
                                    printf("                               2- Remover do carrinho\n");
                                    printf("                               3- Limpar Carrinho\n");
                                    printf("                               0- Voltar\n\n");
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("                                DIGITE SUA OPCAO:");
                                    printf(ANSI_COLOR_RESET);
                                    setbuf(stdin, NULL);
                                    scanf("%d", &opcao2);
                                    if (opcao2 == 1)
                                    {
                                        system("cls");
                                        print_logo();
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("\n\n                           ---- Pagamento via PIX ----\n\n");
                                        printf(ANSI_COLOR_RESET);
                                        printf("                                # ## ## # ### # #\n");
                                        printf("                                ### ## # # ##  ##\n");
                                        printf("                                ####  ## ## #####\n");
                                        printf("                                ### ### # ##### #\n");
                                        printf("                                ####  #### ##### \n");
                                        printf("                                ### ##  ##### ###\n");
                                        printf("                                # # # ##### ### #\n");
                                        printf("                                ## ##  #### ## ##\n");
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("\n                    Pressione Enter para finalizar pagamento...\n");
                                        printf(ANSI_COLOR_RESET);
                                        while (1)
                                        {
                                            if (_kbhit())
                                            {
                                                tecla = _getch();
                                                if (tecla == 13)
                                                { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                                    printf(ANSI_COLOR_YELLOW);
                                                    printf("\n                             Confirmando Pagamento");
                                                    i = 3;
                                                    while (i > 0)
                                                    {
                                                        imprimelento("...", 500);
                                                        printf("\b\b\b   \b\b\b");
                                                        i--;
                                                    }
                                                    printf("\n\n             Pagamento Realizado com Sucesso! Obrigado por Comprar :)\n\n");
                                                    printf(ANSI_COLOR_RESET);
                                                    system("pause");
                                                    break;
                                                    // Retorna ao menu anterior
                                                }
                                            }
                                        }
                                        insere_do_carrinho_para_comprados(l, it, relatorio);
                                        // insere_relatorio(produto, relatorio);
                                    }
                                    else if (opcao2 == 2)
                                    {
                                        do
                                        {
                                            printf("\n                 Digite o Numero do Produto de deseja Remover:");
                                            setbuf(stdin, NULL);
                                            printf(ANSI_COLOR_YELLOW);
                                            scanf("%d", &num);
                                        } while (num > c->valor.total_carrinho - 1);
                                        ret = devolve_produtos(l, l_vendedores, retorno_lista, it, num);
                                        printf("                                   ");
                                        imprimelento("\nRemovendo", 100);
                                        i = 3;
                                        while (i > 0)
                                        {
                                            imprimelento("...", 500);
                                            printf("\b\b\b   \b\b\b");
                                            i--;
                                        }
                                        if (ret == 0)
                                            printf("\n\n                              Removido com Sucesso!\n\n");
                                        else
                                            printf("\n\n                                     Erro! :(\n\n");
                                        printf(ANSI_COLOR_RESET);
                                        system("pause");
                                    }
                                    else if (opcao2 == 3)
                                    {
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("\n                               Limpando carrinho");
                                        i = 3;
                                        while (i > 0)
                                        {
                                            imprimelento("...", 200);
                                            printf("\b\b\b   \b\b\b");
                                            i--;
                                        }
                                        num = c->valor.total_carrinho;
                                        while (num > 0)
                                        {
                                            num--;
                                            devolve_produtos(l, l_vendedores, retorno_lista, it, num);
                                        }
                                        printf("\n\n                              Removido com Sucesso!\n\n");
                                        printf(ANSI_COLOR_RESET);
                                        system("pause");
                                    }
                                }
                                else if (opcao2 == 0)
                                {
                                    opcao3 = 10;
                                    break;
                                }
                                else
                                {
                                    printf(ANSI_COLOR_RED);
                                    printf("\n           IMPOSSIVEL REALIZAR OPERACOES, POIS O CARRINHO ESTA VAZIO!\n\n");
                                    printf(ANSI_COLOR_RESET);
                                    system("pause");
                                    break;
                                }
                            } while (opcao2 != 0);
                            break;
                        case 4: // Ver Historico  de  Compras
                            sair = 0;
                            do
                            {
                                system("cls");
                                print_logo();
                                mostrar_comprados(l, it);
                                c = buscar_cliente(l, it);
                                if (c->valor.total_comprados != 0)
                                {
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("\n           Pressione Enter para Avaliar Produtos ou Esc para Voltar...");
                                    printf(ANSI_COLOR_RESET);
                                    while (1)
                                    {
                                        if (_kbhit())
                                        {
                                            tecla = _getch();
                                            if (tecla == 13)
                                            { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                                do
                                                {
                                                    printf("\n                  Digite Numero do Produto que deseja Avaliar:");
                                                    setbuf(stdin, NULL);
                                                    printf(ANSI_COLOR_YELLOW);
                                                    scanf("%d", &pos);
                                                    printf(ANSI_COLOR_RESET);
                                                    printf("\n                                 (Min: 1 Max: 5)");
                                                    printf("\n                              Digite sua Avaliacao:");
                                                    setbuf(stdin, NULL);
                                                    printf(ANSI_COLOR_YELLOW);
                                                    scanf("%d", &num);
                                                    printf(ANSI_COLOR_RESET);
                                                } while ((pos < 0 || pos >= c->valor.total_comprados) || (num > 5 || num < 1));
                                                avaliar_produto(l_vendedores, l, it, pos, num);
                                                printf(ANSI_COLOR_YELLOW);
                                                printf("\n                              Obrigado por Avaliar!\n\n");
                                                printf(ANSI_COLOR_RESET);
                                                system("pause");
                                                break;
                                            }
                                            if (tecla == 27)
                                            { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                                                sair = 1;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    printf(ANSI_COLOR_RED);
                                    printf("\n           IMPOSSIVEL REALIZAR OPERACOES, POIS O HISTORICO ESTA VAZIO!\n\n");
                                    printf(ANSI_COLOR_RESET);
                                    system("pause");
                                    break;
                                }
                            } while (sair != 1);
                            break;
                        case 5: // opcoes de conta
                            system("cls");
                            print_logo();
                            printf("\n\n");
                            mostrar_conta_cliente(l, it);
                            printf(ANSI_COLOR_YELLOW);
                            printf("          Pressione Backspace para Deletar a Conta ou Esc para Voltar...\n");
                            printf(ANSI_COLOR_RESET);
                            while (1)
                            {
                                if (_kbhit())
                                {
                                    tecla = _getch();
                                    if (tecla == 27)
                                    {
                                        break; // Retorna ao menu anterior
                                    }
                                    if (tecla == 8)
                                    { // Verifica se a tecla pressionada é o código ASCII do "Backspace"
                                        printf(ANSI_COLOR_RED);
                                        printf("\n                    TEM CERTEZA QUE DESEJA EXCLUIR SUA CONTA?\n\n");
                                        printf(ANSI_COLOR_RESET);
                                        printf("                Pressione Enter para Continuar ou Esc para Voltar...\n");
                                        while (1)
                                        {
                                            if (_kbhit())
                                            {
                                                tecla = _getch();
                                                if (tecla == 13)
                                                {
                                                    do
                                                    {
                                                        printf("\n                              Digite sua senha:");
                                                        setbuf(stdin, NULL);
                                                        printf(ANSI_COLOR_YELLOW);
                                                        fgets(senha, 30, stdin);
                                                        printf(ANSI_COLOR_RESET);
                                                        senha[strcspn(senha, "\n")] = '\0';
                                                    } while (strcmp(it.senha, senha) != 0);
                                                    printf(ANSI_COLOR_YELLOW);
                                                    printf("\n                                 Excluindo conta");
                                                    i = 3;
                                                    while (i > 0)
                                                    {
                                                        imprimelento("...", 500);
                                                        printf("\b\b\b   \b\b\b");
                                                        i--;
                                                    }
                                                    ret = excluir_conta_cliente(l, it);
                                                    if (ret == 0)
                                                        printf("\n\n                          CONTA EXCLUIDA COM SUCESSO! :( \n\n");
                                                    else
                                                        printf("\n\n                                     Erro! :(\n\n");
                                                    printf(ANSI_COLOR_RESET);
                                                    system("pause");
                                                    opcao3 = 0;
                                                    opcao2 = 0;
                                                    opcao = 10;
                                                    break; // Retorna ao menu anterior
                                                }
                                                if (tecla == 27)
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                            break;
                        case 0:
                            opcao3 = 0;
                            opcao2 = 0;
                            opcao = 10;
                            break;
                        default:
                            break;
                        }
                    } while (opcao3 != 0);
                    zerar_produtos(retorno_lista);
                    break;
                }
                if (opcao2 == 2 || opcao2 == 4) // Login e Cadastro de Vendedor
                {
                    /*            CADASTRO/LOGIN VENDEDOR     */
                    num = 3;
                    do
                    {
                        system("cls");
                        print_logo();
                        printf("\n                                                                (Tentativas: ");
                        printf(ANSI_COLOR_CYAN);
                        printf("%d", num);
                        printf(ANSI_COLOR_RESET);
                        printf(")");
                        printf(ANSI_COLOR_YELLOW);
                        printf("\n\n                            --- Digite seus DADOS ---\n\n");
                        printf(ANSI_COLOR_RESET);
                        printf("                            Digite seu nome:");
                        setbuf(stdin, NULL);
                        printf(ANSI_COLOR_YELLOW);
                        fgets(v.cadastro.nome, 30, stdin);
                        printf(ANSI_COLOR_RESET);
                        v.cadastro.nome[strcspn(v.cadastro.nome, "\n")] = '\0';
                        printf("                            Digite sua senha:");
                        setbuf(stdin, NULL);
                        printf(ANSI_COLOR_YELLOW);
                        fgets(v.cadastro.senha, 10, stdin);
                        v.cadastro.senha[strcspn(v.cadastro.senha, "\n")] = '\0';
                        printf(ANSI_COLOR_RESET);
                        printf("                            Digite o nome da loja:");
                        setbuf(stdin, NULL);
                        printf(ANSI_COLOR_YELLOW);
                        fgets(v.nome_loja, 30, stdin);
                        printf(ANSI_COLOR_RESET);
                        v.nome_loja[strcspn(v.nome_loja, "\n")] = '\0';
                        ret = verifica_vendedor(l_vendedores, v);
                        if (ret == 0 && opcao2 == 2) // VENDEDOR EXISTE E ELE TENTOU CRIAR
                        {
                            printf(ANSI_COLOR_RED);
                            printf("\n                    DADOS DE USUARIO JA EXISTE, TENTE OUTRO!\n");
                            printf(ANSI_COLOR_RESET);
                            Sleep(1000);
                            num--;
                            if (num == 0)
                            {
                                break;
                            }
                        }
                        if (ret == 3 && opcao2 == 4) // VENDEDOR N EXISTE NA LISTA E ELE FEZ LOGIN
                        {

                            printf(ANSI_COLOR_RED);
                            printf("\n                       NOME DE USUARIO OU SENHA INCORRETOS!\n");
                            printf(ANSI_COLOR_RESET);
                            Sleep(1000);
                            num--;
                            if (num == 0)
                            {
                                break;
                            }
                        }

                    } while ((opcao2 == 2 && ret == 0) || (opcao2 == 4 && ret == 3));
                    if (ret == 0 && opcao2 == 4)
                    {
                        verifica_vendedor_e_retorna(l_vendedores, &v);
                    }

                    if (num == 0)
                    {
                        opcao = 10;
                        opcao2 = 0;
                        opcao3 = 0;
                        break;
                    }
                    if (opcao2 == 2)
                    {
                        // cadastro
                        v.total_produtos = 0;
                        v.inicio = NULL;
                        insere_novo_vendedor(l_vendedores, v);
                        printf(ANSI_COLOR_YELLOW);
                        printf("\n");
                        printf("                                   ");
                        imprimelento("SALVANDO...", 200);
                        printf(ANSI_COLOR_RESET);
                    }
                    if (opcao2 == 4)
                    {
                        // Login
                        printf(ANSI_COLOR_YELLOW);
                        printf("\n");
                        printf("                                  ");
                        imprimelento("CARREGANDO...", 200);
                        printf(ANSI_COLOR_RESET);
                    }
                    do
                    {
                        system("cls");
                        print_logo();
                        printf("\n");
                        printf("                                BEM VINDO, ");
                        printf(ANSI_COLOR_YELLOW);
                        printf("%s!\n\n", v.cadastro.nome);
                        printf("                            -- O QUE DESEJA FAZER? --\n\n");
                        printf(ANSI_COLOR_RESET);
                        printf("                               1- Cadastrar Produto\n");
                        printf("                               2- Remover Produto\n");
                        printf("                               3- Ver Produtos\n");
                        printf("                               4- Ver Conta\n");
                        printf("                               0- Voltar\n\n");
                        printf(ANSI_COLOR_YELLOW);
                        printf("                               DIGITE SUA OPCAO:");
                        printf(ANSI_COLOR_RESET);
                        scanf("%d", &opcao3);
                        switch (opcao3)
                        {
                        case 1:
                            /*  cadastrar produto */
                            system("cls");
                            print_logo();
                            printf("\n\n");
                            do
                            {

                                printf("                         Insira o Nome do Produto:");
                                setbuf(stdin, NULL);
                                fgets(p.NOME, 30, stdin);
                                p.NOME[strcspn(p.NOME, "\n")] = '\0';
                                do
                                {
                                    printf("                         Insira a Categoria do Produto (1 ao 12):");
                                    setbuf(stdin, NULL);
                                    scanf("%d", &p.CATEGORIA);
                                } while (p.CATEGORIA < 0 || p.CATEGORIA > 12);

                                printf("                         Insira a Descricao do Produto:");
                                setbuf(stdin, NULL);
                                fgets(p.DESCRICAO, 100, stdin);
                                p.DESCRICAO[strcspn(p.DESCRICAO, "\n")] = '\0';
                                do
                                {
                                    printf("                         Insira a Quantidade do Produto:");
                                    setbuf(stdin, NULL);
                                    scanf("%d", &p.QUANTIDADE);
                                } while (p.QUANTIDADE <= 0);
                                do
                                {
                                    printf("                         Insira o Valor do Produto:");
                                    scanf("%f", &p.VALOR);
                                } while (p.VALOR <= 0);
                                p.NOTA_AVALIACAO = 0;
                                p.QUANT_AVALIACAO = 0;
                                strcpy(p.nome_loja, v.nome_loja);

                                if (verifica_produto(v.inicio, p) == 0) // MESMO NOME DE PRODUTO
                                {
                                    printf(ANSI_COLOR_RED);
                                    printf("                            NOME DE PRODUTO JA EXISTE!\n\n");
                                    printf(ANSI_COLOR_RESET);
                                    system("pause");
                                }

                            } while (verifica_produto(v.inicio, p) == 0);

                            if (vendedor_adiciona_produtos(&v, p) == 0)
                            {
                                atualiza_lista_vendedores(v, l_vendedores);
                                printf(ANSI_COLOR_YELLOW);
                                printf("                   CADASTRO DO PRODUTO REALIZADO COM SUCESSO!\n\n");
                                printf(ANSI_COLOR_RESET);
                                system("pause");
                            }
                            else
                            {
                                printf(ANSI_COLOR_RED);
                                printf("                           CADASTRO DO PRODUTO FALHOU!\n\n");
                                printf(ANSI_COLOR_RESET);
                                system("pause");
                            }
                            break;
                        case 2:
                            /*       remover produtos           */
                            system("cls");
                            print_logo();
                            printf("\n\n");
                            mostra_produtos_vendedor(v);
                            if (v.total_produtos == 0)
                                break;
                            printf("                     Qual Produto deseja Remover? por Indice [i]\n");
                            printf(ANSI_COLOR_RED);
                            printf("                                Remover Produto:");
                            printf(ANSI_COLOR_RESET);
                            scanf("%d", &indice);
                            if (removerPosicao_produto_do_vendedor(&v, indice) == 0)
                            {
                                printf(ANSI_COLOR_YELLOW);
                                printf("\n");
                                printf("                                   ");
                                imprimelento("Removendo", 200);
                                i = 3;
                                while (i > 0)
                                {
                                    imprimelento("...", 500);
                                    printf("\b\b\b   \b\b\b");
                                    i--;
                                }
                                printf(ANSI_COLOR_RESET);
                            }
                            else
                            {
                                printf(ANSI_COLOR_RED);
                                printf("\n                        NAO FOI POSSIVEL REMOVER PRODUTO!\n");
                                printf(ANSI_COLOR_RESET);
                            }
                            atualiza_lista_vendedores(v, l_vendedores);
                            break;
                        case 3:
                            /*       Mostrar produtos           */
                            system("cls");
                            print_logo();
                            printf("\n\n");
                            mostra_produtos_vendedor(v);
                            printf("\n");
                            system("pause");
                            break;
                        case 4:
                            /*    deletar conta   */
                            system("cls");
                            print_logo();
                            printf("\n\n");
                            mostrar_conta_vendedor(v);
                            printf(ANSI_COLOR_YELLOW);
                            printf("         Pressione Backspace para Deletar a Conta ou Esc para Voltar...\n");
                            printf(ANSI_COLOR_RESET);
                            while (1)
                            {
                                if (_kbhit())
                                {
                                    tecla = _getch();
                                    if (tecla == 27)
                                    {
                                        break; // Retorna ao menu anterior
                                    }
                                    if (tecla == 8)
                                    { // Verifica se a tecla pressionada é o código ASCII do "Backspace"
                                        printf(ANSI_COLOR_RED);
                                        printf("\n                    TEM CERTEZA QUE DESEJA EXCLUIR SUA CONTA?\n\n");
                                        printf(ANSI_COLOR_YELLOW);
                                        printf("               Pressione Enter para Continuar ou Esc para Voltar...\n");
                                        printf(ANSI_COLOR_RESET);
                                        while (1)
                                        {
                                            if (_kbhit())
                                            {
                                                tecla = _getch();
                                                if (tecla == 13)
                                                {
                                                    printf(ANSI_COLOR_YELLOW);
                                                    printf("\n                                Excluindo conta");
                                                    i = 3;
                                                    while (i > 0)
                                                    {
                                                        imprimelento("...", 500);
                                                        printf("\b\b\b   \b\b\b");
                                                        i--;
                                                    }
                                                    if (remover_vendedor_item(l_vendedores, v) == 0)
                                                        printf("\n\n                          CONTA EXCLUIDA COM SUCESSO! :( \n\n");
                                                    else
                                                        printf("\n\n                                    Erro! :(\n\n");
                                                    printf(ANSI_COLOR_RESET);
                                                    system("pause");
                                                    opcao3 = 0;
                                                    opcao2 = 0;
                                                    opcao = 10;
                                                    break; // Retorna ao menu anterior
                                                }
                                                if (tecla == 27)
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    break;
                                }
                            }
                            break;
                        case 0:
                            /* SAIR */
                            v.inicio = NULL;
                            v.total_produtos = 0;
                        // Zerando os campos para nao dar B.O
                        default:
                            break;
                        }
                    } while (opcao3 != 0);
                }
            } while (opcao2 != 0);
            break;
        case 2:
            system("cls");
            printf("\n");
            printf("=========================================================================\n");
            printf(ANSI_COLOR_YELLOW);
            printf("\nO que voce pode esperar da Powerful Machine:\n\n");
            printf("Variedade Inigualavel: ");
            printf(ANSI_COLOR_RESET);
            printf("Oferecemos uma ampla gama de produtos eletronicos,\n");
            printf("desde smartphones  e laptops ate  dispositivos  inteligentes para  casa e\n");
            printf("acessorios  de  ultima  geracao. Seja  qual  for a sua  necessidade, voce\n");
            printf("encontrara  a  solucao  perfeita  em  nossa  loja.\n\n");
            printf(ANSI_COLOR_YELLOW);
            printf("Qualidade  Garantida:");
            printf(ANSI_COLOR_RESET);
            printf(" Na  Powerful Machine, qualidade eh  a nossa priori-\n");
            printf("dade. Trabalhamos  com  as  principais   marcas  do  mercado  e  produtos\n");
            printf("de  alta  qualidade  para  garantir  a  satisfacao  de  nossos  clientes.\n\n");
            printf(ANSI_COLOR_YELLOW);
            printf("Atendimento  Personalizado:");
            printf(ANSI_COLOR_RESET);
            printf(" Nossa  equipe esta  sempre  pronta  para aju-\n");
            printf("da-lo  a encontrar  o  produto  certo  que  atenda as  suas  necessidades\n");
            printf("e orcamento, orientacao e suporte para  tornar sua experiencia  de compra\n");
            printf("mais facil e agradavel.\n\n");
            printf(ANSI_COLOR_YELLOW);
            printf("Precos Competitivos:");
            printf(ANSI_COLOR_RESET);
            printf(" Com  precos competitivos e ofertas especiais, garan-\n");
            printf("timos que  voce obtenha o melhor custo-beneficio em sua compra de eletro-\n");
            printf("nicos na Powerful Machine.\n\n");
            printf(ANSI_COLOR_YELLOW);
            printf("Conveniencia Online:");
            printf(ANSI_COLOR_RESET);
            printf(" Alem de nossa loja fisica, oferecemos uma plataforma\n");
            printf("de compras  online conveniente, permitindo que voce compre  seus  eletro-\n");
            printf("nicos favoritos no conforto de sua casa.\n\n");
            printf(ANSI_COLOR_YELLOW);
            printf("Assistencia Tecnica Especializada:");
            printf(ANSI_COLOR_RESET);
            printf(" Alem  das vendas, oferecemos  servicos\n");
            printf("de assistencia tecnica de primeira linha para garantir que seus disposi-\n");
            printf("tivos funcionem perfeitamente.\n\n");
            printf("=========================================================================\n");
            // Pressione Esc para voltar
            printf("Pressione Esc para voltar ao menu anterior...\n");
            while (1)
            {
                if (_kbhit())
                {
                    tecla = _getch();
                    if (tecla == 27)
                    {          // Verifica se a tecla pressionada é o código ASCII do "Esc"
                        break; // Retorna ao menu anterior
                    }
                }
            }
            break;
        case 0:
            /* SAIR */
            system("cls");
            printf(ANSI_COLOR_YELLOW);
            printf("Saindo");
            i = 3;
            while (i > 0)
            {
                i--;
                imprimelento("...", 500);
                printf("\b\b\b   \b\b\b");
            }
            system("cls");
            printf(ANSI_COLOR_RED);
            printf("                        ___\n");
            printf("                    __,' __`.                _..----....____\n");
            printf("        __...--.'``;.   ,.   ;``--..__     .'    ,-._    _.-'\n");
            printf("  _..-''-------'   `'   `'   `'     O ``-''._   (,;') _,'\n");
            printf(",'________________                          \\`-._`-','\n");
            printf(" `._              ```````````------...___   '-.._'-:\n");
            printf("    ```--.._      ,.                     ````--...__\\-.\n");
            printf("            `.--. `-`                       ____    |  |`\n");
            printf("              `. `.                       ,'`````.  ;  ;`\n");
            printf("                `._`.        __________   `.      \'__/`\n");
            printf("                   `-:._____/______/___/____`.     \\  `\n");
            printf("                               |       `._    `.    \\\n");
            printf("                               `._________`-.   `.   `.___\n");
            printf("                                                  `------'`\n");
            printf("\n\nVolte sempre!\n\n");
            printf(ANSI_COLOR_YELLOW);
            printf("Pressione Enter para gerar Relatorio de Vendas ou Esc para encerrar o programa...\n");
            printf(ANSI_COLOR_RESET);
            while (1)
            {
                if (_kbhit())
                {
                    tecla = _getch();
                    if (tecla == 13)
                    { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                        system("cls");
                        mostrar_relatorio(relatorio);
                        printf("\n");
                        system("pause");
                        break; // Retorna ao menu anterior
                    }
                    if (tecla == 27)
                    {          // Verifica se a tecla pressionada é o código ASCII do "Esc"
                        break; // Retorna ao menu anterior
                    }
                }
            }
            break;
        default:
            break;
        }
    } while (opcao != 0);
    salvar_clientes(l);
    salvarListaVendedores(l_vendedores);
    limpa_lista_clientes(l);
    limpar_vendedores(l_vendedores);
    free(pesquisa);
    free(senha);
    limpar_lista_produtos(retorno_lista2);
    limpar_lista_produtos(retorno_lista);
    return 0;
}

void print_logo()
{
    printf(ANSI_COLOR_RED);
    printf("+-------===========================+++++++++++===========================-------+\n");
    printf("|   * .  ^           ____    .       *      .     __       _         *      .   |\n");
    printf("|       / \\     *   |  _ \\ _____  .   _____ _ __ / _|_   _| |              *    |\n");
    printf("|      /___\\        | |_) / _ \\ \\ /\\ / / _ \\ '__| |_| | | | |    .       .      |\n");
    printf("|  *  |=   =|  *    |  __/ (_) \\ V  V /  __/ |  |  _| |_| | |                   |\n");
    printf("|     |     |     . |_|  _\\___/ \\_/\\_/ \\___|_|  |_|  \\__,_|_|        *          |\n");
    printf("|     |     |       |  \\/  | __ _  ___| |__ (_)_ __   ___               *       |\n");
    printf("|     |##!##|   *   | |\\/| |/ _` |/ __| '_ \\| | '_ \\ / _ \\     *          *     |\n");
    printf("|    /|##!##|\\      | |  | | (_| | (__| | | | | | | |  __/               .      |\n");
    printf("|   / |##!##| \\     |_|  |_|\\__,_|\\___|_| |_|_|_| |_|\\___|      *               |\n|");
    printf("   |/^  |  ^\\|         *                      .                            *   |\n");
    printf("+-------===========================+++++++++++===========================-------+\n");
    printf(ANSI_COLOR_RESET);
}

void imprimelento(char *p, int N)
{
    int i;
    for (i = 0; *(p + i) != '\0'; i++)
    {
        printf("%c", *(p + i));
        fflush(stdout);
        Sleep(N);
    }
}

void mostrar_conta_cliente(lista_clientes *l, cadastro it)
{
    if (l == NULL)
        return;
    if (lista_clientes_vazia(l) == 0)
        return;
    no_clientes *search = buscar_cliente(l, it);
    if (search != NULL)
    {
        printf("Nome: %s\tSenha: %s\n", search->valor.cadastro.nome, search->valor.cadastro.senha);
        printf("Historico de compras: (TOTAL: %d)\n", search->valor.total_comprados);
        no_produtos *prod = search->valor.comprados_inicio;
        int j = 0;
        while (prod != NULL)
        {
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            printf("Produto %d: ", j);
            printf("Nome: %s | ", prod->produto.NOME);
            printf("Quantidade: %d | ", prod->produto.QUANTIDADE);
            printf("Valor: R$%.2f | ", prod->produto.VALOR);
            printf("Categoria: %d\n", prod->produto.CATEGORIA);
            printf("Quantidade de Avaliacoes: %d | ", prod->produto.QUANT_AVALIACAO);
            printf("Nota de Avalicao: %d | ", prod->produto.NOTA_AVALIACAO);
            printf("Fornecedor: %s\n", prod->produto.nome_loja);
            printf("Descricao: %s\n", prod->produto.DESCRICAO);
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            j++;
            prod = prod->prox;
        }
        if (search->valor.comprados_inicio == NULL)
            printf("Nenhum produto foi comprado!\n");
        j = 0;
        printf("\nProdutos no Carrinho: (TOTAL: %d)\n", search->valor.total_carrinho);
        prod = search->valor.carrinho_inicio;
        while (prod != NULL)
        {
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            printf("Produto %d: ", j);
            printf("Nome: %s | ", prod->produto.NOME);
            printf("Quantidade: %d | ", prod->produto.QUANTIDADE);
            printf("Valor: R$%.2f | ", prod->produto.VALOR);
            printf("Categoria: %d\n", prod->produto.CATEGORIA);
            printf("Quantidade de Avaliacoes: %d | ", prod->produto.QUANT_AVALIACAO);
            printf("Nota de Avalicao: %d | ", prod->produto.NOTA_AVALIACAO);
            printf("Fornecedor: %s\n", prod->produto.nome_loja);
            printf("Descricao: %s\n", prod->produto.DESCRICAO);
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            j++;
            prod = prod->prox;
        }
        if (search->valor.carrinho_inicio == NULL)
            printf("Nenhum produto no carrinho!\n");
        printf("\n");
        return;
    }
    return;
}

void mostrar_carrinho(lista_clientes *l, cadastro it)
{
    if (l != NULL)
        if (lista_clientes_vazia(l) != 0)
        {
            no_clientes *search = buscar_cliente(l, it);
            if (search != NULL)
            {
                int j = 0;
                printf("\nProdutos no Carrinho: (total:%d)\n\n", search->valor.total_carrinho);
                if (search->valor.carrinho_inicio == NULL)
                {
                    printf("Nenhum produto no carrinho!\n");
                }
                else
                {
                    no_produtos *prod = search->valor.carrinho_inicio;
                    while (prod != NULL)
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("--------===========================+++++++++++===========================--------\n");
                        printf(ANSI_COLOR_RESET);
                        printf("Produto %d: ", j);
                        printf("Nome: %s | ", prod->produto.NOME);
                        printf("Quantidade: %d | ", prod->produto.QUANTIDADE);
                        printf("Valor: R$%.2f | ", prod->produto.VALOR);
                        printf("Categoria: %d\n", prod->produto.CATEGORIA);
                        printf("Quantidade de Avaliacoes: %d | ", prod->produto.QUANT_AVALIACAO);
                        printf("Nota de Avalicao: %d | ", prod->produto.NOTA_AVALIACAO);
                        printf("Fornecedor: %s\n", prod->produto.nome_loja);
                        printf("Descricao: %s\n", prod->produto.DESCRICAO);
                        printf(ANSI_COLOR_YELLOW);
                        printf("--------===========================+++++++++++===========================--------\n");
                        printf(ANSI_COLOR_RESET);
                        j++;
                        prod = prod->prox;
                    }
                }
            }
        }
}

void mostrar_comprados(lista_clientes *l, cadastro it)
{
    if (l == NULL)
        return;
    if (lista_clientes_vazia(l) == 0)
        return;
    no_clientes *search = buscar_cliente(l, it);
    if (search != NULL)
    {
        int j = 0;
        printf("\nHistorico de Produtos Comprados: (total:%d)\n\n", search->valor.total_comprados);
        if (search->valor.comprados_inicio == NULL)
        {
            printf("Nenhum produto no comprados!\n");
            return;
        }
        no_produtos *prod = search->valor.comprados_inicio;
        while (prod != NULL)
        {
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            printf("Produto %d: ", j);
            printf("Nome: %s | ", prod->produto.NOME);
            printf("Quantidade: %d | ", prod->produto.QUANTIDADE);
            printf("Valor: R$%.2f | ", prod->produto.VALOR);
            printf("Categoria: %d\n", prod->produto.CATEGORIA);
            printf("Quantidade de Avaliacoes: %d | ", prod->produto.QUANT_AVALIACAO);
            printf("Nota de Avalicao: %d | ", prod->produto.NOTA_AVALIACAO);
            printf("Fornecedor: %s\n", prod->produto.nome_loja);
            printf("Descricao: %s\n", prod->produto.DESCRICAO);
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            j++;
            prod = prod->prox;
        }
        return;
    }
    return;
}

void mostrar_produtos(lista_produtos *l)
{
    if (l == NULL)
    {
        printf("Lista de Produtos nao Criada!\n");
        return;
    }
    if (listaVazia_produtos(l) == 0)
    {
        return;
    }
    if (l != NULL)
    {
        no_produtos *no_Lista = l->inicio;
        int j = 0;
        while (no_Lista != NULL)
        {
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            printf("Produto %d: ", j);
            printf("Nome: %s | ", no_Lista->produto.NOME);
            printf("Quantidade: %d | ", no_Lista->produto.QUANTIDADE);
            printf("Valor: R$%.2f | ", no_Lista->produto.VALOR);
            printf("Categoria: %d\n", no_Lista->produto.CATEGORIA);
            printf("Quantidade de Avaliacoes: %d | ", no_Lista->produto.QUANT_AVALIACAO);
            printf("Nota de Avalicao: %d | ", no_Lista->produto.NOTA_AVALIACAO);
            printf("Fornecedor: %s\n", no_Lista->produto.nome_loja);
            printf("Descricao: %s\n", no_Lista->produto.DESCRICAO);
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            j++;
            no_Lista = no_Lista->prox;
        }
    }
}

void mostra_produtos_vendedor(vendedor v)
{
    if (v.inicio == NULL)
    {
        printf(ANSI_COLOR_YELLOW);
        printf("O VENDEDOR NAO POSSUI PRODUTOS!\n");
        printf(ANSI_COLOR_RESET);
    }
    else
    {
        printf("Produtos do vendedor:\n");
        no_produtos *temp = v.inicio;
        int j = 0;
        while (temp != NULL)
        {
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            printf("Produto %d: ", j);
            printf("Nome: %s | ", temp->produto.NOME);
            printf("Quantidade: %d | ", temp->produto.QUANTIDADE);
            printf("Valor: R$%.2f | ", temp->produto.VALOR);
            printf("Categoria: %d\n", temp->produto.CATEGORIA);
            printf("Quantidade de Avaliacoes: %d | ", temp->produto.QUANT_AVALIACAO);
            printf("Nota de Avalicao: %d | ", temp->produto.NOTA_AVALIACAO);
            printf("Fornecedor: %s\n", temp->produto.nome_loja);
            printf("Descricao: %s\n", temp->produto.DESCRICAO);
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            j++;
            temp = temp->prox;
        }
    }
}

void mostrar_conta_vendedor(vendedor v)
{
    printf("Nome: %s\tSenha: %s\n", v.cadastro.nome, v.cadastro.senha);
    printf("Nome da Loja: %s\n\n", v.nome_loja);
    if (v.inicio == NULL)
    {
        printf(ANSI_COLOR_YELLOW);
        printf("O VENDEDOR NAO POSSUI PRODUTOS!\n\n");
        printf(ANSI_COLOR_RESET);
    }
    else
    {
        printf("PRODUTOS DO VENDEDOR: (TOTAL: %d)\n\n", v.total_produtos);
        no_produtos *temp = v.inicio;
        int j = 0;
        while (temp != NULL)
        {
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            printf("Produto %d: ", j);
            printf("Nome: %s | ", temp->produto.NOME);
            printf("Quantidade: %d | ", temp->produto.QUANTIDADE);
            printf("Valor: R$%.2f | ", temp->produto.VALOR);
            printf("Categoria: %d\n", temp->produto.CATEGORIA);
            printf("Quantidade de Avaliacoes: %d | ", temp->produto.QUANT_AVALIACAO);
            printf("Nota de Avalicao: %d | ", temp->produto.NOTA_AVALIACAO);
            printf("Fornecedor: %s\n", temp->produto.nome_loja);
            printf("Descricao: %s\n", temp->produto.DESCRICAO);
            printf(ANSI_COLOR_YELLOW);
            printf("--------===========================+++++++++++===========================--------\n");
            printf(ANSI_COLOR_RESET);
            j++;
            temp = temp->prox;
        }
    }
}

void mostrar_relatorio(lista_produtos *l)
{
    if (l == NULL)
        return;
    if (listaVazia_produtos(l) == 0)
    {
        printf(ANSI_COLOR_YELLOW);
        printf("NENHUM PRODUTO FOI VENDIDO!\n\n");
        printf(ANSI_COLOR_RESET);
        return;
    }
    produtos p;
    int cat;
    print_logo();
    printf(ANSI_COLOR_YELLOW);
    printf("\n\n--------===================----RELATORIO DE VENDAS----===================--------\n\n");
    printf("PRODUTO MAIS VENDIDO:\n");
    produto_mais_vendido(l, &p);
    printf("--------===========================+++++++++++===========================--------\n");
    printf(ANSI_COLOR_RESET);
    printf("Nome: %s | ", p.NOME);
    printf("Quantidade: %d | ", p.QUANTIDADE);
    printf("Valor: R$%.2f | ", p.VALOR);
    printf("Categoria: %d\n", p.CATEGORIA);
    printf("Quantidade de Avaliacoes: %d | ", p.QUANT_AVALIACAO);
    printf("Nota de Avalicao: %d | ", p.NOTA_AVALIACAO);
    printf("Fornecedor: %s\n", p.nome_loja);
    printf("Descricao: %s\n", p.DESCRICAO);
    printf(ANSI_COLOR_YELLOW);
    printf("--------===========================+++++++++++===========================--------\n");
    printf("PRODUTO MENOS VENDIDO:\n");
    produto_menos_vendido(l, &p);
    printf("--------===========================+++++++++++===========================--------\n");
    printf(ANSI_COLOR_RESET);
    printf("Nome: %s | ", p.NOME);
    printf("Quantidade: %d | ", p.QUANTIDADE);
    printf("Valor: R$%.2f | ", p.VALOR);
    printf("Categoria: %d\n", p.CATEGORIA);
    printf("Quantidade de Avaliacoes: %d | ", p.QUANT_AVALIACAO);
    printf("Nota de Avalicao: %d | ", p.NOTA_AVALIACAO);
    printf("Fornecedor: %s\n", p.nome_loja);
    printf("Descricao: %s\n", p.DESCRICAO);
    printf(ANSI_COLOR_YELLOW);
    printf("--------===========================+++++++++++===========================--------\n");
    categoria_mais_vendida(l, &cat);
    printf("CATEGORIA DE PRODUTO MAIS VENDIDO: %d\n", cat);
    printf(ANSI_COLOR_YELLOW);
    printf("--------===========================+++++++++++===========================--------\n");
    printf("TODOS OS PRODUTOS QUE FORAM VENDIDOS:\n");
    printf(ANSI_COLOR_RESET);
    int j = 0;
    no_produtos *no = l->inicio;
    while (no != NULL)
    {
        printf(ANSI_COLOR_YELLOW);
        printf("--------===========================+++++++++++===========================--------\n");
        printf(ANSI_COLOR_RESET);
        printf("Produto %d: ", j);
        printf("Nome: %s | ", no->produto.NOME);
        printf("Quantidade: %d | ", no->produto.QUANTIDADE);
        printf("Valor: R$%.2f | ", no->produto.VALOR);
        printf("Categoria: %d\n", no->produto.CATEGORIA);
        printf("Quantidade de Avaliacoes: %d | ", no->produto.QUANT_AVALIACAO);
        printf("Nota de Avalicao: %d | ", no->produto.NOTA_AVALIACAO);
        printf("Fornecedor: %s\n", no->produto.nome_loja);
        printf("Descricao: %s\n", no->produto.DESCRICAO);
        printf(ANSI_COLOR_YELLOW);
        printf("--------===========================+++++++++++===========================--------\n");
        printf(ANSI_COLOR_RESET);
        j++;
        no = no->prox;
    }
    return;
}