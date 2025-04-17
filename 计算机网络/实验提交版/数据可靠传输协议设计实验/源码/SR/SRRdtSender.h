#pragma once
#include "RdtSender.h"
class SRRdtSender : public RdtSender
{
private:
	int sendbase, nextSeqnum;
	static const int seqSize = 8; 
	static const int windSize = 4;
	Packet* const sendBuf;
	bool* const bufStatus;
	

private:
	void printSlideWindow() const;
	bool inWindow(int seqnum) const;

public:
	SRRdtSender();
	bool send(const Message& message);
	bool getWaitingState();
	void timeoutHandler(int seqnum);
	void receive(const Packet& ackPkt);
	virtual ~SRRdtSender();
};
