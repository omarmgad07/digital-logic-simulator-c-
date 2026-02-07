#pragma once

#include "action.h"
#include "..\Components\NOT2.h"

class AddNOTgate2 : public Action
{
private:
    int Cx, Cy;                 
    GraphicsInfo GInfoBackup;   
    NOT2* createdGate;          

public:
    AddNOTgate2(ApplicationManager* pApp);
    virtual ~AddNOTgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
