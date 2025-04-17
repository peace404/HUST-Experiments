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
	const std::string RESET = "\033[0m";  // ������ɫ
	const std::string BLUE = "\033[34m";   // ��ɫ
	const std::string YELLOW = "\033[1;33m"; // ����ɫ
	const std::string COL[3] = { RESET, YELLOW ,BLUE };
	cout << "��ǰ�Ļ������ڣ�";
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
	pUtils->printPacket("���ͷ����ͱ���", sendBuf[nextSeqnum]);
	if (sendbase == nextSeqnum)
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pns->sendToNetworkLayer(RECEIVER, sendBuf[nextSeqnum]);
	//������ϣ�����״̬
	nextSeqnum = (nextSeqnum + 1) % seqSize;
	std::cout << "���ͷ����ͺ󴰿ڣ�";
	printSlideWindow();
	std::cout << std::endl;
	return true;
}

void TCPRdtSender::timeoutHandler(int seqNum)
{
	pns->sendToNetworkLayer(RECEIVER, sendBuf[sendbase]);
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pUtils->printPacket("��ʱ�ش�:", sendBuf[sendbase]);
}

void TCPRdtSender::receive(const Packet& ackPkt)
{
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum != ackPkt.checksum){
		pUtils->printPacket("���ͷ�û����ȷ�յ�ȷ��", ackPkt);
		return;
	}
	if (inWindow(ackPkt.acknum)){
		sendbase = (ackPkt.acknum + 1) % seqSize;
		pns->stopTimer(SENDER, 0);
		if (sendbase != nextSeqnum)
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		dupAckNum = 0;
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		std::cout << "���ʹ���״̬��";
		printSlideWindow();
		std::cout << std::endl;
	}
	else{  //�Ѿ�ȷ�ϵ������ack
		dupAckNum = (dupAckNum + 1) % 4;
		pUtils->printPacket("���ͷ��յ�����ACK", ackPkt);
		if (dupAckNum == 3){  //�����ش�
			pns->sendToNetworkLayer(RECEIVER, sendBuf[sendbase]);
			std::cout << "\n�յ�������������ack�������ش�\n";
		}
	}    
}
