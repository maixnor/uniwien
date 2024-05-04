#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    struct utsname buf;
    uname(&buf);
    printf("Hostname: %s\n", buf.nodename);
    printf("OS: %s\n", buf.sysname);
    printf("Version: %s\n", buf.version);
    printf("Release: %s\n", buf.release);
    return 0;
}
