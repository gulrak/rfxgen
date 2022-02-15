#include "random.h"

//-----------------------------------------------------------------------------
// Based on splitmix64 public domain code by Sebastiano Vigna (vigna@acm.org), 2015
// and xoroshiro128++ 1.0 public domain code by David Blackman and Sebastiano Vigna (vigna@acm.org), 2019
//-----------------------------------------------------------------------------

static uint64_t s[2];

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

static uint64_t splitmix64(uint64_t* seed) {
	uint64_t z = (*seed += UINT64_C(0x9E3779B97F4A7C15));
	z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
	return z ^ (z >> 31);
}

void seedRandom(uint64_t seed)
{
    s[0] = splitmix64(&seed);
    s[1] = splitmix64(&seed);
}

uint64_t nextRandom(void)
{
	const uint64_t s0 = s[0];
	uint64_t s1 = s[1];
	const uint64_t result = rotl(s0 + s1, 17) + s0;

	s1 ^= s0;
	s[0] = rotl(s0, 49) ^ s1 ^ (s1 << 21); // a, b
	s[1] = rotl(s1, 28); // c

	return result>>1; // ensure positive values if used in signed context
}

