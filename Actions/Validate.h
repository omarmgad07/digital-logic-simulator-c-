#pragma once
#include "Action.h"

class Validate : public Action
{
public:
    Validate(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    void Undo() override {

    }

    void Redo() override {

    }
};
