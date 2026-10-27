#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

// functie care primeste 2 pointeri la 2 sateliti
// returneaza negativ sau pozitiv in functie de compararea celor 2
// ajuta la ordonarea minheapului
int compara_sateliti (Satelit *a, Satelit *b) {

    // compara intai dupa frecventa, daca frecventa e egala compara dupa nume
    if (a -> frecventa != b -> frecventa) {
        return a -> frecventa - b -> frecventa;
    } else {
        return strcmp(a -> nume, b -> nume);
    }
}

// functie care primeste indexul unui satelit si adresa minheapului
// muta satelitul cu indexul dat "mai sus" pana cand este mai mare decat parintele
void minheap_up (Minheap * minheap, int idx) {

    if(idx == 0) return;

    // comparam satelitul dat cu satelitul parinte
    int idx_parinte = (idx - 1) / 2;
    if (compara_sateliti(minheap -> info[idx], minheap -> info[idx_parinte]) < 0) {

        // facem interschimbare daca satelitul dat este mai mic ca parintele si reapelam functia cu indexul parintelui
        Satelit * temp = minheap -> info[idx];
        minheap -> info[idx] = minheap -> info[idx_parinte];
        minheap -> info[idx_parinte] = temp;
        idx = idx_parinte;

        // functia este reapelata pana cand ajunge pe pozitia corespunzatoare
        minheap_up(minheap, idx);

    }
}

// functie care primeste indexul unui satelit si adresa minheapului
// muta satelitul cu indexul dat "mai jos" pana cand este mai mic decat ambii copii sau pana devine frunza
void minheap_down (Minheap * minheap, int idx) {
    
    // minim_idx va contine indexul satelitului copil cel mai mic
    int minim_idx = idx;
    int idx_copil_stanga = idx * 2 + 1;

    // daca exista copilul din stanga, il comparam cu satelitul dat
    if (idx_copil_stanga < minheap -> dim && compara_sateliti(minheap -> info[minim_idx], minheap -> info[idx_copil_stanga]) > 0)
        minim_idx = idx_copil_stanga;

    int idx_copil_dreapta = idx * 2 + 2;

    // facem compararea si cu satelitul copil din dreapta, daca exista
    if (idx_copil_dreapta < minheap -> dim && compara_sateliti(minheap -> info[minim_idx], minheap -> info[idx_copil_dreapta]) > 0)
        minim_idx = idx_copil_dreapta;

    // minim_idx diferit de idx => satelitul dat este mai mare decat cel putin unul din copii
    // facem interschimbarea dintre copilul minim si satelitul dat apoi reapelam functia cu indexul copilului minim
    if (minim_idx != idx) {

        Satelit * temp = minheap -> info[idx];
        minheap -> info[idx] = minheap -> info[minim_idx];
        minheap -> info[minim_idx] = temp;
        idx = minim_idx;

        // functia este reapelata pana cand ajunge pe pozitia corespunzatoare
        minheap_down(minheap, idx);

    }
}

// functie care insereaza un satelit la sfarsitul minheapului
void inserare_minheap (Minheap * minheap, Satelit * satelit) {

    minheap -> info [minheap -> dim] = satelit;
    minheap_up(minheap, minheap -> dim);
    minheap -> dim ++;

}

// functie care extrage satelitul minim din minheap (primul)
Satelit * extragere_minim_satelit (Minheap * minheap) {

    if (minheap -> dim == 0)
        return NULL;

    Satelit * satelit = minheap -> info[0];

    // punem in locul lui temporar ultimul satelit si scadem cu 1 dimensiunea minheapului
    minheap -> info[0] = minheap -> info[minheap -> dim - 1];
    minheap -> dim --;

    // ordonam minheapul la forma corecta
    minheap_down(minheap, 0);
    return satelit;

}

// functie care creeaza arborele binar de sateliti, cu tot cu cei de legatura
// returneaza radacina arborelui
// nr ajuta la retinerea numarului de sateliti din arbore
Satelit * construire_retea_arbore (Minheap * minheap, int * nr) {

    // cand dimensiunea minheapului ajunge la 1 acesta ramane doar cu radacina
    while (minheap -> dim != 1) {

        // extragem cate 2 sateliti (cei mai mici)
        (*nr) ++;
        Satelit * a = extragere_minim_satelit(minheap);
        Satelit * b = extragere_minim_satelit(minheap);

        // creem satelitul de legatura corespunzator
        Satelit * legatura = (Satelit *) malloc (sizeof(Satelit));
        legatura -> frecventa = a -> frecventa + b -> frecventa;
        legatura -> nume = (char *) malloc ((strlen(a -> nume) + strlen(b -> nume) + 1) * sizeof(char));
        strcpy(legatura -> nume, a -> nume);
        strcat(legatura -> nume, b -> nume);

        // legam satelitul auxiliar cu cei 2 sateliti
        legatura -> stanga = a;
        legatura -> dreapta = b;

        // il inseram la sfarsitul minheapului pentru urmatoarele legaturi
        inserare_minheap(minheap, legatura);

    }
    
    // extragem ultimul satelit din minheap (radacina) si il returnam
    Satelit * radacina = extragere_minim_satelit(minheap);
    return radacina;
}

// functia principala, citeste satelitii, ii pune in minheap, creeaza arborele
// practic imbina toate functiile precedente si conform inputului creeaza arborele de sateliti specific
// returneaza radacina arborelui de care avem nevoie pentru urmatoarele functii
Satelit * radacina_retea (FILE *f, int * nr) {

    int nr_sateliti;
    fscanf(f, "%d", &nr_sateliti);
    (*nr) = nr_sateliti;

    Minheap * minheap = (Minheap *) malloc (sizeof(Minheap));
    minheap -> dim = 0;

    for (int i = 1; i <= nr_sateliti; i++) {

        int frecventa;
        char nume[16];
        fscanf(f, "%d", &frecventa);
        fscanf(f, "%s", nume);

        Satelit * satelit = (Satelit *) malloc (sizeof(Satelit));
        satelit -> frecventa = frecventa;
        satelit -> nume = (char *) malloc ((strlen(nume) + 1) * sizeof(char));
        strcpy(satelit -> nume, nume);

        satelit -> stanga = NULL;
        satelit -> dreapta = NULL;

        inserare_minheap(minheap, satelit);

    }

    Satelit * radacina = construire_retea_arbore(minheap, nr);
    free (minheap);
    return radacina;
}

// afiseaza satelitii pe niveluri
void afisare_retea_arbori (Satelit * radacina, int nr, FILE * g) {

    // coada in care punem pe rand satelitii pe niveluri
    // inc va reprezenta indicele primului satelit de pe nivelul pe care afisam
    // sf va reprezenta cu 1 mai mult decat indicele ultimului satelit de pe nivelul pe care afisam
    Satelit * coada[nr];
    int inc = 0;
    int sf = 0;

    // punem radacina
    coada[sf] = radacina;
    sf ++;

    // cand inc nu mai e mai mic ca sf => nu mai avem nivele de afisat in arbore
    while (inc < sf) {

        // parcurgem nivelul curent si afisam satelitii
        for (int i = inc; i < sf; i ++) {

            fprintf(g, "%d-%s", coada[i] -> frecventa, coada[i] -> nume);

            if (i == sf - 1) {
                fprintf(g, "\n");
            } else {
                fprintf(g, " ");
            }
        }

        // pentru fiecare satelit de pe nivelul tocmai afisat, verificam, pe rand, daca mai are copii
        // ii punem in coada, actualizam indicii inc si sf pentru noul nivel care urmeaza sa fie afisat
        int aux = sf;
        for (int i = inc; i < aux; i++) {

            inc ++;
            if (coada[i] -> stanga != NULL) {
                coada[sf] = coada[i] -> stanga;
                sf ++;
            }

            if (coada[i] -> dreapta != NULL) {
                coada[sf] = coada[i] -> dreapta;
                sf ++;
            }
        }
    }
}

// functia principala pentru taskul 2
void decodificare_sateliti (Satelit * radacina, FILE * f, FILE * g) {

    // citim numarul de decodificari pe care trebuie sa le facem
    int nr_decodificari;
    fscanf(f, "%d", &nr_decodificari);
    fgetc(f);

    // citim codificarile pe rand si apelam functia care ne afiseaza satelitii specifici
    for (int i = 1; i <= nr_decodificari; i ++) {
        
        int count = 0;
        char codificare[1001];
        fgets(codificare, 1001, f);
        codificare[strlen(codificare) - 1] = '\0'; 
        
        parcurgere_decodificare_sateliti(radacina, radacina, count, codificare, strlen(codificare), g);
    }
}

// count este initial 0, retine caracterul curent din codificare
void parcurgere_decodificare_sateliti (Satelit * radacina, Satelit * satelit_curent, int count, char sir[], int lungime, FILE * g) {

    // daca count este egal cu lungimea codificarii, inseamna ca am terminat, daca mai e o frunza de afisat, o afisam
    if (count == lungime && satelit_curent -> stanga == NULL && satelit_curent -> dreapta == NULL) {
        
        fprintf(g, "%s\n", satelit_curent -> nume);
        return;
    }

    if (count == lungime) {

        fprintf(g, "\n");
        return;
    }
    
    // daca am ajuns la o frunza, o afisam si reincepem cautarea pentru restul codificarii de la radacina 
    if (satelit_curent -> stanga == NULL && satelit_curent -> dreapta == NULL) {

        fprintf(g, "%s ", satelit_curent -> nume);
        parcurgere_decodificare_sateliti(radacina, radacina, count, sir, lungime, g);
        return;
    }

    // in functie de valoarea caracterului curent (1/0), apelam functia mergand in directia corespunzatoare in arbore
    if (sir[count] == '0') {
        
        count ++;
        parcurgere_decodificare_sateliti(radacina, satelit_curent -> stanga, count, sir, lungime, g);
        return;

    }

    if (sir[count] == '1') {

        count ++;
        parcurgere_decodificare_sateliti(radacina, satelit_curent -> dreapta, count, sir, lungime, g);
        return;
    }
}

// functie care returneaza numarul de niveluri din arbore (radacina se considera pe nivelul 1)
int nr_niveluri_arbore (Satelit * satelit) {

    if (satelit == NULL)
        return 0;

    int st = nr_niveluri_arbore (satelit -> stanga);
    int dr = nr_niveluri_arbore (satelit -> dreapta);
    if (st <= dr) return 1 + dr;
    else return 1 + st;
}

// functia principala pentru taskul 3
void codificare_sateliti (Satelit * radacina, FILE * f, FILE * g) {

    // citim numarul de codificari pe care trebuie sa le facem
    int nr_codificari;
    fscanf(f, "%d", &nr_codificari);
    fgetc(f);
    int nr_niveluri = nr_niveluri_arbore(radacina);

    // citim decodificarile pe rand si apelam functia care ne afiseaza codificarile specificice
    for (int i = 1; i <= nr_codificari; i ++) {

        char decodificare[16];
        fgets(decodificare, 16, f);
        decodificare[strlen(decodificare) - 1] = '\0';

        // in acest sir vom retine codificarea pe care o vom afisa
        // este de dimensiunea maxima posibila, cu ajutorul functiei care ne calculeaza numarul de niveluri din arbore
        char sir[nr_niveluri + 1];
        for (int j = 0; j < nr_niveluri + 1; j ++)
        sir[j] = '0';

        parcurgere_codificare_sateliti (radacina, sir, decodificare, 0, g);
    }
}

void parcurgere_codificare_sateliti (Satelit * satelit, char sir[], char decodificare[], int nivel, FILE * g) {

    if (satelit == NULL)
        return;

    // daca decodificarea este la fel ca numele satelitului afisam codificarea lui retinuta in variabila sir
    if (strcmp(satelit -> nume, decodificare) == 0) {

        for (int i = 0; i < nivel; i ++)
        fprintf(g, "%c", sir[i]);
        return;
    }

    // cu ajutorul variabilei "nivel" actualizam sirul cu codificarea
    // reapelam functia si pentru dreapta si pentru stanga cu sirul si nivelul actualizat
    sir[nivel] = '0';
    parcurgere_codificare_sateliti (satelit -> stanga, sir, decodificare, nivel + 1, g);

    sir[nivel] = '1';
    parcurgere_codificare_sateliti (satelit -> dreapta, sir, decodificare, nivel + 1, g);
}

// functia principala pentru taskul 4
void gasire_parinte_comun (Satelit * radacina, int nr, FILE * f, FILE * g) {

    // citim numarul de sateliti
    int nr_sateliti;
    fscanf(f, "%d", &nr_sateliti);
    fgetc(f);
    char **vector_sateliti = (char**) malloc (nr_sateliti * sizeof(char *));

    // citim pe rand satelitii pentru care trebuie sa gasim parintele si ii punem in vectorul de sateliti
    for (int i = 0; i < nr_sateliti; i ++) {

        char satelit[16];
        fgets(satelit, 16, f);
        satelit[strlen(satelit) - 1] = '\0';
        vector_sateliti[i] = (char *) malloc ((strlen(satelit) + 1) * sizeof(char));
        strcpy(vector_sateliti[i], satelit);
    }

    // apelam functia care ne gaseste parintele comun, apoi eliberam memoria pentru vectorul de sateliti
    afisare_parinte_comun (radacina, vector_sateliti, nr_sateliti, nr, g);
    for (int i = 0; i < nr_sateliti; i++)
    free (vector_sateliti[i]);
    free(vector_sateliti);
}

// parcurgem arborele de sateliti pe niveluri
// ultimul satelit gasit care contine in numele lui numele tuturor satelitilor dati este cel parinte
// adica acela care contine doar numele satelitilor dati, fara alti sateliti
void afisare_parinte_comun (Satelit * satelit, char ** vector_sateliti, int nr_sateliti, int nr, FILE * g) {

    // coada in care punem pe rand satelitii pe niveluri
    // inc va reprezenta indicele primului satelit de pe nivelul pe care il verificam
    // sf va reprezenta cu 1 mai mult decat indicele ultimului satelit de pe nivelul pe care verificam
    Satelit * coada[nr];
    int inc = 0;
    int sf = 0;

    // punem radacina
    coada[sf] = satelit;
    // maxim va contine la sfarsit indicele parintelui
    int maxim = 0;
    sf ++;

    // cand inc nu mai e mai mic ca sf => nu mai avem nivele de verificat in arbore
    while (inc < sf) {

        // parcurgem nivelul curent si verificam satelitii
        for (int i = inc; i < sf; i ++) {

            int ok = 1;
            for (int j = 0; j < nr_sateliti; j ++)
            if (strstr(coada[i] -> nume, vector_sateliti[j]) == 0) ok = 0;
            if (ok == 1 && i > maxim)
                maxim = i;
        }

        // pentru fiecare satelit de pe nivelul tocmai verificat, verificam, pe rand, daca mai are copii
        // ii punem in coada, actualizam indicii inc si sf pentru noul nivel care urmeaza sa fie verificat
        int aux = sf;
        for (int i = inc; i < aux; i++) {

            inc ++;
            if (coada[i] -> stanga != NULL) {
                coada[sf] = coada[i] -> stanga;
                sf ++;
            }

            if (coada[i] -> dreapta != NULL) {
                coada[sf] = coada[i] -> dreapta;
                sf ++;
            }
        }
    }
    
    // afisam numele parintelui
    fprintf(g, "%s\n", coada[maxim] -> nume);
}

// functie care elibereaza memoria pentru satelitii din arbore si pentru numele lor
void eliberare_arbore (Satelit * radacina) {

    if (radacina == NULL) return;
    eliberare_arbore (radacina -> stanga);
    eliberare_arbore (radacina -> dreapta);
    if (radacina != NULL) {

        free(radacina -> nume);
        radacina -> nume = NULL;
        free(radacina);
        radacina = NULL;

    }
}
