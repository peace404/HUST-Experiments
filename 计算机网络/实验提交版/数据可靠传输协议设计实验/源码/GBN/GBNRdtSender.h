#pragma once

#include "RdtSender.h"
class GBNRdtSender :public RdtSender
{
private:
	int base; //基序号
	int nextSeqnum;	//下一个待发分组的序号
	static const int windSize = 4; //滑动窗口大小
	static const int seqSize = 8; //序号空间
	Packet* const sendBuf; //发送缓冲区
public:
	bool getWaitingState();
	bool send(const Message& message);	//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);	//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);	//Timeout handler，将被NetworkServiceSimulator调用
	void printSlideWindow() const;
public:
	GBNRdtSender();
	virtual ~GBNRdtSender();
};


