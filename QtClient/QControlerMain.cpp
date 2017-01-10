#include "QControlerMain.h"
#include "Sender.h"

#include <iostream>
using namespace std;

extern Sender sender_m;

QControlerMain::QControlerMain(QObject *parent) : QObject(parent)
{

}

QControlerMain::~QControlerMain(){

}

void QControlerMain::hdn_send_message(QString content){
    CMessage message = { CMessage::MESS_A, content.toStdString()};
//    StreamBaseSptr stream(new StreamUDP("127.0.0.1", 5002));
    StreamBaseSptr stream(new StreamTCP("127.0.0.1", 5001));
    sender_m.push({ stream, message, send_and_close});
    cout << content.toStdString() << "\n";
}
