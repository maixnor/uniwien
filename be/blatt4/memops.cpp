#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <sstream>

#include "proto.h"

#if __has_include(<format>)
#include <format>
#else
#include <iomanip>
#endif

// assertions for std::memcpy
static_assert(
	std::is_trivially_copyable<struct message_unit>::value,
	"struct message_unit is not trivially copyable!");
static_assert(
	std::is_trivially_copyable<struct challenge_unit>::value,
	"struct challenge_unit is not trivially copyable!");

#ifdef __cpp_lib_format
/**
	using C++20 std::format for a bytes representation
*/
std::string get_bytes(const char *buf, std::size_t buf_len)
{
	// char should be exactly 8 bits for this program
	static_assert(
		CHAR_BIT == 8,
		"Number of bits in a byte is not 8!");
	// same effect
	static_assert(
		std::numeric_limits<unsigned char>::digits == 8,
		"Number of bits in a byte is not 8!");

	std::stringstream ss;
	for (std::size_t byte_off{0}; byte_off < buf_len; ++byte_off) {
		ss << std::format(
			"{:02x}", // assuming 8 bit char here
			static_cast<unsigned char>(buf[byte_off]));
	}
	return ss.str();
}
#else
/**
	using regular C++ overloads
*/
std::string get_bytes(const char *buf, std::size_t buf_len)
{
	// char should be exactly 8 bits for this program
	static_assert(
		CHAR_BIT == 8,
		"Number of bits in a byte is not 8!");
	// same effect
	static_assert(
		std::numeric_limits<unsigned char>::digits == 8,
		"Number of bits in a byte is not 8!");

	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (std::size_t byte_off{0}; byte_off < buf_len; ++byte_off) {
		ss << std::setw(2) // assuming 8 bit char here
			<< static_cast<int>(
				static_cast<unsigned char>(buf[byte_off]));
	}
	return ss.str();
}
#endif

std::string split_by_len(
	const std::string &to_split,
	std::size_t split_len,
	char delim = '\n')
{
	std::string split_str;
	for (std::size_t pos{0}; pos < to_split.size(); pos += split_len) {
		if (pos) {
			split_str += delim;
		}
		split_str += to_split.substr(pos, split_len);
	}
	return split_str;
}

int main()
{
	// using designators for readability
	struct message_unit msg {
		.msg_type = msg_type::CHALLENGE,
		.server_info = server_info::WRONG
	};
	struct challenge_unit chall {
		.op = proto_op::RIGHT_SHIFT,
		.lhs = 1,
		.rhs = 3333333333,
		.answer = 1283
	};

	constexpr std::size_t buf_sz{
		sizeof(struct message_unit) +
		sizeof(struct challenge_unit)};
	char test_buf[buf_sz];

	std::memcpy(test_buf, &msg, sizeof(msg));
	std::memcpy(test_buf + sizeof(msg), &chall, sizeof(chall));

	// get bytes representation of buffer content for console output
	std::string byte_str{get_bytes(test_buf, sizeof(test_buf))};
	std::cout << byte_str << "\n\n";
	std::cout << split_by_len(
		byte_str, sizeof(std::uint32_t) * (CHAR_BIT / 4)) << '\n';

	return EXIT_SUCCESS;
}
