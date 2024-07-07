/* SIMION George Constantin - 313CB */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

// Structura pentru arborele de sufixe
typedef struct node {
    char data;                                                                   // Litera din fiecare celula
    struct node *children[27];                                                   // 27 de copii pentru fiecare celula
} Node, *Tree;

// Coada pentru BFS
typedef struct celulaCoada{
    Node *nod;
    struct celulaCoada *pre, *urm;
} TCelulaCoada, *TListaCoada;

typedef struct coada{
    TListaCoada inc, sf;
    int index;
} TcelulaCodita, *TCoada;

/* Task 4 */
// Structura pentru arborele compresat 
typedef struct node_compact {
    char info[100];                                                               // Cuvantul din fiecare celula
    int index;                                                                    // Index care reprezinta pozitia ultimei litere pe care am adaugat-o in cuvantul compresat
    struct node_compact *children[27];
} NodeCompact, *TreeCompact;

// Coda pentru BFS-ul arborelui compresat
typedef struct celulaCoadaCompact{
    NodeCompact *nod;
    struct celulaCoadaCompact *pre, *urm;
} TCelulaC_comp, *TListaC_comp;

typedef struct coadaCompact{
    TListaC_comp inc, sf;
} TCelC_comp, *TC_comp;

/* Citire + cerintele cu argumente variabile */
void cerinte(char * cerinta, Tree sufixTree, char *argv[], int nr_sufixe, FILE *fin, FILE *fout);
void citire(int argc, char *argv[]);

/* Task 1 */
/* Creare arbore de sufixe */
Tree CreateNode(char data);
void insertSufix(Tree root, const char *sufix);
Tree CreateSufixTree(int nr_cuv, char **cuvinte);
void citire(int argc, char *argv[]);

/* Task 1 */
/* Functii BFS */
TCoada InitQ();
void IntrQ(TCoada coada, Node *nod);
Node *ExtrQ(TCoada *coada);
void BFS(Tree sufix, FILE *fout);
void FreeTree(Tree arb);

/* Task 2 */
int nrFrunze(Tree arb);
int countSufix(Tree arb, int K);
int nrSufixe(Tree arb, int K);
int nrMaxDescendenti(Tree arb, int max);

/* Task 3 */
int verifSufix(Tree arb, char *sufix);

/* Task 4 */
int findCopil(Tree arb);
int nrCopii(Tree arb);
TreeCompact compresie(Tree arb);
TC_comp InitQComp();
void IntrQCompact(TC_comp coada, NodeCompact *nod);
NodeCompact *ExtrQComp(TC_comp *coada);
void BFSCompact(TreeCompact arbSufix, FILE *fout);
void FreeCompact(TreeCompact arb);