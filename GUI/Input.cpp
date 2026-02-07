#include "Input.h"
#include "Output.h"
#include <iostream>

Input::Input(window* pW)
{
	pWind = pW;
}

void Input::GetPointClicked(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);
}
bool Input::CheckEnterPressed() const
{
    char key;
    if (pWind->GetKeyPress(key))   
    {
        if (key == 13)            
            return true;
    }
    return false;
}


string Input::GetString(Output* pOut)
{
	string characters = "";
	char key;

	while (true)
	{
		pWind->WaitKeyPress(key);

		if (key == 13)
		{
			break;
		}
		else if (key == 27)
		{
			characters = "";
			break;
		}
		else if (key == 8)
		{
			if (!characters.empty())
				characters.erase(characters.size() - 1);
		}
		else
		{
			characters += key;
		}


		pOut->PrintMsg(characters);
	}

	return characters;
}


ActionType Input::GetUserAction() const
{
    int x, y;
    pWind->WaitMouseClick(x, y);

    int topBarBottom = UI.ToolBarHeight;               
    int bottomBarTop = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;
    int drawingTop = topBarBottom;
    int drawingBottom = bottomBarTop;

    if (UI.AppMode == DESIGN)
    {
        if (y >= 0 && y < topBarBottom)
        {
            int ClickedItemOrder = x / UI.ToolItemWidth;
            switch (ClickedItemOrder)
            {
            case ITM_AND2: return ADD_AND_GATE_2;
            case ITM_OR2: return ADD_OR_GATE_2;
            case ITM_NAND2: return ADD_NAND_GATE_2;
            case ITM_NOR2: return ADD_NOR_GATE_2;
            case ITM_XOR2: return ADD_XOR_GATE_2;
            case ITM_XNOR2: return ADD_XNOR_GATE_2;
            case ITM_AND32: return ADD_3AND_GATE_2;
            case ITM_NOR32: return ADD_3NOR_GATE_2;
            case ITM_XOR32: return ADD_3XOR_GATE_2;
            case ITM_BUFF2: return ADD_BUFF_GATE_2;
            case ITM_NOT2: return ADD_NOT_GATE_2;
            case ITM_SWITCH: return ADD_Switch;
            case ITM_LED: return ADD_LED;
            case ITM_Connection: return ADD_CONNECTION;
            case ITM_sim: return SIM_MODE;
            case ITM_EXIT: return EXIT;
            default: return DSN_TOOL;
            }
        }

        if (y >= drawingTop && y < drawingBottom)
            return SELECT;

        if (y >= bottomBarTop && y < UI.height - UI.StatusBarHeight)
        {
            int ClickedItemOrder = x / UI.ToolItemWidth;
            switch (ClickedItemOrder)
            {
            case ITM_UNDO_B: return UNDO;
            case ITM_REDO_B: return REDO;
            case ITM_SAVE_B: return SAVE;
            case ITM_EDIT_B: return EDIT_Label;
            case ITM_delete_B: return DEL;
            case ITM_move_B: return MOVE;
            case ITM_import_B: return LOAD;
            case ITM_copy_B: return COPY;
            case ITM_paste_B: return PASTE;
            case ITM_cut_B: return CUT;
            case ITM_select_B: return SELECT_BUTTON;
            default: return DSN_TOOL;
            }
        }

        return STATUS_BAR;
    }

    else // SIMULATION MODE
    {
        if (y >= 0 && y < topBarBottom)
        {
            int ClickedItemOrder = x / UI.ToolItemWidth;

            switch (ClickedItemOrder)
            {
            case ITM_TRUTH: return Create_TruthTable;
            case ITM_VALIDATE: return VALIDATE_CIRCUIT;
            case ITM_PROBE: return PROBE_CIRCUIT;
            case ITM_BACK: return DSN_MODE;
            case ITM_EXIT2: return EXIT;
            default: return DSN_TOOL;
            }
        }

        if (y >= drawingTop && y < drawingBottom)
            return SELECT;

        if (y >= bottomBarTop && y < UI.height - UI.StatusBarHeight)
        {
            int ClickedItemOrder = x / UI.ToolItemWidth;
            switch (ClickedItemOrder)
            {
            case ITM_UNDO_B: return UNDO;
            case ITM_REDO_B: return REDO;
            case ITM_SAVE_B: return SAVE;
            case ITM_EDIT_B: return EDIT_Label;
            default: return DSN_TOOL;
            }
        }

        return STATUS_BAR;
    }
}
bool Input::CheckMouseClick(int& x, int& y)
{
    if (pWind->GetMouseClick(x, y))
        return true;    

    return false;       
}

bool Input::IsShiftPressed() const
{
    return (GetKeyState(VK_SHIFT) & 0x8000) != 0;
}


Input::~Input()
{
}