#pragma once

#include "action.h"
#include "..\Components\BUFF2.h"

class AddBUFFgate2 : public Action
{
private:
    int Cx, Cy;
    GraphicsInfo GInfoBackup;
    BUFF2* createdGate;

public:
    AddBUFFgate2(ApplicationManager* pApp);
    virtual ~AddBUFFgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
