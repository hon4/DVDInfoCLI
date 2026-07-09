#include "pad_str.hpp"

#include <string>

std::string pad_str_right(std::string s, int to_len) {
	if (s.length() < to_len) {
		s.append(to_len - s.length(), ' ');
	}

	return s;
}
