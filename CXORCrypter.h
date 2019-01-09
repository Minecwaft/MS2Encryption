#pragma once
#include "IBufferCrypter.h"
class CXORCrypter : public IBufferCrypter
{
public:
	uint8_t* swap_bytes;
	void init();
	int32_t encrypt(uint8_t* buffer, uint32_t length, uint32_t seqKey);
	int32_t decrypt(uint8_t* buffer, uint32_t length, uint32_t seqKey);
	CXORCrypter();
	~CXORCrypter();
};

