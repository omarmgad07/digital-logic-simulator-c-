#include "AddXNORgate2.h"
#include "..\ApplicationManager.h"

AddXNORgate2::AddXNORgate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddXNORgate2::~AddXNORgate2(void)
{
}

void AddXNORgate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("2-Input XNOR Gate: Click to add the gate");

    pIn->GetPointClicked(Cx, Cy);

    pOut->ClearStatusBar();
}

void AddXNORgate2::Execute()
{
    ReadActionParameters();

    int Len = UI.AND2_Width;
    int Wdth = UI.AND2_Height;

    GInfoBackup.x1 = Cx - Len / 2;
    GInfoBackup.x2 = Cx + Len / 2;
    GInfoBackup.y1 = Cy - Wdth / 2;
    GInfoBackup.y2 = Cy + Wdth / 2;

    int TopLimit = UI.ToolBarHeight;


    int BottomLimit = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;

    if (GInfoBackup.y1 < TopLimit || GInfoBackup.y2 > BottomLimit)
    {
        pManager->GetOutput()->PrintMsg("Error: Pls place component inside drawing area");
        return; 
    }

    createdGate = new XNOR2(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddXNORgate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddXNORgate2::Redo()
{
    if (!createdGate) return;

    XNOR2* restored = new XNOR2(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
