#include "ProbeCircuit.h"
#include "../ApplicationManager.h"
#include "../Components/Component.h"
#include "../Components/Connection.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

ProbeCircuit::ProbeCircuit(ApplicationManager* pApp)
    : Action(pApp)
{
}

void ProbeCircuit::ReadActionParameters()
{
}

void ProbeCircuit::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    
    if (pManager->GetCompCount() == 0)
    {
        pOut->PrintMsg("No circuit to probe!");
        return;
    }


    pOut->PrintMsg("Click a component to probe...");
    int x, y;
    pIn->GetPointClicked(x, y);

    Component* comp = pManager->GetComponentAt(x, y);

   
    if (!comp)
    {
        pOut->PrintMsg("No component here!");
        return;
    }

    
    Connection* wire = dynamic_cast<Connection*>(comp);
    if (wire)
    {
        int val = wire->GetOutPinStatus();
        pOut->PrintMsg("Wire signal = " + std::to_string(val));
        return;
    }

    int outVal = comp->GetOutPinStatus();
    if (outVal != -1)
    {
        pOut->PrintMsg("Output = " + std::to_string(outVal));
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        int inVal = comp->GetInputPinStatus(i);
        if (inVal != -1)
        {
            pOut->PrintMsg("Input " + std::to_string(i) + " = " + std::to_string(inVal));
            return;
        }
    }

    pOut->PrintMsg("Component detected but no logic value.");
}

void ProbeCircuit::Undo() {}
void ProbeCircuit::Redo() {}
