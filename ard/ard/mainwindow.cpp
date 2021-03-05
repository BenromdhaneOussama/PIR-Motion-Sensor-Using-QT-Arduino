#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino();
    switch (ret)
    {
    case(0):
        qDebug()<<"arduino is available and connected to:"<<A.getarduino_port_name();
        break;
    case(1):
        qDebug()<<"arduino is available but not connected to:"<<A.getarduino_port_name();
        break;
    case(-1):
        qDebug()<<"arduino is not available";


    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    A.write_to_arduino("1");
}

void MainWindow::on_pushButton_2_clicked()
{
    A.write_to_arduino("0");
}
void MainWindow::update_label()
{
    data=A.read_from_arduino();
    if(data=="1")
    ui->label_3->setText("ON");
    else if (data=="0")
        ui->label_3->setText("OFF");


}

