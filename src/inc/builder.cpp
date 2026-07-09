#include "builder.hpp"

#include <iostream>
#include <map>
#include <any>
#include <string>
#include <sstream>
#include <cstdint>
#include <vector>

#include "version.hpp"
#include "format_number.hpp"

std::string get_dvdinfo_video_info();
std::string get_dvdinfo_audio_info();
std::string get_movie_video_files_str(const std::vector<std::string>& files);

std::string get_dvdinfo(const std::map<std::string, std::any>& dvdinfo_data) {
	std::string ret;

	std::map<std::string, std::any> data = dvdinfo_data;

	for (const auto& [key, value] : data) {
		std::cout << key << " : " << value.type().name() << "\n";
	}

	std::map<std::string, std::any> dvdinfo_data_video = std::any_cast<std::map<std::string, std::any>>(data["video"]);

	std::ostringstream oss;
	oss << "DVD INFO\n"
		<< "Disc Label: " << std::any_cast<std::string>(data.at("disc_label")) << "\n"
		<< "Disc Title: " << std::any_cast<std::string>(data.at("disc_title")) << "\n"
		<< "Disc Size: " << format_number(std::any_cast<std::uint64_t>(data.at("disc_size"))) << " bytes\n"
		<< "DVDInfo: " << DVDINFO_VER << "\n"
		<< "\n"
		<< "MOVIE\n"
		<< "Parts: " << std::any_cast<std::uint32_t>(dvdinfo_data_video.at("parts")) << "\n"
		<< "Video Files: " << get_movie_video_files_str(std::any_cast<std::vector<std::string>>(dvdinfo_data_video.at("video_files"))) << "\n"
		<< "MetaFile: " << std::any_cast<std::string>(dvdinfo_data_video.at("metafile")) << "\n"
		<< "Movie Size: " << format_number(std::any_cast<std::uint64_t>(dvdinfo_data_video.at("movie_size"))) << " bytes\n"
		<< "Length: " << std::any_cast<std::string>(dvdinfo_data_video.at("length")) << " (h:m:s.ms)\n"
		<< "Standard: " << std::any_cast<std::string>(dvdinfo_data_video.at("standard")) << "\n"
		<< "\n"
		<< "VIDEO" << "\n"
		<< "Codec    BitRate          Description\n"
		<< "-----    -------          -----------\n"
		<< get_dvdinfo_video_info() << "\n"
		<< "\n"
		<< "AUDIO\n"
		<< "Codec    Language    Bitrate    Description\n"
		<< "-----    --------    -------    -----------\n"
		<< get_dvdinfo_audio_info() << "\n";

	ret = oss.str();

	return ret;
}

std::string get_dvdinfo_video_info() {
	return "MPEG-2   6000 kbps (avg)  576p / 25.000 FPS / 16:9 / Main Profile";
}

std::string get_dvdinfo_audio_info() {
	return "AC-3     Greek       448 kbps   5.1 / 48.0 kHz / Dolby Digital";
}

std::string get_movie_video_files_str(const std::vector<std::string>& files) {
	std::string ret;

	for (size_t i = 0; i < files.size(); ++i) {
		if (i > 0)
			ret += ", ";

		ret += files[i];
	}

	return ret;
}
