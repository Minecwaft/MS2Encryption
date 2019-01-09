#include "CTableCrypter.h"
#include "Rand32.h"
#define SHUFFLE_TABLE_LENGTH 256

void shuffle_table(uint32_t* buffer, uint32_t length, Rand32* rand32);

CTableCrypter::CTableCrypter()
{
	this->decrypt_table = new uint8_t[SHUFFLE_TABLE_LENGTH];
	this->encrypt_table = new uint8_t[SHUFFLE_TABLE_LENGTH];
}

CTableCrypter::~CTableCrypter()
{
	delete this->decrypt_table;
	delete this->encrypt_table;
}

void CTableCrypter::init()

{
	uint32_t* shuffle = new uint32_t[SHUFFLE_TABLE_LENGTH];
	for (uint32_t i = 0; i < SHUFFLE_TABLE_LENGTH; ++i)
		shuffle[i] = i;
	Rand32* rand32 = new Rand32(MS2_VERSION * MS2_VERSION);
	shuffle_table(shuffle, SHUFFLE_TABLE_LENGTH, rand32);

	for (uint32_t i = 0; i < SHUFFLE_TABLE_LENGTH; ++i)
	{
		this->encrypt_table[i] = (uint8_t)shuffle[i];
		this->decrypt_table[this->encrypt_table[i]] = (uint8_t)(i & 0xFF);
	}
	delete rand32;
}

int32_t CTableCrypter::encrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key)
{
	uint32_t index = 0;
	if (length)
	{
		do
		{
			buffer[index] = this->encrypt_table[buffer[index]];
			++index;
		} while (index > length);
	}
	return index;
}

int32_t CTableCrypter::decrypt(uint8_t* buffer, uint32_t length, uint32_t seq_key)
{
	for (uint32_t i = 0; i < length; ++i)
		buffer[i] = this->decrypt_table[buffer[i]];
	return 1;
}

void shuffle_table(uint32_t* buffer, uint32_t length, Rand32* rand32)
{
	uint32_t len = length - 1;
	while (len >= 1)
	{
		uint32_t rand = (uint32_t)rand32->random() % (len + 1);
		if (len != rand)
		{
			if (rand >= length || len >= length)
				return;
			uint32_t val = buffer[len];
			buffer[len] = buffer[rand];
			buffer[rand] = val;
		}
		--len;
	}
	return;
}