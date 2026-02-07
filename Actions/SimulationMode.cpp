#include "SimulationMode.h"
#include "Validate.h"
#include "ProbeCircuit.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Actions/GenerateTruthTable.h"

// [IMPORTANT] Includes for Component Checks
#include "../Components/Connection.h"
#include "../Components/Gate.h"
#include "../Components/LED.h" 
#include "../Components/SWITCH.h"     
#include "../Components/OutputPin.h" 

SimulationMode::SimulationMode(ApplicationManager* pApp)
    : Action(pApp)
{
}

void SimulationMode::ReadActionParameters()
{
}

void SimulationMode::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // ============================================================
    // 1. VALIDATION CHECK (Before switching modes)
    // ============================================================

    if (pManager->GetCompCount() == 0)
    {
        pOut->PrintMsg("Circuit is empty! Cannot switch to simulation.");
        return;
    }

    for (int i = 0; i < pManager->GetCompCount(); i++)
    {
        Component* comp = pManager->GetComponent(i);

        // CHECK 1: SWITCH (Must be first)
        SWITCH* pSwitch = dynamic_cast<SWITCH*>(comp);
        if (pSwitch)
        {
            if (pSwitch->GetOutputPin()->getNumConnections() == 0)
            {
                pOut->PrintMsg("Invalid: SWITCH found with unconnected OUTPUT.");
                return;
            }
            continue;
        }

        // CHECK 2: LED (Must be before Gate)
        LED* pLED = dynamic_cast<LED*>(comp);
        if (pLED)
        {
            InputPin* pin = pLED->GetInputPin(0);
            if (pin && !pin->getConnection())
            {
                pOut->PrintMsg("Invalid: LED found with unconnected INPUT.");
                return;
            }
            continue;
        }

        // CHECK 3: GATE (Generic)
        Gate* pGate = dynamic_cast<Gate*>(comp);
        if (pGate)
        {
            // A. Check Inputs
            for (int j = 0; j < pGate->GetInputCount(); j++)
            {
                InputPin* pin = pGate->GetInputPin(j);
                if (pin && !pin->getConnection())
                {
                    pOut->PrintMsg("Invalid: GATE found with unconnected INPUT.");
                    return;
                }
            }

            // B. Check Output
            if (pGate->GetOutputPin()->getNumConnections() == 0)
            {
                pOut->PrintMsg("Invalid: GATE found with unconnected OUTPUT.");
                return;
            }
            continue;
        }
    }

    // ============================================================
    // 2. SWITCH TO SIMULATION MODE
    // ============================================================

    UI.AppMode = SIMULATION;
    pOut->PrintMsg("Switched to Simulation Mode. Click switches to toggle.");
    pOut->ClearToolBar();
    pOut->CreateSimulationToolBar();
    pOut->ClearBottomToolBar();

    // Force an initial update to ensure initial states are drawn correctly
    pManager->UpdateInterface();

    // ============================================================
    // 3. SIMULATION LOOP
    // ============================================================

    while (UI.AppMode == SIMULATION)
    {
        int x, y;
        pIn->GetPointClicked(x, y);

        // --------------------------------------------------------
        // A. Handle Toolbar Clicks
        // --------------------------------------------------------
        if (y >= 0 && y < UI.ToolBarHeight)
        {
            int item = x / UI.ToolItemWidth;

            switch (item)
            {
            case ITM_BACK:
                UI.AppMode = DESIGN;
                pOut->ClearToolBar();
                pOut->CreateDesignToolBar();
                pOut->CreateBottomToolBar();
                pOut->PrintMsg("Back to Design Mode.");
                return; // Exit the loop and function

            case ITM_VALIDATE:
            {
                Validate v(pManager);
                v.Execute();
                break;
            }

            case ITM_PROBE:
            {
                ProbeCircuit pr(pManager);
                pr.Execute();
                break;
            }

            case ITM_TRUTH:
            {
                GenerateTruthTable tt(pManager);
                tt.Execute();
                break;
            }

            case ITM_EXIT2:
                exit(0);
                break;
            }

            continue; // Wait for next click
        }

        // --------------------------------------------------------
        // B. Handle Switch Toggling & Signal Propagation
        // --------------------------------------------------------
        Component* comp = pManager->GetComponentAt(x, y);

        // If user clicked on a SWITCH
        SWITCH* sw = dynamic_cast<SWITCH*>(comp);
        if (sw)
        {
            // 1. Toggle the switch state
            sw->Toggle();

            // 2. Propagate the signal through the circuit
            // We loop multiple times to let signals travel (Switch -> Gate -> Gate -> LED)
            int count = pManager->GetCompCount();

            for (int k = 0; k < 3; k++) // 3 Passes for propagation depth
            {
                // Pass 1: Connections (Move Output -> Input)
                for (int i = 0; i < count; i++)
                {
                    Component* c = pManager->GetComponent(i);
                    if (dynamic_cast<Connection*>(c))
                        c->Operate();
                }

                // Pass 2: Gates/LEDs (Calculate Input -> Output)
                for (int i = 0; i < count; i++)
                {
                    Component* c = pManager->GetComponent(i);
                    if (!dynamic_cast<Connection*>(c))
                        c->Operate();
                }
            }

            // 3. Redraw the circuit with new states (Green/Red lines)
            pManager->UpdateInterface();
        }
    }
}