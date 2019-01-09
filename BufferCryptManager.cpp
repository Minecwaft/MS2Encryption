#include "BufferCryptManager.h"
#include "CRearrangeCrypter.h"
#include "CTableCrypter.h"
#include "CXORCrypter.h"

#define NUM_CRYPTERS 3

BufferCryptManager::BufferCryptManager(int32_t version)
{
	this->crypters = new IBufferCrypter*[4];
	this->crypters[0] = NULL;
	this->crypters[(version + ENCRYPT_REARRANGE) % 3 + 1] = new CRearrangeCrypter();
	this->crypters[(version + ENCRYPT_XOR) % 3 + 1] = new CXORCrypter();
	this->crypters[(version + ENCRYPT_TABLE) % 3 + 1] = new CTableCrypter();
	for (int32_t i = NUM_CRYPTERS; i > 0; --i)
		this->crypters[i]->init();
}


BufferCryptManager::~BufferCryptManager()
{
	//does this even matter? This will never be called Pepega
	for (int32_t i = NUM_CRYPTERS; i > 0; --i)
		delete this->crypters[i];
}

bool BufferCryptManager::decrypt(uint8_t* buffer, int32_t length, int32_t seq_block, int32_t seq_recv)
{
	if (seq_block != 0)
	{
		int32_t block = 0;
		while (seq_block > 0)
		{
			block = seq_block + 10 * (block - seq_block / 10);
			seq_block /= 10;
		}
		if (block != 0)
		{
			int32_t index;
			while (block > 0)
			{
				index = block / 10;
				IBufferCrypter* crypter = this->crypters[block % 10];
				if (crypter != nullptr)
				{
					if (!crypter->decrypt(buffer, length, seq_block))
						return false;
				}
				block = index;
			}
			return true;
		}
	}
	return true;
}

int32_t BufferCryptManager::encrypt(uint8_t* buffer, int32_t length, int32_t seq_block, int32_t seq_send)
{
	int32_t index = 0;
	if (seq_block != 0)
	{
		int32_t block = seq_block / 10;
		while (block != 0)
		{
			block = seq_block / 10;
			index = 10 * block;
			IBufferCrypter* crypter = this->crypters[seq_block % 10];
			if (crypter != nullptr)
				crypter->encrypt(buffer, length, seq_send);
			seq_block = block;
		}
	}
	return index;
}

//these two functions maybe better suited to be in SocketSequence.cpp
uint16_t encode_sequence_base(uint32_t base, uint32_t send_sequence)
{ //base == MS2_VERSION
	if (send_sequence)
		send_sequence = (base ^ (send_sequence >> 16));
	else
		send_sequence = base;
	return send_sequence;
}

uint32_t decode_sequence_base(uint32_t recv_sequence, uint32_t raw)
{
	if (raw != MS2_VERSION)
		raw = ((recv_sequence >> 16) ^ raw);
	else
		return raw;
	return raw;
}
