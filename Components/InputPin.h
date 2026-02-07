#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"

class Component;
class Connection;

class InputPin : public Pin
{
private:
    Component* pComp;
    Connection* pConn;

public:
    InputPin() : pComp(nullptr), pConn(nullptr) {}

    void setComponent(Component* pCmp);
    Component* getComponent() const;

    void setConnection(Connection* c);
    Connection* getConnection() const;
};

#endif
