#pragma once
#include "RdtSender.h"
class TCPRdtSender : public RdtSender
{
private:
	int sendbase,  nextSeqnum;
	static const int seqSize = 8, windSize = 4;
	Packet* const sendBuf;				
	int dupAckNum;		//�յ�3������ack�����ش�

private:
	bool inWindow(int seqnum) const;
	void printSlideWindow() const;

public:
	TCPRdtSender();
	virtual ~TCPRdtSender();

public:
	bool getWaitingState();
	bool send(const Message& message);
	void timeoutHandler(int seqNum);
	void receive(const Packet& ackPkt);
};


