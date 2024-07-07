# Task 1 - Arbore de Sufixe

## Cuprins
1. [Task 1 - Arbore de Sufixe](#task-1---arbore-de-sufixe)
2. [Task 2 - Statistici Arbore](#task-2---statistici-arbore)
3. [Task 3 - Căutare Sufix în Arbore](#task-3---căutare-sufix-în-arbore)
4. [Task 4 - Arbore de Sufixe Compresat](#task-4---arbore-de-sufixe-compresat)
5. [Checker-ul](#checker-ul)

## Task 1 - Arbore de Sufixe

Pentru realizarea acestui task și crearea arborelui de sufixe, citesc toate cuvintele într-un vector de cuvinte, iar mai apoi la fiecare cuvânt pun la final caracterul `$` și îl introduc în arbore. Pentru introducerea în arbore mă bazez pe proprietatea arborelui de sufixe, mai exact că toți copiii unui nod sunt în ordine alfabetică. Așa că pentru introducere calculez indexul fiecărei litere și creez nodul cu litera respectivă.

Pentru afișarea de tip BFS am folosit o coadă cu operațiile ei de bază: introducere și extragere. Pentru algoritmul de BFS am folosit un index în structură ca să rețin nivelul la care sunt. La început, bag toți copiii rădăcinii în coadă și după scot câte unul pe rând, scad nivelul, bag copiii nodului curent în coadă și afișez litera din nod.

## Task 2 - Statistici Arbore

Pentru realizarea acestui task am implementat 3 funcții diferite care prezentau câteva statistici ale arborelui:
1. **Număr frunze:** Verific recursiv fiecare nod dacă are toți copiii NULL, iar dacă îi are adaug 1.
2. **Număr sufixe de dimensiune dată:** Încep prin a număra sufixele fără rădăcină, apoi folosindu-mă de o funcție ajutătoare adun recursiv pentru fiecare copil, scăzând dimensiunea lui K la fiecare apel, câte 1 dacă dimensiunea lui K a ajuns 0 și sunt pe nodul cu sufixul `$`.
3. **Numărul maxim de descendenți:** Mă folosesc de un maxim primit ca parametru, inițializat cu 0, iar apoi recursiv număr copiii fiecărui nod și verific dacă este mai mare ca maxim.

## Task 3 - Căutare Sufix în Arbore

Pentru realizarea acestui task am avut de verificat dacă câteva sufixe se află în arbore sau nu. Inițial citesc fiecare sufix și îi concatenez caracterul `$`, iar apoi îl caut în arbore parcurgând fiecare caracter al acestuia, calculându-i indexul din arbore și verificând dacă există un copil al nodului curent care are acel index. În caz că există, merg pe următorul nod și pe următorul caracter din sufixul căutat, iar dacă nu există, returnez 0. În final, în caz că există și nu am returnat 0, returnez 1.

## Task 4 - Arbore de Sufixe Compresat

Pentru realizarea acestui task mi-am creat un nou arbore folosind o structură asemănătoare cu cea de la arborele de sufixe, doar că în componenta acesteia am folosit un vector de caractere și un index care reprezintă indexul ultimului caracter adăugat în acel nod. Pentru adăugarea în acest arbore, parcurg recursiv arborele inițial și verific pentru fiecare nod dacă există și are un singur copil. Dacă aceste 2 proprietăți sunt îndeplinite, calculez indexul unde acest copil este în arborele inițial, îi adaug litera în cuvântul care urmează să se creeze și merg pe acel copil în continuare ca să continui verificarea. În caz în care copilul este caracterul `$`, opresc căutarea pentru că acesta nu trebuie adăugat în compresie. Mai departe, în caz de numărul de copii este diferit de 1, adaug în nodul curent caracterul din arborele inițial. Apoi apelez recursiv funcția pentru fiecare copil.

Pentru afișarea de tip BFS am folosit aproximativ aceleași funcții ca cele de la BFS-ul inițial, doar cu mici schimbări. Funcțiile de inițializare, introducere, extragere au rămas la fel, doar că au fost adaptate la un nou tip de nod, care poate să conțină și un cuvânt, nu numai litere. Pentru BFS inițial, initializez coada, apoi introduc copiii rădăcinii în coadă. Apoi, cât timp coada nu e goală, calculez nivelul și după cât timp nivelul este diferit de 0, extrag câte un nod din coadă, scad nivelul, afișez cuvântul din nod, apoi introduc toți copiii ne-NULL în coadă.

## Checker-ul

Programul are 0 memory-leak-uri conform utilitarului valgrind.
