#include "smtpmanager.h"


smtpmanager::smtpmanager(QObject *parent)
    : QObject{parent}
{}
bool smtpmanager::login(QString email, QString password) {
    if (!smtppointer) { // Check if the pointer is already initialized
        smtppointer = new SmtpClient("smtp.zoho.eu", 465, SmtpClient::SslConnection);
    }

    user = email;
    pass = password;
    smtppointer->connectToHost();
    if (!smtppointer->waitForReadyConnected()) {
        qDebug() << "Failed to connect to host!";
        return false;
    }

    smtppointer->login(user, pass);
    if (!smtppointer->waitForAuthenticated()) {
        qDebug() << "Failed to login!";
        return false;
    }

    return true;
}


bool smtpmanager::send(QString tomail,QString ccmail, QString subject, QString body, QList<QString> urls){

    MimeMessage message;

    EmailAddress sender(user, "Your Name");
    message.setSender(sender);

    // Handle "To" addresses
    QStringList tomails = tomail.split(" ");
    for (const QString &i : tomails) {
        QString trimmedAddress = i.trimmed(); // Trim spaces
        if (!trimmedAddress.isEmpty()) {
            EmailAddress to(trimmedAddress, "Recipient's Name");
            message.addRecipient(to);
        }
    }

    // Handle "Cc" addresses
    QStringList ccmails = ccmail.split(" ");
    for (const QString &i : ccmails) {
        QString trimmedAddress = i.trimmed(); // Trim spaces
        if (!trimmedAddress.isEmpty()) {
            EmailAddress cc(trimmedAddress, "Recipient's Name");
            message.addCc(cc);
        }
    }

    message.setSubject(subject);

    MimeText text;

    text.setText(body);

    message.addPart(&text);

    QFile* pointers[urls.count()];
    MimeAttachment* mfiles[urls.count()];
    for(int j=0;j<urls.count();j++){
        pointers[j] = new QFile(urls[j]);
        mfiles[j] = new MimeAttachment(pointers[j]);
        message.addPart(mfiles[j]);

    }
    /*for(int j=0;j<urls.count();j++){
    QFile file(urls[j]);
    MimeAttachment mfile(&file);
    message.addPart(&mfile);
    }*/


    smtppointer->sendMail(message);
    if (!smtppointer->waitForMailSent()) {
        qDebug() << "Failed to send mail!";
        return false;
    }

    smtppointer->quit();
    return true;

}
