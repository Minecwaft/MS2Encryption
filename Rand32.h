#pragma once
#include <stdint.h>

#define RAND32_FLOAT_CONSTANT 255.0f

class Rand32
{
public:
	int32_t s1;
	int32_t s2;
	int32_t s3;

	Rand32();
	Rand32(uint32_t seed);
	~Rand32();
	int32_t crt_rand32(uint32_t seed);
	//int64_t range_long_rand32(uint32_t range, uint32_t start); //TODO do this later
	int32_t random();
	float randomfloat();
};

