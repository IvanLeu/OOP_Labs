#include <string>

std::string extract_digits(const std::string& in) {
	std::string out = "";

	for (const auto& c : in) {
		if (c >= '0' && c <= '9') {
			out.push_back(c);
		}
		else {
			if (out.back() != ' ') {
				out.push_back(' ');
			}
			continue;
		}
	}

	return out;
}