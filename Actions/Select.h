#pragma once
#include "Action.h"

class Select : public Action
{
public:
    Select(ApplicationManager* pApp);

    virtual void ReadActionParameters() {}
    virtual void Execute();

    virtual void Undo() {}
    virtual void Redo() {}
};
