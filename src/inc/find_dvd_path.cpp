#include "find_dvd_path.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm>

std::string find_dvd_path(std::string inp) {
	namespace fs = std::filesystem;

	fs::path p(inp);

	// Check for DVD files
	std::string ext = p.extension().string();
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	if (ext == ".ifo" || ext == ".vob") {
		fs::path parent = p.parent_path();
		if (parent.filename() == "VIDEO_TS")
			return parent.lexically_normal().string();
	} else {
		// It's a dir like VIDEO_TS.
		std::string path = p.lexically_normal().string();

		if (!path.empty() && (path.back() == '/' || path.back() == '\\')) {
			path.pop_back();
		}
		return path;
	}

	return "";
}
