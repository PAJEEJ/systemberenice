#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

typedef struct
{
    unsigned long long codigo;
    char nome[25];
    float valor;
    int quantidade;
    int vendas_totais;
} produto;

typedef struct vendas{
    produto p;
    int qtd_vendida;
    float subtotal;
} vendas;

typedef struct No{
    produto prod;
    struct No* prox;
    struct No* ant;
}No;

typedef struct Lista{
    No* inicio;
}Lista;

typedef struct No_venda{
    struct vendas Venda;
    struct No_venda *prox;
}No_venda;

typedef struct Lista_venda{
    No_venda *inicio;
} Lista_venda;

void inicializar_lista(Lista* lista);

void desalocar_lista(Lista *lista);

Lista *cadastrar_produtos(Lista *lista, int novo_tam);

int verificar_codigo(Lista *lista, unsigned long long codigo);

int verificar_string(char str[25]);

void atualizar_produto(Lista *lista);

void visualizar_estoque(Lista *lista);

Lista* excluir_produto(Lista* lista);

Lista* ler_produtos(Lista* lista);

void salvar_produtos(Lista* lista);
//-----------------------------------------------------------------
void submenu_venda(Lista *lista);
void adicionar_venda(Lista *lista, produto p, int qtd_vendida);
void liberar_vendas(Lista_venda *lista);
void realizar_venda(Lista *lista);
void imprimir_cupom_fiscal(Lista_venda *lista, float total);
float pagamento(float total, int f_pagamento);
void relatorio_vendas(Lista* lista);
//---------------------------------------------------------------------
void salvar_itens_vendidos(Lista_venda* lista, float total_compra);

#endif // FUNCOES_H_INCLUDED
