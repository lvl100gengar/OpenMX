#include "Connection.h"

#include "../protocol/EndPoint.h"

namespace OpenMX {

EndPoint Connection::endPoint()
{
    return EndPoint(remoteEndPoint.address().to_v4().to_uint(), remoteEndPoint.port());
}

} // namespace OpenMX