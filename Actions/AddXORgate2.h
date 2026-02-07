#pragma once

#include "action.h"
#include "..\Components\XOR2.h"

class AddXORgate2 : public Action
{
private:
    int Cx, Cy;
    GraphicsInfo GInfoBackup;   
    XOR2* createdGate;          

public:
    AddXORgate2(ApplicationManager* pApp);
    virtual ~AddXORgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
