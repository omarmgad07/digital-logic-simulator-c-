#include "UndoAction.h"
#include "../ApplicationManager.h"

void UndoAction::Execute()
{
    pManager->UndoAction();
}
