#pragma once

#include <type_traits>

class Eleven {
public:
	Eleven() noexcept;
	explicit Eleven(auto num) requires(std::is_unsigned_v<decltype(num)>) {
		auto num_cpy = num;

		while (num_cpy) {
			len++;
			num_cpy /= 11;
		}

		ptr = new unsigned char[len];

		size_t i = 0;
		while (num) {
			ptr[i] = num % 11;
			num /= 11;
			i++;
		}
	}
	Eleven(size_t size, auto num) requires(std::is_unsigned_v<decltype(num)>) {
		len = size;
		ptr = new unsigned char[len];

		size_t i = 0;
		while (num) {
			ptr[i] = num % 11;
			num /= 11;
			i++;
		}
	}
	Eleven(const Eleven&) noexcept;
	Eleven& operator=(const Eleven&) noexcept;
	Eleven(Eleven&&) noexcept;
	Eleven& operator=(Eleven&&) noexcept;
	static Eleven add(const Eleven& lhs, const Eleven& rhs) noexcept;
	static Eleven subtract(const Eleven& lhs, const Eleven& rhs) noexcept;
	static bool greater_than(const Eleven& lhs, const Eleven& rhs) noexcept;
	static bool less_than(const Eleven& lhs, const Eleven& rhs) noexcept;
	static bool equal(const Eleven& lhs, const Eleven& rhs) noexcept;
	~Eleven() noexcept;
private:
	size_t len;
	unsigned char* ptr;
};