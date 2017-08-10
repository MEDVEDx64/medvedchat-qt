#include "mainwindow.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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

    QGridLayout *grid = new QGridLayout(wgt);
    QGridLayout *subGrid = new QGridLayout(subWgt);

    subGrid->setMargin(0);

    QLabel *serverAddressLabel = new QLabel(tr("Host:"), subWgt);
    QLabel *nickNameLabel = new QLabel(tr("Nickname:"), subWgt);
    QPushButton *changeHostBtn = new QPushButton(tr("(Re-)Connect"), subWgt);
    QPushButton *changeNickNameBtn = new QPushButton(tr("Set nickname"), subWgt);

    serverAddressWgt = new QLineEdit("themassacre.org", subWgt);
    nickNameWgt = new QLineEdit(makeRandomNickName(), subWgt);
    chatWgt = new QTextEdit(subWgt);
    inputWgt = new QLineEdit(subWgt);

    userListWgt = new QListView(wgt);

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
}
