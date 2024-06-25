#ifndef PROTO_H
#define PROTO_H

#ifndef __cplusplus
#include <stddef.h>
#include <stdint.h>
#else
#include <cstddef>
#include <cstdint>
using std::uint32_t;
#endif

/**
	for interpretation of `challenge_unit`'s `op` member values
	(could also be made `enum class` for C++)
*/
enum proto_op {
	ADD = 0,
	SUB = 1,
	MUL = 2,
	LEFT_SHIFT = 3,
	RIGHT_SHIFT = 4,
	// marks end of enum values ... not from protocol itself
	OP_END = 5
};

/**
	for interpretation of `message_unit`'s `msg_type` member values
	(could also be made `enum class` for C++)
*/
enum msg_type {
	CHALLENGE = 0,
	SERVER_INFO = 1
};

/**
	for interpretation of `message_unit`'s `server_info` member values
	(could also be made `enum class` for C++)

	if `msg_type` does not correspond to `SERVER_INFO`, `server_info`
	shall not be interpreted as it does not contain any information
*/
enum server_info {
	CORRECT = 0,
	WRONG = 1,
};

/**
	no padding
	size: sizeof(uint32_t) + 4
	alignment requirement: alignof(uint32_t)

	this struct is always part of a protocol message

	`msg_type` is to be interpreted according to `enum msg_type`

	`server_info` is to be interpreted according to `enum server_info`
*/
struct message_unit {
	uint32_t msg_type;
	uint32_t server_info;
};

/**
	no padding
	size: 4 * sizeof(uint32_t)
	alignment requirement: alignof(uint32_t)

	this struct should come right after `struct message_unit`
	in the protocol message

	`op` is to be interpreted according to `enum proto_op`
	(excluding `OP_END`)

	`lhs` and `rhs` are the left- and right-hand sides of the mathematical
	calculation, respectively

	`answer` should either:
		hold the correct answer to these
		operations on unsigned integers (client answer)
	or
		be 0 (server initiation)
*/
struct challenge_unit {
	uint32_t op;
	uint32_t lhs;
	uint32_t rhs;
	uint32_t answer;
};

/**
	packets for this protocol should be composed of
	a `message_unit` followed by an optional `challenge_unit`

	the `challenge_unit` shall be omitted if the `msg_type`
	corresponds to `enum msg_type`'s `SERVER_INFO` value

	if the server's message has the type `SERVER_INFO`, the value of
	`server_info` in `struct message_unit` signals the client
	the success status of their challenge response
*/

#endif // PROTO_H
