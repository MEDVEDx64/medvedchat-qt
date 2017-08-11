#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QListView>

#include "client.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void createInterior();

    QLineEdit *serverAddressWgt;
    QLineEdit *nickNameWgt;
    QTextEdit *chatWgt;
    QListView *userListWgt;
    QLineEdit *inputWgt;

    Client *client;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changeHost();
    void changeNickName();
};

#endif // MAINWINDOW_H
