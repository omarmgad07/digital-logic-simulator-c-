#pragma once

#include "action.h"
#include "..\Components\OR2.h"

class AddORgate2 : public Action
{
private:
    int Cx, Cy;                 
    GraphicsInfo GInfoBackup;   
    OR2* createdGate;           

public:
    AddORgate2(ApplicationManager* pApp);
    virtual ~AddORgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
