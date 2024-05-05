#include <stdio.h>
#include <unistd.h>
#include <sys/statx.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    struct statx sb;
    int result = statx(argv[1], &sb, STATX_BASIC_STATS);
    if (result == -1) {
        perror("statx");
        return 1;
    }

    printf("UID: %u, GID: %u\n", sb.uid, sb.gid);
    printf("Size: %zu\n", sb.size);
    printf("%s\n", rwx_to_string(sb.mode));

    return 0;
}

// thank you llama3
char *rwx_to_string(mode_t mode) {
    static char buf[10];
    sprintf(buf, "%c%c%c%c%c%c",
             (mode & S_IRUGO) ? 'r' : '-',
             (mode & S_IWUGO) ? 'w' : '-',
             (mode & S_IXUGO) ? 'x' : '-',
             (mode >> 6) & 7,
             (mode >> 3) & 7,
             mode & 7);
    return buf;
}
