#pragma once

#include "action.h"
#include "..\Components\LED.h"

class AddLED : public Action
{
private:
    int Cx, Cy;
    GraphicsInfo GInfoBackup;  
    LED* createdGate;           

public:
    AddLED(ApplicationManager* pApp);
    virtual ~AddLED(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
