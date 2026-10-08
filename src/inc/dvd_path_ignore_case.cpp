#include "dvd_path_ignore_case.hpp"

#include <filesystem>
#include <string>
#include <cctype>

std::string dvd_path_ignore_case(const std::string& path) {
	namespace fs = std::filesystem;

	fs::path input(path);

	if (input.empty()) return {};

	fs::path current = input.is_absolute() ? input.root_path() : fs::current_path();

	for (const auto& component : input.relative_path()) {
		std::string wanted = component.string();

		// First try the exact path.
		fs::path exact = current / component;

		std::error_code ec;

		if (fs::exists(exact, ec)) {
			current = exact;
			continue;
		}

		// Exact path doesn't exist, so search case-insensitively.
		bool found = false;

		if (!fs::is_directory(current, ec)) return {};

		for (const auto& entry : fs::directory_iterator(current, ec)) {
			if (ec) return {};

			std::string actual = entry.path().filename().string();

			if (actual.size() != wanted.size()) continue;

			bool equal = true;

			for (size_t i = 0; i < wanted.size(); ++i) {
				if (std::tolower(static_cast<unsigned char>(actual[i])) != std::tolower(static_cast<unsigned char>(wanted[i]))) {
					equal = false;
					break;
				}
			}

			if (equal) {
				current = entry.path();
				found = true;
				break;
			}
		}

		if (!found) return {};
	}

	return current.string();
}
