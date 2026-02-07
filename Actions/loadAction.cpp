#include "LoadAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"

#include "../Components/AND2.h"
#include "../Components/OR2.h"
#include "../Components/NAND2.h"
#include "../Components/XOR2.h"
#include "../Components/NOR2.h"
#include "../Components/XNOR2.h"
#include "../Components/AND32.h"
#include "../Components/NOR32.h"
#include "../Components/XOR32.h"
#include "../Components/NOT2.h"
#include "../Components/BUFF2.h"
#include "../Components/SWITCH.h"
#include "../Components/LED.h"
#include "../Components/Connection.h"
#include "../Components/Gate.h"

#include <fstream>
#include <iostream>
#include <sstream> 

LoadAction::LoadAction(ApplicationManager* pApp) : Action(pApp) {}

void LoadAction::ReadActionParameters() {}

void LoadAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    std::ifstream file("circuit_save.txt");

    if (!file.is_open())
    {
        pOut->PrintMsg("Error: Cannot open circuit_save.txt");
        return;
    }

    pOut->PrintMsg("Loading circuit...");
    pOut->ClearDrawingArea();

    // 1. CLEAR EXISTING SYSTEM
    int existingCount = pManager->GetCompCount();
    for (int i = 0; i < existingCount; i++) {
        Component* pComp = pManager->GetComponent(0);
        pManager->DeleteComponent(pComp);
    }

    std::string line;
    int compCount = 0;

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> compCount;
    }
    else {
        return;
    }

   
    struct LoadedItem {
        int fileID;
        Component* compPtr;
    };

    // Allocate array based on the count read from file
    LoadedItem* idList = new LoadedItem[compCount];
    int loadedItemsCount = 0;

    const int UI_COMP_WIDTH = 50;
    const int UI_COMP_HEIGHT = 50;

    // 2. LOAD COMPONENTS
    for (int i = 0; i < compCount; i++)
    {
        if (!std::getline(file, line) || line.empty()) break;

        std::stringstream ss(line);
        std::string type, label;
        int fileID, x, y;

        ss >> type >> fileID >> label >> x >> y;

        if (ss.fail()) continue;

        GraphicsInfo gfx;
        gfx.x1 = x; gfx.y1 = y;
        gfx.x2 = x + UI_COMP_WIDTH; gfx.y2 = y + UI_COMP_HEIGHT;

        Component* comp = nullptr;

        if (type == "AND2") comp = new AND2(gfx, 2);
        else if (type == "OR2") comp = new OR2(gfx, 2);
        else if (type == "NAND2") comp = new NAND2(gfx, 2);
        else if (type == "XOR2") comp = new XOR2(gfx, 2);
        else if (type == "NOR2") comp = new NOR2(gfx, 2);
        else if (type == "XNOR2") comp = new XNOR2(gfx, 2);
        else if (type == "AND32") comp = new AND32(gfx, 3);
        else if (type == "NOR32") comp = new NOR32(gfx, 3);
        else if (type == "XOR32") comp = new XOR32(gfx, 3);
        else if (type == "NOT2") comp = new NOT2(gfx, 1);
        else if (type == "BUFF2") comp = new BUFF2(gfx, 1);
        else if (type == "SWITCH") comp = new SWITCH(gfx, 1);
        else if (type == "LED") comp = new LED(gfx);

        if (comp)
        {
            if (label != "-" && label != "") comp->SetLabel(label);
            comp->SetSelected(false);
            pManager->AddComponent(comp);

            idList[loadedItemsCount].fileID = fileID;
            idList[loadedItemsCount].compPtr = comp;
            loadedItemsCount++;
        }
    }

    // Skip to Connections
    while (std::getline(file, line)) {
        if (line.find("Connections") != std::string::npos) break;
    }

    // 3. LOAD CONNECTIONS
    while (std::getline(file, line))
    {
        if (line.empty() || line.find("-1") != std::string::npos) break;

        std::stringstream ss(line);
        int index, srcID, dstID, dstPinNo;
        int x1, y1, x2, y2;

        ss >> index >> srcID >> dstID >> dstPinNo >> x1 >> y1 >> x2 >> y2;
        if (ss.fail()) continue;

        Component* srcComp = nullptr;
        Component* dstComp = nullptr;

        
        for (int k = 0; k < loadedItemsCount; k++)
        {
            if (idList[k].fileID == srcID) srcComp = idList[k].compPtr;
            if (idList[k].fileID == dstID) dstComp = idList[k].compPtr;
        }

        if (!srcComp || !dstComp) continue;

        OutputPin* outPin = nullptr;
        InputPin* inPin = nullptr;

        if (Gate* g = dynamic_cast<Gate*>(srcComp)) outPin = g->GetOutputPin();
        else if (SWITCH* sw = dynamic_cast<SWITCH*>(srcComp)) outPin = sw->GetOutputPin();

        int pinIndex = dstPinNo - 1;
        if (Gate* g = dynamic_cast<Gate*>(dstComp)) inPin = g->GetInputPin(pinIndex);
        else if (LED* l = dynamic_cast<LED*>(dstComp)) inPin = l->GetInputPin(pinIndex);
        else if (SWITCH* sw = dynamic_cast<SWITCH*>(dstComp)) inPin = sw->GetInputPin(pinIndex);

        if (outPin && inPin)
        {
            GraphicsInfo connGfx;
            connGfx.x1 = x1; connGfx.y1 = y1;
            connGfx.x2 = x2; connGfx.y2 = y2;

            Connection* conn = new Connection(connGfx, outPin, inPin);

            // Link pointers so Move/Delete works
            outPin->ConnectTo(conn);
            inPin->setConnection(conn);
            conn->setSourcePin(outPin);
            conn->setDestPin(inPin);

            conn->SetSelected(false);
            pManager->AddComponent(conn);
        }
    }

    // Cleanup temporary array
    delete[] idList;

    pManager->UpdateInterface();
    pOut->PrintMsg("Circuit loaded successfully!");
}