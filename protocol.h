// TPMP implementation

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#include <QString>

#define MAX_PAYLOAD_SIZE 0xffff
#define FLIP16(v) ((v >> 8) | ((v&0xff) << 8))

// Commands
#define CLI_NO_ACTION           0
#define CLI_LOGIN               1
#define CLI_PRIVATE             2
#define CLI_USERLIST_REQUEST    3
#define SRV_NOTIFICATION        32
#define SRV_TEXT                33
#define SRV_USERLIST            34

// Payload types
#define PL_TEXT                 1
#define PL_SHIT                 0

#pragma pack(push,1)

typedef struct
{
    uint8_t type: 1;
    uint8_t command: 7;
    uint16_t length_be;
}
RawPacketHeader;

typedef struct
{
    RawPacketHeader header;
    char payload[MAX_PAYLOAD_SIZE];
}
RawPacket;

#pragma pack(pop)

RawPacket *createPacket();
void destroyPacket(RawPacket **pkt);
uint32_t getPacketLength(RawPacket *pkt);

QString getPacketText(RawPacket *pkt);
void setPacketText(RawPacket *pkt, QString text);

#endif // PROTOCOL_H
