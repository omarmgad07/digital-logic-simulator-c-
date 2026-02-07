#include "AddNOR32gate2.h"
#include "..\ApplicationManager.h"

AddNOR32gate2::AddNOR32gate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddNOR32gate2::~AddNOR32gate2(void)
{
}

void AddNOR32gate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("3-Input NOR3 Gate: Click to add the gate");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void AddNOR32gate2::Execute()
{
    ReadActionParameters();

    int Len = UI.NOR32_Width;
    int Wdth = UI.NOR32_Height;

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

    createdGate = new NOR32(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddNOR32gate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddNOR32gate2::Redo()
{
    if (!createdGate) return;

    NOR32* restored = new NOR32(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
