#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include "Actions/Action.h"
#include "Components/Component.h"
#include "Components/Connection.h"

// Removed <stack> include

class ApplicationManager
{
    friend class AddANDgate2;

    // Define constants for array sizes
    enum { MaxCompCount = 200, MaxHistory = 200 };

private:
    int CompCount;
    Component* CompList[MaxCompCount];

    Output* OutputInterface;
    Input* InputInterface;

    Component* Clipboard;

    // REPLACED STACKS WITH ARRAYS
    // Old: std::stack<Action*> UndoStack;
    // Old: std::stack<Action*> RedoStack;

    Action* UndoList[MaxHistory]; // Array to store Undo actions
    int UndoCount;                // Counter for current Undo index

    Action* RedoList[MaxHistory]; // Array to store Redo actions
    int RedoCount;                // Counter for current Redo index

public:

    ApplicationManager();
    ~ApplicationManager();

    // -- Component Management --
    void AddComponent(Component* pComp);
    Component* GetComponent(int index) const;
    Component* GetComponentAt(int x, int y);
    int GetCompCount() const;
    void DeleteComponent(Component* pComp);
    void BreakConnections(Component* comp);

    // -- Clipboard --
    void SetClipboard(Component* c);
    Component* GetClipboard() const;

    // -- Interface Access --
    Output* GetOutput();
    Input* GetInput();

    // -- Action Execution --
    ActionType GetUserAction();
    void ExecuteAction(ActionType ActType);

    // -- Undo/Redo --
    void UndoAction();
    void RedoAction();

    void UpdateInterface();

    Component* GetSelectedComponent() const;

    void GetConnectionsOfComponent(Component* comp, Connection* conns[], int& count);
};

#endif