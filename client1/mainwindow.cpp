#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui -> textEdit -> toPlainText();
    textSocket->write(text.toStdString().c_str(),strlen(text.toStdString().c_str()));
    ui -> textEdit ->clear();
    ui ->textEdit->cursor();
}
void MainWindow::socket_init(){
    textSocket = new QTcpSocket();
    textSocket -> abort();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString serverAddress = ui -> lineEdit -> text();
    quint16 serverPort = ui->lineEdit_2-> text().toInt();
    textSocket -> connectToHost(serverAddress,serverPort);
    connect(textSocket,SIGNAL(readyRead()),this,SLOT(reveiveNews()));
    QMessageBox::information(this,tr("提示"),tr("连接成功！"));
}
void MainWindow::reveiveNews(){
    if(!isHead&&!isFile){
        ui->progressBar->setValue(0);
        QByteArray text = textSocket -> readAll();
        QString strText = QVariant(text).toString();
        if(strText == "headiscoming"){
            isHead = true;
        }else{
            ui ->textEdit_2->append("服务器: " + strText);
        }
    }else if(isHead){
        isHead = false;
        isFile = true;
        QByteArray head = textSocket -> readAll();
        qDebug()<<head;
        fileName = QVariant(head).toString().section("##",0,0);
        fileSize = QVariant(head).toString().section("##",1,1).toInt();
        ui->progressBar->setMaximum(fileSize);
        ui->progressBar->setMinimum(0);
        recSize = 0;
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);
        textSocket->write("headReceiveSuccess");
    }else if(isFile){
        QByteArray buf = textSocket -> readAll();
        qint64 len = file.write((buf));
        recSize += len;
        ui->progressBar->setValue(recSize);
        if(recSize == fileSize){
            file.close();
            QMessageBox::information(this,"完成","文件接收完毕");
            isFile = false;
        }
    }

}


