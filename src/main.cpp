#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#include "inc/version.hpp"
#include "inc/help.hpp"
#include "inc/builder.hpp"
#include "inc/dvdinfolib.hpp"
#include "inc/find_dvd_path.hpp"

void test();
std::string dvdpath;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "DVDInfo: No input file specified.\n\n";
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0) {
			show_help();
			return 0;
		} else if (strcmp(argv[i], "-v") == 0) {
			show_ver();
			return 0;
		} else {
			dvdpath = find_dvd_path(std::string(argv[i]));
			//Add checks
		}
    }

	std::cout << "0: " << find_dvd_path("/mnt/cdrom/VIDEO_TS/") << "\n";
	std::cout << "1: " << find_dvd_path("/mnt/cdrom/VIDEO_TS") << "\n";
	std::cout << "2: " << find_dvd_path("/mnt/cdrom/VIDEO_TS/VIDEO_TS.IFO") << "\n";
	std::cout << "3: " << find_dvd_path("/mnt/cdrom/VIDEO_TS/VIDEO_TS.VOB") << "\n";
	//test();

	return 0;
}

void test() {
	std::cout << GetDiscTitle("VIDEO_TS.IFO") << "\n\n";
	
	
	std::map<std::string, std::any> dvdinfo_data;
	dvdinfo_data["disc_label"] = std::string("Alice");
	dvdinfo_data["disc_title"] = std::string("Alice");
	dvdinfo_data["disc_size"] = std::uint64_t{5};

	//DVDInfo Movie Info
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
	
	//DVDInfo Video Tracks
	std::vector<std::map<std::string, std::any>> video_tracks;
	
	std::map<std::string, std::any> vtrack0;
	vtrack0["codec"] = std::string("x264");
	vtrack0["bitrate"] = std::string("6000 kbps (avg)");
	vtrack0["description"] = std::string("576p / 25.000 FPS / 16:9 / Main Profile");
	
	video_tracks.push_back(vtrack0);
	
	dvdinfo_data["video_tracks"] = video_tracks;
	
	//DVDInfo Audio Tracks
	std::vector<std::map<std::string, std::any>> audio_tracks;
	
	std::map<std::string, std::any> atrack0;
	atrack0["codec"] = std::string("AC-3");
	atrack0["language"] = std::string("Greek");
	atrack0["bitrate"] = std::uint32_t{448};
	atrack0["description"] = std::string("5.1 / 48.0 kHz / Dolby Digital");
	
	audio_tracks.push_back(atrack0);
	
	dvdinfo_data["audio_tracks"] = audio_tracks;

	std::cout << get_dvdinfo(dvdinfo_data);
}