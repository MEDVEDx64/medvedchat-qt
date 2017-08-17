#include "protocol.h"

#include <stdlib.h>
#include <string.h>

RawPacket *createPacket()
{
    RawPacket *pkt = (RawPacket*)malloc(sizeof(RawPacket));
    memset(pkt, 0, sizeof(RawPacket));

    return pkt;
}

void destroyPacket(RawPacket **pkt)
{
    free(*pkt);
    *pkt = NULL;
}

uint32_t getPacketLength(RawPacket *pkt)
{
    return sizeof(pkt->header) + FLIP16(pkt->header.length_be);
}

QString getPacketText(RawPacket *pkt)
{
    return pkt->header.type == PL_TEXT
            ? QString::fromUtf8(pkt->payload)
            : QString("");
}

void setPacketText(RawPacket *pkt, QString text)
{
    pkt->header.type = PL_TEXT;
    QByteArray bytes = text.toUtf8();

    const int len = bytes.size();
    const int dstLen = sizeof(pkt->payload) - 1;
    const int finalLen = len > dstLen ? dstLen : len;

    memset(pkt->payload, 0, dstLen);
    memcpy(pkt->payload, bytes.constData(), finalLen);

    pkt->header.length_be = FLIP16(finalLen);
}
