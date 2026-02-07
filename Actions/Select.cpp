#include "Select.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Components/Component.h"

Select::Select(ApplicationManager* pApp)
    : Action(pApp)
{
}

void Select::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg(
        "Select Mode: Click component to select/deselect - click empty area to exit"
    );

    int x, y;

    while (true)
    {
        if (pIn->CheckMouseClick(x, y))
        {
            Component* c = pManager->GetComponentAt(x, y);

            if (c)
            {
                // 🔁 TOGGLE
                c->SetSelected(!c->IsSelected());
                pManager->UpdateInterface();
            }
            else
            {
                // Click on empty area → exit select mode
                break;
            }
        }
    }

    pOut->PrintMsg("Exited Select Mode");
}
