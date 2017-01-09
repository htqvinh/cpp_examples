#ifndef QCONTROLERMAIN_H
#define QCONTROLERMAIN_H

#include <QObject>
#include <QString>

class QControlerMain : public QObject
{
    Q_OBJECT
public:
    explicit QControlerMain(QObject *parent = 0);
    ~QControlerMain();

signals:

public slots:
    void hdn_send_message(QString message);
};

#endif // QCONTROLERMAIN_H
