#include "serverInterface.hpp"

namespace ipc
{

ServerInterface::ServerInterface(const QString &UID)
        : IpcEndpoint{UID}
    {}

}
