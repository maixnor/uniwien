/**
	Example program which behaves similarly to the program `rg` (ripgrep)
*/

#include <cstdlib>
#include <csignal>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

extern "C" {
#include <unistd.h>
}

namespace fs = std::filesystem;

std::ostream&
print_matching_lines(
	std::pair<std::ifstream, std::string> &lookup_pair,
	std::ostream &o = std::cout)
{
	size_t count{1};
	for (std::string line; std::getline(lookup_pair.first, line, '\n'); ++count) {
		if (line.find(lookup_pair.second) != std::string::npos) {
			o << ' ' << count << ':' << line << '\n';
		}
	}
	return o;
}

std::ostream&
operator<<(
	std::ostream &o,
	std::pair<std::ifstream, std::string> &lookup_pair)
{
	return print_matching_lines(lookup_pair, o);
}

int
main(int argc, char *argv[])
{
	// check arguments
	if (argc != 3) { // argc == 3 -> two commandline argument specified
		std::cout << "usage: ./ripgrep <directory_path> <lookup_string>\n";
		exit(EXIT_FAILURE);
	}

	std::error_code ec;
	fs::directory_iterator procfs_iter{argv[1], ec};
	// ensure it's a directory
	if (ec) {
		std::cout << "Not a directory that can be iterated over!" << '\n';
		pid_t my_pid = getpid();
		kill(my_pid, SIGALRM);
	}

	for (const fs::directory_entry &e : procfs_iter) {
		const fs::path path{e};
		// ensure it's a regular file that we want to read
		if (!e.is_regular_file()) {
			continue;
		}

		std::ifstream file{path};
		if (file.is_open()) {
			// print filename
			std::cout << path.string() << ":\n";
			auto lookup_pair = std::make_pair(std::move(file), std::string{argv[2]});
			// print matching lines with line count (calls print_matching_lines)
			std::cout << lookup_pair;
		}
	}

	return EXIT_SUCCESS;
}

/**	to read a whole file
	const std::string filename{"<filename>"};
	std::ifstream file{filename, std::ios::in}; // we only want to read from the file (is the default mode!)
	std::string read_file(file_size, '\0'); // allocate needed space
	file.read(&read_file.front(), file_size); // read to array allocated by string
*/