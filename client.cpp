#include "client.h"

#include <stdlib.h>
#include <stdio.h>

#include <QMessageBox>

Client::Client(QString host, uint16_t port, QString nickName, QObject *parent): QObject(parent)
  , socket(new QTcpSocket(this))
  , nickName(nickName)
{
    connect(socket, &QAbstractSocket::connected, this, &Client::login);
    connect(socket, &QAbstractSocket::readyRead, this, &Client::fetch);
    connect(socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &Client::handleError);
    connect(socket, &QAbstractSocket::disconnected, this, &Client::disconnected);

    socket->connectToHost(host, port);
}

void Client::setNickname(QString nickName)
{
    this->nickName = nickName;
    login();
}

void Client::login()
{
    RawPacket *pkt = createPacket();
    pkt->header.command = CLI_LOGIN;
    setPacketText(pkt, nickName);

    sendPacket(pkt);

    destroyPacket(&pkt);
}

void Client::fetch()
{
    memset(&buffer, 0, sizeof(buffer));
    socket->read((char*)&buffer, sizeof(buffer));

    // trimming unwanted overflow data if any
    uint16_t len = FLIP16(buffer.header.length_be);
    if(len == sizeof(buffer.payload)) len--;
    buffer.payload[len] = 0;

    emit incomingPacket(&buffer);
}

void Client::handleError(QAbstractSocket::SocketError err)
{
    if(err != QAbstractSocket::RemoteHostClosedError)
    {
        emit error(tr("Error while operating with remote host: %1").arg(socket->errorString()));
        shutdown();
    }
}

void Client::sendPacket(RawPacket *pkt)
{
    socket->write((char*)pkt, getPacketLength(pkt));
}

void Client::shutdown()
{
    socket->close();
}
