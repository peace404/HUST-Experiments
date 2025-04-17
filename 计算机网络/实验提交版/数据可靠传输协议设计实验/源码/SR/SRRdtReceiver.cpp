#include "SRRdtReceiver.h"
#include "stdafx.h"
#include "Global.h"
#pragma warning(disable: 6386)
SRRdtReceiver::SRRdtReceiver() : recvBuf(new Message[seqSize]), bufStatus(new bool[seqSize]), rcvbase(0)
{
	for (int i = 0; i < seqSize; i++)
		bufStatus[i] = false;
	lastAckPkt.acknum = -1; 
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	
	memset(lastAckPkt.payload, '.', Configuration::PAYLOAD_SIZE);
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

SRRdtReceiver::~SRRdtReceiver()
{
	delete[] recvBuf;
	delete[] bufStatus;
}

bool SRRdtReceiver::inWindow(int seqnum) const
{
	int windowEnd = (rcvbase + windSize) % seqSize;
	return (rcvbase < windowEnd) ? (seqnum >= rcvbase && seqnum < windowEnd) : (seqnum >= rcvbase || seqnum < windowEnd);
}
 
void SRRdtReceiver::receive(const Packet& packet)
{
    if (pUtils->calculateCheckSum(packet) != packet.checksum){
        pUtils->printPacket("数据校验错误", packet);
        return;
    }
    if (!inWindow(packet.seqnum)){
        pUtils->printPacket("不是窗口内的分组，忽略", packet);
        lastAckPkt.acknum = packet.seqnum;
        lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
        pns->sendToNetworkLayer(SENDER, lastAckPkt);
        return;
    }
    pUtils->printPacket("接收方正确收到发送方的报文", packet);
    if (packet.seqnum == rcvbase){   // 按序分组
        Message msg;
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        int flag = rcvbase;
        for (int i = (rcvbase + 1) % seqSize; bufStatus[i] && i != (rcvbase + windSize) % seqSize; i = (i + 1) % seqSize)
            flag = i;
        for (int i = rcvbase; i != (flag + 1) % seqSize; i = (i + 1) % seqSize){
            pns->delivertoAppLayer(RECEIVER, recvBuf[i]);
            bufStatus[i] = false;
        }
        rcvbase = (flag + 1) % seqSize;
        std::cout << "接收方窗口滑动：";
        printSlideWindow();
    }
    else{ // 乱序分组缓存
        memcpy(recvBuf[packet.seqnum].data, packet.payload, sizeof(packet.payload));
        bufStatus[packet.seqnum] = true;
        printf("报文序号中断，接收方缓存报文序号%d，rcvbase=%d\n", packet.seqnum, rcvbase);
    }
    lastAckPkt.acknum = packet.seqnum;
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
    pUtils->printPacket("接收方发送确认报文", lastAckPkt);
    pns->sendToNetworkLayer(SENDER, lastAckPkt);
}


void SRRdtReceiver::printSlideWindow() const
{
	const std::string RESET = "\033[0m";  // 重置颜色
	const std::string GREEN = "\033[32m";  // 绿色
	const std::string BLUE = "\033[34m";   // 蓝色
	const std::string YELLOW = "\033[1;33m"; // 亮黄色
	const std::string COL[4] = { RESET, GREEN, YELLOW, BLUE };
	int window[seqSize]{};
	int windEnd = (rcvbase + windSize) % seqSize;
	int flag = rcvbase;
	for (int i = rcvbase; i != windEnd; i = (i + 1) % seqSize) {
		if (bufStatus[i]) {
			window[i] = 1;
			flag = i;
		}
		else
			window[i] = 2;
	}
	for (int i = rcvbase; i != flag; i = (i + 1) % seqSize) {
		if(!bufStatus[i])
			window[i] = 3;
	}
	for (int i = 0; i < seqSize; i++) {
		cout << COL[window[i]] << i << " ";
	}
	std::cout << RESET << std::endl;
}
