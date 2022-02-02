#include "linked_list_cell.h"
#include "list_universe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


universe list_load(char *argv) {
    FILE * p_file = NULL;
    p_file = fopen(argv, "r");
    
    
    // read dimensions on first line
    int width         = 0;
    int height        = 0;
    int fscanf_result = 0;

    fscanf_result = fscanf(p_file, "%d %d", &width, &height);

    if (fscanf_result != 2) {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    // read simulation steps on second line
    int steps = 0;

    fscanf_result = fscanf(p_file, "%d\n", &steps);

    if (fscanf_result != 1) {
        fprintf(stderr, "Second line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    universe u;
    u.width = width;
    u.height = height;
    u.nb_step = steps;
    // read following height lines
    // line_buffer contains a line and is a correct string
    // width + 2 is needed to hold the '\0' end of string character
    // and the newline character
    char line_buffer[width + 2];
    int k = 0;
    int alive_i[width*height]; // on crée des tableaux de coordonnées des cellules vivantes tels que (alive_i[k], alive_j[k]) soit la kième cellule vivante recensée
    int alive_j[width*height]; // width*height est la taille maximale atteignable par ces tableaux
    for (int i = 0; i < height; i++) {
        fgets(line_buffer, width + 2, p_file);
        for (int j = 0; j < width; j++) {
            if (line_buffer[j] == 'o') {
                alive_i[k] = i;
                alive_j[k] = j;
                k++;
            }
        }
    }
    if (k != 0) {
        u.list = cons(nil(), alive_i[0], alive_j[0], true);
    }
    for (int m=1; m<k; m++) {
        insert_element(u.list, alive_i[m], alive_j[m], true);
    }
    fclose(p_file);
    
    return u;
}
