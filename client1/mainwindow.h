#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QFileInfo>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void socket_init();
    QTcpSocket* textSocket;
public slots:
    void reveiveNews();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    bool isHead = false;
    bool isFile = false;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recSize;
};

#endif // MAINWINDOW_H
