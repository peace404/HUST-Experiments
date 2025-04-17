#pragma once
#include "RdtReceiver.h"
class SRRdtReceiver : public RdtReceiver
{
private:
	int rcvbase;
	static const int seqSize = 8, windSize = 4;
	Packet lastAckPkt;
	Message* const recvBuf;
	bool* const bufStatus;

private:
	void printSlideWindow() const;
	bool inWindow(int seqnum) const;

public:
	SRRdtReceiver();
	void receive(const Packet& packet);
	virtual ~SRRdtReceiver();
};

