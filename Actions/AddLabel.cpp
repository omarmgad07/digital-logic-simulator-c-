#include "AddLabel.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Components/Connection.h"
#include "AddConnection.h"
#include "Delete.h"

AddLabel::AddLabel(ApplicationManager* pApp)
    : Action(pApp), selected(nullptr)
{
}

void AddLabel::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click a component or connection to edit...");

    int x, y;
    pIn->GetPointClicked(x, y);
    selected = pManager->GetComponentAt(x, y);

    if (!selected)
        pOut->PrintMsg("Nothing selected");
    else
        pOut->ClearStatusBar();
}

void AddLabel::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    
    Component* pTopMostComp = nullptr; 
    int selectedCount = 0;
    int count = pManager->GetCompCount();

    // Loop through all components to find
   
    for (int i = 0; i < count; i++)
    {
        Component* pComp = pManager->GetComponent(i);

        if (pComp->IsSelected())
        {
            selectedCount++;

            
            if (pTopMostComp == nullptr)
            {
                pTopMostComp = pComp;
            }
            else
            {
                if (pComp->GetGraphicsInfo().y1 < pTopMostComp->GetGraphicsInfo().y1)
                {
                    pTopMostComp = pComp;
                }
            }
        }
    }

    
    if (selectedCount > 0 && pTopMostComp != nullptr)
    {
        pOut->PrintMsg("Enter 1 label for the selected group:");
        string circuitLabel = pIn->GetString(pOut);

        
        pTopMostComp->SetLabel(circuitLabel);

        pOut->ClearStatusBar();
        pManager->UpdateInterface();
        return; // EXIT HERE so we don't start the single-click mode
    }

    

    ReadActionParameters();
    if (!selected)
        return;

    // Handle Connection special case
    if (Connection* conn = dynamic_cast<Connection*>(selected))
    {
        pOut->PrintMsg("1: Edit label   |   2: Edit source/destination");
        string choice = pIn->GetString(pOut);

        if (choice == "1")
        {
            pOut->PrintMsg("Enter new connection label:");
            string lbl = pIn->GetString(pOut);
            conn->SetLabel(lbl);
        }
        else if (choice == "2")
        {
            conn->SetSelected(true);

            Action* delAct = new Delete(pManager);
            delAct->Execute();
            delete delAct;

            pOut->PrintMsg("Create new connection");
            Action* addAct = new AddConnection(pManager);
            addAct->Execute();
            delete addAct;
        }
    }
    // Handle Standard Component
    else
    {
        string oldLabel = selected->GetLabel();

        if (oldLabel.empty())
            pOut->PrintMsg("Enter new label:");
        else
            pOut->PrintMsg("Current label: " + oldLabel + " | Enter new label:");

        string newLabel = pIn->GetString(pOut);
        selected->SetLabel(newLabel);
    }

    pOut->ClearStatusBar();
    pManager->UpdateInterface();
}