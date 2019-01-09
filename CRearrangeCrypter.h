#pragma once
#include "IBufferCrypter.h"
class CRearrangeCrypter : public IBufferCrypter
{
public:
	void init();
	int32_t encrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key);
	int32_t decrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key);
	CRearrangeCrypter();
	~CRearrangeCrypter();
};

