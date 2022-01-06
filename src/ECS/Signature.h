#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <bitset>

constexpr unsigned int MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif // SIGNATURE_H
