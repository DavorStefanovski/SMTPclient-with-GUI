#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <smtpmanager.h>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qDebug() << QSslSocket::supportsSsl();
    smtpmanager Manager;
    engine.rootContext()->setContextProperty("Manager", &Manager);

    const QUrl url(QStringLiteral("qrc:/aplikacija/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
