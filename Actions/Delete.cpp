#include "Delete.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Components/Component.h"

Delete::Delete(ApplicationManager* pApp)
    : Action(pApp)
{
}

void Delete::ReadActionParameters()
{
    SelectedList.clear();
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    for (int i = 0; i < pManager->GetCompCount(); i++)
    {
        Component* c = pManager->GetComponent(i);
        if (c->IsSelected())
            SelectedList.push_back(c);
    }

    if (SelectedList.empty())
    {
        pOut->PrintMsg("Click on a component to delete...");

        int x, y;
        pIn->GetPointClicked(x, y);

        Component* comp = pManager->GetComponentAt(x, y);
        if (comp)
            SelectedList.push_back(comp);
        else
            pOut->PrintMsg("No component found at that location.");
    }
}

void Delete::Execute()
{
    ReadActionParameters();

    if (SelectedList.empty())
        return;

    Output* pOut = pManager->GetOutput();

    for (Component* comp : SelectedList)
    {
        if (!comp) continue;

        pManager->BreakConnections(comp);

        pManager->DeleteComponent(comp);

        pOut->PrintMsg("Component deleted");
    }

    pManager->UpdateInterface();
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}
