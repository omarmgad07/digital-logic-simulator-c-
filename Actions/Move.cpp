#include "Move.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Components/Connection.h"

Move::Move(ApplicationManager* pApp) : Action(pApp)
{
    Selected = nullptr;
    selectedCount = 0;
}

void Move::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    selectedCount = 0;

    int compCount = pManager->GetCompCount();
    for (int i = 0; i < compCount; i++)
    {
        Component* c = pManager->GetComponent(i);
        if (c->IsSelected())
        {
            // Ignore wires (they move with gates)
            if (dynamic_cast<Connection*>(c)) continue;

            if (selectedCount < MAX_COMPONENTS)
            {
                selectedList[selectedCount++] = c;
            }
        }
    }

    // 2. IF NOTHING SELECTED, ASK USER TO CLICK ONE
    if (selectedCount == 0)
    {
        pOut->PrintMsg("Move: Click on the component you want to move...");
        int x, y;
        pIn->GetPointClicked(x, y);

        Selected = pManager->GetComponentAt(x, y);

        if (Selected && !dynamic_cast<Connection*>(Selected))
        {
            selectedList[selectedCount++] = Selected;
            Selected->SetSelected(true);
        }
        else
        {
            pOut->PrintMsg("No valid component selected.");
            return;
        }
    }
    else
    {
        pOut->PrintMsg("Move: Click destination for selected components...");
    }

    // 3. STORE OLD POSITIONS
    for (int i = 0; i < selectedCount; i++)
    {
        oldPositions[i] = selectedList[i]->GetGraphicsInfo();
    }

    // 4. GET DESTINATION CLICK
    int nx, ny;
    pIn->GetPointClicked(nx, ny);

    

    GraphicsInfo firstOld = oldPositions[0];
    int w = firstOld.x2 - firstOld.x1;
    int h = firstOld.y2 - firstOld.y1;

    int centerX = firstOld.x1 + w / 2;
    int centerY = firstOld.y1 + h / 2;

    int rawDx = nx - centerX;
    int rawDy = ny - centerY;

   
    int dx = (rawDx / 10) * 10;
    int dy = (rawDy / 10) * 10;

    for (int i = 0; i < selectedCount; i++)
    {
        GraphicsInfo oldG = oldPositions[i];
        GraphicsInfo newG;

        newG.x1 = oldG.x1 + dx;
        newG.y1 = oldG.y1 + dy;
        newG.x2 = oldG.x2 + dx;
        newG.y2 = oldG.y2 + dy;

        // Boundary Check (Prevent moving off screen)
        if (newG.x1 < 0) {
            int diff = -newG.x1;
            newG.x1 += diff; newG.x2 += diff;
        }
        if (newG.y1 < UI.ToolBarHeight) {
            int diff = UI.ToolBarHeight - newG.y1;
            newG.y1 += diff; newG.y2 += diff;
        }

        newPositions[i] = newG;
    }

    pOut->ClearStatusBar();
}

void Move::Execute()
{
    if (selectedCount == 0) ReadActionParameters();
    if (selectedCount == 0) return;

    for (int i = 0; i < selectedCount; i++)
    {
        Component* c = selectedList[i];

        
        GraphicsInfo currentG = c->GetGraphicsInfo();
        GraphicsInfo targetG = newPositions[i];

        int dx = targetG.x1 - currentG.x1;
        int dy = targetG.y1 - currentG.y1;

        // 1. Move Component
        c->SetGraphicsInfo(targetG);
        c->SetSelected(false); // Deselect after move

        // 2. Move Wires (Relative Mode)
        Connection* conns[100];
        int connCount = 0;
        pManager->GetConnectionsOfComponent(c, conns, connCount);

        for (int j = 0; j < connCount; j++)
        {
            if (!conns[j]) continue;

            GraphicsInfo connGfx = conns[j]->GetGraphicsInfo();
            bool changed = false;

            // If wire starts at this moving component -> shift start point
            if (conns[j]->getSourcePin() && conns[j]->getSourcePin()->getComponent() == c) {
                connGfx.x1 += dx;
                connGfx.y1 += dy;
                changed = true;
            }

            // If wire ends at this moving component -> shift end point
            if (conns[j]->getDestPin() && conns[j]->getDestPin()->getComponent() == c) {
                connGfx.x2 += dx;
                connGfx.y2 += dy;
                changed = true;
            }

            if (changed) {
                conns[j]->SetGraphicsInfo(connGfx);
            }
        }
    }
    pManager->UpdateInterface();
}

void Move::Undo()
{
    for (int i = 0; i < selectedCount; i++)
    {
        Component* c = selectedList[i];
        GraphicsInfo currentG = c->GetGraphicsInfo();
        GraphicsInfo targetG = oldPositions[i];

        int dx = targetG.x1 - currentG.x1;
        int dy = targetG.y1 - currentG.y1;

        c->SetGraphicsInfo(targetG);

        // Move Wires Back
        Connection* conns[100];
        int connCount = 0;
        pManager->GetConnectionsOfComponent(c, conns, connCount);

        for (int j = 0; j < connCount; j++)
        {
            if (!conns[j]) continue;
            GraphicsInfo connGfx = conns[j]->GetGraphicsInfo();
            bool changed = false;

            if (conns[j]->getSourcePin() && conns[j]->getSourcePin()->getComponent() == c) {
                connGfx.x1 += dx; connGfx.y1 += dy; changed = true;
            }
            if (conns[j]->getDestPin() && conns[j]->getDestPin()->getComponent() == c) {
                connGfx.x2 += dx; connGfx.y2 += dy; changed = true;
            }
            if (changed) conns[j]->SetGraphicsInfo(connGfx);
        }
    }
    pManager->UpdateInterface();
}

void Move::Redo()
{
    for (int i = 0; i < selectedCount; i++)
    {
        Component* c = selectedList[i];
        GraphicsInfo currentG = c->GetGraphicsInfo();
        GraphicsInfo targetG = newPositions[i];

        int dx = targetG.x1 - currentG.x1;
        int dy = targetG.y1 - currentG.y1;

        c->SetGraphicsInfo(targetG);

        // Move Wires Forward
        Connection* conns[100];
        int connCount = 0;
        pManager->GetConnectionsOfComponent(c, conns, connCount);

        for (int j = 0; j < connCount; j++)
        {
            if (!conns[j]) continue;
            GraphicsInfo connGfx = conns[j]->GetGraphicsInfo();
            bool changed = false;

            if (conns[j]->getSourcePin() && conns[j]->getSourcePin()->getComponent() == c) {
                connGfx.x1 += dx; connGfx.y1 += dy; changed = true;
            }
            if (conns[j]->getDestPin() && conns[j]->getDestPin()->getComponent() == c) {
                connGfx.x2 += dx; connGfx.y2 += dy; changed = true;
            }
            if (changed) conns[j]->SetGraphicsInfo(connGfx);
        }
    }
    pManager->UpdateInterface();
}