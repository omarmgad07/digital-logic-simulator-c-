#include "AddORgate2.h"
#include "..\ApplicationManager.h"

AddORgate2::AddORgate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddORgate2::~AddORgate2(void)
{
}

void AddORgate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("OR Gate: Click to add the gate");

    pIn->GetPointClicked(Cx, Cy);

    pOut->ClearStatusBar();
}

void AddORgate2::Execute()
{
    ReadActionParameters();

    int Len = UI.OR2_Width;
    int Wdth = UI.OR2_Height;

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

    createdGate = new OR2(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddORgate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddORgate2::Redo()
{
    if (!createdGate) return;

    OR2* restored = new OR2(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
