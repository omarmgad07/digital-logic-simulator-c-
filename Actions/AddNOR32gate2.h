#pragma once
#ifndef _ADD_NOR32_GATE_H
#define _ADD_NOR32_GATE_H

#include "action.h"
#include "..\Components\NOR32.h"

class AddNOR32gate2 : public Action
{
private:
    int Cx, Cy;
    GraphicsInfo GInfoBackup;
    NOR32* createdGate;

public:
    AddNOR32gate2(ApplicationManager* pApp);
    virtual ~AddNOR32gate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
