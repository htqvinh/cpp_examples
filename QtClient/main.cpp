
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

#include "Sender.h"

/* Global variables start */
Sender sender;
/* Global variables end */

int main(int argc, char** argv){
    QGuiApplication app(argc, argv);

    // Using QQuickView
    QQuickView view;
    view.setSource(QUrl::fromLocalFile("../QtClient/QViewMain.qml"));
    view.rootContext()->setContextProperty("QvTranslator", nullptr);
    view.show();

    app.exec();
}
