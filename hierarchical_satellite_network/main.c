#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char *argv[]) {

    (void) argc;
    char *task = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];
    int nr = 0;
    
    if (strcmp(task, "-c1") == 0) {
        
        FILE *f = fopen(input_file, "r");
        FILE *g = fopen(output_file, "w");
        Satelit * radacina = radacina_retea(f, &nr);
        afisare_retea_arbori (radacina, nr, g);
        eliberare_arbore (radacina);
        fclose(f);
        fclose(g);

    } else if (strcmp(task, "-c2") == 0) {

        FILE *f = fopen(input_file, "r");
        FILE *g = fopen(output_file, "w");
        Satelit * radacina = radacina_retea(f, &nr);
        decodificare_sateliti (radacina, f, g);
        eliberare_arbore (radacina);
        fclose(f);
        fclose(g);

    } else if (strcmp(task, "-c3") == 0) {

        FILE *f = fopen(input_file, "r");
        FILE *g = fopen(output_file, "w");
        Satelit * radacina = radacina_retea(f, &nr);
        codificare_sateliti (radacina, f, g);
        eliberare_arbore (radacina);
        fclose(f);
        fclose(g);

    } else if (strcmp(task, "-c4") == 0) {

        FILE *f = fopen(input_file, "r");
        FILE *g = fopen(output_file, "w");
        Satelit * radacina = radacina_retea(f, &nr);
        gasire_parinte_comun (radacina, nr, f, g);
        eliberare_arbore (radacina);
        fclose(f);
        fclose(g);

    } else {

        // rezolva task5

    }

return 0;
}


