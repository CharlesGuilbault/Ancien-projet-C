#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list_cell.h"

void merge_sort(linked_list l) {
    linked_list head = l;

    // si la liste chainée comporte 1 ou 0 cellule :
    if ((head == NULL) || (head->next == NULL)) {
        return;
    } 
  
    // séparation de la liste en deux
    linked_list *sep = separate(head);

    // tri des deux sous listes
    merge_sort(sep[0]); 
    merge_sort(sep[1]); 
  
    
    l = sortedmerge(sep[0], sep[1]);
    free(sep);
}

linked_list *separate(linked_list s) {
    linked_list *sep = malloc(2*sizeof(linked_list));
    linked_list a; 
    linked_list b;

    linked_list fin; 
    linked_list milieu;
    milieu = s;
    fin = s->next;
  
    // lorsque fin avance de 2, milieu avance de 1
    while (fin != NULL) {
        fin = fin->next;
        if (fin != NULL) {
            milieu = milieu->next;
            fin = fin->next;
        }
    }

    // milieu se situe au milieu de la liste
    a = s; 
    b = milieu->next; 
    milieu->next = NULL;
    
    sep[0] = a;
    sep[1] = b;
    return sep;
}

linked_list sortedmerge(linked_list a, linked_list b) { 
    linked_list result = NULL; 
    // si a ou b sont des listes vides
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 

    // on determine dans quel ordre disposer a et b
    if (a->i < b->i) { 
        result = a; 
        result->next = sortedmerge(a->next, b); 
    }
    if (a->i > b->i) { 
        result = b; 
        result->next = sortedmerge(a, b->next); 
    } 
    else if (a->i == b->i) {
        if (a->j < b->j) { 
            result = a; 
            result->next = sortedmerge(a->next, b); 
        }
        else if (a->j > b->j) { 
            result = b; 
            result->next = sortedmerge(a, b->next);
        }
    }
    return (result); 
}

linked_list go_to_position(const linked_list list, int pos) {
    linked_list current_cell = list;

    for (int i = 0; i < pos; i++) {
        current_cell = current_cell->next;
    }

    return current_cell;
}

linked_list nil() {
    return NULL;
}

linked_list cons(linked_list list, int i, int j, bool alive_next) {
    linked_list new_cell = malloc(sizeof(cell));

    if (new_cell == NULL) {
        printf("problem with creating cell in cons!\n");
    }

    new_cell->i = i;
    new_cell->j = j;
    new_cell->alive_next = alive_next;
    new_cell->next  = list;

    return new_cell;
}

int size(const linked_list list) {
    int length = 0;
    cell *current_cell = list;

    while (current_cell != NULL) {
        current_cell = current_cell->next;
        length++;
    }

    return length;
}

void get_element(const linked_list list, int pos,int *coord) {
    // not very efficient to use size function but...
    int length = size(list);

    assert(list != NULL && pos >= 0 && pos < length);

    // go to position
    cell *p_cell = go_to_position(list, pos);
    coord[0] = p_cell->i;
    coord[1] = p_cell->j;
    coord[2] = p_cell->alive_next;
}

bool is_empty(const linked_list list) {
    return list == NULL;
}


linked_list insert_element(linked_list list, int i, int j, bool alive_next) {

    linked_list new_cell = malloc(sizeof(cell));
    linked_list *ptr_cell = NULL;
    ptr_cell = &list;

    if (new_cell == NULL) {
        printf("problem with creating cell in insert_element!\n");
    }

    new_cell->i = i;
    new_cell->j = j;
    new_cell->alive_next = alive_next;

    if (list == NULL) {
        new_cell->next = NULL;
        return new_cell;
    } else {
        new_cell->next = (*ptr_cell)->next;
        list->next = new_cell;
        merge_sort(list);
        return list;
    }
}

void remove_element(linked_list list, int pos) {
    cell *current_cell = list;
    cell *old_cell     = NULL;

    // not very efficient to use size function but...
    int length = size(list);

    assert(list != NULL && pos >= 0 && pos < length);

    if (pos == 0) {
        list = current_cell->next;
        free(current_cell);

        return;
    }

    current_cell       = go_to_position(list, pos - 1);
    old_cell           = current_cell->next;
    current_cell->next = old_cell->next;

    free(old_cell);
}

void deallocate_list(linked_list list) {
    cell *temp_cell    = NULL;
    cell *current_cell = list;

    while (current_cell != NULL) {
        temp_cell    = current_cell;
        current_cell = current_cell->next;
        free(temp_cell);
    }
}

void print_list(const linked_list list) {
    cell *current_cell = list;

    printf("[ ");

    while (current_cell != NULL) {
        printf("%d", current_cell->i);
        printf("%d", current_cell->j);
        printf("%d", current_cell->alive_next);

        if (current_cell->next != NULL) {
            printf(", ");
            current_cell = current_cell->next;
        } else {
            printf(" ");
            break;
        }
    }

    printf("]");
}