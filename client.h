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
    explicit Client(QString host, uint16_t port, QString nickName, QObject *parent = 0);

    void setNickname(QString nickName);
    void sendPacket(RawPacket *pkt);
    void shutdown();

private:
    QString nickName;
    QTcpSocket *socket;
    RawPacket buffer;

signals:
    void incomingPacket(RawPacket *pkt);
    void disconnected();
    void error(QString text);

private slots:
    void login();
    void fetch();
    void handleError(QAbstractSocket::SocketError err);
};

#endif // CLIENT_H
