#include "clientInterface.hpp"

namespace ipc
{

ClientInterface::ClientInterface(const QString &UID)
        : IpcEndpoint{UID}
    {}

ClientInterface::~ClientInterface() = default;

}
