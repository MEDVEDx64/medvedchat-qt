#include "client.h"

#include <QMessageBox>

Client::Client(QString host, uint16_t port, QObject *parent): QObject(parent)
  , socket(new QTcpSocket(this))
{
    connect(socket, &QAbstractSocket::connected, this, &Client::login);
    connect(socket, &QAbstractSocket::readyRead, this, &Client::fetch);
    connect(socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &Client::handleError);

    socket->connectToHost(host, port);
}

void Client::login()
{
}

void Client::fetch()
{
    socket->read((char*)&buffer, sizeof(buffer.header));
    socket->read((char*)buffer.payload, FLIP16(buffer.header.length_be));

    // Construct message object and emit incomingMessage here
}

void Client::handleError(QAbstractSocket::SocketError err)
{
    if(err != QAbstractSocket::RemoteHostClosedError)
    {
        QMessageBox::warning(Q_NULLPTR, tr("Networking failure")
                             ,tr("Error while operating with remote host: %1")
                             .arg(socket->errorString()));

        shutdown();
    }
}

void Client::shutdown()
{
    socket->close();
}
