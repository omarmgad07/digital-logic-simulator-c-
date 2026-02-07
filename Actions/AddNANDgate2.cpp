#include "AddNANDgate2.h"
#include "..\ApplicationManager.h"

AddNANDgate2::AddNANDgate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddNANDgate2::~AddNANDgate2(void)
{
}

void AddNANDgate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("2-Input NAND Gate: Click to add the gate");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void AddNANDgate2::Execute()
{
    ReadActionParameters();

    int Len = UI.NAND2_Width;
    int Wdth = UI.NAND2_Height;

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

    createdGate = new NAND2(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddNANDgate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddNANDgate2::Redo()
{
    if (!createdGate) return;

    NAND2* restored = new NAND2(GInfoBackup, AND2_FANOUT);

    createdGate = restored;

    pManager->AddComponent(restored);
}
