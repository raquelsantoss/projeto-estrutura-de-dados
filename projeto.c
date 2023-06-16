#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_DESCRICAO 100
#define MAX_MARCA 50
#define MAX_SITE 100
#define MAX_TELEFONE 15
#define MAX_UF 3
#define MAX_PRODUTOS 100
#define MAX_FABRICANTES 100

typedef struct Fabricante
{
    char marca[MAX_MARCA];
    char site[MAX_SITE];
    char telefone[MAX_TELEFONE];
    char uf[MAX_UF];
} Fabricante;

typedef struct Produto
{
    char descricao[MAX_DESCRICAO];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    Fabricante fabricante;
} Produto;

typedef struct ProdutoNode
{
    Produto produto;
    struct ProdutoNode *next;
} ProdutoNode;

typedef struct FabricanteNode
{
    Fabricante fabricante;
    struct FabricanteNode *next;
} FabricanteNode;

ProdutoNode *produtos = NULL;
FabricanteNode *fabricantes = NULL;
int numProdutos = 0;
int numFabricantes = 0;

void adicionarProduto(Produto produto)
{
    if (numProdutos >= MAX_PRODUTOS)
    {
        printf("Limite máximo de produtos atingido.\n");
        return;
    }

    ProdutoNode *newNode = (ProdutoNode *)malloc(sizeof(ProdutoNode));
    newNode->produto = produto;
    newNode->next = NULL;

    if (produtos == NULL)
    {
        produtos = newNode;
    }
    else
    {
        ProdutoNode *current = produtos;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    numProdutos++;
}

void adicionarFabricante(Fabricante fabricante)
{
    if (numFabricantes >= MAX_FABRICANTES)
    {
        printf("Limite máximo de fabricantes atingido.\n");
        return;
    }

    FabricanteNode *newNode = (FabricanteNode *)malloc(sizeof(FabricanteNode));
    newNode->fabricante = fabricante;
    newNode->next = NULL;

    if (fabricantes == NULL)
    {
        fabricantes = newNode;
    }
    else
    {
        FabricanteNode *current = fabricantes;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    numFabricantes++;
}

void listarMarcas()
{
    printf("Lista de marcas:\n");
    FabricanteNode *current = fabricantes;
    while (current != NULL)
    {
        printf("- Marca: %s\n", current->fabricante.marca);
        current = current->next;
    }
}

void listarProdutos()
{
    printf("Lista de produtos:\n");
    ProdutoNode *current = produtos;
    while (current != NULL)
    {
        printf("- Descrição: %s\n", current->produto.descricao);
        printf("  Peso: %.2f\n", current->produto.peso);
        printf("  Valor de compra: %.2f\n", current->produto.valorCompra);
        printf("  Valor de venda: %.2f\n", current->produto.valorVenda);
        printf("  Valor do lucro: %.2f\n", current->produto.valorLucro);
        printf("  Percentual do lucro: %.2f%%\n", current->produto.percentualLucro);
        printf("  Fabricante: %s\n", current->produto.fabricante.marca);
        printf("\n");
        current = current->next;
    }
}

void listarProdutosPorEstado(const char *uf)
{
    printf("Produtos do estado %s:\n", uf);
    ProdutoNode *current = produtos;
    while (current != NULL)
    {
        if (strcmp(current->produto.fabricante.uf, uf) == 0)
        {
            printf("- Descrição: %s\n", current->produto.descricao);
            printf("  Peso: %.2f\n", current->produto.peso);
            printf("  Valor de compra: %.2f\n", current->produto.valorCompra);
            printf("  Valor de venda: %.2f\n", current->produto.valorVenda);
            printf("  Valor do lucro: %.2f\n", current->produto.valorLucro);
            printf("  Percentual do lucro: %.2f%%\n", current->produto.percentualLucro);
            printf("  Fabricante: %s\n", current->produto.fabricante.marca);
            printf("\n");
        }
        current = current->next;
    }
}

void listarProdutosPorMarca(const char *marca)
{
    printf("Produtos da marca %s:\n", marca);
    ProdutoNode *current = produtos;
    while (current != NULL)
    {
        if (strcmp(current->produto.fabricante.marca, marca) == 0)
        {
            printf("- Descrição: %s\n", current->produto.descricao);
            printf("  Peso: %.2f\n", current->produto.peso);
            printf("  Valor de compra: %.2f\n", current->produto.valorCompra);
            printf("  Valor de venda: %.2f\n", current->produto.valorVenda);
            printf("  Valor do lucro: %.2f\n", current->produto.valorLucro);
            printf("  Percentual do lucro: %.2f%%\n", current->produto.percentualLucro);
            printf("  Fabricante: %s\n", current->produto.fabricante.marca);
            printf("\n");
        }
        current = current->next;
    }
}

void encontrarProdutoMaisCaro()
{
    ProdutoNode *current = produtos;
    float maxValor = 0.0;

    while (current != NULL)
    {
        if (current->produto.valorVenda > maxValor)
        {
            maxValor = current->produto.valorVenda;
        }
        current = current->next;
    }

    printf("Produto(s) mais caro(s):\n");
    current = produtos;

    while (current != NULL)
    {
        if (current->produto.valorVenda == maxValor)
        {
            printf("- Descrição: %s\n", current->produto.descricao);
            printf("  Valor de venda: %.2f\n", current->produto.valorVenda);
            printf("  Fabricante: %s\n", current->produto.fabricante.marca);
            printf("\n");
        }
        current = current->next;
    }
}

void encontrarProdutoMaisBarato()
{
    ProdutoNode *current = produtos;
    float minValor = current->produto.valorVenda;

    while (current != NULL)
    {
        if (current->produto.valorVenda < minValor)
        {
            minValor = current->produto.valorVenda;
        }
        current = current->next;
    }

    printf("Produto(s) mais barato(s):\n");
    current = produtos;

    while (current != NULL)
    {
        if (current->produto.valorVenda == minValor)
        {
            printf("- Descrição: %s\n", current->produto.descricao);
            printf("  Valor de venda: %.2f\n", current->produto.valorVenda);
            printf("  Fabricante: %s\n", current->produto.fabricante.marca);
            printf("\n");
        }
        current = current->next;
    }
}

void ordenarProdutosPorValor()
{
    int i, j;
    int trocado;
    ProdutoNode *current;
    Produto temp;

    if (produtos == NULL)
    {
        return;
    }

    for (i = 0; i < numProdutos - 1; i++)
    {
        current = produtos;
        trocado = 0;

        for (j = 0; j < numProdutos - i - 1; j++)
        {
            if (current->produto.valorVenda > current->next->produto.valorVenda)
            {
                temp = current->produto;
                current->produto = current->next->produto;
                current->next->produto = temp;
                trocado = 1;
            }
            current = current->next;
        }

        if (trocado == 0)
        {
            break;
        }
    }
}

void ordenarProdutosPorLucro()
{
    int i, j;
    int trocado;
    ProdutoNode *current;
    Produto temp;

    if (produtos == NULL)
    {
        return;
    }

    for (i = 0; i < numProdutos - 1; i++)
    {
        current = produtos;
        trocado = 0;

        for (j = 0; j < numProdutos - i - 1; j++)
        {
            if (current->produto.valorLucro > current->next->produto.valorLucro)
            {
                temp = current->produto;
                current->produto = current->next->produto;
                current->next->produto = temp;
                trocado = 1;
            }
            current = current->next;
        }

        if (trocado == 0)
        {
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    Produto produto;
    Fabricante fabricante;

    do
    {
        printf("Menu:\n");
        printf("1. Adicionar produto\n");
        printf("2. Adicionar fabricante\n");
        printf("3. Listar todas as marcas\n");
        printf("4. Listar todos os produtos\n");
        printf("5. Listar os produtos de um determinado estado\n");
        printf("6. Listar os produtos de uma determinada marca\n");
        printf("7. Apresentar o estado onde está registrado o produto mais caro\n");
        printf("8. Apresentar o fabricante onde está registrado o produto mais barato\n");
        printf("9. Listar todos os produtos em ordem crescente de valor\n");
        printf("10. Listar todos os produtos em ordem crescente de maior 'valor do lucro'\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        system("cls");

        switch (opcao)
        {
        case 1:
            printf("Adicionar produto:\n");
            printf("Descrição: ");
            scanf(" %[^\n]s", produto.descricao);
            printf("Peso: ");
            scanf("%f", &produto.peso);
            printf("Valor de compra: ");
            scanf("%f", &produto.valorCompra);
            printf("Valor de venda: ");
            scanf("%f", &produto.valorVenda);
            produto.valorLucro = produto.valorVenda - produto.valorCompra;
            produto.percentualLucro = (produto.valorLucro / produto.valorCompra) * 100;
            printf("Marca: ");
            scanf(" %[^\n]s", fabricante.marca);
            printf("Site: ");
            scanf(" %[^\n]s", fabricante.site);
            printf("Telefone: ");
            scanf(" %[^\n]s", fabricante.telefone);
            printf("UF: ");
            scanf(" %[^\n]s", fabricante.uf);
            produto.fabricante = fabricante;
            adicionarProduto(produto);
            adicionarFabricante(fabricante);
            printf("Produto adicionado com sucesso!\n\n");
            break;

        case 2:
            printf("Adicionar fabricante:\n");
            printf("Marca: ");
            scanf(" %[^\n]s", fabricante.marca);
            printf("Site: ");
            scanf(" %[^\n]s", fabricante.site);
            printf("Telefone: ");
            scanf(" %[^\n]s", fabricante.telefone);
            printf("UF: ");
            scanf(" %[^\n]s", fabricante.uf);
            adicionarFabricante(fabricante);
            printf("Fabricante adicionado com sucesso!\n\n");
            break;

        case 3:
            listarMarcas();
            printf("\n");
            break;

        case 4:
            listarProdutos();
            printf("\n");
            break;

        case 5:
            printf("Digite o estado: ");
            scanf(" %[^\n]s", fabricante.uf);
            listarProdutosPorEstado(fabricante.uf);
            printf("\n");
            break;

        case 6:
            printf("Digite a marca: ");
            scanf(" %[^\n]s", fabricante.marca);
            listarProdutosPorMarca(fabricante.marca);
            printf("\n");
            break;

        case 7:
            encontrarProdutoMaisCaro();
            printf("\n");
            break;

        case 8:
            encontrarProdutoMaisBarato();
            printf("\n");
            break;

        case 9:
            ordenarProdutosPorValor();
            printf("Lista de produtos em ordem crescente de valor:\n");
            listarProdutos();
            printf("\n");
            break;

        case 10:
            ordenarProdutosPorLucro();
            printf("Lista de produtos em ordem crescente de maior 'valor do lucro':\n");
            listarProdutos();
            printf("\n");
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
