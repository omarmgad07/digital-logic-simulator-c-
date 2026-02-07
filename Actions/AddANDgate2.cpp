#include "AddANDgate2.h"
#include "..\ApplicationManager.h"

AddANDgate2::AddANDgate2(ApplicationManager* pApp)
    : Action(pApp)
{
    createdGate = nullptr;
}

AddANDgate2::~AddANDgate2()
{
}

void AddANDgate2::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("2-Input AND Gate: Click to add the gate");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void AddANDgate2::Execute()
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

    createdGate = new AND2(GInfoBackup, AND2_FANOUT);

    pManager->AddComponent(createdGate);
}

void AddANDgate2::Undo()
{
    if (createdGate)
    {
        pManager->DeleteComponent(createdGate); 
    }
}

void AddANDgate2::Redo()
{
    if (!createdGate) 
        return;

   
    AND2* restored = new AND2(GInfoBackup, AND2_FANOUT);

    createdGate = restored; 
    pManager->AddComponent(restored);
}
