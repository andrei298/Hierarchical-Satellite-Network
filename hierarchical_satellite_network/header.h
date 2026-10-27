#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Satelit{

    int frecventa;
    char *nume;
    struct Satelit *stanga;
    struct Satelit *dreapta;

}Satelit;

typedef struct Minheap{

    Satelit *info[100];
    int dim;

}Minheap;

int compara_sateliti(Satelit *a, Satelit *b);
void minheap_up(Minheap * minheap, int idx);
void minheap_down(Minheap * minheap, int idx);
void inserare_minheap(Minheap * minheap, Satelit * satelit);
Satelit * extragere_minim_satelit(Minheap * minheap);
Satelit * construire_retea_arbore(Minheap * minheap, int * nr);
Satelit * radacina_retea(FILE *f, int * nr);
void afisare_retea_arbori (Satelit * radacina, int nr, FILE * g);
void decodificare_sateliti (Satelit * radacina, FILE * f, FILE * g);
void parcurgere_decodificare_sateliti(Satelit * radacina, Satelit * satelit_curent, int count, char sir[], int lungime, FILE * g);
void codificare_sateliti (Satelit * radacina, FILE * f, FILE * g);
void parcurgere_codificare_sateliti (Satelit * satelit, char sir[], char codificare[], int nivel, FILE * g);
int nr_niveluri_arbore (Satelit * satelit);
void gasire_parinte_comun (Satelit * radacina, int nr, FILE * f, FILE * g);
void afisare_parinte_comun (Satelit * satelit, char ** vector_sateliti, int nr_sateliti, int nr, FILE * g);
void eliberare_arbore (Satelit * radacina);
