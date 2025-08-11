#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define APP_DIR "/usr/share/applications/"

int main(int argc, char **argv) {
    struct dirent *de;

    if (argc < 2) {
        printf("Please give the name");
        exit(0);
    }

    char *file = strcat(argv[1], ".desktop");

    DIR *dr = opendir(APP_DIR);

    if (dr == NULL) {
        printf("Failed opening the directory\n");
        exit(1);
    }

    while ((de = readdir((dr))) != NULL) {
        if (strcmp(de->d_name, file) == 0) {
            printf("%s\n", de->d_name);

            char path[300];
            snprintf(path, sizeof(path), "%s%s", APP_DIR, de->d_name);
            // char *path = strcat(dir, de->d_name);

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
            break;
        }
    }

    closedir(dr);
    return 0;
}
