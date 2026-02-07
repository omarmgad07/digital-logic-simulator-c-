#include "SaveAction.h"
#include "../ApplicationManager.h"
#include "../Components/Component.h"
#include "../Components/Connection.h"
#include "../Components/OutputPin.h"
#include "../Components/InputPin.h"
#include "../Components/Gate.h"  
#include "../Components/LED.h"   
#include "../Components/SWITCH.h"
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

#include <fstream>
#include <string>

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp) {}

void SaveAction::ReadActionParameters() {}

void SaveAction::Execute()
{
    const std::string filename = "circuit_save.txt";
    std::ofstream out(filename);
    if (!out.is_open())
    {
        pManager->GetOutput()->PrintMsg("Error: cannot open file for saving.");
        return;
    }

    const int maxComps = 200;
    Component* nonConnections[maxComps];
    Connection* connections[maxComps];
    int nonConnCount = 0, connCount = 0;

    int totalComp = pManager->GetCompCount();

    for (int i = 0; i < totalComp; i++)
    {
        Component* c = pManager->GetComponent(i);
        if (nonConnCount >= maxComps || connCount >= maxComps) break;

        Connection* conn = dynamic_cast<Connection*>(c);
        if (conn)
            connections[connCount++] = conn;
        else
            nonConnections[nonConnCount++] = c;
    }

    int fileIds[maxComps];
    for (int i = 0; i < nonConnCount; i++)
        fileIds[i] = i + 1;

    out << nonConnCount << "\n";

    for (int i = 0; i < nonConnCount; i++)
    {
        Component* c = nonConnections[i];

        std::string shortType = "UNKNOWN";

        if (dynamic_cast<AND2*>(c)) shortType = "AND2";
        else if (dynamic_cast<OR2*>(c)) shortType = "OR2";
        else if (dynamic_cast<NAND2*>(c)) shortType = "NAND2";
        else if (dynamic_cast<NOR2*>(c)) shortType = "NOR2";
        else if (dynamic_cast<XOR2*>(c)) shortType = "XOR2";
        else if (dynamic_cast<XNOR2*>(c)) shortType = "XNOR2";
        else if (dynamic_cast<AND32*>(c)) shortType = "AND32";
        else if (dynamic_cast<NOR32*>(c)) shortType = "NOR32";
        else if (dynamic_cast<XOR32*>(c)) shortType = "XOR32";
        else if (dynamic_cast<NOT2*>(c)) shortType = "NOT2";
        else if (dynamic_cast<BUFF2*>(c)) shortType = "BUFF2";
        else if (dynamic_cast<SWITCH*>(c)) shortType = "SWITCH";
        else if (dynamic_cast<LED*>(c)) shortType = "LED";

        int compId = fileIds[i];
        std::string label = c->GetLabel();
        if (label.empty() || label.find(' ') != std::string::npos) label = "-";

        GraphicsInfo g = c->GetGraphicsInfo();
        out << shortType << " " << compId << " " << label << " "
            << g.x1 << " " << g.y1 << " " << g.x2 << " " << g.y2 << "\n";
    }

    out << "Connections\n";

    int connIndex = 1;
    for (int i = 0; i < connCount; i++)
    {
        Connection* conn = connections[i];
        OutputPin* src = conn->getSourcePin();
        InputPin* dst = conn->getDestPin();

        int srcId = -1, dstId = -1;
        Component* srcComp = (src) ? src->getComponent() : nullptr;
        Component* dstComp = (dst) ? dst->getComponent() : nullptr;

        if (srcComp && dstComp)
        {
            for (int j = 0; j < nonConnCount; j++)
            {
                if (nonConnections[j] == srcComp) srcId = fileIds[j];
                if (nonConnections[j] == dstComp) dstId = fileIds[j];
            }
        }

        int dstPinNo = -1;

        if (Gate* g = dynamic_cast<Gate*>(dstComp)) {
            for (int k = 0; k < 3; k++) {
                if (g->GetInputPin(k) == dst) {
                    dstPinNo = k + 1; 
                    break;
                }
            }
        }
        else if (LED* l = dynamic_cast<LED*>(dstComp)) {
            if (l->GetInputPin(0) == dst) dstPinNo = 1;
        }
        else if (SWITCH* s = dynamic_cast<SWITCH*>(dstComp)) {
            for (int k = 0; k < 3; k++) {
                if (s->GetInputPin(k) == dst) {
                    dstPinNo = k + 1;
                    break;
                }
            }
        }

        if (srcId != -1 && dstId != -1 && dstPinNo != -1)
        {
            GraphicsInfo g = conn->GetGraphicsInfo();
            out << connIndex << " " << srcId << " " << dstId << " "
                << dstPinNo << " "
                << g.x1 << " " << g.y1 << " " << g.x2 << " " << g.y2 << "\n";

            connIndex++;
        }
    }

    out << "-1\n";
    out.close();
    pManager->GetOutput()->PrintMsg("Circuit saved to '" + filename + "'.");
}