#pragma once
#include "Action.h"

class GenerateTruthTable : public Action
{
public:
    GenerateTruthTable(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

