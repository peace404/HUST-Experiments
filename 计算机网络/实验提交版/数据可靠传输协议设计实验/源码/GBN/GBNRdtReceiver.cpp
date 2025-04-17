#include "stdafx.h"
#include "Global.h"
#include "GBNRdtReceiver.h"

GBNRdtReceiver::GBNRdtReceiver() :expectSequenceNumberRcvd(0){
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为0，使得当第一个接受的数据包出错时该确认报文的确认号为0
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

GBNRdtReceiver::~GBNRdtReceiver() { ; }


void GBNRdtReceiver::receive(const Packet& packet)
{
	if (pUtils->calculateCheckSum(packet) == packet.checksum && // 检查校验和是否正确
		expectSequenceNumberRcvd == packet.seqnum) {
		pUtils->printPacket("接收方正确收到发送方的报文", packet);
		Message msg; // 提取消息并递交给应用层
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		lastAckPkt.acknum = packet.seqnum;
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方发送确认报文", lastAckPkt);
		expectSequenceNumberRcvd = (expectSequenceNumberRcvd + 1) % seqSize;  // 更新期望序号
	}
	else {  // 打印错误信息
		if (pUtils->calculateCheckSum(packet) != packet.checksum)
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		else
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号错误", packet);
		pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
	}
	pns->sendToNetworkLayer(SENDER, lastAckPkt);
}
