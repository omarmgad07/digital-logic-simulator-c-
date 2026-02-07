#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

#include "Pin.h"

class Connection;
class Component;

class OutputPin : public Pin
{
private:
    Connection* m_Connections[MAX_CONNS];
    int m_FanOut;
    int m_Conn;
    Component* pComp;

public:
    // Constructor
    OutputPin(int r_FanOut)
        : m_FanOut(r_FanOut), m_Conn(0), pComp(nullptr)
    {
        for (int i = 0; i < MAX_CONNS; i++)
            m_Connections[i] = nullptr;
    }

    void setComponent(Component* c)
    {
        pComp = c;
    }

    Component* getComponent() const
    {
        return pComp;
    }

    bool ConnectTo(Connection* r_Conn)
    {
        if (m_Conn < m_FanOut)
        {
            m_Connections[m_Conn++] = r_Conn;
            return true;
        }
        return false;
    }

    // Returns the number of connections
    int GetConnectionCount() const { return m_Conn; }

    // Returns a specific connection pointer
    Connection* GetConnection(int i) { return m_Connections[i]; }

    // Methods implemented in OutputPin.cpp
    void RemoveConnection(int index);
    void ClearConnections();

    // -------------------------------------------------------------
    // Helper function for Validation compatibility
    // -------------------------------------------------------------
    int getNumConnections() const { return m_Conn; }
};

#endif