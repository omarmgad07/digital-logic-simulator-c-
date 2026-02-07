#include "Action.h"

class AddConnection : public Action
{
private:
    int x1, y1;   
    int x2, y2;   

public:
    AddConnection(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo() {}
    virtual void Redo() {}
};
