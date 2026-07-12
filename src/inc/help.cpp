#include "help.hpp"

#include <iostream>

void show_help() {
	std::cout << "DVDInfoCLI\n"
			<< "============\n"
			<< "\n"
			<< "Usage: dvdinfo [OPTIONS] <filename/dirname> [OPTIONS]\n"
			<< "\n"
			<< "Options:\n"
			<< "  -h             Show this message and exit.\n"
			<< "  -v             Show version info and exit.\n"
			<< "  -o <filename>  Specify output file.\n"
			<< "\n";
}

void show_ver() {
	std::cout << "DVDInfo (DVDInfoCLI)\n"
			<< "======================\n"
			<< "\n"
			<< "Edition: CLI\n"
			<< "Version: " << DVDINFOCLI_VERSION << "\n"
			<< "Language: C++\n"
			<< "\n";
}
