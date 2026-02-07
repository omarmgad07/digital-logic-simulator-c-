#ifndef _ADD_AND_GATE_H
#define _ADD_AND_GATE_H

#include "Action.h"
#include "..\Components\AND2.h"

class AddANDgate2 : public Action
{
private:
    int Cx, Cy;                 
    GraphicsInfo GInfoBackup;   
    AND2* createdGate;          

public:
    AddANDgate2(ApplicationManager* pApp);
    virtual ~AddANDgate2();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
