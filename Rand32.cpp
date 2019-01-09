#include "Rand32.h"

Rand32::Rand32()
{
}

Rand32::Rand32(uint32_t seed)
{
	uint32_t rand = this->crt_rand32(seed);
	this->s1 = seed | 0x100000;
	this->s2 = rand | 0x1000;
	this->s3 = this->crt_rand32(rand) | 0x10;
}


Rand32::~Rand32()
{
}

int32_t Rand32::crt_rand32(uint32_t seed)
{
	return 214013 * seed + 2531011;
}

int32_t Rand32::random()
{
	uint32_t v3;
	uint32_t v4;
	uint32_t v5;
	v3 = ((((this->s1 >> 6) & 0x3FFFFFF) ^ (this->s1 << 12)) & 0x1FFF) ^ ((this->s1 >> 19) & 0x1FFF) ^ (this->s1 << 12);
	v4 = ((((this->s2 >> 23) & 0x1FF) ^ (this->s2 << 4)) & 0x7F) ^ ((this->s2 >> 25) & 0x7F) ^ (this->s2 << 4);
	v5 = ((((this->s3 << 17) ^ ((this->s3 >> 8) & 0xFFFFFF)) & 0x1FFFFF) ^ (this->s3 << 17)) ^ ((this->s3 >> 11) & 0x1FFFFF);

	this->s1 = v3;
	this->s2 = v4;
	this->s3 = v5;
	return (v3 ^ v4 ^ v5);
}

float Rand32::randomfloat()
{
	int32_t bits = ((this->random() & 0x7FFFFF) | 0x3F800000);
	float result = *reinterpret_cast<float*>(&bits) - 1.0f;
	return result;
}