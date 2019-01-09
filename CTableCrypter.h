#pragma once
#include "IBufferCrypter.h"
class CTableCrypter : public IBufferCrypter
{
public:
	uint8_t* decrypt_table;
	uint8_t* encrypt_table;
	void init();
	int32_t encrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key);
	int32_t decrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key);
	CTableCrypter();
	~CTableCrypter();
};

