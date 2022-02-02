#include "list_conway.h"
#include "list_universe.h"
#include "linked_list_cell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void list_step(universe u, linked_list universe_elt) {

    int n = size(u.list);
    int alive_i[n];
    int alive_j[n];
    int *coord = calloc(3,sizeof(int));
    for (int k=0; k<n; k++) {
        get_element(u.list, k, coord);
        alive_i[k] = coord[0];
        alive_j[k] = coord[1];
    }

    for (int m=0; m<n; m++) {
        int v = 0;
        get_element(u.list, m, coord);
        for (int k=0; k<n; k++) {
            if (k != m) {
                int i = alive_i[k];
                int j = alive_j[k];
                int v = 0;
                voisin_a(v, i, j, coord);
            }
        }
        if ((v != 2) && (v !=3)) {
            go_to_position(u.list, m)->alive_next = false;
        }
    } 
    free(coord);
    // fonction non terminée
}

void voisin_a(int v, int i, int j, int *coord) { // ajoute 1 à v si (i,j) est une case voisine de (coord[0], coord[1])

    if ((i = coord[0]-1) && (j == coord[1]-1)) { // si (i,j) est en haut à gauche de (coord[0], coord[1])
        v++;
    }
    if ((i = coord[0]-1) && (j == coord[1])) { // on regarde ici en haut de (coord[0], coord[1])
        v++;
    }
    if ((i = coord[0]-1) && (j == coord[1]+1)) { // en haut à droite de (coord[0], coord[1])
        v++;
    }
    if ((i = coord[0]) && (j == coord[1]-1)) { // à gauche
        v++;
    }
    if ((i = coord[0]) && (j == coord[1]+1)) { // à droite
        v++;
    }
    if ((i = coord[0]+1) && (j == coord[1]-1)) { // en bas à gauche
        v++;
    }
    if ((i = coord[0]+1) && (j == coord[1])) { // en bas
        v++;
    }
    if ((i = coord[0]+1) && (j == coord[1]+1)) { // en bas à droite
        v++;
    }
}




