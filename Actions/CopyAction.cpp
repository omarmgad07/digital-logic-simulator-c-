#include "CopyAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Components/Component.h"

CopyAction::CopyAction(ApplicationManager* pApp) : Action(pApp) {}

void CopyAction::ReadActionParameters() {}

void CopyAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

   
    pOut->PrintMsg("Select a component to COPY...");

    int x, y;
    pIn->GetPointClicked(x, y);

    Component* comp = pManager->GetComponentAt(x, y);

    
    if (!comp)
    {
        pOut->PrintMsg("No component selected!");
        return;
    }


    Component* copied = comp->Clone(comp->GetGraphicsInfo());
    pManager->SetClipboard(copied);

    pOut->PrintMsg("Component copied!");
}
