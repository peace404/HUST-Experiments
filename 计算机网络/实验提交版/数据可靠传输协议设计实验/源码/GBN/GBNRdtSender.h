#pragma once

#include "RdtSender.h"
class GBNRdtSender :public RdtSender
{
private:
	int base; //�����
	int nextSeqnum;	//��һ��������������
	static const int windSize = 4; //�������ڴ�С
	static const int seqSize = 8; //��ſռ�
	Packet* const sendBuf; //���ͻ�����
public:
	bool getWaitingState();
	bool send(const Message& message);	//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);	//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);	//Timeout handler������NetworkServiceSimulator����
	void printSlideWindow() const;
public:
	GBNRdtSender();
	virtual ~GBNRdtSender();
};


