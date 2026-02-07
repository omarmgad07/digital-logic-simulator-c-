#include "AddSWITCH.h"
#include "..\ApplicationManager.h"

AddSWITCH::AddSWITCH(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddSWITCH::~AddSWITCH(void)
{
}

void AddSWITCH::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("SWITCH: Click to add the switch");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void AddSWITCH::Execute()
{
    ReadActionParameters();

    int Len = UI.SWITCH_Width;
    int Wdth = UI.SWITCH_Height;

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

    createdGate = new SWITCH(GInfoBackup, AND2_FANOUT);
    pManager->AddComponent(createdGate);
}

void AddSWITCH::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddSWITCH::Redo()
{
    if (!createdGate) return;

    SWITCH* restored = new SWITCH(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
