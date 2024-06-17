#include "posfixa.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>

void inicializarPilha(Pilha *pilha)
{
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, double valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

double desempilhar(Pilha *pilha)
{
    if (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    }
    else
    {
        fprintf(stderr, "Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

void limparMemoria(Pilha *pilha)
{
    while (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        pilha->topo = temp->proximo;
        free(temp);
    }
}

int precedencia(char operador)
{
    if (operador == '+' || operador == '-')
    {
        return 1;
    }
    else if (operador == '*' || operador == '/')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void inicializarPilhaCaracter(PilhaCaracter *pilha)
{
    pilha->proximo = NULL;
}

void empilharCaracter(PilhaCaracter *pilha, char dado)
{
    PilhaCaracter *novo = malloc(sizeof(PilhaCaracter));
    novo->dado = dado;
    novo->proximo = pilha->proximo;
    pilha->proximo = novo;
}

char desempilharCaracter(PilhaCaracter *pilha)
{
    if (pilha->proximo == NULL)
    {
        return ' ';
    }
    PilhaCaracter *temp = pilha->proximo;
    char dado = temp->dado;
    pilha->proximo = temp->proximo;
    free(temp);
    return dado;
}

double avaliarExpressaoPosfixada(const char *expressao)
{
    Pilha pilha;
    inicializarPilha(&pilha);

    for (int i = 0; expressao[i] != '\0'; ++i)
    {
        if (isdigit(expressao[i]) || (expressao[i] == '.' && isdigit(expressao[i + 1])))
        {
            empilhar(&pilha, strtod(&expressao[i], NULL));
            while (isdigit(expressao[i]) || expressao[i] == '.')
            {
                ++i;
            }
        }
        else if (expressao[i] == ' ' || expressao[i] == '\t')
        {
            continue;
        }
        else
        {
            double operando2 = desempilhar(&pilha);
            double operando1;
            switch (expressao[i])
            {
            case '+':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, operando1 + operando2);
                break;
            case '-':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, operando1 - operando2);
                break;
            case '*':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, operando1 * operando2);
                break;
            case '/':
                if (operando2 != 0.0)
                {
                    operando1 = desempilhar(&pilha);
                    empilhar(&pilha, operando1 / operando2);
                }
                else
                {
                    fprintf(stderr, "Erro na expressão: Divisão por zero\n");
                    limparMemoria(&pilha);
                    exit(EXIT_FAILURE);
                }
                break;
            case '^':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, pow(operando1, operando2));
                break;
            case 'l':
                if (operando2 > 0)
                {
                    empilhar(&pilha, log10(operando2));
                }
                else
                {
                    fprintf(stderr, "Erro na expressão: Logaritmo de número não positivo\n");
                    limparMemoria(&pilha);
                    exit(EXIT_FAILURE);
                }
                break;
            case 's':
                empilhar(&pilha, sin(operando2));
                break;
            case 'c':
                empilhar(&pilha, cos(operando2));
                break;
            case 't':
                empilhar(&pilha, tan(operando2));
                break;
            case 'a':
                if (operando2 >= -1 && operando2 <= 1)
                {
                    empilhar(&pilha, asin(operando2));
                }
                else
                {
                    fprintf(stderr, "Erro na expressão: Arco seno fora do domínio [-1, 1]\n");
                    limparMemoria(&pilha);
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                fprintf(stderr, "Erro na expressão: Operador inválido '%c'\n", expressao[i]);
                limparMemoria(&pilha);
                exit(EXIT_FAILURE);
            }
        }
    }

    if (pilha.topo == NULL)
    {
        fprintf(stderr, "Erro: Pilha vazia\n");
        limparMemoria(&pilha);
        exit(EXIT_FAILURE);
    }

    double resultado = desempilhar(&pilha);
    limparMemoria(&pilha);
    return resultado;
}

void traduzirParaPrefixada(const char *expressaoPosfixaAtual)
{
    PilhaCaracter pilha;
    inicializarPilhaCaracter(&pilha);

    char expressaoPrefixa[100];
    int index = 0;

    for (int i = strlen(expressaoPosfixaAtual) - 1; i >= 0; --i)
    {
        if (isdigit(expressaoPosfixaAtual[i]) || (expressaoPosfixaAtual[i] == '.' && isdigit(expressaoPosfixaAtual[i - 1])))
        {
            expressaoPrefixa[index++] = expressaoPosfixaAtual[i];
        }
        else if (expressaoPosfixaAtual[i] == ' ' || expressaoPosfixaAtual[i] == '\t')
        {
            continue;
        }
        else if (expressaoPosfixaAtual[i] == '+' || expressaoPosfixaAtual[i] == '-' ||
                 expressaoPosfixaAtual[i] == '*' || expressaoPosfixaAtual[i] == '/' ||
                 expressaoPosfixaAtual[i] == '^' || expressaoPosfixaAtual[i] == 'l' ||
                 expressaoPosfixaAtual[i] == 's' || expressaoPosfixaAtual[i] == 'c' ||
                 expressaoPosfixaAtual[i] == 't' || expressaoPosfixaAtual[i] == 'a')
        {
            empilharCaracter(&pilha, expressaoPosfixaAtual[i]);
        }
        else if (expressaoPosfixaAtual[i] == 'r')
        {
            empilharCaracter(&pilha, 'r');
            --i;
        }
        else
        {
            while (pilha.proximo != NULL && pilha.proximo->dado != '(' && (precedencia(expressaoPosfixaAtual[i]) <= precedencia(pilha.proximo->dado)))
            {
                char op = desempilharCaracter(&pilha);
                expressaoPrefixa[index++] = op;
            }
            empilharCaracter(&pilha, expressaoPosfixaAtual[i]);
        }
    }

    while (pilha.proximo != NULL)
    {
        char op = desempilharCaracter(&pilha);
        expressaoPrefixa[index++] = op;
    }

    printf("Expressao Pre-fixada: ");
    for (int i = index - 1; i >= 0; --i)
    {
        printf("%c ", expressaoPrefixa[i]);
    }

    printf("\n\n");
}