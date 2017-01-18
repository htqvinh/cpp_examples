
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

#include "Sender.h"
#include "Listener.h"
#include "QControlerMain.h"

extern int process_message(const CMessage& m);

/* Global variables start */
QControlerMain main_controler;
StreamBaseSptr stream_m(new StreamTCP("127.0.0.1", 5001));
Listener listener_m(stream_m, process_message);
Sender sender_m;
/* Global variables end */

int main(int argc, char** argv){
    QGuiApplication app(argc, argv);

    sender_m.active();

    // Using QQuickView
    QQuickView view;
    view.setSource(QUrl::fromLocalFile("/data/proj/cpp_examples/QtClient/QViewMain.qml"));

    QObject *root = (QObject*)view.rootObject();

    QObject::connect(root, SIGNAL(sgn_send_message(QString)),
                     &main_controler, SLOT(hdn_send_message(QString)));
    QObject::connect(root, SIGNAL(sgn_signin(QString)),
                     &main_controler, SLOT(hdn_signin(QString)));
    QObject::connect(root, SIGNAL(sgn_signout(QString)),
                     &main_controler, SLOT(hdn_signout(QString)));
    QObject::connect(&main_controler, SIGNAL(sgn_recv_msg(QString)),
                     root, SIGNAL(sgn_recv_message(QString)));

    view.show();
    app.exec();
}
