/* SIMION George Constantin - 313CB */

#include "sufix.h"

TCoada InitQ()
/* Initializare coada */
{
    TCoada coada = (TCoada)malloc(sizeof(TcelulaCodita));
    if (coada) {
        coada->inc = NULL;
        coada->sf = NULL;
    }

    return coada;
}

void IntrQ(TCoada coada, Node *nod)
/* Introducere in coada */
{
    TListaCoada aux = (TListaCoada)malloc(sizeof(TCelulaCoada));
    if(!aux) return;

    aux->nod = nod;

    if (coada->inc == NULL && coada->sf == NULL) {
        aux->urm = NULL;
        aux->pre = NULL;

        coada->inc = aux;
        coada->sf = aux;                                                        /* Daca coada are un sg element, si inc si sf pointeaza spre acelasi nod */

    } else {
        aux->urm = NULL;
        aux->pre = coada->sf;

        coada->sf->urm = aux;
        coada->sf = aux;                                                           /* Inseram in coada */
    }
}

Node *ExtrQ(TCoada *coada)
/* Extragere din coada */
{
    if ((*coada)->inc == NULL) return NULL;

    TListaCoada temp = (*coada)->inc;
    Node *nod = temp->nod;
    (*coada)->inc = temp->urm;                                                      /* Extragem primul element din coada si verificam daca coada e goala */

    if ((*coada)->inc == NULL) {
        (*coada)->sf = NULL;
    }

    free(temp);
    return nod;
}

void BFS(Tree arbSufix, FILE *fout)
/* Algoritmul de BFS */
{
    if (arbSufix == NULL) {
        fprintf(fout, "Arbore Vid\n");
        return;
    }                                                                                   /* Arborele e vid */

    TCoada c = InitQ();                                                                 /* Initializam coada */
    c->index = 0;
    int j = 0;
    for (j = 0; j < 27; j++) {
        if (arbSufix->children[j] != NULL) {
            IntrQ(c, arbSufix->children[j]);
            c->index++;                                                                 /* Punem copii radacinei in coada */
        }
    }

    int noduri_parcurse = 0;
    int noduri_nivel = c->index;

    while (c->inc != NULL) {
        Tree curent = ExtrQ(&c);
        noduri_nivel--;                                                                 /* Extragem primul element din coada si scadem nivelul */

        if (curent != NULL) {
            int j = 0;
            for (j = 0; j < 27; j++) {
                if (curent->children[j] != NULL) {
                    IntrQ(c, curent->children[j]);                                      /* Daca nodul curent are copii, ii punem in coada */
                    noduri_parcurse++;
                }
            }
            if (curent->data != '\0') {
                fprintf(fout, "%c ", curent->data);                                     /* Printam nodul curent */
            }
        }
        if (noduri_nivel == 0) {
            fprintf(fout, "\n");                                                        /* Daca am terminat nivelul printam \n */
            noduri_nivel = noduri_parcurse;
            noduri_parcurse = 0;
        }
    }
    free(c);
}