#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <SPI.h>
#include <MFRC522.h>
#include <cstdio>
#include <QtSql/QSqlDatabase>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("/home/pi/fia.db");
       if(!mydb.open())
           qDebug() << "Can't Connect to DB !";
       else
           qDebug() << "Connected Successfully to DB !";
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->clear();
}
void MainWindow::clear(){
    ui->lineEdit->setText("");
}


