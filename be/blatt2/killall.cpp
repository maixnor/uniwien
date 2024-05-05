#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <process_name>" << std::endl;
        return 1;
    }

    std::string proc_name = argv[1];
    
    for (const auto& entry : std::filesystem::directory_iterator("/proc")) {
        std::string pid_str = entry.path().filename().string();
        try {
            int pid = std::stoi(pid_str);
            std::string path = "/proc/" + pid_str + "/cmdline";
            std::ifstream cmd_file(path);
            std::string contents;
            if (cmd_file >> contents) {
                if (contents.find(proc_name) != std::string::npos) {
                    // Use the `kill` syscall to terminate the process
                    int result = kill(pid, SIGKILL);
                    if (result == 0) {
                        std::cout << "Process " << pid << " killed successfully." << std::endl;
                    } else {
                        std::cerr << "Error killing process " << pid << std::endl;
                        return 1;
                    }
                }
            }
        } catch (const std::invalid_argument& ex) {
            // Ignore non-numeric directory names in /proc
            continue;
        }
    }

    return 0;
}

