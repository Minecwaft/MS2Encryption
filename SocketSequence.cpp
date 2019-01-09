#include "SocketSequence.h"



SocketSequence::SocketSequence(uint32_t recv, uint32_t send, uint32_t block)
{
	this->recv_sequence = recv;
	this->send_sequence = send;
	this->block_key = block;
}


SocketSequence::~SocketSequence()
{
}

void SocketSequence::update_recv_sequence()
{
	this->recv_sequence = this->rand.crt_rand32(this->recv_sequence);
}
void SocketSequence::update_send_sequence()
{
	this->send_sequence = this->rand.crt_rand32(this->send_sequence);
}