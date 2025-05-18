#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <clientInterface.hpp>
#include <serverInterface.hpp>
#include "ipcMessage.hpp"
#include <tuple>

using namespace ipc;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ClientInterface *client1 = ClientInterface::create("client1");
    ClientInterface *client2 = ClientInterface::create("client2");
    ServerInterface *server = ServerInterface::create("server");

    QObject::connect(server,&ServerInterface::readyRead,&app,[&](){
        std::optional<std::tuple<QString,IPCMessage>> opt = server->readMessage();
        if (!opt.has_value())
            return;

        std::tuple<QString,IPCMessage> clientMSG = *opt;
        qDebug() << "client is" << std::get<0>(clientMSG)
                 << "message is" << (std::get<1>(clientMSG)).data();
    },Qt::AutoConnection);

    server->startServer();
    client1->connectToServer("server");
    client2->connectToServer("server");

    IPCMessage client1Message{CommandMode::Info,"hello from client 1"};
    client1->sendMessage(client1Message);

    IPCMessage client2Message{CommandMode::Info,"hello from client 2"};
    client2->sendMessage(client2Message);

    return app.exec();
}
