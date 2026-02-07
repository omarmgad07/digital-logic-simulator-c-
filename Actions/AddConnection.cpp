#include "AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"

AddConnection::AddConnection(ApplicationManager* pApp) : Action(pApp) {}

void AddConnection::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click the OUTPUT pin");
    pIn->GetPointClicked(x1, y1);

    pOut->PrintMsg("Click the INPUT pin");
    pIn->GetPointClicked(x2, y2);
}

void AddConnection::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();

    Component* SrcCmp = pManager->GetComponentAt(x1, y1);
    Component* DstCmp = pManager->GetComponentAt(x2, y2);

    if (!SrcCmp || !DstCmp)
        return;

    // =====================================================
    // SOURCE VALIDATION
    // =====================================================

    // ❌ LED cannot be source
    if (dynamic_cast<LED*>(SrcCmp))
    {
        pOut->PrintMsg("LED cannot be a source of connection.");
        return;
    }

    OutputPin* pSrcPin = nullptr;

    if (SWITCH* sw = dynamic_cast<SWITCH*>(SrcCmp))
        pSrcPin = sw->GetOutputPin();
    else if (Gate* gate = dynamic_cast<Gate*>(SrcCmp))
        pSrcPin = gate->GetOutputPin();

    if (!pSrcPin)
        return;

    // =====================================================
    // DESTINATION CAPACITY CHECK
    // =====================================================
    if (Gate* gate = dynamic_cast<Gate*>(DstCmp))
    {
        bool hasFreeInput = false;
        for (int i = 1; i <= gate->GetInputCount(); i++)
        {
            InputPin* pin = gate->GetInputPin(i);
            if (pin && pin->getConnection() == nullptr)
            {
                hasFreeInput = true;
                break;
            }
        }

        if (!hasFreeInput)
        {
            pOut->PrintMsg("This gate has no free input pins.");
            return;
        }
    }

    // =====================================================
    // DESTINATION PIN SELECTION (FIXED FOR 3-INPUT GATES)
    // =====================================================
    InputPin* pDstPin = nullptr;

    if (LED* led = dynamic_cast<LED*>(DstCmp))
    {
        pDstPin = led->GetInputPin(1);
    }
    else if (Gate* gate = dynamic_cast<Gate*>(DstCmp))
    {
        int count = gate->GetInputCount();
        GraphicsInfo GI = gate->GetGraphicsInfo();
        int pinH = (GI.y2 - GI.y1) / (count + 1);

        // 1️⃣ choose nearest pin by Y
        int bestIndex = 1;
        int bestDist = 1000000;

        for (int i = 1; i <= count; i++)
        {
            int pinY = GI.y1 + i * pinH;
            int dist = abs(y2 - pinY);
            if (dist < bestDist)
            {
                bestDist = dist;
                bestIndex = i;
            }
        }

        pDstPin = gate->GetInputPin(bestIndex);

        // 2️⃣ if chosen pin already connected → pick first free pin
        if (pDstPin && pDstPin->getConnection() != nullptr)
        {
            for (int i = 1; i <= count; i++)
            {
                InputPin* pin = gate->GetInputPin(i);
                if (pin && pin->getConnection() == nullptr)
                {
                    pDstPin = pin;
                    break;
                }
            }
        }
    }

    if (!pDstPin)
        return;

    // =====================================================
    // FINAL VALIDATION
    // =====================================================
    if (pDstPin->getConnection() != nullptr)
    {
        pOut->PrintMsg("This input pin is already connected.");
        return;
    }

    // =====================================================
    // CREATE CONNECTION
    // =====================================================
    GraphicsInfo G;
    G.x1 = x1;
    G.y1 = y1;
    G.x2 = x2;
    G.y2 = y2;

    Connection* pConn = new Connection(G, pSrcPin, pDstPin);

    pSrcPin->ConnectTo(pConn);
    pDstPin->setConnection(pConn);

    pManager->AddComponent(pConn);
}
