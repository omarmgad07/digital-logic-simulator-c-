#pragma once
#include "Action.h"

class ProbeCircuit : public Action
{
public:
    ProbeCircuit(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
