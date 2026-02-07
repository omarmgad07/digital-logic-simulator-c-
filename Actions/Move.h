#pragma once
#include "Action.h"
#include "../Components/Component.h"

#define MAX_COMPONENTS 100  

class Move : public Action
{
private:
    Component* Selected;               
    GraphicsInfo OldGfx;               
    GraphicsInfo NewGfx;               

    
    Component* selectedList[MAX_COMPONENTS];
    int selectedCount;                 

    
    GraphicsInfo oldPositions[MAX_COMPONENTS];
    GraphicsInfo newPositions[MAX_COMPONENTS];

    void MoveConnections(Component* comp); 

public:
    Move(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
