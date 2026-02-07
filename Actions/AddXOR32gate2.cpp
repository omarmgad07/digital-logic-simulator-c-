#include "AddXOR32gate2.h"
#include "..\ApplicationManager.h"

AddXOR32gate2::AddXOR32gate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddXOR32gate2::~AddXOR32gate2(void)
{
}

void AddXOR32gate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("3-Input XOR3 Gate: Click to add the gate");

    pIn->GetPointClicked(Cx, Cy);

    pOut->ClearStatusBar();
}

void AddXOR32gate2::Execute()
{
    ReadActionParameters();

    int Len = UI.XOR32_Width;
    int Wdth = UI.XOR32_Height;

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

    createdGate = new XOR32(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddXOR32gate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddXOR32gate2::Redo()
{
    if (!createdGate)
        return;

    XOR32* restored = new XOR32(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
