#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <bitset>

constexpr unsigned int MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

inline bool are_matching(const Signature& entity, const Signature& system)
{
	return (entity & system) == system;
}

#endif // SIGNATURE_H
