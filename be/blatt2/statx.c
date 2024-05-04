extern "C" {
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
}
#include <iostream>

// Simplified example. Full implementation would check return values for errors.
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path>\n";
        return 1;
    }
    
    struct statx buf;
    syscall(SYS_statx, AT_FDCWD, argv[1], 0, STATX_BASIC_STATS, &buf);
    
    std::cout << "UID: " << buf.stx_uid << ", GID: " << buf.stx_gid << std::endl;
    std::cout << "Size: " << buf.stx_size << std::endl;
    // Permissions would require bitwise AND to extract and format properly.
    
    return 0;
}
