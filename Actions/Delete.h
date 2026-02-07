#ifndef _DELETE_H
#define _DELETE_H

#include "Action.h"
#include <vector>

class Component;

class Delete : public Action
{
private:
    std::vector<Component*> SelectedList;  

public:
    Delete(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
