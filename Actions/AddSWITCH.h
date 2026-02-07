#pragma once

#include "action.h"
#include "..\Components\SWITCH.h"

class AddSWITCH : public Action
{
private:
    int Cx, Cy;                 
    GraphicsInfo GInfoBackup;   
    SWITCH* createdGate;        

public:
    AddSWITCH(ApplicationManager* pApp);
    virtual ~AddSWITCH(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
