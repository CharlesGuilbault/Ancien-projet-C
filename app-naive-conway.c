/**
 * @file app-naive-conway.c
 *
 * @brief affiche le contenue d'un fichier en lui applicant la simulation en executant ./app-naive-conway ./nom_du_fichier
 *
 * @author M. Poadi
 *
 */

#include "naive_loader.h"
#include "naive_universe.h"
#include "naive_conway.h"
#include "naive_ppm_writer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
    // testing if a filename has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide a file name!\n");
        exit(EXIT_FAILURE);
    }
    
    // open file. The filename is the first argument on the command
    // line, hence stored in argv[1]
    FILE *p_file = NULL;

    p_file = fopen(argv[1], "r");
    
    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    universe u = naive_load(argv[1]);
    naive_simulation(u, 'y');
    free(u.universe_elt);
    fclose(p_file);
    return 0;

}





