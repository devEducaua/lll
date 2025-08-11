#include <dirent.h>
#define APP_DIR "/usr/share/applications/"

void exec_command(struct dirent *de, DIR *dr);
void show_apps(struct dirent *de);
