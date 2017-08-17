#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>

#include "client.h"

#define NSTYLE_REMOTE           1
#define NSTYLE_INTERNAL         2
#define NSTYLE_INTERNAL_ERR     3

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void createInterior();

    QLineEdit *serverAddressWgt;
    QLineEdit *nickNameWgt;
    QTextEdit *chatWgt;
    QListWidget *userListWgt;
    QLineEdit *inputWgt;

    Client *client;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changeHost();
    void changeNickName();
    void sendMessage();

    void handlePacket(RawPacket *pkt);
    void handleDisconnection();
    void handleError(QString text);

    void moveTextCursorToEnd();

private:
    void printNotification(QString text, int style);
    void printMessage(QString text, QString sender, bool isPrivate);
};

#endif // MAINWINDOW_H
