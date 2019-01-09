#pragma once
#include <stdint.h>
#include "Rand32.h"

class SocketSequence
{
public:
	uint32_t recv_sequence;
	uint32_t send_sequence;
	uint32_t block_key;
	Rand32 rand;

	void update_recv_sequence();
	void update_send_sequence();
	SocketSequence(uint32_t recv, uint32_t send, uint32_t block);
	~SocketSequence();
};

