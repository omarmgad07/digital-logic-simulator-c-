#pragma once
#ifndef ACTIONCUT_H
#define ACTIONCUT_H
#pragma once
#include "Action.h"

class ActionCut : public Action
{
public:
    ActionCut(ApplicationManager* pApp);
    virtual ~ActionCut();
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};
#endif
