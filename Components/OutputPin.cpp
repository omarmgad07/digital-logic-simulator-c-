#include "OutputPin.h"
#include "Connection.h"

void OutputPin::RemoveConnection(int index)
{
    if (index < 0 || index >= m_Conn)
        return;

    // Shift left
    for (int i = index; i < m_Conn - 1; i++)
        m_Connections[i] = m_Connections[i + 1];

    m_Connections[m_Conn - 1] = nullptr;
    m_Conn--;
}

void OutputPin::ClearConnections()
{
    for (int i = 0; i < m_Conn; i++)
        m_Connections[i] = nullptr;

    m_Conn = 0;
}
