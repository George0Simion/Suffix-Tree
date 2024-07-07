/* SIMION George Constantin - 313CB */

#include "sufix.h"

int nrFrunze(Tree arb)
/* Functie care numara frunzele din arbore */
{
    if (arb == NULL) return 0;
    bool isLeaf = true;

    int i = 0;
    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) {
            isLeaf = false;                                                         /* Verificam daca e frunza */
            break;
        }
    }

    if (isLeaf) {
        return 1;                                                                   /* Daca e frunza returnam 1 */
    }

    int nr = 0;
    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) {
            nr += nrFrunze(arb->children[i]);                                       /* Verificam mai departe fiecare nod si il adunam */
        }
    }
    return nr;
}

int countSufix(Tree arb, int K)
/* Functie care numara sufixele de dimensiune K */
{
    if (arb == NULL) return 0;
    if (K == 0 && arb->data == '$') return 1;                                       /* Daca am ajuns la finalul unui sufix si K == 0, returnam 1 */

    int count = 0, i = 0;
    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) {
            count += countSufix(arb->children[i], K - 1);                            /* Pentru fiecare copil scadem K si verificam mai departe copii lui */
        }
    }
    return count;
}

int nrSufixe(Tree arb, int K)
/* Functie care numara sufixele pornind de la radacina */
{
    if (arb == NULL) return 0;

    int total = 0, i = 0;
    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) {
            total += countSufix(arb->children[i], K);                                 /* Pentru fiecare copil al radacinei apelam functia de numarare a sufixelor */
        }
    }
    return total;
}

int nrMaxDescendenti(Tree arb, int max)
/* Functie care numara maximul de descendenti */
{
    if (arb == NULL) return 0;

    int nr = 0, i = 0;
    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) {
            nr++;                                                                      /* Verificam daca are copii si ii numaram */
        }
    }
    if (nr > max) max = nr;                                                             /* Daca nr de copii e mai mare decat maximul, il schimbam */

    for (i = 0; i < 27; i++) {
        if (arb->children[i] != NULL) {
            nrMaxDescendenti(arb->children[i], max);                                    /* Pentru fiecare copil apelam functia */
        }
    }
    return max;
}