#include "GenerateTruthTable.h"
#include "..\ApplicationManager.h"
#include "../Components/TruthTable.h"

GenerateTruthTable::GenerateTruthTable(ApplicationManager* pApp)
    : Action(pApp)
{
}

void GenerateTruthTable::ReadActionParameters()
{
   
}

void GenerateTruthTable::Execute()
{
    ReadActionParameters();

    TruthTable TT(pManager);
    TT.BuildTruthTable();
}

void GenerateTruthTable::Undo() {}
void GenerateTruthTable::Redo() {}
