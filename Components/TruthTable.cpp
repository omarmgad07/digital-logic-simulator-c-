#include "TruthTable.h"
#include "../ApplicationManager.h"
#include "../Components/SWITCH.h"
#include "../Components/LED.h"

#include <cstring>
#include <string>

TruthTable::TruthTable(ApplicationManager* pApp)
    : pManager(pApp)
{
}

void TruthTable::BuildTruthTable()
{
    Output* pOut = pManager->GetOutput();
    int compCount = pManager->GetCompCount();

    if (compCount == 0)
    {
        pOut->PrintMsg("No components in the circuit.");
        return;
    }

    const int MAX_COMPS = 200;

    SWITCH* inputs[MAX_COMPS];
    int inputCount = 0;

    LED* outputs[MAX_COMPS];
    int outputCount = 0;

    int originalStates[MAX_COMPS];

    for (int i = 0; i < compCount; i++)
    {
        Component* c = pManager->GetComponent(i);

        if (SWITCH* sw = dynamic_cast<SWITCH*>(c))
        {
            inputs[inputCount++] = sw;
        }
        else if (LED* led = dynamic_cast<LED*>(c))
        {
            outputs[outputCount++] = led;
        }
    }

    if (inputCount == 0 || outputCount == 0)
    {
        pOut->PrintMsg("Need at least 1 SWITCH and 1 LED.");
        return;
    }

    for (int i = 0; i < inputCount; i++)
        originalStates[i] = inputs[i]->GetStatus();

    pOut->ClearTruthTableArea();

    int x = 200;
    int y = 160;

    char line[200];

    std::string header = "";

    for (int i = 0; i < inputCount; i++)
        header += "I" + std::to_string(i + 1) + "   ";

    header += "|   ";

    for (int i = 0; i < outputCount; i++)
        header += "O" + std::to_string(i + 1) + "   ";

    strcpy(line, header.c_str());
    pOut->DrawTruthLine(x, y, line);
    y += 25;

    int totalComb = 1 << inputCount;

    for (int comb = 0; comb < totalComb; comb++)
    {
        for (int i = 0; i < inputCount; i++)
        {
            bool bit = (comb >> i) & 1;
            inputs[i]->SetStatus(bit ? HIGH : LOW);
            inputs[i]->Operate();
        }

        for (int iter = 0; iter < 5; iter++)
            for (int k = 0; k < compCount; k++)
                pManager->GetComponent(k)->Operate();

        std::string row = "";

        for (int i = 0; i < inputCount; i++)
            row += std::to_string(inputs[i]->GetStatus()) + "    ";

        row += "|   ";

        for (int i = 0; i < outputCount; i++)
            row += std::to_string(outputs[i]->GetInputPinStatus(1)) + "    ";

        strcpy(line, row.c_str());
        pOut->DrawTruthLine(x, y, line);
        y += 25;
    }

    for (int i = 0; i < inputCount; i++)
    {
        inputs[i]->SetStatus(originalStates[i] == HIGH ? HIGH : LOW);
        inputs[i]->Operate();
    }

    for (int iter = 0; iter < 5; iter++)
        for (int k = 0; k < compCount; k++)
            pManager->GetComponent(k)->Operate();

   

    pOut->PrintMsg("Truth Table displayed on screen.");

}
