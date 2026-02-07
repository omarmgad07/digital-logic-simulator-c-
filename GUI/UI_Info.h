#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;

	static const int	width = 1300, height = 750,
		wx = 15, wy = 15,
		StatusBarHeight = 50,
		ToolBarHeight = 80,
		ToolItemWidth = 80;

	color DrawColor;
	color SelectColor;
	color ConnColor;
	color MsgColor;
	color BkGrndColor;



	static const int AND2_Width = 100, AND2_Height = 100;
	static const int OR2_Width = 100, OR2_Height = 100;
	static const int NAND2_Width = 100, NAND2_Height = 100;
	static const int NOR2_Width = 100, NOR2_Height = 100;
	static const int XOR2_Width = 100, XOR2_Height = 100;
	static const int XNOR2_Width = 100, XNOR2_Height = 100;
	static const int AND32_Width = 80, AND32_Height = 80;
	static const int NOR32_Width = 80, NOR32_Height = 80;
	static const int XOR32_Width = 80, XOR32_Height = 80;
	static const int BUFF2_Width = 100, BUFF2_Height = 100;
	static const int NOT2_Width = 100, NOT2_Height = 100;
	static const int SWITCH_Width = 80, SWITCH_Height = 80;
	static const int LED_Width = 80, LED_Height = 80;
}UI;	//create a single global object UI

#endif