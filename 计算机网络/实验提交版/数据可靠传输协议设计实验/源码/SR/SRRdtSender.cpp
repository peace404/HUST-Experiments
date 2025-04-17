#include "SRRdtSender.h"
#include "stdafx.h"
#include "Global.h"

SRRdtSender::SRRdtSender() : sendbase(0), nextSeqnum(0), sendBuf(new Packet[seqSize]), bufStatus(new bool[seqSize])
{
	for (int i = 0; i < seqSize; i++)
		bufStatus[i] = false;
}

SRRdtSender::~SRRdtSender()
{
	delete[] bufStatus;
	delete[] sendBuf;
}

bool SRRdtSender::getWaitingState()
{
	return (sendbase + windSize) % seqSize == (nextSeqnum) % seqSize;
}

//�ж�����Ƿ��ڴ�����
bool SRRdtSender::inWindow(int seqnum) const
{
	int windowEnd = (sendbase + windSize) % seqSize;
	return (sendbase < windowEnd) ? (seqnum >= sendbase && seqnum < windowEnd) : (seqnum >= sendbase || seqnum < windowEnd);
}

bool SRRdtSender::send(const Message& message)
{
	if (getWaitingState())
		return false;
	bufStatus[nextSeqnum] = false;
	sendBuf[nextSeqnum].acknum = -1;
	sendBuf[nextSeqnum].seqnum = nextSeqnum;
	memcpy(sendBuf[nextSeqnum].payload, message.data, sizeof(message.data));
	sendBuf[nextSeqnum].checksum = pUtils->calculateCheckSum(sendBuf[nextSeqnum]);
	pUtils->printPacket("���ͷ����ͱ���", sendBuf[nextSeqnum]);
	pns->sendToNetworkLayer(RECEIVER, sendBuf[nextSeqnum]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, nextSeqnum);
	nextSeqnum = (nextSeqnum + 1) % seqSize;
	std::cout << "���ͷ����ڣ�";
	printSlideWindow();
	std::cout << std::endl;
	return true;
}

void SRRdtSender::receive(const Packet& ackPkt)
{
	if (pUtils->calculateCheckSum(ackPkt) != ackPkt.checksum){
		pUtils->printPacket("���ͷ�û����ȷ�յ�ȷ��", ackPkt);
		return;
	}
	pns->stopTimer(SENDER, ackPkt.acknum);
	if (!inWindow(ackPkt.acknum))
		return;
	bufStatus[ackPkt.acknum] = true;  //���´���
	while (bufStatus[sendbase] == true){
		bufStatus[sendbase] = false;
		sendbase = (sendbase + 1) % seqSize;
	}
	pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
	std::cout << "���ͷ����ڣ�";
	printSlideWindow();
	std::cout << std::endl;
}

void SRRdtSender::timeoutHandler(int seqnum)
{
	pUtils->printPacket("��ʱ�ش�", sendBuf[seqnum]);
	pns->sendToNetworkLayer(RECEIVER, sendBuf[seqnum]);
	pns->stopTimer(SENDER, seqnum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqnum);

}

void SRRdtSender::printSlideWindow() const
{
	const std::string RESET = "\033[0m";  // ������ɫ
	const std::string GREEN = "\033[32m";  // ��ɫ
	const std::string BLUE = "\033[34m";   // ��ɫ
	const std::string YELLOW = "\033[1;33m"; // ����ɫ
	const std::string COL[4] = { RESET, GREEN, YELLOW, BLUE };
	int window[seqSize]{};
	int windEnd = (sendbase + windSize) % seqSize;

	for (int i = sendbase; i != nextSeqnum; i = (i + 1) % seqSize)
		window[i] = bufStatus[i] ? 1 : 2;
	for (int i = nextSeqnum; i != windEnd; i = (i + 1) % seqSize) 
		window[i] = 3;
	for (int i = 0; i < seqSize; i++)
		cout << COL[window[i]] << i << " ";
	std::cout << RESET << std::endl;
}
