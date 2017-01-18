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
    void sgn_recv_msg(QString message);

public slots:
    void hdn_send_message(QString message);
    void hdn_signin(QString usrname);
    void hdn_signout(QString usrname);
};

#endif // QCONTROLERMAIN_H
