#pragma once

#include "action.h"
#include "..\Components\NAND2.h"

class AddNANDgate2 : public Action
{
private:
    int Cx, Cy;
    GraphicsInfo GInfoBackup;   
    NAND2* createdGate;

public:
    AddNANDgate2(ApplicationManager* pApp);
    virtual ~AddNANDgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
