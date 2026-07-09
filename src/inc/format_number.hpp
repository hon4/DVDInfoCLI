#ifndef FORMAT_NUMBER_HPP
#define FORMAT_NUMBER_HPP

#include <string>

template<typename T>
std::string format_number(T value) {
	std::string s = std::to_string(value);

	int pos = static_cast<int>(s.length()) - 3;

	while (pos > 0) {
		s.insert(pos, ",");
		pos -= 3;
	}

	return s;
}

#endif
