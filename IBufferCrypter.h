#pragma once
#include <stdint.h>
#define MS2_VERSION 101

class IBufferCrypter
{
public:
	virtual void init() = 0;
	virtual int32_t encrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key) = 0;
	virtual int32_t decrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key) = 0;
	IBufferCrypter();
	~IBufferCrypter();
};

