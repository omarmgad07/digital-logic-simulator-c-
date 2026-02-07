#ifndef _PIN_H
#define _PIN_H

#include "../Defs.h"

class Pin
{
protected:
    STATUS m_Status;

public:
    Pin() { m_Status = LOW; }

    virtual void setStatus(STATUS s) { m_Status = s; }
    virtual STATUS getStatus() const { return m_Status; }
};

#endif
