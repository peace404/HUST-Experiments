#pragma once

#include "RdtReceiver.h"
class GBNRdtReceiver:public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;   // �ڴ��յ�����һ���������
	Packet lastAckPkt;				//�ϴη��͵�ȷ�ϱ���
	static const int seqSize = 8;	//���ڴ�С
public:
	GBNRdtReceiver();
	virtual ~GBNRdtReceiver();

public:

	void receive(const Packet& packet);	//���ձ��ģ�����NetworkService����

};

