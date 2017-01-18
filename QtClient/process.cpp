#include "general.h"
#include "Listener.h"
#include "QControlerMain.h"

extern Listener listener_m;
extern QControlerMain main_controler;

int process_message(const CMessage& m){

    switch (m._Type) {
    case CMessage::M_LOGIN:
    {
        string content = m._Data;
        break;
    }
    case CMessage::M_CHATG:
    {
        string content = m._Data;
        emit main_controler.sgn_recv_msg(QString(content.c_str()));
        break;
    }
    default:
        break;
    }

    return 0;
}
