#include "CRearrangeCrypter.h"

CRearrangeCrypter::CRearrangeCrypter() {}


CRearrangeCrypter::~CRearrangeCrypter() {}

void CRearrangeCrypter::init() {}

int32_t CRearrangeCrypter::encrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key)
{
	int32_t len = length >> 1;
	if (len)
	{
		for (uint32_t i = 0; i < len; ++i)
		{
			uint8_t byte = buffer[i];
			buffer[i] = buffer[i + len];
			buffer[i + len] = byte;
		}
	}
	return 1;
}
int32_t CRearrangeCrypter::decrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key)
{
	uint32_t len = length >> 1;
	if (len)
	{
		for (uint32_t i = 0; i < len; ++i)
		{
			uint8_t byte = buffer[i];
			buffer[i] = buffer[i + len];
			buffer[i + len] = byte;
		}
	}
	return 1;
}