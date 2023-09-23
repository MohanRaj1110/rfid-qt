// Adapted from
// https://github.com/miguelbalboa/rfid/blob/master/examples/ReadUidMultiReader/ReadUidMultiReader.ino

#include <cstdio>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MFRC522.h"
#include<QDebug>
#include<iostream>
#include <sstream>
#include <iomanip>
#include<QThread>
#include<QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#define RST_1_PIN RPI_V2_GPIO_P1_15
#define RST_2_PIN RPI_V2_GPIO_P1_18
#define SS_1_PIN RPI_V2_GPIO_P1_38
#define SS_2_PIN RPI_V2_GPIO_P1_40

#define NR_OF_READERS 2

uint8_t ssPins[] = {SS_1_PIN, SS_2_PIN};
uint8_t rstPins[] = {RST_1_PIN, RST_2_PIN};
int stop=1,count;
QString key="";
/**
 * Helper routine to dump a byte array as hex values.
 */


void MainWindow::printHex(uint8_t *buffer, size_t bufferSize) {
    MFRC522 mfrc522[NR_OF_READERS];
   int count;
  for (size_t i = 0; i < bufferSize; i++) {
    printf(" %02X", buffer[i]);
    qDebug()<<buffer[i];
    QString hexQString = QString("%1").arg(buffer[i], 0, 16).toUpper();
    key=key+hexQString;
    qDebug()<<key;
  }
  if(key.length()>=7){
  stop=0;
  QString dummy;
  QSqlQuery qry;
  qry.prepare("select cardID from rfid_scan where cardID='"+key+"'");
  qry.exec();
  while(qry.next());
  dummy=qry.value(1).toString();
  qDebug()<<dummy;
  ui->lineEdit_2->setText(dummy);
  if(dummy==""){
      QSqlQuery query;
      query.prepare("insert into rfid_scan(cardID,Testcount)values('"+key+"','"+count+"')");
      query.exec();
      qDebug()<<"new card";
}
}}
int MainWindow::on_pushButton_clicked(){
clear();
stop=1;
key="";
QThread::msleep(2000);
reader();
}
int MainWindow::reader(){

  MFRC522 mfrc522[NR_OF_READERS];  // Create MFRC522 instance
  for (size_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader],
                             rstPins[reader]);  // Init each MFRC522 card
    printf("Reader ");
    printf("%u", reader);
    printf(": ");
    mfrc522[reader].PCD_DumpVersionToSerial();
  }

  while (stop==1) {
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
      // Look for new cards
      mfrc522[reader].PCD_AntennaOn();

      if ((mfrc522[reader].PICC_IsNewCardPresent() ||
           mfrc522[reader].PICC_IsNewCardPresent()) &&
          mfrc522[reader].PICC_ReadCardSerial()) {
        printf("Reader ");
        //QString a;
        // Show some details of the PICC (that is: the tag/card)
        printf(": Card UID:");
        printHex(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
        ui->lineEdit->setText(key);
        //sprintf(a,"%X",(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size));
        //qDebug()<<mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size;
        printf("\n");
        printf("PICC type: ");
        MFRC522::PICC_Type piccType =
            mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
        printf(mfrc522[reader].PICC_GetTypeName(piccType).c_str());
        printf("\n");
      } else {
        printf("Reader %u: none\n", reader);

      }
      mfrc522[reader].PCD_AntennaOff();

      bcm2835_delay(250);
    }
  }

  return 0;
}

