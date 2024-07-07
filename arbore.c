/* SIMION George Constantin - 313CB */

#include "sufix.h"

void cerinte(char * cerinta, Tree sufixTree, char *argv[], int nr_sufixe, FILE *fin, FILE *fout)
/* Functie care verifica / executa cerinta */
{
    if (strcmp(cerinta, "-c1") == 0) {
        BFS(sufixTree, fout);                                                       /* Arborele de sufixe este creat, apelam BFS */

    } else if (strcmp(cerinta, "-c2") == 0) {
        int param = atoi(argv[2]);

        fprintf(fout, "%d\n", nrFrunze(sufixTree));
        fprintf(fout, "%d\n", nrSufixe(sufixTree, param));
        fprintf(fout, "%d\n", nrMaxDescendenti(sufixTree, 0));                      /* Interpretam al doilea argument ca un int si facem statisticile pe arbore */

    } else if (strcmp(cerinta, "-c3") == 0) {
        int i = 0;
        for (i = 0; i < nr_sufixe; i++) {
            char *sufix_caut = malloc(sizeof(char) * 100);
            fscanf(fin, "%s", sufix_caut);
            strcat(sufix_caut, "$");                                                /* Alocam memorie, citim sufixele si le adaugam $ la final */

            fprintf(fout, "%d\n", verifSufix(sufixTree, sufix_caut));

            free(sufix_caut);                                                       /* Pentru fiecare sufix apelam functia de verificare si afisam daca apartine sau nu */
        }

    } else if (strcmp(cerinta, "-c4") == 0) {
        TreeCompact arb_comp = compresie(sufixTree);
        BFSCompact(arb_comp, fout);
        FreeCompact(arb_comp);                                                      /* Creem noul arbore, il afisam si eliberam memoria */
    }
}

void citire(int argc, char *argv[])
/* Functie pentru citire + analizarea argumentelor variabile */
{
    char *cerinta = argv[1];                                                        /* Cerinta = primul argument */

    FILE *fin = fopen(argv[argc - 2], "r");
    FILE *fout = fopen(argv[argc - 1], "w");
    if (!fin || !fout) return;                                                      /* Deschidem fisiere de I/O si verificam deschiderea acestora */

    int nr = 0, nr_sufixe = 0;
    fscanf(fin, "%d", &nr);                                                         /* Citim nr de arbori */

    if (strcmp(cerinta, "-c3") == 0) {
        fscanf(fin, "%d", &nr_sufixe);
    }                                                                               /* Citim nr de sufixe pentru cerinta 3 */

    char **cuv = malloc(sizeof(char*) * nr);
    int i = 0;
    for (i = 0; i < nr; i++) {
        cuv[i] = malloc(sizeof(char) * 100);
        fscanf(fin, "%s", cuv[i]);
    }                                                                               /* Alocam 100 de caractere pentru fiacre cuvant citim si le stocam intr-un vector */

    Tree sufixTree = CreateSufixTree(nr, cuv);                                      /* Creem arborele de sufixe */
    cerinte(cerinta, sufixTree, argv, nr_sufixe, fin, fout);                        /* In functie de cerinta executam functiile necesare */

    for (i = 0; i < nr; i++) {
        free(cuv[i]);
    }
    free(cuv);

    FreeTree(sufixTree);

    fclose(fin);
    fclose(fout);                                                                    /* Eliberam memoria si inchidem fisierele */
}

int main(int argc, char *argv[]) {
    citire(argc, argv);                                                              /* Apelam functia de citire / interpretare a argumentelor variabile */
    
    return 0;
}