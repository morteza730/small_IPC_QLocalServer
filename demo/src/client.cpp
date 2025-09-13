#include <QCoreApplication>
#include <QObject>

#include "IPCInterface/clientInterface.hpp"

using namespace ipc;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    std::unique_ptr<ClientInterface> client = ClientInterface::create("client");

    QObject::connect(client.get(),&ClientInterface::readyRead,&app,[&](){
        IPCMessage msg = client->readMessage();
        qDebug() << msg.data();
    },Qt::AutoConnection);

    client->connectToServer("server");

    IPCMessage clientMessage{CommandMode::Info,"hello from client"};
    client->sendMessage(clientMessage);

    return app.exec();
}
