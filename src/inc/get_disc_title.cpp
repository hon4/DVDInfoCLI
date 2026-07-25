#include "get_disc_title.hpp"

#include <iostream>
#include <fstream>
#include <string>

std::string get_disc_title(std::string dvdpath) {
	std::string vtsifopath = dvdpath + "/VIDEO_TS.IFO";

	std::ifstream file(vtsifopath, std::ios::binary);
	if (!file) {
		std::cerr << "Error: Failed to open file." << std::endl;
		return "";
	}

	// Disk Title starts at byte 64
	file.seekg(64);
	if (!file) {
		std::cerr << "Error: Seek failed." << std::endl;
		return "";
	}

	std::string disk_title;
	char ch;
	while (file.get(ch)) {
		if (ch == '\0') {
			break; // NULL terminator found (0x00)
		}
		disk_title += ch;
	}

	return disk_title;
}
