#include "posfixa.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    const char *expressao1 = "3 4 + 5 *";
    double resultado1 = avaliarExpressaoPosfixada(expressao1);
    printf("Teste 1, Resultado: %.2lf\n", resultado1);
    traduzirParaPrefixada(expressao1);

    const char *expressao2 = "7 2 * 4 +";
    double resultado2 = avaliarExpressaoPosfixada(expressao2);
    printf("Teste 2, Resultado: %.2lf\n", resultado2);
    traduzirParaPrefixada(expressao2);

    const char *expressao3 = "8 5 2 4 + * +";
    double resultado3 = avaliarExpressaoPosfixada(expressao3);
    printf("Teste 3, Resultado: %.2lf\n", resultado3);
    traduzirParaPrefixada(expressao3);

    const char *expressao4 = "6 2 / 3 + 4 *";
    double resultado4 = avaliarExpressaoPosfixada(expressao4);
    printf("Teste 4, Resultado: %.2lf\n", resultado4);
    traduzirParaPrefixada(expressao4);

    const char *expressao5 = "9 5 2 8 * 4 + * +";
    double resultado5 = avaliarExpressaoPosfixada(expressao5);
    printf("Teste 5, Resultado: %.2lf\n", resultado5);
    traduzirParaPrefixada(expressao5);

    const char *expressao6 = "2 3 + l 5 /";
    double resultado6 = avaliarExpressaoPosfixada(expressao6);
    printf("Teste 6, Resultado: Aprox. %.3lf\n", resultado6);
    traduzirParaPrefixada(expressao6);

    const char *expressao7 = "10 l 3 ^ 2 +";
    double resultado7_corrigido = avaliarExpressaoPosfixada(expressao7);
    printf("Teste 7, Resultado: %.0lf\n", resultado7_corrigido);
    traduzirParaPrefixada(expressao7);

    const char *expressao8 = "45 60 + 30 c *";
    double resultado8 = avaliarExpressaoPosfixada(expressao8);
    printf("Teste 8, Resultado: Aprox. %.2lf\n", resultado8);
    traduzirParaPrefixada(expressao8);

    const char *expressao9_corrigida = "0.5 45 s ^ 2 +";
    double resultado9_corrigido = avaliarExpressaoPosfixada(expressao9_corrigida);
    printf("Teste 9, Resultado: Aprox. %.2lf\n", resultado9_corrigido);
    traduzirParaPrefixada(expressao9_corrigida);


    return 0;
}