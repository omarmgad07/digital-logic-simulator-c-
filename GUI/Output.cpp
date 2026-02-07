#include "Output.h"

Output::Output()
{


	UI.AppMode = DESIGN;


	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();
	CreateStatusBar();
	CreateBottomToolBar();

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width,
		UI.height - UI.StatusBarHeight - UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2] = "images\\Menu\\OR.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Nand.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\NOR.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\XOR.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\XNOR.jpg";
	MenuItemImages[ITM_AND32] = "images\\Menu\\3AND.jpg";
	MenuItemImages[ITM_NOR32] = "images\\Menu\\3NOR.jpg";
	MenuItemImages[ITM_XOR32] = "images\\Menu\\3XOR.jpg";
	MenuItemImages[ITM_BUFF2] = "images\\Menu\\BUFF.jpg";
	MenuItemImages[ITM_NOT2] = "images\\Menu\\NOT.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\SWITCH.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\LED.jpg";
	MenuItemImages[ITM_Connection] = "images\\Menu\\Connection.jpg";
	MenuItemImages[ITM_sim] = "images\\Menu\\SIM.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";


	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}


void Output::ClearToolBar() const
{
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;

	string MenuItemImages[ITM_SIM_CNT];

	
	MenuItemImages[ITM_TRUTH] = "images\\Menu\\truth.jpg";
	MenuItemImages[ITM_VALIDATE] = "images\\Menu\\validate.jpg";
	MenuItemImages[ITM_PROBE] = "images\\Menu\\probe.jpg";
	MenuItemImages[ITM_BACK] = "images\\Menu\\left.jpg";
	MenuItemImages[ITM_EXIT2] = "images\\Menu\\Menu_Exit.jpg";

	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0,
			UI.ToolItemWidth, UI.ToolBarHeight);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::CreateBottomToolBar() const
{
	// prepare list of images
	string BottomItemImages[ITM_BTM_CNT];

	BottomItemImages[ITM_UNDO_B] = "images\\Menu\\undo.jpg";
	BottomItemImages[ITM_REDO_B] = "images\\Menu\\redo.jpg";
	BottomItemImages[ITM_SAVE_B] = "images\\Menu\\save2.jpg";
	BottomItemImages[ITM_EDIT_B] = "images\\Menu\\edit.jpg";
	BottomItemImages[ITM_delete_B] = "images\\Menu\\delete.jpg";
	BottomItemImages[ITM_move_B] = "images\\Menu\\move.jpg";
	BottomItemImages[ITM_import_B] = "images\\Menu\\import.jpg";
	BottomItemImages[ITM_copy_B] = "images\\Menu\\copy.jpg";
	BottomItemImages[ITM_paste_B] = "images\\Menu\\Paste.jpg";
	BottomItemImages[ITM_select_B] = "images\\Menu\\select.jpg";

	BottomItemImages[ITM_cut_B] = "images\\Menu\\cut.jpg";

	int y = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;


	for (int i = 0; i < ITM_BTM_CNT; i++)
		pWind->DrawImage(BottomItemImages[i], i * UI.ToolItemWidth, y,
			UI.ToolItemWidth, UI.ToolBarHeight);


	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, y, UI.width, y);
}
//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\OR2.jpg";
	else
		GateImage = "Images\\Gates\\OR.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Nand2.jpg";
	else
		GateImage = "Images\\Gates\\Nand.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NAND2_Width, UI.NAND2_Height);
}
void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\NOR2.jpg";
	else
		GateImage = "Images\\Gates\\NOR.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOR2_Width, UI.NOR2_Height);
}


void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\XOR2.jpg";
	else
		GateImage = "Images\\Gates\\XOR.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR2_Width, UI.XOR2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\XNOR2.jpg";
	else
		GateImage = "Images\\Gates\\XNOR.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XNOR2_Width, UI.XNOR2_Height);
}

void Output::DrawAND32(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\3AND2.jpg";
	else
		GateImage = "Images\\Gates\\3AND.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND32_Width, UI.AND32_Height);
}

void Output::DrawNOR32(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\3NOR2.jpg";
	else
		GateImage = "Images\\Gates\\3NOR.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOR32_Width, UI.NOR32_Height);
}
void Output::DrawXOR32(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\3XOR2.jpg";
	else
		GateImage = "Images\\Gates\\3XOR.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR32_Width, UI.XOR32_Height);
}
void Output::DrawBUFF2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\BUFF2.jpg";
	else
		GateImage = "Images\\Gates\\BUFF.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.BUFF2_Width, UI.BUFF2_Height);

}
void Output::DrawNOT2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\NOT2.jpg";
	else
		GateImage = "Images\\Gates\\NOT.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOT2_Width, UI.NOT2_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool isOn) const
{
	string GateImage;

	if (isOn)
		GateImage = "Images\\Gates\\SWITCH2.jpg";  
	else
		GateImage = "Images\\Gates\\SWITCH.jpg";    

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,
		UI.SWITCH_Width, UI.SWITCH_Height);

}
void Output::DrawLED(GraphicsInfo r_GfxInfo, bool isOn) const
{
	string GateImage;

	if (isOn)
		GateImage = "Images\\Gates\\LEDH.jpg";   // ON (RED)
	else
		GateImage = "Images\\Gates\\LED.jpg";    // OFF

	pWind->DrawImage(GateImage,
		r_GfxInfo.x1, r_GfxInfo.y1,
		UI.LED_Width, UI.LED_Height);
}

//TODO: Add similar functions to draw all components


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{


	color lineColor = selected ? RED : BLACK;
	int   penWidth = selected ? 4 : 2;

	pWind->SetPen(lineColor, penWidth);

	int x1 = r_GfxInfo.x1;
	int y1 = r_GfxInfo.y1;
	int x2 = r_GfxInfo.x2;
	int y2 = r_GfxInfo.y2;


	if (y1 == y2)
	{
		pWind->DrawLine(x1, y1, x2, y2);
		return;
	}


	int midX = (x1 + x2) / 2;

	pWind->DrawLine(x1, y1, midX, y1);
	pWind->DrawLine(midX, y1, midX, y2);
	pWind->DrawLine(midX, y2, x2, y2);
}
void Output::DrawComponentLabel(const GraphicsInfo& r_GfxInfo, const string& label) const
{
	if (label.empty()) return;

	// Choose a font size that's readable but small
	pWind->SetFont(18, PLAIN, BY_NAME, "Arial");
	pWind->SetPen(BLACK);

	
	int gateWidth = UI.AND2_Width;   // default
	int gateHeight = UI.AND2_Height; // default

	
	int x1 = r_GfxInfo.x1;
	int y1 = r_GfxInfo.y1;

	
	int approxCharWidth = 7;
	int textWidth = static_cast<int>(label.length()) * approxCharWidth;

	
	int labelX = x1 + gateWidth / 2 - textWidth / 2;
	int labelY = y1 + gateHeight + 6; 
	
	if (labelX < 2) labelX = 2;

	pWind->DrawString(labelX, labelY, label);
}

void Output::ClearBottomToolBar() const
{
	// Calculate the Y coordinate where the bottom toolbar starts
	// (Must match the math used in CreateBottomToolBar)
	int yStart = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;

	// Set Pen and Brush to Background Color (White)
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);

	// Draw a rectangle covering the Bottom Toolbar area
	pWind->DrawRectangle(0, yStart, UI.width, yStart + UI.ToolBarHeight);
}




//TODO: Add code to draw connection

void Output::ClearTruthTableArea()
{
	int left = 150;
	int top = 120;
	int right = UI.width - 150;
	int bottom = UI.height - 200;

	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(RGB(240, 240, 240)); // loooono ahamr
	pWind->DrawRectangle(left, top, right, bottom);

	pWind->SetFont(22, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLUE);
	pWind->DrawString(left + 20, top + 10, "Truth Table");
}


void Output::DrawTruthLine(int x, int y, const char* text)
{
	pWind->SetPen(BLACK);
	pWind->SetFont(18, PLAIN, BY_NAME, "Arial");
	pWind->DrawString(x, y, text);
}


Output::~Output()
{
	delete pWind;
}