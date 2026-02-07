#include "AddNORgate2.h"
#include "..\ApplicationManager.h"

AddNORgate2::AddNORgate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("2-Input NOR Gate: Click to add the gate");

    pIn->GetPointClicked(Cx, Cy);

    pOut->ClearStatusBar();
}

void AddNORgate2::Execute()
{
    ReadActionParameters();

    int Len = UI.NOR2_Width;   
    int Wdth = UI.NOR2_Height;

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

    createdGate = new NOR2(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddNORgate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddNORgate2::Redo()
{
    if (!createdGate) return;

    NOR2* restored = new NOR2(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
