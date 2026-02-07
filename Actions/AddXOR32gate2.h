#pragma once
#ifndef _ADD_XOR32_GATE_H
#define _ADD_XOR32_GATE_H

#include "action.h"
#include "..\Components\XOR32.h"

class AddXOR32gate2 : public Action
{
private:
    int Cx, Cy;                 
    GraphicsInfo GInfoBackup;   
    XOR32* createdGate;         

public:
    AddXOR32gate2(ApplicationManager* pApp);
    virtual ~AddXOR32gate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
