// TPMP implementation

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define MAX_PAYLOAD_SIZE 0x10000
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

typedef struct
{
    unsigned int command: 7;
    unsigned int type: 1;
    uint16_t length_be;
}
RawPacketHeader;

typedef struct
{
    RawPacketHeader header;
    char payload[MAX_PAYLOAD_SIZE];
}
RawPacket;

class AbstractMessage
{
public:
    AbstractMessage(RawPacket raw);
};

#endif // PROTOCOL_H
