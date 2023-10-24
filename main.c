#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<inttypes.h>
#include "funcoes.h"

int main()
{
    Lista *lista = (Lista*) malloc(sizeof (lista)); // Ponteiro para a lista de produtos.
     if(lista == NULL){
        puts("Erro ao alocar memoria");
    }
    inicializar_lista(lista);

    int novo_tam; // Vari�vel para armazenar o tamanho da lista de produtos.
    int menu_1, menu_produtos; // Vari�veis para armazenar as op��es dos menus.

    do {
        printf("\n------------------------------------------------------------------");
        printf("\n========================| MENU PRINCIPAL |========================\n");
        printf("------------------------------------------------------------------");
        printf("\n1\t\t\tProdutos\n2\t\t\tVendas \n3\t\t\tSair\n");
        printf("\n==================================================================\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &menu_1);
        getchar();

        switch (menu_1) {
            case 1:
                do {
                    printf("\n-----------------------PRODUTOS-----------------------\n");
                    printf("\n1\t\t      Exibir\n2\t\t      Cadastrar\n3\t\t      Atualizar\n4\t\t      Excluir\n5\t\t      Salvar\n6\t\t      Ler\n7\t\t      Voltar\n");
                    printf("\n------------------------------------------------------\n");
                    printf("\nDigite a opcao desejada: ");
                    scanf("%d", &menu_produtos);
                    getchar();
                    switch (menu_produtos) {
                        case 1:
                            visualizar_estoque(lista);
                            break;
                        case 2:
                            printf("\nDigite o numero de produtos que deseja cadastrar: ");
                            scanf("%i", &novo_tam);
                            getchar();
                            if (novo_tam <= 0) {
                                printf("\nValor Invalido\n");
                            }else{
                                lista = cadastrar_produtos(lista, novo_tam);
                            }
                            break;
                        case 3:
                            atualizar_produto(lista);
                            break;
                        case 4:
                            lista = excluir_produto(lista);
                            break;
                        case 5:
                            salvar_produtos(lista);
                            break;
                        case 6:
                           lista = ler_produtos(lista);
                            break;
                        case 7:
                            break;
                        default:
                            printf("\nOpcao invalida, tente novamente\n");
                            break;
                    }
                } while (menu_produtos != 7);

                break;

            case 2:
               submenu_venda(lista);
                break;

            case 3:
                printf("\nSaindo do programa\n");
                break;

            default:
                printf("\nOpcao invalida, tente novamente\n");
                break;
        }
    } while (menu_1 != 3);

    desalocar_lista(lista);

    return 0;
}
