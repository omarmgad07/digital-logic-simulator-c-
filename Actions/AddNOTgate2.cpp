#include "AddNOTgate2.h"
#include "..\ApplicationManager.h"

AddNOTgate2::AddNOTgate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddNOTgate2::~AddNOTgate2(void)
{
}

void AddNOTgate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("NOT Gate: Click to add the gate");

    pIn->GetPointClicked(Cx, Cy);

    pOut->ClearStatusBar();
}

void AddNOTgate2::Execute()
{
    ReadActionParameters();

    int Len = UI.NOT2_Width;
    int Wdth = UI.NOT2_Height;

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

    createdGate = new NOT2(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddNOTgate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddNOTgate2::Redo()
{
    if (!createdGate) return;

    NOT2* restored = new NOT2(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
