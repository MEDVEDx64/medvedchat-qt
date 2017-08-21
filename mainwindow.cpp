#include "mainwindow.h"
#include "value.h"
#include "style.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , client(Q_NULLPTR)
{
    srand(time(0));

    setWindowTitle(tr("MedvedChat"));
    createInterior();
}

MainWindow::~MainWindow()
{
}

QString makeRandomNickName()
{
    char nick[10];
    memset(nick, 0, sizeof(nick));
    sprintf(nick, "User%d", rand() % 900 + 100);
    return QString(nick);
}

void MainWindow::createInterior()
{
    QWidget *wgt = new QWidget(this);
    QWidget *subWgt = new QWidget(wgt);

    setCentralWidget(wgt);
    setMinimumSize(480, 420);

    QGridLayout *grid = new QGridLayout(wgt);
    QGridLayout *subGrid = new QGridLayout(subWgt);

    subGrid->setMargin(0);

    QLabel *serverAddressLabel = new QLabel(tr("&Host:"), subWgt);
    QLabel *nickNameLabel = new QLabel(tr("&Nickname:"), subWgt);
    QPushButton *changeHostBtn = new QPushButton(tr("(Re-)Connect"), subWgt);
    QPushButton *changeNickNameBtn = new QPushButton(tr("Set nickname"), subWgt);

    serverAddressWgt = new QLineEdit(vget_ensure("host", "localhost"), subWgt);
    nickNameWgt = new QLineEdit(vget_ensure("nickname", makeRandomNickName()), subWgt);
    chatWgt = new QTextEdit(subWgt);
    inputWgt = new QLineEdit(subWgt);

    userListWgt = new QListWidget(wgt);

    inputWgt->setFocus();

    serverAddressLabel->setBuddy(serverAddressWgt);
    nickNameLabel->setBuddy(nickNameWgt);
    chatWgt->setReadOnly(true);
    userListWgt->setMaximumWidth(160);

    subGrid->addWidget(serverAddressLabel, 0, 0);
    subGrid->addWidget(serverAddressWgt, 0, 1);
    subGrid->addWidget(changeHostBtn, 0, 2);
    subGrid->addWidget(nickNameLabel, 0, 3);
    subGrid->addWidget(nickNameWgt, 0, 4);
    subGrid->addWidget(changeNickNameBtn, 0, 5);

    subGrid->addWidget(chatWgt, 1, 0, 1, 6);
    subGrid->addWidget(inputWgt, 2, 0, 1, 6);

    grid->addWidget(subWgt, 0, 0);
    grid->addWidget(userListWgt, 0, 1);

    connect(changeHostBtn, &QPushButton::clicked, this, &MainWindow::changeHost);
    connect(changeNickNameBtn, &QPushButton::clicked, this, &MainWindow::changeNickName);
    connect(serverAddressWgt, SIGNAL(returnPressed()), changeHostBtn, SIGNAL(clicked()));
    connect(nickNameWgt, SIGNAL(returnPressed()), changeNickNameBtn, SIGNAL(clicked()));
    connect(inputWgt, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);

    setStyleSheet(STYLE_STR);
}

void MainWindow::changeHost()
{
    if(client)
    {
        client->shutdown();
        delete client;
        client = Q_NULLPTR;
    }

    QString v = serverAddressWgt->text();
    if(!v.length())
    {
        QMessageBox::warning(this, tr("Error"), tr("Address value cannot be empty"));
        return;
    }

    QString addr = v;
    uint16_t port = DEFAULT_PORT;

    if(v.contains(':'))
    {
        QStringList s = v.split(':');
        addr = s[0];
        port = s[1].toUShort();
    }

    printNotification(tr("Connecting to host ") + addr + ":" + QString::number(port), NSTYLE_INTERNAL);
    client = new Client(addr, port, nickNameWgt->text(), this);

    connect(client, &Client::incomingPacket, this, &MainWindow::handlePacket);
    connect(client, &Client::disconnected, this, &MainWindow::handleDisconnection);
    connect(client, &Client::error, this, &MainWindow::handleError);

    vset("host", serverAddressWgt->text());
    inputWgt->setFocus();
}

void MainWindow::changeNickName()
{
    if(client != Q_NULLPTR)
    {
        client->setNickname(nickNameWgt->text());
    }

    vset("nickname", nickNameWgt->text());
    inputWgt->setFocus();
}

void MainWindow::handlePacket(RawPacket *pkt)
{
    if(pkt->header.type != PL_TEXT) return;
    QString text = getPacketText(pkt);

    switch (pkt->header.command) {
    case SRV_NOTIFICATION:
        printNotification(text, NSTYLE_REMOTE);
        break;

    case SRV_TEXT:
        if(text.contains('\n'))
        {
            QStringList s = text.split('\n');
            printMessage(s[1], s[0], false);
        }

        break;

    case SRV_USERLIST: {
        userListWgt->clear();

        QStringList names = text.split('\n');
        for(int i = 0; i < names.length(); i++)
        {
            userListWgt->insertItem(i, names[i]);
        }

        break;
    }

    default:
        break;
    }
}

void MainWindow::sendMessage()
{
    if(client == Q_NULLPTR)
    {
        return;
    }

    QString text = inputWgt->text();
    if(text.length() == 0)
    {
        return;
    }

    inputWgt->setText("");

    RawPacket *pkt = createPacket();
    pkt->header.command = CLI_NO_ACTION;
    setPacketText(pkt, text);

    client->sendPacket(pkt);
    destroyPacket(&pkt);
}

void MainWindow::moveTextCursorToEnd()
{
    QTextCursor cursor = chatWgt->textCursor();
    cursor.movePosition(QTextCursor::End);
    chatWgt->setTextCursor(cursor);
}

void MainWindow::printNotification(QString text, int style)
{
    QString prefix = style == NSTYLE_REMOTE ? "<x style=\"color: #028\">** "
            : style == NSTYLE_INTERNAL ? "<i style=\"color: #282\">"
            : style == NSTYLE_INTERNAL_ERR ? "<i style=\"color: #820\">" : "";
    QString postfix = style == NSTYLE_REMOTE ? "</x>"
            : (style == NSTYLE_INTERNAL || style == NSTYLE_INTERNAL_ERR) ? "</i>" : "";

    moveTextCursorToEnd();
    chatWgt->insertHtml(prefix + text.toHtmlEscaped() + postfix + "<br>\n");
    moveTextCursorToEnd();
}

void MainWindow::printMessage(QString text, QString sender, bool isPrivate)
{
    moveTextCursorToEnd();

    if(isPrivate)
    {
        chatWgt->insertHtml("<i style=\"color: #444\">");
    }

    chatWgt->insertHtml("<b>" + sender.toHtmlEscaped() + ":</b> " + text.toHtmlEscaped());

    if(isPrivate)
    {
        chatWgt->insertHtml("</i>");
    }

    chatWgt->insertHtml("<br>\n");
    moveTextCursorToEnd();
}

void MainWindow::handleDisconnection()
{
    userListWgt->clear();
    printNotification(tr("Disconnected."), NSTYLE_INTERNAL);
}

void MainWindow::handleError(QString text)
{
    userListWgt->clear();
    printNotification(text, NSTYLE_INTERNAL_ERR);
}
