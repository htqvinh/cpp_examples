
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

#include "Sender.h"
#include "QControlerMain.h"

/* Global variables start */
Sender sender_m;
/* Global variables end */

int main(int argc, char** argv){
    QGuiApplication app(argc, argv);

    sender_m.active();

    // Using QQuickView
    QQuickView view;
    view.setSource(QUrl::fromLocalFile("/data/proj/cpp_examples/QtClient/QViewMain.qml"));
    view.rootContext()->setContextProperty("QvTranslator", nullptr);

    QObject *root = (QObject*)view.rootObject();
    QControlerMain main_controler;
    QObject::connect(root, SIGNAL(sgn_send_message(QString)),
                         &main_controler, SLOT(hdn_send_message(QString)));

    view.show();
    app.exec();
}
