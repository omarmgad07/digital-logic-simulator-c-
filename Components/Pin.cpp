#ifndef _PIN_H
#define _PIN_H

#include "../Defs.h"

class Pin
{
protected:
    STATUS m_Status;

public:
    Pin();
    virtual void setStatus(STATUS s);
    virtual STATUS getStatus() const;  
};

#endif
