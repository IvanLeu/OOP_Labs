#include <iostream>
#include <string>

std::string extract_digits(const std::string &in) {
  std::string out;

  for (const auto &c : in) {
    if (c >= '0' && c <= '9') {
      out.push_back(c);
    }
  }

  return out;
}

int main() {
  std::string input_string;
  std::cin >> input_string;

  std::cout << extract_digits(input_string);

  return 0;
}
