#include "QControlerMain.h"
#include "Sender.h"
#include "Listener.h"

#include <iostream>
#include <string>
using namespace std;

extern Sender sender_m;
extern Listener listener_m;
extern StreamBaseSptr stream_m;


QControlerMain::QControlerMain(QObject *parent) : QObject(parent)
{

}

QControlerMain::~QControlerMain(){

}

void QControlerMain::hdn_send_message(QString content){
    CMessage message = { CMessage::M_CHATG, content.toStdString()};
    sender_m.push({ StreamBaseSptr(new StreamTCP("127.0.0.1", 5001)), message, send_and_close});
}

void QControlerMain::hdn_signin(QString usrname){
    CMessage message = { CMessage::M_LOGIN, usrname.toStdString()};
    sender_m.push({ stream_m, message, send_and_keep});
    listener_m.active();
}

void QControlerMain::hdn_signout(QString usrname){
    CMessage message = { CMessage::M_LOGOUT, usrname.toStdString()};
    sender_m.push({ stream_m, message, send_and_close});
}
