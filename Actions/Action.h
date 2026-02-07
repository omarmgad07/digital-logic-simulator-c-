#ifndef _ACTION_H
#define _ACTION_H

class ApplicationManager; 


class Action
{
protected:
	ApplicationManager* pManager;	
public:
	Action(ApplicationManager* pApp) { pManager = pApp; }	

	virtual void ReadActionParameters() = 0;

	virtual void Execute() = 0;

	virtual void Undo() {}
	virtual void Redo() {}

};

#endif