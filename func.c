#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include "funcoes.h"

void inicializar_lista(Lista* lista){
    lista->inicio = NULL;
}
void desalocar_lista(Lista *lista)
{
    if(lista->inicio == NULL){
            return;
    }
    if(lista->inicio->prox == NULL){
        free(lista->inicio);
        return;
    }
    No *atual = lista->inicio;
    while(atual != NULL)
    {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    lista->inicio = NULL;
}

void visualizar_estoque(Lista *lista)// Fun��o para exibir o estoque
{
    No* ptr = lista->inicio;

    printf("\n-------------------------------------------------------------------------------------\n");
    printf("Codigo\t\t Produto\t\t\t Valor(unidade)\t\t Estoque\n\n");
    printf("-------------------------------------------------------------------------------------\n");
     if (ptr == NULL){
        printf("Nenhum produto foi cadastrado");
    }
    while(ptr != NULL){
        printf("%-16" PRIu64 " %-32sR$%-22.2f%-8i\n", ptr->prod.codigo, ptr->prod.nome, ptr->prod.valor, ptr->prod.quantidade);
        ptr = ptr->prox;
    }
    printf("\n-------------------------------------------------------------------------------------\n");
}


Lista *cadastrar_produtos(Lista *lista, int novo_tam)// Fun��o para cadastrar produtos
{
    int verifica = 0;
    produto prod;

    for(int i = 0; i < novo_tam; i++){
            No* novo = (No*) malloc(sizeof(No)); // Aloca a mem�ria para adicionar um novo no a lista de produtos.
            do{
                prod.vendas_totais = 0;
                printf("\nDigite o codigo do produto: ");
                scanf("%" SCNu64, &prod.codigo);
                getchar();
                if(prod.codigo <= 0)
                {
                    verifica = 1;
                    printf("\nCodigo invalido\n");
                }
                else
                {
                    verifica = verificar_codigo(lista, prod.codigo); // Verifica se o c�digo j� existe

                    if(verifica == 0)
                    {
                        printf("\nDigite o nome do produto: ");
                        fgets(prod.nome, sizeof(prod.nome), stdin); // L� o nome do produto
                        size_t l = strlen(prod.nome);
                          // Se foi excedido o tamanho da string, e preciso eliminar os caracteres restante para passar para a proxima linha
                            if(l == sizeof(prod.nome)-1)
                            while(fgetc(stdin) != '\n'); // Eliminar o enter e outros caracteres ate achar o fim da linha

                        char *lf;
                        if ((lf = strchr(prod.nome, '\n')) != NULL) *lf = '\0'; // Remove o caractere de nova linha do nome
                        verifica = verificar_string(prod.nome); // Verifica se o nome � v�lido
                        if(verifica == 0)
                        {
                            printf("\nDigite o preco do produto: ");
                            scanf("%f", &prod.valor); // L� o pre�o do produto
                            getchar();
                            if(prod.valor >= 0)
                            {
                                printf("\nDigite a quantidade em estoque: ");
                                scanf("%i", &prod.quantidade); // L� a quantidade em estoque do produto
                                getchar();
                                if(prod.quantidade < 0)
                                {
                                    printf("\nA quantidade digitada nao e valida. Tente novamente\n");
                                    verifica = 1;
                                }
                            }
                            else
                            {
                                printf("\nO valor digitado nao e valido. Tente novamente\n");
                                verifica = 1;
                            }
                        }
                        else
                        {
                            printf("\nO nome digitado nao e valido. Tente novamente\n");
                        }
                    }
                    else
                    {
                        printf("\nO codigo digitado ja existe. Tente novamente\n");
                    }
                    printf("\n------------------------------------------------------\n");
                }
            }while (verifica == 1);

            novo->prod = prod;
            novo->ant = NULL;
            novo->prox = NULL;

            if(lista->inicio == NULL){
                lista->inicio = novo;
            }
            else{
                    No* ptr = lista->inicio;
                while(ptr->prox != NULL){
                    ptr = ptr->prox;
                }
                novo->ant = ptr;
                novo->prox = NULL;
                ptr->prox = novo;

            }
        }
        return lista;
    }


int verificar_codigo(Lista *lista, unsigned long long codigo)// Fun��o para verificar se um c�digo j� existe no vetor de produtos
{
    No*ptr = lista->inicio;
    while(ptr != NULL){
        if (ptr->prod.codigo == codigo) {
            return 1; // Retorna 1 se o c�digo j� existe
        }
        ptr = ptr->prox;
    }
    return 0; // Retorna 0 se o c�digo n�o existe
}

int verificar_string(char str[25])// Fun��o para verificar se uma string � v�lida (n�o cont�m apenas espa�os em branco)
{
    int len = strlen(str);
    if(len > 25)
    {
        return 1; // Retorna 1 se a string � inv�lida (maior que 25 caracteres)
    }
    for(int i = 0; i < len; i++)
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            return 0; // Retorna 0 se a string � v�lida (cont�m pelo menos um caractere diferente de espa�o em branco)
        }
    }
    return 1; // Retorna 1 se a string � inv�lida (cont�m apenas espa�os em branco)
}


void atualizar_produto(Lista* lista)// Fun��o para atualizar um produto no estoque
{
    if(lista->inicio == NULL){
        puts("Lista vazia");
        return;
    }
    int old_qnt, quantidade;
    float old_value, valor;
    unsigned long long codigo;
    int invalid = 0;
    visualizar_estoque(lista);
    printf("\nDigite o codigo do produto que deseja atualizar: ");
    scanf("%" SCNu64, &codigo);
    No* ptr = lista->inicio;
    while(ptr != NULL && ptr->prod.codigo != codigo){
        ptr = ptr->prox;
    }
    if(ptr != NULL){
        do{
            old_qnt = ptr->prod.quantidade; // Armazena a quantidade anterior do produto
            printf("\nDigite a nova quantidade: ");
            scanf("%d", &quantidade); // L� a nova quantidade do produto
            getchar();
            if (quantidade <= 0){
                printf("\n\nQuantidade invalida\n");
                invalid = 1; // Indica que a quantidade � inv�lida
            }
            else{
                ptr->prod.quantidade = quantidade; // Atualiza a quantidade do produto
                printf("\n\nQuantidade atualizada\n");
            }
            old_value = ptr->prod.valor; // Armazena o valor anterior do produto
            printf("\nDigite o novo valor: ");
            scanf("%f", &valor); // L� o novo valor do produto
            getchar();
            if (quantidade <= 0)
            {
                printf("\n\nValor invalido\n");
                invalid = 1; // Indica que o valor � inv�lido
            }
            else
            {
                ptr->prod.valor = valor; // Atualiza o valor do produto
                printf("\nValor Atualizado\n");
                invalid = 0;
            }

        }
        while(invalid == 1); // Repete enquanto a quantidade ou o valor forem inv�lidos

        printf("\nQuantidade anterior: %d\n", old_qnt);
        printf("\nQuantidade atual: %d\n", ptr->prod.quantidade);
        printf("\nValor anterior: R$%.2f\n", old_value);
        printf("\nValor atual: R$%.2f\n", ptr->prod.valor);

    }else
    {
        printf("\nProduto nao encontrado\n");
    }
}


Lista* excluir_produto(Lista* lista)//Fun�ao para excluir produto
{
    if(lista->inicio == NULL){
        puts("\nLista vazia\n");
        return lista;
    }
    unsigned long long codigo;
    visualizar_estoque(lista);
    printf("\nDigite o codigo do produto que deseja excluir:");
    scanf("%" SCNu64, &codigo);
    getchar();

    No* ptr = lista->inicio;
    while(ptr != NULL && ptr->prod.codigo != codigo){
        ptr = ptr->prox;
    }

    if(ptr != NULL){
       int valid;
       printf(" \n %s Encontrado\n Digite 1 para excluir ou outro numero para voltar ao menu\n", ptr->prod.nome);
       scanf("%d", &valid);
       if(valid == 1){
        if(ptr->ant == NULL){
            lista->inicio = ptr->prox;
        }else{
            ptr->ant->prox = ptr->prox;
        }
        if(ptr->prox != NULL){
            ptr->prox->ant = ptr->ant;
        }
        free(ptr);

        printf("\n**PRODUTO EXCLUIDO**\n");

    }else
    return lista;

    }else
    {
        printf("\nCodigo nao encontrado\n");
    }
    return lista; // Retorna o vetor atualizado
}

void salvar_produtos(Lista *lista)
{
    FILE *arq;
    arq = fopen("produtos.txt", "w"); // Abre o arquivo para escrita
    if(arq == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }
    No* ptr = lista->inicio;
    while(ptr != NULL)
    {
        fprintf(arq, "%" PRIu64 "\n%s\n%.2f\n%i\n%i\n", ptr->prod.codigo, ptr->prod.nome, ptr->prod.valor, ptr->prod.quantidade, ptr->prod.vendas_totais); // Escreve as informa��es do produto no arquivo
        ptr = ptr->prox;
    }
    fclose(arq); // Fecha o arquivo
    printf("\nProdutos salvos com sucesso.\n");
}

Lista* ler_produtos(Lista *lista)
{
    int result;
    lista->inicio = NULL;
    FILE *arq;
    arq = fopen("produtos.txt", "r"); // Abre o arquivo para leitura
    if(arq == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return NULL;
    }
    while(!feof(arq)) // L� uma linha do arquivo
    {

        No* novo = (No*) malloc(sizeof(No));
        if (novo == NULL){
            puts("Erro ao alocar memoria");
            return NULL;
        }


        produto prod;

        result = fscanf(arq, "%" SCNu64 "%s %f %i %i", &prod.codigo, prod.nome, &prod.valor, &prod.quantidade, &prod.vendas_totais);
        if(result != 5){
            free(novo);
            break;
        }
        novo->prod = prod;
        novo->ant = NULL;
        novo->prox = NULL;

        if(lista->inicio == NULL){
            lista->inicio = novo;
        }else{
            No* ptr = lista->inicio;
            while(ptr->prox != NULL){
                ptr = ptr->prox;

            }
            novo->ant = ptr;
            novo->prox = NULL;
            ptr->prox = novo;
        }
    }
    fclose(arq); // Fecha o arquivo
          printf("\nProdutos carregados com sucesso.\n");

    return lista;
}
void salvar_itens_vendidos(Lista_venda* lista, float total_compra){
    time_t agora;
    struct tm *info_time; // Struct que cont�m as unidades de tempo
    char nome_arq[50];

    time(&agora);
    info_time = localtime(&agora);

    // Salvando o nome do arquivo no formato Ano-Mes-Dia_Hora-Minuto-Segundo.txt
    sprintf(nome_arq, "%04d-%02d-%02d_%02d-%02d-%02d.txt", info_time->tm_year + 1900, info_time->tm_mon + 1,
            info_time->tm_mday, info_time->tm_hour, info_time->tm_min, info_time->tm_sec);

    FILE *arq = fopen(nome_arq, "w");
    if (arq == NULL) {
        puts("Erro ao abrir arquivo");
        return;
    }
    fprintf(arq, "Itens vendidos:\n");
    fprintf(arq, "\n------------------------------------------");
    // c�digo, nome, quantidade vendida, subtotal, total_compra;
    for (No_venda* it = lista->inicio; it != NULL; it = it->prox) {
        fprintf(arq, "\n------------------------------------------\n");
        fprintf(arq, "Codigo: %" PRIu64 "\n", it->Venda.p.codigo);
        fprintf(arq, "Nome: %s\n", it->Venda.p.nome);
        fprintf(arq, "Quantidade vendida: %i\n", it->Venda.qtd_vendida);
        fprintf(arq, "Valor: R$%.2f\n", it->Venda.subtotal);
        fprintf(arq, "\n------------------------------------------");
    }
    fprintf(arq, "Total: R$%.2f\n", total_compra);

    fclose(arq);

    printf("\nLista de itens vendidos salva no arquivo: %s\n", nome_arq);
}


void submenu_venda(Lista *lista)//Submenu de vendas
{
    int opcao;

    do
    {
        printf("------------------------------------------------------------------\n");
        printf("======================|Sub-menu Vendas |==========================\n");
        printf("------------------------------------------------------------------\n");
        printf("\n1\t\t\tRealizar venda\n2\t\t\tRelatorio de vendas \n3\t\t\tVoltar\n");
        printf("\n================================================================\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        getchar();



        switch (opcao)
        {
        case 1:
            if (lista == NULL)
            {
                printf("Nem produtos no estoque, impossivel realizar a venda");
                break;
            }
            realizar_venda(lista);
            break;
        case 2:
            relatorio_vendas(lista);
            break;
        case 3:
            printf("Retornando ao menu principal.\n");
            break;
        default:
            printf("Opcao invalida. Por favor, tente novamente.\n");
            break;
        }
    }
    while (opcao != 3); // Repete o loop at� que a op��o 3 (Voltar) seja escolhida
}



void liberar_vendas(Lista_venda *lista)
{
    if(lista->inicio->prox == NULL){
        free(lista->inicio);
        return;
    }
    No_venda *atual = lista->inicio;
    while(atual != NULL)
    {
        No_venda *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    lista->inicio = NULL;
}


void realizar_venda(Lista *lista)
{
    Lista_venda *lista_venda = (Lista_venda*) malloc(sizeof(Lista_venda));
    lista_venda->inicio = NULL;
    vendas aux;
    float retornopagamento;
    int venda_realizada = 0;
    unsigned long long cod_produto;
    int vender_outro,forma_pagamento;
    int quantidade;
    float total_compra = 0;

    do {
    visualizar_estoque(lista);

    if (lista->inicio == NULL) {
        printf("Nenhum produto cadastrado. Impossivel realizar venda.\n");
        return;
    }

    printf("\nDigite o codigo do produto que deseja vender: ");
    scanf("%" SCNu64,&cod_produto);
    getchar();

    No *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->prod.codigo == cod_produto) {
            break;
        }
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Produto nao encontrado.\n");
        printf("Digite 1 para tentar novamente ou outra coisa para sair\n");
        scanf("%d", &vender_outro);
        getchar();
        if(lista_venda->inicio == NULL && vender_outro != 1){
            return;
        }
        continue;
    }
    if (atual->prod.codigo == cod_produto) {

        printf("Digite a quantidade que deseja vender: ");
        scanf("%d", &quantidade);
        getchar();

        if (quantidade <= atual->prod.quantidade && quantidade > 0){
            atual->prod.quantidade -= quantidade;
            atual->prod.vendas_totais += quantidade;
            aux.p = atual->prod;
            aux.subtotal = quantidade * aux.p.valor;
            aux.qtd_vendida = quantidade;
            printf("Total a pagar: R$%.2f\n", aux.subtotal);
            total_compra += aux.subtotal;

            No_venda* novo = (No_venda*) malloc(sizeof(No_venda));
            novo->Venda = aux;
            novo->prox = NULL;

            if(lista_venda->inicio == NULL || novo->Venda.subtotal > lista_venda->inicio->Venda.subtotal){
                novo->prox = lista_venda->inicio;
                lista_venda->inicio = novo;
            }else{
                No_venda* ptr = lista_venda->inicio;

                while(ptr->prox != NULL && novo->Venda.subtotal < ptr->prox->Venda.subtotal){
                    ptr = ptr->prox;
                }
                novo->prox = ptr->prox;
                ptr->prox = novo;
            }
            venda_realizada++;
        } else {
                if(quantidade <= 0){
                    puts("Quantidade invalida");
            }else{
                printf("Quantidade insuficiente em estoque.\n");
            }
        }
    }

    printf("Deseja vender outro produto?\n1 - Sim\n2 - Nao\n");
    scanf("%d", &vender_outro);
    getchar();
    if(vender_outro == 1){
        atual = atual->prox;
    }

} while (vender_outro == 1);
if(venda_realizada == 0){
    return;
}
       do
    {
        imprimir_cupom_fiscal(lista_venda, total_compra);
        printf("\n---------------------------------\n");
        printf("========Formas de pagamento========\n");
        printf("\n---------------------------------\n");
        printf("\n1\t A vista\n2\t A prazo\n");
        printf("\n---------------------------------\n");
        printf("\nSelecione a forma de pagamento: ");
        scanf("%i", &forma_pagamento);
        getchar();

        if((forma_pagamento != 1) && (forma_pagamento != 2))
        {
            printf("\nPagamento inv�lido\n");
        }
    }while((forma_pagamento != 1) && (forma_pagamento != 2));
    do{
         retornopagamento = pagamento(total_compra, forma_pagamento);
    }while(retornopagamento == 0);

    salvar_itens_vendidos(lista_venda, total_compra);
    puts("\n");
    liberar_vendas(lista_venda);

}

void imprimir_cupom_fiscal(Lista_venda *lista, float total)
{
    No_venda *atual = lista->inicio;
    printf("------------------------------------------------------------------\n");
    printf("=========================| Cupom Fiscal |=========================\n");
    printf("------------------------------------------------------------------\n");
    printf("%10s | %20s | %18s | %8s\n", "Codigo", "Nome", "Quantidade Vendida", "Subtotal");
    printf("------------------------------------------------------------------\n");

    while (atual != NULL) {
        printf("%10" PRIu64 " | %20s| %18d | %8.2f\n", atual->Venda.p.codigo,  atual->Venda.p.nome, atual->Venda.qtd_vendida,  atual->Venda.subtotal);
        atual = atual->prox;
    }
     printf("------------------------------------------------------------------\n");
     printf("TOTAL: R$%.2f\n", total);
     printf("------------------------------------------------------------------\n");
}

float pagamento(float total, int f_pagamento)
{
    float totalpagamento = 0, valorcliente = 0, troco, falta;
    int resposta;
    switch(f_pagamento)
    {
    case 1:  //Pagamento a vista.
    {
        if((total <= 50.00) && (total > 0)) // 5% de desconto.
        {
            totalpagamento = total * 0.95;
        }
        else
        {
            if((total > 50.00) && (total < 100.00)) // 10% de desconto.
            {
                totalpagamento = total * 0.90;
            }
            else
            {
                if(total >= 100.00)  // 18% de desconto.
                {
                    totalpagamento = total * 0.82;
                }
            }
        }
        printf("\nValor da compra: R$%.2f\n", totalpagamento);

        do
        {
            printf("\nPrecisa de troco?\n1\t Sim\n2\t Nao\n");
            printf("\nResposta: ");
            scanf("%i", &resposta);
            getchar();
        }
        while(resposta!=1 && resposta!=2);

        if(resposta == 1)
        {
            do
            {
                printf("\nDigite o valor recebido do cliente: ");
                scanf("%f", &valorcliente);
                getchar();
                if(valorcliente > totalpagamento)
                {
                    troco = valorcliente - totalpagamento;
                    printf("\n\nTroco: R$%.2f\n", troco);
                }
                else
                {
                    troco = valorcliente - totalpagamento;
                    falta = troco * -1; //Se o valor recebido do cliente for menor que o valor do(s) produto(s), o cliente n�o pagou dinheiro suficiente.
                    printf("\nFaltam: R$%.2f\n", falta);
                }
            }
            while(valorcliente<totalpagamento);
        }
        else
        {
            totalpagamento = totalpagamento;
        }

    }

    break;
    case 2: //Pagamneto parcelado.
    {
        int parcelas;
        float vparcela;
        printf("\nParcelamento em ate 12 vezes\n");
        printf("\nDigite o numero de parcelas: ");
        scanf("%i", &parcelas);
        getchar();
        if((parcelas > 1) && (parcelas <= 3))  // acrescentado 5% no valor final.
        {
            totalpagamento = total * 1.05;
            vparcela = totalpagamento / parcelas;
            printf("\n\nValor das parcelas: %ix R$%.2f\n", parcelas, vparcela);
            printf("\nValor Final: R$%.2f\n", totalpagamento);
        }
        else
        {
            if((parcelas > 3) && (parcelas <= 12))  //acrescimo de 8% no valor final.
            {
                totalpagamento = total * 1.08;
                vparcela = totalpagamento / parcelas;
                printf("\nValor das parcelas: %i x R$%.2f\n", parcelas, vparcela);
                printf("\nValor Final: R$%.2f\n", totalpagamento);
            }
            else
            {
                printf("\nNumero de parcelas invalido\n");
                totalpagamento = 0;
            }
        }

    }
    break;
    default:
        printf("\nPagamento invalido\n");


    }
    return totalpagamento;

}void relatorio_vendas(Lista* lista)
{
    if (lista->inicio == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("------------------------------------------------------------------\n");
    printf("=====================| Relatorio de Vendas |=======================\n");
    printf("------------------------------------------------------------------\n");
    printf("%10s | %20s | %8s | %12s\n", "Codigo", "Nome", "Quantidade", "Vendas Totais");
    printf("------------------------------------------------------------------\n");

    for (No* it = lista->inicio; it != NULL; it = it->prox) {
        printf("%10" PRIu64 " | %20s | %8d | %12d\n", it->prod.codigo, it->prod.nome, it->prod.quantidade,it->prod.vendas_totais);
    }
}

