#include "Validate.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../Components/Gate.h"


#include "../Components/SWITCH.h" 
#include "../Components/LED.h"    
#include "../Components/OutputPin.h" 

Validate::Validate(ApplicationManager* pApp) : Action(pApp)
{
}

void Validate::ReadActionParameters()
{
}

void Validate::Execute()
{
    Output* pOut = pManager->GetOutput();

    if (pManager->GetCompCount() == 0)
    {
        pOut->PrintMsg("No circuit to validate!");
        return;
    }

    // Loop through ALL components
    for (int i = 0; i < pManager->GetCompCount(); i++)
    {
        Component* pComp = pManager->GetComponent(i);

        
        // CHECK 1: SWITCH 
        // (Must be checked FIRST because it inherits from Gate)
        SWITCH* pSwitch = dynamic_cast<SWITCH*>(pComp);
        if (pSwitch)
        {
            // Use the getter we added to OutputPin.h
            if (pSwitch->GetOutputPin()->getNumConnections() == 0)
            {
                pOut->PrintMsg("Invalid: Found a SWITCH with unconnected OUTPUT.");
                return;
            }
            continue; // Move to next component
        }

        // CHECK 2: LED 
        // (MOVED UP: Must be checked BEFORE Gate)
        LED* pLED = dynamic_cast<LED*>(pComp);
        if (pLED)
        {
           
            InputPin* pInPin = pLED->GetInputPin(0);

            if (pInPin && !pInPin->getConnection())
            {
                pOut->PrintMsg("Invalid: Found an LED with unconnected INPUT.");
                return;
            }
            continue; // Move to next component
        }

        // CHECK 3: GATE (AND, OR, NOT, etc.)
        // (Only runs if it was NOT a Switch and NOT an LED)
        Gate* pGate = dynamic_cast<Gate*>(pComp);
        if (pGate)
        {
            // 1. Check INPUTS
            for (int j = 0; j < pGate->GetInputCount(); j++)
            {
                InputPin* pInPin = pGate->GetInputPin(j);

                // If pin pointer exists but connection is NULL
                if (pInPin && !pInPin->getConnection())
                {
                    pOut->PrintMsg("Invalid: Found a GATE with an unconnected INPUT.");
                    return;
                }
            }

            // 2. Check OUTPUT
            if (pGate->GetOutputPin()->getNumConnections() == 0)
            {
                pOut->PrintMsg("Invalid: Found a GATE with unconnected OUTPUT.");
                return;
            }

            continue;
        }
    }

    // If we finished the loop, the circuit is valid
    pOut->PrintMsg("Circuit is VALID!");
}