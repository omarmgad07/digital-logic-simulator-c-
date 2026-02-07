#include "ApplicationManager.h"

// Actions
#include "Actions/AddANDgate2.h"
#include "Actions/AddORgate2.h"
#include "Actions/AddNANDgate2.h"
#include "Actions/AddXORgate2.h"
#include "Actions/AddConnection.h"
#include "Actions/AddNORgate2.h"
#include "Actions/AddXNORgate2.h"
#include "Actions/AddAND32gate2.h"
#include "Actions/AddNOTgate2.h"
#include "Actions/AddBUFFgate2.h"
#include "Actions/AddLED.h"
#include "Actions/AddNOR32gate2.h"
#include "Actions/AddXOR32gate2.h"
#include "Actions/AddSWITCH.h"
#include "Actions/SimulationMode.h"
#include "Actions/Validate.h"
#include "Actions/ProbeCircuit.h"
#include "Actions/CopyAction.h"
#include "Actions/PasteAction.h"
#include "Actions/GenerateTruthTable.h"
#include "Actions/Delete.h"
#include "Actions/saveAction.h"
#include "Actions/LoadAction.h"
#include "Actions/Move.h"
#include "Actions/UndoAction.h"
#include "Actions/RedoAction.h"
#include "Actions/AddLabel.h"
#include "Actions/Select.h"
#include "Actions/ActionCut.h"

#include "Components/Connection.h"

ApplicationManager::ApplicationManager()
{
    CompCount = 0;
    Clipboard = nullptr;

    // Initialize Component List
    for (int i = 0; i < MaxCompCount; i++)
        CompList[i] = nullptr;

    // Initialize Undo/Redo Arrays
    UndoCount = 0;
    RedoCount = 0;
    for (int i = 0; i < MaxHistory; i++) {
        UndoList[i] = nullptr;
        RedoList[i] = nullptr;
    }

    OutputInterface = new Output();
    InputInterface = OutputInterface->CreateInput();
}

int ApplicationManager::GetCompCount() const
{
    return CompCount;
}

Component* ApplicationManager::GetComponent(int index) const
{
    if (index >= 0 && index < CompCount)
        return CompList[index];
    return nullptr;
}

void ApplicationManager::AddComponent(Component* pComp)
{
    if (CompCount < MaxCompCount && pComp)
        CompList[CompCount++] = pComp;
}

ActionType ApplicationManager::GetUserAction()
{
    return InputInterface->GetUserAction();
}

void ApplicationManager::ExecuteAction(ActionType ActType)
{
    Action* pAct = nullptr;

    switch (ActType)
    {
    case ADD_AND_GATE_2:     pAct = new AddANDgate2(this); break;
    case ADD_OR_GATE_2:      pAct = new AddORgate2(this); break;
    case ADD_NAND_GATE_2:    pAct = new AddNANDgate2(this); break;
    case ADD_XOR_GATE_2:     pAct = new AddXORgate2(this); break;
    case ADD_NOR_GATE_2:     pAct = new AddNORgate2(this); break;
    case ADD_XNOR_GATE_2:    pAct = new AddXNORgate2(this); break;
    case ADD_3AND_GATE_2:    pAct = new AddAND32gate2(this); break;
    case ADD_3NOR_GATE_2:    pAct = new AddNOR32gate2(this); break;
    case ADD_3XOR_GATE_2:    pAct = new AddXOR32gate2(this); break;
    case ADD_NOT_GATE_2:     pAct = new AddNOTgate2(this); break;
    case ADD_BUFF_GATE_2:    pAct = new AddBUFFgate2(this); break;
    case ADD_CONNECTION:     pAct = new AddConnection(this); break;
    case ADD_LED:            pAct = new AddLED(this); break;
    case ADD_Switch:         pAct = new AddSWITCH(this); break;
    case COPY:               pAct = new CopyAction(this); break;
    case PASTE:              pAct = new PasteAction(this); break;
    case DEL:                pAct = new Delete(this); break;
    case MOVE:               pAct = new Move(this); break;
    case SAVE:               pAct = new SaveAction(this); break;
    case LOAD:               pAct = new LoadAction(this); break;
    case CUT:                pAct = new ActionCut(this); break;
    case SIM_MODE:           pAct = new SimulationMode(this); break;
    case VALIDATE_CIRCUIT:   pAct = new Validate(this); break;
    case PROBE_CIRCUIT:      pAct = new ProbeCircuit(this); break;
    case Create_TruthTable:  pAct = new GenerateTruthTable(this); break;
    case SELECT_BUTTON:      pAct = new Select(this); break;

    case UNDO:
        pAct = new ::UndoAction(this);
        break;

    case REDO:
        pAct = new ::RedoAction(this);
        break;

    case EDIT_Label:         pAct = new AddLabel(this); break;

    case EXIT:
        return;
    }

    if (pAct)
    {
        pAct->Execute();

        // Handle Undo/Redo Stacks
        if (ActType != UNDO && ActType != REDO)
        {
            // Push to Undo List manually
            if (UndoCount < MaxHistory) {
                UndoList[UndoCount++] = pAct;
            }
            else {
                
            }

            // Clear Redo List manually
            // When a new action is done, the redo history is invalid
            for (int i = 0; i < RedoCount; i++) {
                if (RedoList[i]) {
                    delete RedoList[i];
                    RedoList[i] = nullptr;
                }
            }
            RedoCount = 0;
        }
        else
        {
            // Delete the temporary Undo/Redo action object itself
            delete pAct;
        }
    }
}

void ApplicationManager::BreakConnections(Component* comp)
{
    for (int i = 0; i < CompCount; i++)
    {
        Connection* conn = dynamic_cast<Connection*>(CompList[i]);
        if (!conn) continue;

        bool broken = false;

        if (conn->getSourcePin() && conn->getSourcePin()->getComponent() == comp)
        {
            conn->setSourcePin(nullptr);
            broken = true;
        }

        if (conn->getDestPin() && conn->getDestPin()->getComponent() == comp)
        {
            conn->setDestPin(nullptr);
            broken = true;
        }

        if (broken)
        {
            if (!conn->getSourcePin() || !conn->getDestPin())
            {
                DeleteComponent(conn);
                i--;
            }
        }
    }
}

void ApplicationManager::UpdateInterface()
{
    OutputInterface->ClearDrawingArea();

    for (int i = 0; i < CompCount; i++)
        if (dynamic_cast<Connection*>(CompList[i]))
            CompList[i]->Operate();

    for (int i = 0; i < CompCount; i++)
        if (!dynamic_cast<Connection*>(CompList[i]))
            CompList[i]->Operate();

    for (int i = 0; i < CompCount; i++)
        CompList[i]->Draw(OutputInterface);
}

Output* ApplicationManager::GetOutput() { return OutputInterface; }
Input* ApplicationManager::GetInput() { return InputInterface; }

Component* ApplicationManager::GetComponentAt(int x, int y)
{
    for (int i = CompCount - 1; i >= 0; i--)
        if (CompList[i] && CompList[i]->HitTest(x, y))
            return CompList[i];
    return nullptr;
}

void ApplicationManager::DeleteComponent(Component* comp)
{
    if (!comp) return;

    for (int i = 0; i < CompCount; i++)
    {
        if (CompList[i] == comp)
        {
            delete CompList[i];

            for (int j = i; j < CompCount - 1; j++)
                CompList[j] = CompList[j + 1];

            CompList[CompCount - 1] = nullptr;
            CompCount--;
            return;
        }
    }
}

void ApplicationManager::SetClipboard(Component* c) { Clipboard = c; }
Component* ApplicationManager::GetClipboard() const { return Clipboard; }



void ApplicationManager::UndoAction()
{
    if (UndoCount == 0) return;

    UndoCount--;
    Action* last = UndoList[UndoCount];

    // Perform Undo
    last->Undo();

    // Push to Redo List
    if (RedoCount < MaxHistory) {
        RedoList[RedoCount++] = last;
    }

    UpdateInterface();
}

void ApplicationManager::RedoAction()
{
    // Check if empty
    if (RedoCount == 0) return;

    // Pop from Redo List
    RedoCount--;
    Action* last = RedoList[RedoCount];

    // Perform Redo
    last->Redo();

    // Push to Undo List
    if (UndoCount < MaxHistory) {
        UndoList[UndoCount++] = last;
    }

    UpdateInterface();
}

Component* ApplicationManager::GetSelectedComponent() const
{
    for (int i = 0; i < CompCount; i++)
        if (CompList[i] && CompList[i]->IsSelected())
            return CompList[i];

    return nullptr;
}

void ApplicationManager::GetConnectionsOfComponent(Component* comp, Connection* conns[], int& count)
{
    count = 0;

    for (int i = 0; i < CompCount; i++)
    {
        Component* c = CompList[i];

        Connection* conn = dynamic_cast<Connection*>(c);
        if (conn)
        {
            if ((conn->getSourcePin() && conn->getSourcePin()->getComponent() == comp) ||
                (conn->getDestPin() && conn->getDestPin()->getComponent() == comp))
            {
                if (count < 100)
                    conns[count++] = conn;
            }
        }
    }
}

ApplicationManager::~ApplicationManager()
{
    for (int i = 0; i < CompCount; i++)
        delete CompList[i];

    delete OutputInterface;
    delete InputInterface;

    // CLEAN UP MANUAL STACKS
    for (int i = 0; i < UndoCount; i++)
        delete UndoList[i];

    for (int i = 0; i < RedoCount; i++)
        delete RedoList[i];
}