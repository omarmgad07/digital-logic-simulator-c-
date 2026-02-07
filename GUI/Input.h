#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input
{
private:
	window* pWind;

public:
	Input(window*);
	void GetPointClicked(int&, int&);
	string GetString(Output*);
	ActionType GetUserAction() const;
	bool CheckEnterPressed() const;
	bool CheckMouseClick(int& x, int& y);  
	bool IsShiftPressed() const;
	bool CheckEscPressed();
	~Input();
};
