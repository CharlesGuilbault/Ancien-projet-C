#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("%s is called with %d parameters\n",
           argv[0], argc - 1);

    for (int i = 1; i < argc; i++) {
        printf("parameter #%d: %s\n", i, argv[i]);
    }

    return 0;
}
