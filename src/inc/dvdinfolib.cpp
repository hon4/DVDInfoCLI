#include "dvdinfolib.hpp"

#include <string>
#include <fstream>

std::string GetDiscTitle(std::string VIDEOTSFile) {
	std::string ret;

	std::ifstream file(VIDEOTSFile, std::ios::binary);

	if (!file)
		throw std::runtime_error("Cannot open file");

	file.seekg(64);

	if (!file)
		throw std::runtime_error("Cannot seek to position");

	char c;

	while (file.get(c)) {
		if (c == '\0')  // 0x00 NULL terminator
			break;

		ret += c;
	}

	return ret;
}
