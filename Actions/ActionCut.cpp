#include "ActionCut.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

ActionCut::ActionCut(ApplicationManager* pApp) : Action(pApp) {}

ActionCut::~ActionCut(void) {}

void ActionCut::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click on a component to cut");

    int x, y;
    pIn->GetPointClicked(x, y);

    Component* pComp = pManager->GetComponentAt(x, y);

    if (!pComp)
    {
        pOut->PrintMsg("No component selected. Cut cancelled.");
        return;
    }

    pComp->SetSelected(true);

    
    GraphicsInfo oldGfx = pComp->GetGraphicsInfo();

    Component* cloned = pComp->Clone(oldGfx);

    pManager->SetClipboard(cloned);

    pManager->DeleteComponent(pComp);

    pOut->PrintMsg("Component cut successfully");
}



void ActionCut::ReadActionParameters()
{
}
void ActionCut::Undo() {}
void ActionCut::Redo() {}