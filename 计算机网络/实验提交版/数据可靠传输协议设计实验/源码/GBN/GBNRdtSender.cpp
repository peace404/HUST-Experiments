#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"
#pragma warning(disable: 6386)
GBNRdtSender::GBNRdtSender() :base(0), nextSeqnum(0), sendBuf(new Packet[8]) { ; }

GBNRdtSender::~GBNRdtSender() { delete[] sendBuf; }

//窗口满返回true
bool GBNRdtSender::getWaitingState()  
{
	return (base + windSize) % seqSize == nextSeqnum % seqSize;
}

bool GBNRdtSender::send(const Message& message)
{
	if (getWaitingState())
		return false;
	sendBuf[nextSeqnum].acknum = -1; //忽略ACK
	sendBuf[nextSeqnum].seqnum = nextSeqnum;
	memcpy(sendBuf[nextSeqnum].payload, message.data, sizeof(message.data));
	sendBuf[nextSeqnum].checksum = pUtils->calculateCheckSum(sendBuf[nextSeqnum]);
	pUtils->printPacket("发送方发送报文", sendBuf[nextSeqnum]);
	if (base == nextSeqnum) 
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);//开启计时器
	pns->sendToNetworkLayer(RECEIVER, sendBuf[nextSeqnum]);
	nextSeqnum = (nextSeqnum + 1) % seqSize;
	printSlideWindow(); //打印窗口信息
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt)
{
	if (pUtils->calculateCheckSum(ackPkt) != ackPkt.checksum ){  //校验检查和
		pUtils->printPacket("数据校验错误", ackPkt);
		return;
	}
	base = (ackPkt.acknum + 1) % seqSize;
	pns->stopTimer(SENDER, 0);
	if (base != nextSeqnum) {
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	}
	pUtils->printPacket("发送方正确收到确认", ackPkt);
	printSlideWindow();
}

void GBNRdtSender::timeoutHandler(int seqNum)
{
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0); //重启计时器，重新计时
	for (int i = base; i != nextSeqnum; i = (i + 1) % seqSize){ //重传
		pns->sendToNetworkLayer(RECEIVER, sendBuf[i]);
		pUtils->printPacket("超时重传:", sendBuf[i]);
	}
}

void GBNRdtSender::printSlideWindow() const
{
	const std::string RESET = "\033[0m";  // 重置颜色
	const std::string BLUE = "\033[34m";   // 蓝色
	const std::string YELLOW = "\033[1;33m"; // 亮黄色
	const std::string COL[3] = { RESET, YELLOW ,BLUE };
	cout << "当前的滑动窗口：";
	int window[seqSize]{};
	int end = (base + windSize) % seqSize;
	for (int i = base; i != nextSeqnum; i = (i + 1) % seqSize) 
		window[i] = 1;
	for (int i = nextSeqnum; i != end; i = (i + 1) % seqSize) 
		window[i] = 2;
	for (int i = 0; i < seqSize; i++) 
		cout << COL[window[i]] << i << " ";
	std::cout << RESET << std::endl;
}
