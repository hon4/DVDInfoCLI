#include <iostream>
#include <cstdint>
#include <vector>

#include "inc/version.hpp"
#include "inc/builder.hpp"

int main() {
	std::map<std::string, std::any> dvdinfo_data;
	dvdinfo_data["disc_label"] = std::string("Alice");
	dvdinfo_data["disc_title"] = std::string("Alice");
	dvdinfo_data["disc_size"] = std::uint64_t{5};

	std::map<std::string, std::any> dvdinfo_video;
	dvdinfo_video["parts"] = std::uint32_t{5};
	std::vector<std::string> video_files_arr = {
		"one",
		"two",
		"three"
	};
	dvdinfo_video["video_files"] = video_files_arr;
	dvdinfo_video["metafile"] = std::string("Alice.ifo");
	dvdinfo_video["movie_size"] = std::uint64_t{712};
	dvdinfo_video["length"] = std::string("5 hours");
	dvdinfo_video["standard"] = std::string("PAL");

	dvdinfo_data["video"] = dvdinfo_video;

	std::cout << get_dvdinfo(dvdinfo_data);
	return 0;
}