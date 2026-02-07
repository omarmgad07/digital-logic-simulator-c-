#include "AddBUFFgate2.h"
#include "..\ApplicationManager.h"

AddBUFFgate2::AddBUFFgate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddBUFFgate2::~AddBUFFgate2(void)
{
}

void AddBUFFgate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("BUFFER Gate: Click to add the gate");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void AddBUFFgate2::Execute()
{
    ReadActionParameters();

    int Len = UI.BUFF2_Width;
    int Wdth = UI.BUFF2_Height;

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

    createdGate = new BUFF2(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddBUFFgate2::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddBUFFgate2::Redo()
{
    if (!createdGate) return;

    BUFF2* restored = new BUFF2(GInfoBackup, AND2_FANOUT);

    createdGate = restored;
    pManager->AddComponent(restored);
}
