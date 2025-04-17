#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"
#pragma warning(disable: 6386)
GBNRdtSender::GBNRdtSender() :base(0), nextSeqnum(0), sendBuf(new Packet[8]) { ; }

GBNRdtSender::~GBNRdtSender() { delete[] sendBuf; }

//����������true
bool GBNRdtSender::getWaitingState()  
{
	return (base + windSize) % seqSize == nextSeqnum % seqSize;
}

bool GBNRdtSender::send(const Message& message)
{
	if (getWaitingState())
		return false;
	sendBuf[nextSeqnum].acknum = -1; //����ACK
	sendBuf[nextSeqnum].seqnum = nextSeqnum;
	memcpy(sendBuf[nextSeqnum].payload, message.data, sizeof(message.data));
	sendBuf[nextSeqnum].checksum = pUtils->calculateCheckSum(sendBuf[nextSeqnum]);
	pUtils->printPacket("���ͷ����ͱ���", sendBuf[nextSeqnum]);
	if (base == nextSeqnum) 
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);//������ʱ��
	pns->sendToNetworkLayer(RECEIVER, sendBuf[nextSeqnum]);
	nextSeqnum = (nextSeqnum + 1) % seqSize;
	printSlideWindow(); //��ӡ������Ϣ
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt)
{
	if (pUtils->calculateCheckSum(ackPkt) != ackPkt.checksum ){  //У�����
		pUtils->printPacket("����У�����", ackPkt);
		return;
	}
	base = (ackPkt.acknum + 1) % seqSize;
	pns->stopTimer(SENDER, 0);
	if (base != nextSeqnum) {
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	}
	pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
	printSlideWindow();
}

void GBNRdtSender::timeoutHandler(int seqNum)
{
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0); //������ʱ�������¼�ʱ
	for (int i = base; i != nextSeqnum; i = (i + 1) % seqSize){ //�ش�
		pns->sendToNetworkLayer(RECEIVER, sendBuf[i]);
		pUtils->printPacket("��ʱ�ش�:", sendBuf[i]);
	}
}

void GBNRdtSender::printSlideWindow() const
{
	const std::string RESET = "\033[0m";  // ������ɫ
	const std::string BLUE = "\033[34m";   // ��ɫ
	const std::string YELLOW = "\033[1;33m"; // ����ɫ
	const std::string COL[3] = { RESET, YELLOW ,BLUE };
	cout << "��ǰ�Ļ������ڣ�";
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
