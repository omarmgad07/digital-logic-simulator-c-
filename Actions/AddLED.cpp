#include "AddLED.h"
#include "..\ApplicationManager.h"

AddLED::AddLED(ApplicationManager* pApp) : Action(pApp)
{
    createdGate = nullptr;
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("LED: Click to add the LED");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void AddLED::Execute()
{
    ReadActionParameters();

    int Len = UI.LED_Width;
    int Wdth = UI.LED_Height;

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

    createdGate = new LED(GInfoBackup);

    pManager->AddComponent(createdGate);
}

void AddLED::Undo()
{
    if (createdGate)
        pManager->DeleteComponent(createdGate);
}

void AddLED::Redo()
{
    if (!createdGate) return;

    LED* restored = new LED(GInfoBackup);

    createdGate = restored;
    pManager->AddComponent(restored);
}
