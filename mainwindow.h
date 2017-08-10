#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QListView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void createInterior();

    QLineEdit *serverAddressWgt;
    QLineEdit *nickNameWgt;
    QTextEdit *chatWgt;
    QListView *userListWgt;
    QLineEdit *inputWgt;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
