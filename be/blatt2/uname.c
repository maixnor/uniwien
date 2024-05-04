extern "C" {
#include <sys/utsname.h>
#include <unistd.h>
}
#include <iostream>

int main() {
    struct utsname unameData;
    uname(&unameData);
    
    std::cout << "Hostname: " << unameData.nodename << std::endl;
    std::cout << "OS: " << unameData.sysname << std::endl;
    std::cout << "Version: " << unameData.version << std::endl;
    std::cout << "Release: " << unameData.release << std::endl;
    
    return 0;
}
