#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include "IPCInterface/serverInterface.hpp"
#include <iostream>

using namespace ipc;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    std::unique_ptr<ServerInterface> server = ServerInterface::create("server");

    QObject::connect(server.get(), &ServerInterface::readyRead, &app, [&](const QString &uid) {
        IPCMessage msg = server->readMessage(uid);
        qDebug() << msg.data();
    }, Qt::AutoConnection);

    server->startServer();

    IPCMessage sampleJson(CommandMode::Info, "A message from server");
    QTimer::singleShot(5000, [&]()
                       {server->sendMessage("client",sampleJson);
    std::cout << "message was sent." << std::endl; });

    return app.exec();
}
