#ifndef _ADD_AND32_GATE_H
#define _ADD_AND32_GATE_H

#include "action.h"
#include "..\Components\AND32.h"

class AddAND32gate2 : public Action
{
private:
    int Cx, Cy;               
    GraphicsInfo GInfoBackup;  
    AND32* createdGate;        

public:
    AddAND32gate2(ApplicationManager* pApp);
    virtual ~AddAND32gate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
