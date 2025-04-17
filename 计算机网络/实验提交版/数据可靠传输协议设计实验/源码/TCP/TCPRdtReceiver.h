#pragma once
#include "RdtReceiver.h"
class TCPRdtReceiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;	
	Packet lastAckPkt;				
	static const int seqSize = 8;
public:
	TCPRdtReceiver();
	virtual ~TCPRdtReceiver();
	void receive(const Packet& packet);	
};
