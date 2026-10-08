#include "dvdinfolib.hpp"

#include <string>
#include <fstream>
//libblkid, fcntl.h, unistd.h is for GetDVDLabel from disc
#include <blkid/blkid.h>
#include <fcntl.h>
#include <unistd.h>
//For GetDiscLabel
#include <filesystem>

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

std::string GetDVDLabel(const std::string& device) {
	int fd = open(device.c_str(), O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		return {};

	blkid_probe probe = blkid_new_probe();
	if (!probe) {
		close(fd);
		return {};
	}

	if (blkid_probe_set_device(probe, fd, 0, 0) != 0) {
		blkid_free_probe(probe);
		close(fd);
		return {};
	}

	std::string result;

	if (blkid_do_probe(probe) == 0) {
		const char* label = nullptr;

		if (blkid_probe_lookup_value(probe, "LABEL", &label, nullptr) == 0 && label != nullptr) {
			result = label;
		}
	}

	blkid_free_probe(probe);
	close(fd);

	return result;
}

std::string GetDiscLabel(const std::string& path) {
	namespace fs = std::filesystem;

	fs::path p(path);

	// Its dir, get the folder name
	if (fs::is_directory(p)) {
		return p.filename().string();
	}

	// Its not dir, probablt device so get GetDVDLabel()
	return GetDVDLabel(path);
}
