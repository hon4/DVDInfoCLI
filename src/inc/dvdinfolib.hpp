#ifndef DVDINFOLIB_HPP
#define DVDINFOLIB_HPP

#include <string>
#include <cstdint>

std::string GetDiscTitle(std::string VTSIFOPath);
std::string GetDVDLabel(const std::string& device);
std::string GetDiscLabel(const std::string& path);
uint64_t GetDirectorySize(const std::string& path);
std::string FNDBigger(const std::string& path);

#endif
