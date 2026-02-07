#pragma once
#include "action.h"
#include "..\Components\NOR2.h"

class AddNORgate2 : public Action
{
private:
    int Cx, Cy;                
    GraphicsInfo GInfoBackup;   
    NOR2* createdGate;          

public:
    AddNORgate2(ApplicationManager* pApp);
    virtual ~AddNORgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
