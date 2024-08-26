#ifndef SMTPMANAGER_H
#define SMTPMANAGER_H

#include <QObject>
#include <SmtpMime>
#include <QUrl>
#include <QFile>
class smtpmanager : public QObject
{
    Q_OBJECT
public:
    explicit smtpmanager(QObject *parent = nullptr);
    Q_INVOKABLE bool login(QString email, QString password);
    Q_INVOKABLE bool send(QString tomail, QString ccmail, QString subject, QString body, QList<QString> urls);
signals:
private:
    SmtpClient* smtppointer;
    QString user;
    QString pass;
};

#endif // SMTPMANAGER_H
