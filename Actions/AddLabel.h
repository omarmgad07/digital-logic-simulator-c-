#ifndef ADDLABEL_H
#define ADDLABEL_H

#include "Action.h"
#include "../Components/Component.h"

class AddLabel : public Action
{
    Component* selected;

public:
    AddLabel(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo() {}
    virtual void Redo() {}
};

#endif
