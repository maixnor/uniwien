extern "C" {
    #include <sys/syscall.h>
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include <unistd.h>
    #include<stdio.h>
    #include<stdlib.h>
    #include<sys/utsname.h>
}

#include<iostream>
#include<string>

int main(int argc, const char *argv[]) {
     
    struct statx stats;

    statx(argc, argv[1],AT_STATX_SYNC_AS_STAT,STATX_UID | STATX_GID, &stats);
    std::cout << "UID: " << stats.stx_uid << ", GID: " << stats.stx_gid << "\n"; 

    statx(argc, argv[1],AT_STATX_SYNC_AS_STAT,STATX_SIZE, &stats);
    std::cout << "Size: " << stats.stx_size << "\n";

    statx(argc, argv[1],AT_STATX_SYNC_AS_STAT, STATX_MODE, &stats);
    mode_t mode = stats.stx_mode & 0777;
    
    std::string permissions;
    permissions += (mode & S_IRUSR) ? 'r' : '-';
    permissions += (mode & S_IWUSR) ? 'w' : '-';
    permissions += (mode & S_IXUSR) ? 'x' : '-';
    permissions += (mode & S_IRGRP) ? 'r' : '-';
    permissions += (mode & S_IWGRP) ? 'w' : '-';
    permissions += (mode & S_IXGRP) ? 'x' : '-';
    permissions += (mode & S_IROTH) ? 'r' : '-';
    permissions += (mode & S_IWOTH) ? 'w' : '-';
    permissions += (mode & S_IXOTH) ? 'x' : '-';

    std::cout << permissions;
    return EXIT_SUCCESS;
}
