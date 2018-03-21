#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket* serverSocket;
    QTcpServer* tcpServer;
    //void receiveNews();
    void sendFile();
private:
    Ui::MainWindow *ui;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;


public slots:
    void receiveNews();
    void newConnect();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // MAINWINDOW_H
