#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "func.h"

int main(int argc, char **argv) {
    struct dirent *de;

    DIR *dr = opendir(APP_DIR);

    if (argc == 1) {
        while ((de = readdir(dr)) != NULL) {
            show_apps(de);
        }
    }

    char *file = strcat(argv[1], ".desktop");


    if (dr == NULL) {
        printf("Failed opening the directory\n");
        exit(1);
    }

    while ((de = readdir((dr))) != NULL) {
        if (strcmp(de->d_name, file) == 0) {
            exec_command(de, dr);
            break;
        }
    }

    closedir(dr);
    return 0;
}
