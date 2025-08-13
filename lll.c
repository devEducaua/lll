#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define APP_DIR "/usr/share/applications/"

void exec_command(struct dirent *de, DIR *dr);
void show_apps(struct dirent *de);

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

void show_apps(struct dirent *de) {
    printf("%s\n", de->d_name);
}

void exec_command(struct dirent *de, DIR *dr) {
    printf("%s\n", de->d_name);

    char path[300];
    snprintf(path, sizeof(path), "%s%s", APP_DIR, de->d_name);

    printf("path: %s\n", path);

    FILE *fptr = fopen(path, "r");

    if (!fptr) {
        closedir(dr);
        exit(1);
    }

    char buf[256];

    while (fgets(buf, sizeof(buf), fptr)) {
        char *sptr = strstr(buf, "Exec=");
        if (sptr != NULL) {
            sptr += 5;

            for (char *p = sptr; *p; p++) {
                if (*p == '%' && (*(p+1) == 'f' || *(p+1) == 'u')) {
                    *p = '\0';
                }
            }

            printf("command: %s\n", sptr);
            system(sptr);

            break;
        }
    }
    fclose(fptr);
}
