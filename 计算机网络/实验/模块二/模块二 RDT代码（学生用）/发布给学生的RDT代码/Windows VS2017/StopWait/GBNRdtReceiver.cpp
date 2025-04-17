#include "stdafx.h"
#include "Global.h"
#include "GBNRdtReceiver.h"

GBNRdtReceiver::GBNRdtReceiver() :expectSequenceNumberRcvd(0){
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ0��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ0
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

GBNRdtReceiver::~GBNRdtReceiver() { ; }


void GBNRdtReceiver::receive(const Packet& packet)
{
	if (pUtils->calculateCheckSum(packet) == packet.checksum && // ���У����Ƿ���ȷ
		expectSequenceNumberRcvd == packet.seqnum) {
		pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);
		Message msg; // ��ȡ��Ϣ���ݽ���Ӧ�ò�
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		lastAckPkt.acknum = packet.seqnum;
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
		expectSequenceNumberRcvd = (expectSequenceNumberRcvd + 1) % seqSize;  // �����������
	}
	else {  // ��ӡ������Ϣ
		if (pUtils->calculateCheckSum(packet) != packet.checksum)
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
		else
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ŵ���", packet);
		pUtils->printPacket("���շ����·����ϴε�ȷ�ϱ���", lastAckPkt);
	}
	pns->sendToNetworkLayer(SENDER, lastAckPkt);
}
