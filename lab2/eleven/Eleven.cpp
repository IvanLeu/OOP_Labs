#include "Eleven.h"
#include <algorithm>

Eleven::Eleven() noexcept
	:
	len(0),
	ptr(nullptr)
{}

Eleven::Eleven(const Eleven& other) noexcept {
	*this = other;
}

Eleven& Eleven::operator=(const Eleven& other) noexcept {
	if (this != &other) {
		delete[] ptr;
		len = other.len;

		ptr = new unsigned char[other.len];

		std::copy_n(other.ptr, other.len, ptr);
	}

	return *this;
}

Eleven::Eleven(Eleven&& other) noexcept {
	*this = std::move(other);
}

Eleven& Eleven::operator=(Eleven&& other) noexcept {
	if (this != &other) {
		delete[] ptr;

		len = other.len;
		ptr = other.ptr;

		other.len = 0;
		other.ptr = nullptr;
	}

	return *this;
}


Eleven Eleven::add(const Eleven& lhs, const Eleven& rhs) noexcept {
	size_t sum = 0;

	for (size_t i = 0, len = std::max(lhs.len, rhs.len); i < len; i++) {
		if (lhs.ptr[i] == 'A' || rhs.ptr[i] == 'A') {
			sum += 11;
			continue;
		}
		else {
			sum += (i < lhs.len) ? lhs.ptr[i] - '0' : 0;
			sum += (i < rhs.len) ? rhs.ptr[i] - '0' : 0;
		}
	}

	size_t result_length = 0;

	size_t sum_cpy = sum;
	while (sum_cpy) {
		++result_length;
		sum_cpy /= 11;
	}

	Eleven result{ result_length, 0u };

	for (size_t i = 0; i < result_length; i++) {
		result.ptr[i] = sum % 11;
		sum /= 11;
	}

	return result;
}

Eleven Eleven::subtract(const Eleven& lhs, const Eleven& rhs) noexcept {
	size_t diff = 0;

	for (size_t i = 0, len = std::max(lhs.len, rhs.len); i < len; i++) {
		if (lhs.ptr[i] == 'A') {
			diff += 11;
			continue;
		}
		else if (rhs.ptr[i] == 'A') {
			diff -= 11;
			continue;
		}
		else {
			diff += (i < lhs.len) ? lhs.ptr[i] - '0' : 0;
			diff -= (i < rhs.len) ? rhs.ptr[i] - '0' : 0;
		}
	}

	if (diff < 0) {
		return Eleven();
	}

	size_t result_length = 0;

	size_t diff_cpy = diff;
	while (diff_cpy) {
		++result_length;
		diff_cpy /= 11;
	}

	Eleven result{ result_length, 0u };

	for (size_t i = 0; i < result_length; i++) {
		result.ptr[i] = diff % 11;
		diff /= 11;
	}

	return result;
}

bool Eleven::greater_than(const Eleven& lhs, const Eleven& rhs) noexcept
{
	if (lhs.len > rhs.len) {
		return true;
	}
	else if (lhs.len == rhs.len) {
		for (long long i = lhs.len - 1; i >= 0; i--) {
			if (lhs.ptr[i] != 'A' && rhs.ptr[i] == 'A')
				return false;
			if (lhs.ptr[i] > rhs.ptr[i])
				return true;
		}
	}

	return false;
}

bool Eleven::less_than(const Eleven& lhs, const Eleven& rhs) noexcept
{
	return !greater_than(lhs, rhs) && !equal(lhs, rhs);
}

bool Eleven::equal(const Eleven& lhs, const Eleven& rhs) noexcept
{
	if (lhs.len == rhs.len) {
		for (long long i = lhs.len - 1; i >= 0; i--) {
			if (lhs.ptr[i] != rhs.ptr[i])
				return false;
		}
		return true;
	}

	return false;
}

Eleven::~Eleven() noexcept
{
	delete[] ptr;
	len = 0;
}
