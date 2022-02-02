#include "list_universe.h"
#include "linked_list_cell.h"
#include "list_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



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

    universe u = list_load(argv[1]);
    print_list_universe(u);
    deallocate_list(u.list);
    fclose(p_file);
    return 0;

}