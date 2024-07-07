/* SIMION George Constantin - 313CB */

#include "sufix.h"

int verifSufix(Tree arb, char *sufix)
/* Functie care verifica daca un sufix se afla in arbore */
{
    Tree curent = arb;

    int i = 0;
    for (i = 0; sufix[i] != '\0'; i++) {                                                /* Parcurgem sufixul */
        int index = 0;
        if (sufix[i] == '$') index = 0;
        else index = sufix[i] - 'a' + 1;                                                    /* Calculam indexul */

        if (curent->children[index] == NULL) {                                              /* Daca nu exista copil cu indexul respectiv, sufixul nu se afla in arbore */
            return 0;
        }
        curent = curent->children[index];                                                   /* Trecem la urmatorul nod */
    }
    return 1;
}