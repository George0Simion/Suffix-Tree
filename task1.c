/* SIMION George Constantin - 313CB */

#include "sufix.h"

void FreeTree(Tree arb)
/* Functie care elibereaza memoria arborelui */
{
    if (arb == NULL) return;
    int i = 0;
    for (i = 0; i < 27; i++) {
        FreeTree(arb->children[i]);
    }
    free(arb);
}

Tree CreateNode(char data)
/*Crearea unui nou nod din arbore */
{
    Tree newNode = malloc(sizeof(Node));
    if (!newNode) return NULL;

    newNode->data = data;
    int i = 0;
    for (i = 0; i < 27; i++) {
        newNode->children[i] = NULL;
    }                                                                           /* Creem nodul, punem data in el, si facem copii NULL */

    return newNode;
}

void insertSufix(Tree root, const char *suffix)
/* Inserarea unui nou nod in arborele de sufixe */
{
    Tree current = root;
    
    int i = 0;
    for (i = 0; suffix[i] != '\0'; i++) {
        int index = 0;
        if (suffix[i] == '$') index = 0;
        else index = suffix[i] - 'a' + 1;

        if (current->children[index] == NULL) {
            current->children[index] = CreateNode(suffix[i]);                   /* Copii fiind sortati alfabetic, in functie de indexul fiecareui copil il adaugam in arbore */
        }
        current = current->children[index];
    }
}

Tree CreateSufixTree(int nr_cuv, char **cuvinte)
/* Crearea arborelui de sufixe */
{
    Tree suffixTreeRoot = CreateNode('\0');                                     /* Creem un nod si punem ceva neimporant in el */

    int i = 0;
    for (i = 0; i < nr_cuv; i++) {
        int len = strlen(cuvinte[i]);

        int j = 0;
        for (j = 0; j <= len; j++) {
            char *suffix = malloc(len - j + 2);
            strcpy(suffix, cuvinte[i] + j);
            suffix[len - j] = '$';
            suffix[len - j + 1] = '\0';                                         /* Pentru fiecare sufix ii adaugam $ la final dupa il inseram in arbore */

            insertSufix(suffixTreeRoot, suffix);
            free(suffix);
        }
    }

    return suffixTreeRoot;
}