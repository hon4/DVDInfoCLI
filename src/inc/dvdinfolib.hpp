#ifndef DVDINFOLIB_HPP
#define DVDINFOLIB_HPP

#include <string>

std::string GetDiscTitle(std::string VTSIFOPath);
std::string GetDVDLabel(const std::string& device);
std::string GetDiscLabel(const std::string& path);

#endif
