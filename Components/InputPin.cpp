#include "InputPin.h"
#include "../Components/Connection.h"

void InputPin::setComponent(Component* pCmp)
{
    pComp = pCmp;
}

Component* InputPin::getComponent() const
{
    return pComp;
}

void InputPin::setConnection(Connection* c)
{
    pConn = c;
}

Connection* InputPin::getConnection() const
{
    return pConn;
}
