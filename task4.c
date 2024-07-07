/* SIMION George Constantin - 313CB */

#include "sufix.h"

TC_comp InitQComp()
/* Initializare coada */
{
    TC_comp coada = (TC_comp)malloc(sizeof(TCelC_comp));
    if (coada) {
        coada->inc = NULL;
        coada->sf = NULL;
    }

    return coada;
}

void IntrQCompact(TC_comp coada, NodeCompact *nod)
/* Introducere in coada */
{
    TListaC_comp aux = (TListaC_comp)malloc(sizeof(TCelulaC_comp));
    if(!aux) return;

    aux->nod = nod;
    aux->urm = NULL;

    if (coada->sf == NULL) {
        coada->inc = aux;
        coada->sf = aux;                                                                /* Daca coada are un sg element, si inc si sf pointeaza spre acelasi nod */

    } else {
        coada->sf->urm = aux;
        coada->sf = aux;                                                                /* Inseram in coada */
    }
}

NodeCompact *ExtrQComp(TC_comp *coada)
/* Extragere din coada */
{
    if ((*coada)->inc == NULL) return NULL;

    TListaC_comp temp = (*coada)->inc;
    NodeCompact *nod = temp->nod;
    (*coada)->inc = temp->urm;                                                          /* Extragem primul element din coada si verificam daca coada e goala */

    if ((*coada)->inc == NULL) {
        (*coada)->sf = NULL;
    }

    free(temp);
    return nod;
}

void BFSCompact(TreeCompact arbSufix, FILE *fout)
/* Algoritmul de BFS */
{
    if (arbSufix == NULL) {
        fprintf(fout, "Arbore Vid\n");
        return;
    }
    TC_comp c = InitQComp();                                                      /* Initializam coada pentru BFS */

    int i = 0;
    for (i = 0; i < 27; i++) {
        if (arbSufix->children[i] != NULL) {
            IntrQCompact(c, arbSufix->children[i]);                                     /* Adaugam in coada fiecare copil al arborelui */
        }
    }

    while (c->inc != NULL) {
        int level = 0;
        TListaC_comp aux = c->inc;
        for (aux = c->inc; aux != NULL; aux = aux->urm) {
            level++;                                                                    /* Numaram nivelul curent */
        }

        while (level > 0) {
            TreeCompact curent = ExtrQComp(&c);
            level--;                                                                    /* Scoatem un sufix din coada si scadem nivelul */

            fprintf(fout, "%s ", curent->info);
            int j = 0;
            for (j = 0; j < 27; j++) {
                if (curent->children[j] != NULL) {
                    IntrQCompact(c, curent->children[j]);                               /* Adaugam in coada fiecare copil al sufixului curent */
                }
            }
        }
        fprintf(fout, "\n");
    }

    free(c);
}

int nrCopii(Tree arb)
/* Functie care numara copii unui nod */
{
    int nr = 0, i = 0;
    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) {
            nr++;
        }
    }
    return nr;
}

int findCopil(Tree arb)
/* Functie care returneaza indexul primului copil */
{
    int i = 0;
    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) return i;
    }
    return -1;
}

TreeCompact compresie(Tree arb)
/* Functia care creaza noul arbore compresat */
{
    if (arb == NULL) return NULL;

    TreeCompact arb_comp = (TreeCompact)calloc(1, sizeof(NodeCompact));                     /* Initializam arborele compresat */
    if (!arb_comp) return NULL;
    arb_comp->index = 0;

    Tree curent = arb;

    while (curent && nrCopii(curent) == 1) {                                                /* Cat timp nodul curent are un singur copil */
        int index_copil = findCopil(curent);                                                /* Calculam indexul copilului */
        if (curent->children[index_copil]->data == '$') break;                              /* Daca copilul e $, nu mai continuam */

        arb_comp->info[arb_comp->index++] = curent->data;                                   /* Adaugam in arborele compresat */
        curent = curent->children[index_copil];                                             /* Trecem la urmatorul nod */
    }

    arb_comp->info[arb_comp->index] = curent->data;                                         /* Adaugam ultimul nod */

    if (curent) {
        int i = 0;
        for (i = 0; i < 27; i++) {
            if (curent->children[i] != NULL) {
                arb_comp->children[i] = compresie(curent->children[i]);                     /* Apelam recursiv pentru fiecare copil */
            }
        }
    }

    return arb_comp;
}

void FreeCompact(TreeCompact arb)
/* Functie care elibereaza memoria pentru arborele compresat */
{
    if (arb == NULL) return;

    int i = 0;
    for (i = 0; i < 27; i++) {
        FreeCompact(arb->children[i]);
    }
    free(arb);
}