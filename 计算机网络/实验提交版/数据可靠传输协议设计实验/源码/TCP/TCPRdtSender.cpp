#include "stdafx.h"
#include "TCPRdtSender.h"
#include "Global.h"

TCPRdtSender::TCPRdtSender() : sendbase(0), nextSeqnum(0), dupAckNum(0), sendBuf(new Packet[seqSize]){;}
TCPRdtSender::~TCPRdtSender(){}

bool TCPRdtSender::inWindow(int seqnum) const
{
	int windowEnd = (sendbase + windSize) % seqSize;
	return (sendbase < windowEnd) ? (seqnum >= sendbase && seqnum < windowEnd) : (seqnum >= sendbase || seqnum < windowEnd);
}

void TCPRdtSender::printSlideWindow() const
{
	const std::string RESET = "\033[0m";  // 重置颜色
	const std::string BLUE = "\033[34m";   // 蓝色
	const std::string YELLOW = "\033[1;33m"; // 亮黄色
	const std::string COL[3] = { RESET, YELLOW ,BLUE };
	cout << "当前的滑动窗口：";
	int window[seqSize]{};
	int end = (sendbase + windSize) % seqSize;
	for (int i = sendbase; i != nextSeqnum; i = (i + 1) % seqSize) 
		window[i] = 1;
	for (int i = nextSeqnum; i != end; i = (i + 1) % seqSize) 
		window[i] = 2;
	for (int i = 0; i < seqSize; i++) 
		cout << COL[window[i]] << i << " ";
	std::cout << RESET << std::endl;
}


bool TCPRdtSender::getWaitingState()
{
	return (sendbase + windSize) % seqSize == (nextSeqnum) % seqSize;
}

bool TCPRdtSender::send(const Message& message)
{
	if (getWaitingState())
		return false;
	sendBuf[nextSeqnum].acknum = -1;
	sendBuf[nextSeqnum].seqnum = nextSeqnum;
	memcpy(sendBuf[nextSeqnum].payload, message.data, sizeof(message.data));
	sendBuf[nextSeqnum].checksum = pUtils->calculateCheckSum(sendBuf[nextSeqnum]);
	pUtils->printPacket("发送方发送报文", sendBuf[nextSeqnum]);
	if (sendbase == nextSeqnum)
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pns->sendToNetworkLayer(RECEIVER, sendBuf[nextSeqnum]);
	//发送完毕，更新状态
	nextSeqnum = (nextSeqnum + 1) % seqSize;
	std::cout << "发送方发送后窗口：";
	printSlideWindow();
	std::cout << std::endl;
	return true;
}

void TCPRdtSender::timeoutHandler(int seqNum)
{
	pns->sendToNetworkLayer(RECEIVER, sendBuf[sendbase]);
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pUtils->printPacket("超时重传:", sendBuf[sendbase]);
}

void TCPRdtSender::receive(const Packet& ackPkt)
{
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum != ackPkt.checksum){
		pUtils->printPacket("发送方没有正确收到确认", ackPkt);
		return;
	}
	if (inWindow(ackPkt.acknum)){
		sendbase = (ackPkt.acknum + 1) % seqSize;
		pns->stopTimer(SENDER, 0);
		if (sendbase != nextSeqnum)
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		dupAckNum = 0;
		pUtils->printPacket("发送方正确收到确认", ackPkt);
		std::cout << "发送窗口状态：";
		printSlideWindow();
		std::cout << std::endl;
	}
	else{  //已经确认的冗余的ack
		dupAckNum = (dupAckNum + 1) % 4;
		pUtils->printPacket("发送方收到冗余ACK", ackPkt);
		if (dupAckNum == 3){  //快速重传
			pns->sendToNetworkLayer(RECEIVER, sendBuf[sendbase]);
			std::cout << "\n收到连续三个冗余ack，快速重传\n";
		}
	}    
}
