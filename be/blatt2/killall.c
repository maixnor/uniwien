extern "C" {
  #include <sys/types.h>
  #include <unistd.h>
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>

int main() {
    FILE *fp;
    char buffer[1024];
    struct dirent *ent;

    if ((fp = fopen("/proc/self/task/file", "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    while(fread(fp, &buffer, 1024, sizeof(struct dirent)) > 0) {
        buffer[1023] = '\0';
        sscanf(buffer, "%s", &ent->d_name);

        if ((ent->d_type == DT_REG || ent->d_type == DT_DIR) && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            kill(atoi(ent->d_ino), SIGKILL);
        }
    }

    fclose(fp);

    return 0;
}
