#define POSFIXA

typedef struct No {
    double dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

typedef struct PilhaCaracter {
    char dado;
    struct PilhaCaracter *proximo;
} PilhaCaracter;

void inicializarPilha(Pilha *pilha) ;
void empilhar(Pilha *pilha, double valor);
double desempilhar(Pilha *pilha);
void limparMemoria(Pilha *pilha);
int precedencia(char operador);
void inicializarPilhaCaracter(PilhaCaracter *pilha);
void empilharCaracter(PilhaCaracter *pilha, char dado);
char desempilharCaracter(PilhaCaracter *pilha);
double avaliarExpressaoPosfixada(const char *expressao);
void traduzirParaPrefixada(const char *expressaoPosfixaAtual);