#include "PasteAction.h"
#include "../ApplicationManager.h"
#include "../Components/Component.h"

PasteAction::PasteAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

void PasteAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    Component* clip = pManager->GetClipboard();

    if (!clip)
    {
        pOut->PrintMsg("Clipboard empty!");
        return;
    }

    int x, y;
    pIn->GetPointClicked(x, y);

    GraphicsInfo newGfx;
    newGfx.x1 = x - 50;
    newGfx.y1 = y - 50;
    newGfx.x2 = x + 50;
    newGfx.y2 = y + 50;

    Component* pasted = clip->Clone(newGfx);

    if (!pasted)
    {
        pOut->PrintMsg("Cannot paste this component");
        return;
    }

    pManager->AddComponent(pasted);
    pOut->PrintMsg("Pasted!");
}


void PasteAction::ReadActionParameters() {}
