/**
 * A simple program to load a initial grid data file and "print" it on the
 * console
 *
 * Ex. of usage:
 *
 * ./app-ex-loader ./data/glider.txt
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
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

    // read dimensions on first line
    int width         = 0;
    int height        = 0;
    int fscanf_result = 0;

    fscanf_result = fscanf(p_file, "%d %d", &width, &height);

    if (fscanf_result != 2) {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    printf("grid dimensions (width first): %d x %d\n", width, height);

    // read simulation steps on second line
    int steps = 0;

    fscanf_result = fscanf(p_file, "%d\n", &steps);

    if (fscanf_result != 1) {
        fprintf(stderr, "Second line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    printf("simulation steps: %d\n", steps);

    // read following height lines
    // line_buffer contains a line and is a correct string
    // width + 2 is needed to hold the '\0' end of string character
    // and the newline character
    char line_buffer[width + 2];

    for (int i = 0; i < height; i++) {
        fgets(line_buffer, width + 2, p_file);

        printf("line %2d: %s", i, line_buffer);
    }

    fclose(p_file);

    return EXIT_SUCCESS;
}
