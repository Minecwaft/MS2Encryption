#pragma once
#include <stdint.h>
#include "IBufferCrypter.h"

enum EncryptType
{
	ENCRYPT_NONE = 0,
	ENCRYPT_REARRANGE = 1,
	ENCRYPT_XOR = 2,
	ENCRYPT_TABLE = 3
};

class BufferCryptManager
{
public:
	IBufferCrypter** crypters;
	bool decrypt(uint8_t* buffer, int32_t length, int32_t seq_block, int32_t seq_recv);
	int32_t encrypt(uint8_t* buffer, int32_t length, int32_t seq_block, int32_t seq_send);
	BufferCryptManager();
	~BufferCryptManager();
};

uint16_t encode_sequence_base(uint32_t base, uint32_t key);
uint32_t decode_sequence_base(uint32_t recv, uint32_t raw);

