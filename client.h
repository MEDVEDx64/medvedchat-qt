#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "protocol.h"

#define DEFAULT_PORT 11070
#define BUFFER_SIZE sizeof(RawPacket)

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QString host, uint16_t port, QObject *parent = 0);

    void shutdown();

private:
    QTcpSocket *socket;
    RawPacket buffer;

signals:
    void incomingMessage(AbstractMessage msg);

private slots:
    void login();
    void fetch();
    void handleError(QAbstractSocket::SocketError err);
};

#endif // CLIENT_H
