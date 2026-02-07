#pragma once
#include "..\Defs.h"
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar
	void CreateBottomToolBar() const;

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area
	void ClearToolBar() const;
	void ClearBottomToolBar() const;


	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window


	// Draws 2-input AND gate
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawAND32(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR32(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR32(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawBUFF2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOT2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawLED(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected = false) const;

	void DrawComponentLabel(const GraphicsInfo& r_GfxInfo, const std::string& label) const;


	void ClearTruthTableArea();
	void DrawTruthLine(int x, int y, const char* text);



	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc


	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false) const;

	void PrintMsg(string msg) const;


	~Output();
};