#include "dvdinfolib.hpp"

#include <string>
#include <fstream>
//libblkid, fcntl.h, unistd.h is for GetDVDLabel from disc
#include <blkid/blkid.h>
#include <fcntl.h>
#include <unistd.h>
//For GetDiscLabel and GetDirectorySize
#include <filesystem>
//For GetDirectorySize
#include <cstdint>
//For std::transform
#include <algorithm>

#include "inc/dvd_path_ignore_case.hpp"

std::string GetDiscTitle(std::string VIDEOTSFile) {
	std::string ret;

	std::ifstream file(dvd_path_ignore_case(VIDEOTSFile), std::ios::binary);

	if (!file)
		throw std::runtime_error("GetDiscTitle: Cannot open file");

	file.seekg(64);

	if (!file)
		throw std::runtime_error("GetDiscTitle: Cannot seek to position");

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

uint64_t GetDirectorySize(const std::string& path) {
	uint64_t size = 0;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(dvd_path_ignore_case(path))) {
		if (entry.is_regular_file())
			size += entry.file_size();
	}

	return size;
}

std::string FNDBigger(const std::string& path) {
	namespace fs = std::filesystem;

	uint64_t bigsize = 0;
	std::string bigname;

	for (const auto& entry : fs::directory_iterator(dvd_path_ignore_case(path))) {
		if (!entry.is_regular_file())
			continue;

		std::string name = entry.path().filename().string();

		std::string upper = name;

		std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) { return std::toupper(c); });

		// VTS_*.VOB
		if (upper.size() >= 8 && upper.compare(0, 4, "VTS_") == 0 && upper.compare(upper.size() - 4, 4, ".VOB") == 0) {
			uint64_t size = entry.file_size();

			if (size > bigsize) {
				bigsize = size;
				bigname = entry.path().string();
			}
		}
	}

	return bigname;
}
