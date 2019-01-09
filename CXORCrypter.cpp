#include "CXORCrypter.h"
#include "Rand32.h"
CXORCrypter::CXORCrypter()
{
	this->swap_bytes = new uint8_t[2];
}


CXORCrypter::~CXORCrypter()
{
	delete this->swap_bytes;
}

void CXORCrypter::init()
{
	Rand32* xor1 = new Rand32(MS2_VERSION);
	Rand32* xor2 = new Rand32(MS2_VERSION * 2);
	this->swap_bytes[0] = (xor1->randomfloat() * RAND32_FLOAT_CONSTANT);
	this->swap_bytes[1] = (xor2->randomfloat() * RAND32_FLOAT_CONSTANT);
	delete xor1;
	delete xor2;
}

int32_t CXORCrypter::encrypt(uint8_t* buffer, uint32_t length, uint32_t seqKey)
{
	uint32_t index = 0;
	if (length)
	{
		bool flag = false;
		do
		{
			buffer[index++] ^= this->swap_bytes[flag];
			flag = !flag;
		} while (index < length);
	}
	return index;
}

int32_t CXORCrypter::decrypt(uint8_t* buffer, uint32_t length, uint32_t seqKey)
{
	uint32_t index = 0;
	if (length)
	{
		bool flag = false;
		do
		{
			buffer[index++] ^= this->swap_bytes[flag];
			flag = !flag;
		} while (index < length);
	}
	return 1;
}
